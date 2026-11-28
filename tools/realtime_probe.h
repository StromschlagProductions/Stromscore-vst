#pragma once
// Offline measurement support; clocks, vectors and reports never enter the plugin.
#include <chrono>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <iostream>
#include <numeric>
#include <thread>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <time.h>
#endif
namespace rtprobe {
inline double cpuUs(){
#ifdef _WIN32
 FILETIME c,e,k,u;GetThreadTimes(GetCurrentThread(),&c,&e,&k,&u);ULARGE_INTEGER a{},b{};a.LowPart=k.dwLowDateTime;a.HighPart=k.dwHighDateTime;b.LowPart=u.dwLowDateTime;b.HighPart=u.dwHighDateTime;return (a.QuadPart+b.QuadPart)*.1;
#else
 timespec t{};clock_gettime(CLOCK_THREAD_CPUTIME_ID,&t);return t.tv_sec*1e6+t.tv_nsec*.001;
#endif
}
inline double wallUs(){return std::chrono::duration<double,std::micro>(std::chrono::steady_clock::now().time_since_epoch()).count();}
struct Series {std::vector<double> values;void print(double budget){auto v=values;std::sort(v.begin(),v.end());auto q=[&](double f){return v[static_cast<size_t>((v.size()-1)*f)];};std::cout<<"{\"mean\":"<<std::accumulate(v.begin(),v.end(),0.)/v.size()<<",\"median\":"<<q(.5)<<",\"p95\":"<<q(.95)<<",\"p99\":"<<q(.99)<<",\"p999\":"<<q(.999)<<",\"max\":"<<v.back()<<",\"over_budget\":"<<std::count_if(v.begin(),v.end(),[&](double n){return n>budget;})<<'}';}};
struct Hash {uint64_t value=1469598103934665603ull;void add(uint64_t n){for(int i=0;i<8;++i){value^=(n>>(i*8))&255;value*=1099511628211ull;}}};
}
