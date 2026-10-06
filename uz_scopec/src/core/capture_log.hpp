// Streaming capture logger: CSV or raw-binary spill (GUI-free).
//
// The reader thread calls submit() with each block; encoding and disk I/O
// happen on the logger's own thread behind a bounded queue, so a slow disk
// can never stall ingest — the logger drops whole chunks instead and reports
// it (stats().chunks_dropped).
//
// Formats:
//   csv — float64 "time" column + float32 channel columns, opens in
//         uz_dataviewer / Excel / MATLAB.
//   bin — raw sample-major float32 + a JSON sidecar identical to uz_scope's
//         ("uz_scope-bin-v1"), so the Python tools convert it to Parquet.
//
// Time is reconstructed from absolute int64 sample indices times the
// configured timestep — never trusted from the wire.
#pragma once

#include <condition_variable>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace uz {

struct LoggerStats {
    int64_t rows_written = 0;
    int64_t chunks_dropped = 0;
    int64_t samples_dropped = 0;
    int64_t bytes_written = 0;
};

// Column names for the logged channels: strip the JSO_ prefix, dedup with a
// _chN suffix so columns stay unique.
std::vector<std::string> make_column_names(const std::vector<std::string>& observables);

class CaptureLogger {
public:
    CaptureLogger(const std::filesystem::path& directory, std::string fmt,
                  std::vector<std::string> column_names, double timestep_s,
                  int every_n = 1, size_t queue_chunks = 256);
    ~CaptureLogger();

    // Reader thread: channel-major block (rows = channels, m columns).
    void submit(const float* block, int channels, int64_t m, int64_t start_index);

    // Flush and close; returns the final path.  Idempotent.
    std::filesystem::path close();

    LoggerStats stats() const {
        std::lock_guard lock(stats_mutex_);
        return stats_;
    }
    const std::filesystem::path& path() const { return path_; }
    const std::string& error() const { return error_; }

private:
    struct Chunk {
        std::vector<float> samples;  // channels * m, row-major
        std::vector<int64_t> indices;
        int channels = 0;
    };

    void run();
    void write_chunk(const Chunk& chunk);
    void write_sidecar();

    std::string fmt_;
    std::vector<std::string> columns_;
    double timestep_s_;
    int every_n_;
    size_t queue_chunks_;
    std::filesystem::path path_;
    int64_t first_index_ = -1;
    std::FILE* file_ = nullptr;
    std::string error_;
    LoggerStats stats_;
    mutable std::mutex stats_mutex_;

    std::deque<Chunk> queue_;
    bool closing_ = false;
    bool closed_ = false;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::thread thread_;
};

// One-shot export of a trigger capture (format by extension: .csv or .bin).
std::filesystem::path write_capture(const std::filesystem::path& path,
                                    const std::vector<std::string>& columns,
                                    const float* data, int channels, int64_t m,
                                    int64_t start_index, double timestep_s);

}  // namespace uz
