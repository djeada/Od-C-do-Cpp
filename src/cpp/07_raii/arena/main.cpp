#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory_resource>
#include <vector>

constexpr std::size_t N = 100'000;

struct Object {
    int x;
    int y;
    int z;
};

using Clock = std::chrono::steady_clock;

int main() {
    // ------------------------------------------------------------
    // 1. Ordinary heap allocation
    // ------------------------------------------------------------

    std::vector<Object*> objects;
    objects.reserve(N);

    auto start = Clock::now();

    for (std::size_t i = 0; i < N; ++i)
        objects.push_back(new Object{int(i), 1, 2});

    for (Object* p : objects)
        delete p;

    auto end = Clock::now();

    std::cout
        << "new/delete: "
        << std::chrono::duration<double, std::milli>(end - start).count()
        << " ms\n";


    // ------------------------------------------------------------
    // 2. Arena allocation
    // ------------------------------------------------------------

    std::vector<std::byte> memory(N * sizeof(Object));

    std::pmr::monotonic_buffer_resource arena(
        memory.data(),
        memory.size(),
        std::pmr::null_memory_resource()
    );

    std::pmr::polymorphic_allocator<Object> alloc(&arena);

    objects.clear();

    start = Clock::now();

    for (std::size_t i = 0; i < N; ++i) {
        Object* p = alloc.allocate(1);
        std::construct_at(p, Object{int(i), 1, 2});
        objects.push_back(p);
    }

    // All objects die together.
    arena.release();

    end = Clock::now();

    std::cout
        << "arena:      "
        << std::chrono::duration<double, std::milli>(end - start).count()
        << " ms\n";
}
