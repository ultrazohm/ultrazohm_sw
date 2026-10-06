#include "core/capture_log.hpp"

#include <algorithm>
#include <charconv>
#include <cstdio>
#include <ctime>
#include <nlohmann/json.hpp>
#include <set>
#include <stdexcept>

namespace uz {
namespace {

std::string timestamp_name() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    std::strftime(buf, sizeof(buf), "Scope_%Y-%m-%d_%H-%M-%S", &tm);
    return buf;
}

// Fast float -> chars append (std::to_chars never allocates or locales).
void append_number(std::string& out, double v) {
    char buf[32];
    auto res = std::to_chars(buf, buf + sizeof(buf), v, std::chars_format::general, 9);
    out.append(buf, res.ptr);
}

}  // namespace

std::vector<std::string> make_column_names(const std::vector<std::string>& observables) {
    std::vector<std::string> names;
    std::set<std::string> seen;
    for (size_t slot = 0; slot < observables.size(); ++slot) {
        std::string name = observables[slot];
        if (name.rfind("JSO_", 0) == 0) name = name.substr(4);
        if (name.empty()) name = "ch" + std::to_string(slot + 1);
        if (seen.count(name)) name += "_ch" + std::to_string(slot + 1);
        seen.insert(name);
        names.push_back(std::move(name));
    }
    return names;
}

CaptureLogger::CaptureLogger(const std::filesystem::path& directory, std::string fmt,
                             std::vector<std::string> column_names, double timestep_s,
                             int every_n, size_t queue_chunks)
    : fmt_(std::move(fmt)),
      columns_(std::move(column_names)),
      timestep_s_(timestep_s),
      every_n_(every_n),
      queue_chunks_(queue_chunks) {
    if (fmt_ != "csv" && fmt_ != "bin")
        throw std::invalid_argument("format must be csv or bin (parquet: use uz_scope)");
    if (every_n_ < 1) throw std::invalid_argument("every_n must be >= 1");
    if (timestep_s_ <= 0) throw std::invalid_argument("timestep_s must be > 0");
    std::filesystem::create_directories(directory);
    std::string base = timestamp_name();
    path_ = directory / (base + "." + fmt_);
    for (int suffix = 1; std::filesystem::exists(path_); ++suffix)
        path_ = directory / (base + "_" + std::to_string(suffix) + "." + fmt_);
    file_ = std::fopen(path_.string().c_str(), "wb");
    if (!file_) throw std::runtime_error("cannot open " + path_.string());
    if (fmt_ == "csv") {
        std::string header = "time";
        for (const auto& c : columns_) header += "," + c;
        header += "\n";
        std::fwrite(header.data(), 1, header.size(), file_);
    }
    thread_ = std::thread([this] { run(); });
}

CaptureLogger::~CaptureLogger() { close(); }

void CaptureLogger::submit(const float* block, int channels, int64_t m,
                           int64_t start_index) {
    Chunk chunk;
    chunk.channels = channels;
    // Apply the every-N stride with a global phase so it survives block cuts.
    for (int64_t i = 0; i < m; ++i) {
        int64_t abs_index = start_index + i;
        if (abs_index % every_n_ != 0) continue;
        chunk.indices.push_back(abs_index);
    }
    if (chunk.indices.empty()) return;
    chunk.samples.resize(size_t(channels) * chunk.indices.size());
    for (int c = 0; c < channels; ++c) {
        float* dst = chunk.samples.data() + size_t(c) * chunk.indices.size();
        const float* src = block + size_t(c) * m;
        for (size_t k = 0; k < chunk.indices.size(); ++k)
            dst[k] = src[chunk.indices[k] - start_index];
    }
    std::lock_guard lock(queue_mutex_);
    if (closing_) return;
    if (queue_.size() >= queue_chunks_) {
        // A slow disk must never stall ingest: drop and count.
        std::lock_guard slock(stats_mutex_);
        ++stats_.chunks_dropped;
        stats_.samples_dropped += int64_t(chunk.indices.size());
        return;
    }
    queue_.push_back(std::move(chunk));
    queue_cv_.notify_one();
}

