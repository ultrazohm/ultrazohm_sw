#include "core/netclient.hpp"

#include <chrono>
#include <cstring>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
using socklen_t = int;
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace uz {
namespace {

constexpr double RECONNECT_BACKOFF_S[] = {1.0, 2.0, 5.0};
constexpr size_t RECV_BUFFER_BYTES = 4 * 1024 * 1024;
constexpr int SO_RCVBUF_BYTES = 4 * 1024 * 1024;

#ifdef _WIN32
struct WinsockInit {
    WinsockInit() {
        WSADATA d;
        WSAStartup(MAKEWORD(2, 2), &d);
    }
};
void ensure_sockets() { static WinsockInit init; }
void close_native(intptr_t s) { ::closesocket(static_cast<SOCKET>(s)); }
int last_socket_error() { return WSAGetLastError(); }
#else
void ensure_sockets() {}
void close_native(intptr_t s) { ::close(static_cast<int>(s)); }
int last_socket_error() { return errno; }
#endif

std::string socket_error_string(int code) {
#ifdef _WIN32
    char buf[256] = {};
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
                   static_cast<DWORD>(code), 0, buf, sizeof(buf), nullptr);
    std::string s = buf;
    while (!s.empty() && (s.back() == '\n' || s.back() == '\r')) s.pop_back();
    return s.empty() ? "socket error " + std::to_string(code) : s;
#else
    return std::strerror(code);
#endif
}

}  // namespace

double monotonic_seconds() {
    using clock = std::chrono::steady_clock;
    return std::chrono::duration<double>(clock::now().time_since_epoch()).count();
}

ScopeClient::ScopeClient(FrameGeometry geom, std::string ip_, int port_,
                         bool ack_pacing, ClientCallbacks callbacks, bool reconnect,
                         double connect_timeout_s)
    : geometry(geom),
      ip(std::move(ip_)),
      port(port_),
      ack_pacing_(ack_pacing),
      callbacks_(std::move(callbacks)),
      reconnect_(reconnect),
      connect_timeout_s_(connect_timeout_s) {
    ensure_sockets();
}

ScopeClient::~ScopeClient() { stop(); }

void ScopeClient::start() {
    if (thread_.joinable()) return;
    stop_flag_.store(false);
    thread_ = std::thread([this] { run(); });
}

void ScopeClient::stop() {
    stop_flag_.store(true);
    close_socket();
    if (thread_.joinable()) thread_.join();
}

void ScopeClient::send_command(const Command& cmd) {
    if (ack_pacing_.load()) {
        std::lock_guard lock(cmd_mutex_);
        cmd_queue_.push_back(cmd);
        return;
    }
    std::lock_guard lock(sock_mutex_);
    if (sock_ < 0) throw std::runtime_error("not connected");
    send_raw(sock_, cmd.data(), cmd.size());
    stats.commands_sent.fetch_add(1);
}

int ScopeClient::pending_commands() const {
    std::lock_guard lock(cmd_mutex_);
    return static_cast<int>(cmd_queue_.size());
}

