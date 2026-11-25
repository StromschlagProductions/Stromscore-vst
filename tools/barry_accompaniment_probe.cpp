// Production-path MIDI probe. No scheduler, musical rules or generator state is mocked.
#include "ScoreEngine.h"
#include <cstdlib>
#include <iostream>
using namespace stromscore;
int main(int argc,char** argv)
{
    if(argc!=15)return 2;
    Settings s;s.profile=static_cast<composition::ProfileId>(std::atoi(argv[1]));s.genre=std::atoi(argv[2]);
    s.policy=composition::policyForContext(s.profile,s.genre==GenreScore);
    s.x=std::atof(argv[3]);s.y=std::atof(argv[4]);s.z=std::atof(argv[5]);const int path=std::atoi(argv[6]);
    s.meterNum=std::atoi(argv[7]);s.meterDen=std::atoi(argv[8]);const int initialVariation=std::atoi(argv[9]);s.variation=initialVariation;const int manual=std::atoi(argv[10]);
    for(auto& f:s.follow)f=std::atoi(argv[11])!=0;
    s.swing=std::atof(argv[12]);const int block=std::atoi(argv[13]);const double bpm=std::atof(argv[14]);
    s.key=2;s.melody=true;s.motif=s.melodyMotif=true;s.inertia=true;
    if(manual){s.padPattern=manual==1?PadHeld:PadPulse;s.bassPattern=manual==1?BassHalf:BassQuarter;
        s.arpFigure=ArpCircle;s.arpRate=manual==1?RateEighth:RateSixteenth;}
    Generator g;Transport t;t.playing=true;t.bpm=bpm;EventList e;
    const double spq=48000*60/bpm;const int steps=Meter::from(s.meterNum,s.meterDen).len;
    int64_t at=0;
    auto emit=[&]{for(int i=0;i<e.size;++i){const auto n=e.events[i];
        int rhythm=0;
#ifdef BARRY_ACCOMPANIMENT_CURRENT
        rhythm=g.accompanimentRhythmId();
#endif
        std::cout<<at+n.offset<<','<<int(n.out)<<','<<int(n.channel)<<','<<int(n.note)<<','<<int(n.velocity)<<','<<int(n.type)<<','<<rhythm<<'\n';}};
    for(int step=0;step<128*steps;++step)
    {
        if(path==1||path==2){const double q=step*.25*(path==1?.06:.6);
            s.x=.5f+.47f*std::sin(q);s.y=.65f+.3f*std::sin(q*.7);s.z=.5f+.49f*std::sin(q*.9);s.variation=1+(initialVariation-1+step/(8*steps))%16;}
        if(path==3){const int phase=(step/(4*steps))%4;s.x=.8f;s.y=phase==0||phase==3?.25f:.95f;s.z=phase==0||phase==3?.15f:phase==1?.85f:1.f;}
        const auto end=std::llround((step+1)*.25*spq);
        while(at<end){const int n=static_cast<int>(std::min<int64_t>(block,end-at));t.ppq=at/spq;e.clear();g.process(t,s,n,e);if(e.overflow)return 3;emit();at+=n;}
    }
    t.playing=false;e.clear();g.process(t,s,1,e);emit();
}