void CaptureLogger::run() {
    for (;;) {
        Chunk chunk;
        {
            std::unique_lock lock(queue_mutex_);
            queue_cv_.wait(lock, [this] { return !queue_.empty() || closing_; });
            if (queue_.empty()) return;  // closing and drained
            chunk = std::move(queue_.front());
            queue_.pop_front();
        }
        if (error_.empty()) write_chunk(chunk);
    }
}

void CaptureLogger::write_chunk(const Chunk& chunk) {
    const size_t m = chunk.indices.size();
    if (first_index_ < 0 && m > 0) first_index_ = chunk.indices[0];
    if (fmt_ == "bin") {
        // Sample-major float32, matching uz_scope's spill layout.
        std::vector<float> row(size_t(chunk.channels));
        std::vector<float> out;
        out.reserve(m * size_t(chunk.channels));
        for (size_t k = 0; k < m; ++k)
            for (int c = 0; c < chunk.channels; ++c)
                out.push_back(chunk.samples[size_t(c) * m + k]);
        size_t written = std::fwrite(out.data(), 4, out.size(), file_);
        if (written != out.size()) error_ = "short write to " + path_.string();
        std::lock_guard lock(stats_mutex_);
        stats_.rows_written += int64_t(m);
        stats_.bytes_written += int64_t(written) * 4;
        return;
    }
    std::string text;
    text.reserve(m * (size_t(chunk.channels) + 1) * 14);
    for (size_t k = 0; k < m; ++k) {
        append_number(text, double(chunk.indices[k]) * timestep_s_);
        for (int c = 0; c < chunk.channels; ++c) {
            text += ',';
            append_number(text, double(chunk.samples[size_t(c) * m + k]));
        }
        text += '\n';
    }
    if (std::fwrite(text.data(), 1, text.size(), file_) != text.size())
        error_ = "short write to " + path_.string();
    std::lock_guard lock(stats_mutex_);
    stats_.rows_written += int64_t(m);
    stats_.bytes_written += int64_t(text.size());
}

std::filesystem::path CaptureLogger::close() {
    {
        std::lock_guard lock(queue_mutex_);
        if (closed_) return path_;
        closing_ = true;
        closed_ = true;
        queue_cv_.notify_one();
    }
    if (thread_.joinable()) thread_.join();
    if (file_) {
        std::fclose(file_);
        file_ = nullptr;
    }
    if (fmt_ == "bin") write_sidecar();
    return path_;
}

void CaptureLogger::write_sidecar() {
    nlohmann::json sidecar;
    LoggerStats s = stats();
    sidecar["format"] = "uz_scope-bin-v1";
    sidecar["columns"] = columns_;
    sidecar["dtype"] = "<f4";
    sidecar["timestep_s"] = timestep_s_;
    sidecar["every_n"] = every_n_;
    sidecar["first_index"] = first_index_ < 0 ? 0 : first_index_;
    sidecar["rows"] = s.rows_written;
    sidecar["chunks_dropped"] = s.chunks_dropped;
    sidecar["samples_dropped"] = s.samples_dropped;
    std::filesystem::path p = path_;
    p.replace_extension(".json");
    if (std::FILE* f = std::fopen(p.string().c_str(), "wb")) {
        std::string text = sidecar.dump(2) + "\n";
        std::fwrite(text.data(), 1, text.size(), f);
        std::fclose(f);
    }
}

std::filesystem::path write_capture(const std::filesystem::path& path,
                                    const std::vector<std::string>& columns,
                                    const float* data, int channels, int64_t m,
                                    int64_t start_index, double timestep_s) {
    std::FILE* f = std::fopen(path.string().c_str(), "wb");
    if (!f) throw std::runtime_error("cannot open " + path.string());
    std::string text = "time";
    for (const auto& c : columns) text += "," + c;
    text += "\n";
    for (int64_t k = 0; k < m; ++k) {
        append_number(text, double(start_index + k) * timestep_s);
        for (int c = 0; c < channels; ++c) {
            text += ',';
            append_number(text, double(data[size_t(c) * m + k]));
        }
        text += '\n';
    }
    std::fwrite(text.data(), 1, text.size(), f);
    std::fclose(f);
    return path;
}

}  // namespace uz
