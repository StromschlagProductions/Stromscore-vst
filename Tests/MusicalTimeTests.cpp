#include "TestSupport.h"
#include "ScoreEngine.h"
#include <type_traits>
using namespace stromscore;
int main()
{
 using namespace musicaltime;
 static_assert(!std::is_convertible<int64_t,Tick>::value);
 static_assert(sizeof(Tick)==sizeof(int64_t));
 CHECK(ticksPerQuarter==960&&ticksPerGridStep==240&&kStep==.25);
 for(int num=1;num<=16;++num)for(int den:{1,2,4,8,16})
 {
  const auto ticks=barLength(num,den);const auto meter=Meter::from(num,den);
  CHECK(ticks==fromGridStep(meter.len));CHECK(ticks.value%4==0);
  CHECK(toQuarters(ticks)==num*4./den);
 }
 CHECK(barLength(3,8).value/4==360);
 for(int division:{1,2,3,4,5,6,8,10,12,16,24,32,48,64,96,192})CHECK(ticksPerQuarter%division==0);
 CHECK(ticksPerQuarter%7!=0);
 for(int64_t step:{-4000000000LL,-1LL,0LL,1LL,4000000000LL})CHECK(fromQuarters(toQuarters(fromGridStep(step)))==fromGridStep(step));
 Tick accumulated{};for(int64_t i=0;i<1000000;++i){accumulated.value+=ticksPerGridStep;CHECK(accumulated==fromGridStep(i+1));}
 // Restarts/stops and exact shared-channel note claims remain allocation free.
 Settings s;s.genre=GenrePopRock;s.x=.75f;s.y=.5f;s.z=.3f;s.variety=0;s.channel[OutArp]=s.channel[OutPadLong];
 Generator g;EventList es;Transport t;t.playing=true;
 for(int repeat=0;repeat<2;++repeat){for(int k=0;k<128;++k){t.ppq=k*.25;es.clear();{NoAllocations guard;g.process(t,s,6000,es);}CHECK(!es.overflow);}Transport stop;es.clear();g.process(stop,s,512,es);}
 std::cout<<"Musical time units, all supported meters, 1M-step drift and allocation tests passed\n";
}
