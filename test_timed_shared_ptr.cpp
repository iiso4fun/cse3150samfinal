#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TimedSharedPtr.hpp"
#include <thread>

TEST_CASE("Initial use_count and get before expiry") {
    TimedSharedPtr<int> p(new int(42), 100);
    REQUIRE(p.use_count() == 1);
    REQUIRE(p.get() != nullptr);
}

TEST_CASE("Copy increases reference count") {
    TimedSharedPtr<int> p(new int(7), 100);
    auto q = p;
    REQUIRE(p.use_count() == 2);
    REQUIRE(q.use_count() == 2);
}

TEST_CASE("Expiry returns nullptr") {
    TimedSharedPtr<int> p(new int(1), 50);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    REQUIRE(p.get() == nullptr);
    REQUIRE(p.use_count() == 1);
}

TEST_CASE("Move semantics") {
    TimedSharedPtr<int> p(new int(5), 100);
    TimedSharedPtr<int> q = std::move(p);
    REQUIRE(q.use_count() == 1);
    REQUIRE(p.use_count() == 0);
    REQUIRE(q.get() != nullptr);
}

TEST_CASE("Reset clears pointer and count") {
    TimedSharedPtr<int> p(new int(3), 100);
    p.reset();
    REQUIRE(p.get() == nullptr);
    REQUIRE(p.use_count() == 0);
}