void ScopeClient::run() {
    size_t backoff_idx = 0;
    while (!stop_flag_.load()) {
        std::string error;
        intptr_t sock = do_connect(error);
        if (sock < 0) {
            stats.set_last_error(error);
            double delay = RECONNECT_BACKOFF_S[std::min(
                backoff_idx, std::size(RECONNECT_BACKOFF_S) - 1)];
            ++backoff_idx;
            if (!reconnect_) return;
            for (int i = 0; i < int(delay * 10) && !stop_flag_.load(); ++i)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        backoff_idx = 0;
        stats.connects.fetch_add(1);
        stats.connected_since.store(monotonic_seconds());
        connected_.store(true);
        if (callbacks_.on_connect) callbacks_.on_connect(*this);
        std::string reason = "closed by peer";
        try {
            recv_loop(sock);
        } catch (const std::exception& exc) {
            reason = exc.what();
            stats.set_last_error(reason);
        }
        connected_.store(false);
        close_socket();
        {
            // Stale queued commands must not fire into a fresh connection.
            std::lock_guard lock(cmd_mutex_);
            cmd_queue_.clear();
        }
        if (callbacks_.on_disconnect) callbacks_.on_disconnect(reason);
        if (!reconnect_) return;
    }
}

intptr_t ScopeClient::do_connect(std::string& error) {
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* res = nullptr;
    std::string port_str = std::to_string(port);
    if (int rc = ::getaddrinfo(ip.c_str(), port_str.c_str(), &hints, &res); rc != 0) {
        error = "resolve failed: " + std::string(gai_strerror(rc));
        return -1;
    }
    intptr_t sock = -1;
    for (addrinfo* ai = res; ai != nullptr; ai = ai->ai_next) {
        sock = intptr_t(::socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol));
        if (sock < 0) continue;
#ifdef _WIN32
        DWORD tmo = static_cast<DWORD>(connect_timeout_s_ * 1000);
        ::setsockopt(SOCKET(sock), SOL_SOCKET, SO_RCVTIMEO,
                     reinterpret_cast<const char*>(&tmo), sizeof(tmo));
#else
        timeval tv{};
        tv.tv_sec = long(connect_timeout_s_);
        tv.tv_usec = long((connect_timeout_s_ - tv.tv_sec) * 1e6);
        ::setsockopt(int(sock), SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#endif
        if (::connect(
#ifdef _WIN32
                SOCKET(sock),
#else
                int(sock),
#endif
                ai->ai_addr, socklen_t(ai->ai_addrlen)) == 0)
            break;
        close_native(sock);
        sock = -1;
    }
    ::freeaddrinfo(res);
    if (sock < 0) {
        error = "connect to " + ip + ":" + port_str + " failed: " +
                socket_error_string(last_socket_error());
        return -1;
    }
    int one = 1;
    ::setsockopt(
#ifdef _WIN32
        SOCKET(sock),
#else
        int(sock),
#endif
        IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&one), sizeof(one));
    int rcvbuf = SO_RCVBUF_BYTES;
    ::setsockopt(
#ifdef _WIN32
        SOCKET(sock),
#else
        int(sock),
#endif
        SOL_SOCKET, SO_RCVBUF, reinterpret_cast<const char*>(&rcvbuf), sizeof(rcvbuf));
#ifndef _WIN32
    timeval tv{};  // back to blocking sends after the connect timeout
    ::setsockopt(int(sock), SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#else
    DWORD zero = 0;
    ::setsockopt(SOCKET(sock), SOL_SOCKET, SO_RCVTIMEO,
                 reinterpret_cast<const char*>(&zero), sizeof(zero));
#endif
    std::lock_guard lock(sock_mutex_);
    sock_ = sock;
    return sock;
}

void ScopeClient::close_socket() {
    intptr_t sock;
    {
        std::lock_guard lock(sock_mutex_);
        sock = sock_;
        sock_ = -1;
    }
    if (sock >= 0) {
#ifdef _WIN32
        ::shutdown(SOCKET(sock), SD_BOTH);
#else
        ::shutdown(int(sock), SHUT_RDWR);
#endif
        close_native(sock);
    }
}

void ScopeClient::send_raw(intptr_t sock, const uint8_t* data, size_t len) {
    size_t sent = 0;
    while (sent < len) {
#ifdef _WIN32
        int n = ::send(SOCKET(sock), reinterpret_cast<const char*>(data + sent),
                       int(len - sent), 0);
#else
        ssize_t n = ::send(int(sock), data + sent, len - sent, MSG_NOSIGNAL);
#endif
        if (n <= 0)
            throw std::runtime_error("send failed: " +
                                     socket_error_string(last_socket_error()));
        sent += size_t(n);
    }
}

void ScopeClient::recv_loop(intptr_t sock) {
    const int64_t frame_bytes = geometry.frame_bytes();
    std::vector<uint8_t> buf(std::max<size_t>(RECV_BUFFER_BYTES, 4 * frame_bytes));
    int64_t fill = 0;
    while (!stop_flag_.load()) {
#ifdef _WIN32
        int n = ::recv(SOCKET(sock), reinterpret_cast<char*>(buf.data() + fill),
                       int(int64_t(buf.size()) - fill), 0);
#else
        ssize_t n = ::recv(int(sock), buf.data() + fill, buf.size() - size_t(fill), 0);
#endif
        if (n == 0) return;  // closed by peer
        if (n < 0) {
            if (stop_flag_.load()) return;
            throw std::runtime_error("recv failed: " +
                                     socket_error_string(last_socket_error()));
        }
        fill += n;
        stats.bytes_received.fetch_add(n);
        stats.last_rx_monotonic.store(monotonic_seconds());
        int64_t k = fill / frame_bytes;
        int64_t rem = fill % frame_bytes;
        if (k == 0) continue;
        FrameView view{buf.data(), int(k), geometry};
        if (callbacks_.on_frames) callbacks_.on_frames(view);
        stats.frames.fetch_add(k);
        stats.samples.fetch_add(k * geometry.samples_per_packet);
        if (rem) std::memmove(buf.data(), buf.data() + k * frame_bytes, size_t(rem));
        fill = rem;
        if (ack_pacing_.load()) send_acks(sock, k);
    }
}

void ScopeClient::send_acks(intptr_t sock, int64_t count) {
    // One 8-byte write per frame: lock-step servers parse exactly the first
    // command of each recv, so commands must never coalesce.
    static const Command ZERO = zero_ack();
    for (int64_t i = 0; i < count; ++i) {
        Command data = ZERO;
        {
            std::lock_guard lock(cmd_mutex_);
            if (!cmd_queue_.empty()) {
                data = cmd_queue_.front();
                cmd_queue_.pop_front();
                stats.commands_sent.fetch_add(1);
            }
        }
        send_raw(sock, data.data(), data.size());
    }
}

}  // namespace uz
