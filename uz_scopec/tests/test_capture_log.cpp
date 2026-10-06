#include <doctest/doctest.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>
#include <vector>

#include "core/capture_log.hpp"

using namespace uz;
namespace fs = std::filesystem;

namespace {

fs::path temp_dir(const char* name) {
    fs::path dir = fs::temp_directory_path() / "uz_scopec_tests" / name;
    fs::remove_all(dir);
    fs::create_directories(dir);
    return dir;
}

std::vector<float> block(int channels, int64_t m) {
    std::vector<float> b(size_t(channels) * size_t(m));
    for (int c = 0; c < channels; ++c)
        for (int64_t i = 0; i < m; ++i)
            b[size_t(c) * m + i] = float(c * 1000 + i);
    return b;
}

}  // namespace

TEST_CASE("column names strip JSO_ and dedup") {
    auto names = make_column_names({"JSO_ia", "JSO_ib", "JSO_ia", ""});
    CHECK(names == std::vector<std::string>{"ia", "ib", "ia_ch3", "ch4"});
}

TEST_CASE("csv roundtrip") {
    fs::path dir = temp_dir("csv");
    CaptureLogger logger(dir, "csv", {"a", "b"}, 1e-4);
    auto b = block(2, 10);
    logger.submit(b.data(), 2, 10, 100);
    fs::path path = logger.close();
    CHECK(path.extension() == ".csv");
    std::ifstream in(path);
    std::string line;
    REQUIRE(std::getline(in, line));
    CHECK(line == "time,a,b");
    REQUIRE(std::getline(in, line));
    CHECK(line.substr(0, 5) == "0.01,");  // index 100 * 1e-4 s
    int rows = 1;
    while (std::getline(in, line))
        if (!line.empty()) ++rows;
    CHECK(rows == 10);
    CHECK(logger.stats().rows_written == 10);
}

TEST_CASE("bin spill and sidecar match the uz_scope schema") {
    fs::path dir = temp_dir("bin");
    CaptureLogger logger(dir, "bin", {"x", "y", "z"}, 1e-3, 1);
    auto b = block(3, 7);
    logger.submit(b.data(), 3, 7, 42);
    fs::path path = logger.close();
    CHECK(fs::file_size(path) == 3 * 7 * 4);
    // Sample-major layout: first record = (x0, y0, z0).
    std::ifstream in(path, std::ios::binary);
    float rec[3];
    in.read(reinterpret_cast<char*>(rec), sizeof(rec));
    CHECK(rec[0] == doctest::Approx(0.0f));
    CHECK(rec[1] == doctest::Approx(1000.0f));
    CHECK(rec[2] == doctest::Approx(2000.0f));

    fs::path sidecar = path;
    sidecar.replace_extension(".json");
    REQUIRE(fs::is_regular_file(sidecar));
    std::ifstream sj(sidecar);
    std::ostringstream buf;
    buf << sj.rdbuf();
    auto meta = nlohmann::json::parse(buf.str());
    CHECK(meta["format"] == "uz_scope-bin-v1");
    CHECK(meta["columns"].size() == 3);
    CHECK(meta["dtype"] == "<f4");
    CHECK(meta["first_index"] == 42);
    CHECK(meta["rows"] == 7);
    CHECK(meta["every_n"] == 1);
}

TEST_CASE("every_n stride uses the absolute index phase") {
    fs::path dir = temp_dir("stride");
    CaptureLogger logger(dir, "csv", {"a"}, 1.0, 3);
    auto b = block(1, 10);
    logger.submit(b.data(), 1, 4, 0);      // indices 0..3 -> keeps 0, 3
    logger.submit(b.data() + 4, 1, 6, 4);  // indices 4..9 -> keeps 6, 9
    logger.close();
    CHECK(logger.stats().rows_written == 4);
}

TEST_CASE("filename collision gets a suffix") {
    fs::path dir = temp_dir("collide");
    CaptureLogger a(dir, "csv", {"a"}, 1.0);
    CaptureLogger b2(dir, "csv", {"a"}, 1.0);
    CHECK(a.path() != b2.path());
    a.close();
    b2.close();
}

TEST_CASE("write_capture one-shot") {
    fs::path dir = temp_dir("capture");
    auto b = block(2, 5);
    fs::path path = write_capture(dir / "cap.csv", {"u", "v"}, b.data(), 2, 5, 10, 0.5);
    std::ifstream in(path);
    std::string line;
    REQUIRE(std::getline(in, line));
    CHECK(line == "time,u,v");
    REQUIRE(std::getline(in, line));
    CHECK(line == "5,0,1000");  // t = 10 * 0.5
}
