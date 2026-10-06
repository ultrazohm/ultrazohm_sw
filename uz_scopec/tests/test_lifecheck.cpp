#include <doctest/doctest.h>

#include <vector>

#include "core/lifecheck.hpp"

using namespace uz;

namespace {
void feed(Lifecheck& lc, std::vector<float> v) { lc.update(v.data(), int64_t(v.size())); }
}  // namespace

TEST_CASE("continuous stream, no gaps") {
    Lifecheck lc;
    feed(lc, {0, 1, 2, 3});
    feed(lc, {4, 5, 6});
    CHECK(lc.gaps == 0);
    CHECK(lc.missing == 0);
    CHECK(lc.checked == 7);
}

TEST_CASE("gap within and across blocks") {
    Lifecheck lc;
    feed(lc, {0, 1, 5, 6});
    CHECK(lc.gaps == 1);
    CHECK(lc.missing == 3);
    feed(lc, {9, 10});
    CHECK(lc.gaps == 2);
    CHECK(lc.missing == 5);
}

TEST_CASE("firmware wrap at 1000 is continuity with the default modulo") {
    // javascope.c sends interrupt_counter % 1000; wraps must not count.
    Lifecheck lc;
    std::vector<float> stream;
    for (int i = 0; i < 5000; ++i) stream.push_back(float(i % 1000));
    for (size_t i = 0; i < stream.size(); i += 30)
        lc.update(stream.data() + i, std::min<int64_t>(30, int64_t(stream.size() - i)));
    CHECK(lc.gaps == 0);
    CHECK(lc.missing == 0);
    CHECK(lc.checked == 5000);
}

TEST_CASE("real gap detected across the wrap") {
    Lifecheck lc;
    feed(lc, {996, 997, 998});
    feed(lc, {3, 4});  // dropped 999, 0, 1, 2
    CHECK(lc.gaps == 1);
    CHECK(lc.missing == 4);
}

TEST_CASE("reset") {
    Lifecheck lc;
    feed(lc, {0, 5});
    CHECK(lc.gaps == 1);
    lc.reset();
    feed(lc, {100, 101});
    CHECK(lc.gaps == 0);
    CHECK(lc.checked == 2);
}
