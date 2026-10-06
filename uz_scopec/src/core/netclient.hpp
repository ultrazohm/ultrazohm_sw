// TCP client for the JavaScope stream — the ingest hot path (GUI-free).
//
// One reader thread owns the socket: it recv()s into a preallocated buffer,
// parses every complete frame in one pass, hands the FrameView to a callback,
// and — when ack pacing is on — answers with one 8-byte command per received
// frame (a queued user command if any, else the zero-ack), matching the
// JavaScope's lock-step behaviour that javascope/test_server.py requires.
// The real APU drains its RX queue independently, so pacing can be off there.
//
// Callbacks run on the reader thread and must be fast (ring append + trigger
// bookkeeping); anything slow belongs on another thread.
#pragma once

#include <atomic>
#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "core/protocol.hpp"

namespace uz {

struct NetStats {
    std::atomic<int64_t> bytes_received{0};
    std::atomic<int64_t> frames{0};
    std::atomic<int64_t> samples{0};
    std::atomic<int64_t> commands_sent{0};
    std::atomic<int64_t> connects{0};
    std::atomic<double> last_rx_monotonic{0.0};
    std::atomic<double> connected_since{0.0};

    std::string last_error() const {
        std::lock_guard lock(error_mutex_);
        return last_error_;
    }
    void set_last_error(std::string e) {
        std::lock_guard lock(error_mutex_);
        last_error_ = std::move(e);
    }

private:
    mutable std::mutex error_mutex_;
    std::string last_error_;
};

class ScopeClient;

struct ClientCallbacks {
    std::function<void(const FrameView&)> on_frames;
    // Runs on the reader thread with the (guaranteed-alive) client — queue
    // the channel-select burst here.
    std::function<void(ScopeClient&)> on_connect;
    std::function<void(const std::string& reason)> on_disconnect;
};

double monotonic_seconds();

class ScopeClient {
public:
    ScopeClient(FrameGeometry geometry, std::string ip, int port, bool ack_pacing,
                ClientCallbacks callbacks, bool reconnect = true,
                double connect_timeout_s = 3.0);
    ~ScopeClient();

    void start();
    void stop();

    // Send one 8-byte command; with pacing on it rides the next ack slot.
    void send_command(const Command& cmd);
    int pending_commands() const;

    bool connected() const { return connected_.load(); }
    void set_ack_pacing(bool on) { ack_pacing_.store(on); }
    bool ack_pacing() const { return ack_pacing_.load(); }

    const FrameGeometry geometry;
    const std::string ip;
    const int port;
    NetStats stats;

private:
    void run();
    intptr_t do_connect(std::string& error);
    void close_socket();
    void recv_loop(intptr_t sock);
    void send_acks(intptr_t sock, int64_t count);
    void send_raw(intptr_t sock, const uint8_t* data, size_t len);

    std::atomic<bool> ack_pacing_;
    ClientCallbacks callbacks_;
    const bool reconnect_;
    const double connect_timeout_s_;

    std::deque<Command> cmd_queue_;
    mutable std::mutex cmd_mutex_;
    intptr_t sock_ = -1;
    std::mutex sock_mutex_;
    std::atomic<bool> stop_flag_{false};
    std::atomic<bool> connected_{false};
    std::thread thread_;
};

}  // namespace uz
