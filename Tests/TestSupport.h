#pragma once
#include <cstdlib>
#include <iostream>
#include <new>
#include <cmath>
#include <xmmintrin.h>
inline thread_local bool checkingAllocation = false;
inline thread_local int allocations = 0;
void* operator new (std::size_t n) { if (checkingAllocation) ++allocations; if (auto* p = std::malloc (n ? n : 1)) return p; throw std::bad_alloc(); }
void* operator new[] (std::size_t n) { return ::operator new (n); }
void operator delete (void* p) noexcept { std::free (p); }
void operator delete[] (void* p) noexcept { std::free (p); }
void operator delete (void* p, std::size_t) noexcept { std::free (p); }
void operator delete[] (void* p, std::size_t) noexcept { std::free (p); }
#define CHECK(x) do { if (!(x)) { std::cerr << __FILE__ << ':' << __LINE__ << ": " << #x << '\n'; std::exit (1); } } while (false)
struct NoAllocations {
    NoAllocations() { allocations = 0; checkingAllocation = true; }
    ~NoAllocations() { checkingAllocation = false; CHECK (allocations == 0); }
};
struct NoDenormals { NoDenormals() { _mm_setcsr (_mm_getcsr() | 0x8040); } };

#if defined(STROMSCORE_TRACK_C_HEAP)
inline thread_local bool checkingCHeap = false;
inline thread_local int cHeapCalls = 0;
extern "C" void* __real_malloc (size_t);
extern "C" void* __real_realloc (void*, size_t);
extern "C" void* __real_calloc (size_t, size_t);
extern "C" void* __wrap_malloc (size_t n) { if (checkingCHeap) ++cHeapCalls; return __real_malloc (n); }
extern "C" void* __wrap_realloc (void* p, size_t n) { if (checkingCHeap) ++cHeapCalls; return __real_realloc (p, n); }
extern "C" void* __wrap_calloc (size_t n, size_t m) { if (checkingCHeap) ++cHeapCalls; return __real_calloc (n, m); }
struct NoCHeap {
    NoCHeap() { cHeapCalls = 0; checkingCHeap = true; }
    ~NoCHeap() { checkingCHeap = false; CHECK (cHeapCalls == 0); }
};
#else
using NoCHeap = NoAllocations;
#endif
