#include "realtime_probe.h"
int main(){rtprobe::Series cpu,wall;cpu.values.reserve(100000);wall.values.reserve(100000);
 for(int i=0;i<100000;++i){const double w=rtprobe::wallUs(),c=rtprobe::cpuUs();const double dc=rtprobe::cpuUs()-c,dw=rtprobe::wallUs()-w;cpu.values.push_back(dc);wall.values.push_back(dw);}
 std::cout<<"{\"empty_timing_bracket_cpu_us\":";cpu.print(1333.333333);std::cout<<",\"empty_timing_bracket_wall_us\":";wall.print(1333.333333);std::cout<<"}\n";
}
