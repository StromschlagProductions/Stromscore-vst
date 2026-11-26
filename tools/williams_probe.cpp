#include "ScoreEngine.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#ifdef WILLIAMS_DIAGNOSTICS
namespace stromscore {struct ExecutionTestAccess {
 static void trace(Generator& g,const Settings& s,double ppq,int output,long long sample){
 const auto saved=g.cur;g.cur=&s;const auto at=execution::nominalAt(ppq,execution::Timing::groove,s.swing);const auto pos=g.locate(at);const auto plan=g.roleRhythm(pos,s);
 const auto& part=output==OutPadShort?plan.harmony:plan.bass;
 if(plan.source&&part.active&&part.at(at-pos.bar*16*musicaltime::sixteenth))std::cerr<<"R,"<<sample<<','<<plan.source->rhythm<<','<<plan.source->bassId<<','<<output<<'\n';g.cur=saved;
 }
};}
#endif
using namespace stromscore;
int main(int argc,char** argv){
 if(argc<7)return 2;Settings s;s.profile=static_cast<composition::ProfileId>(std::atoi(argv[1]));const int path=std::atoi(argv[2]),mode=std::atoi(argv[3]),block=std::atoi(argv[4]),bars=std::atoi(argv[5]);s.genre=std::atoi(argv[6]);
 s.policy=composition::policyForContext(s.profile,s.genre==GenreScore);s.key=2;s.variation=argc>7?std::atoi(argv[7]):1;s.scene=false;s.sceneBars=0;s.drive=false;s.melody=mode==1||mode==3;s.mute[kGegenstimme]=mode==0||mode==1;s.melodyMotif=s.motif=true;s.stichFixed=true;
 const float xyz[][3]={{.15f,.2f,.2f},{.15f,.25f,.8f},{.15f,.85f,.2f},{.15f,.85f,.85f},{.85f,.2f,.2f},{.85f,.25f,.8f},{.85f,.85f,.2f},{.85f,.85f,.85f},{.5f,.5f,.5f},{.2f,.3f,1.f},{.2f,.9f,1.f}};
 if(path<11){s.x=xyz[path][0];s.y=xyz[path][1];s.z=xyz[path][2];}
 if(path>=100){const int index=path-100;const auto& w=wendungAt(s.genre,index,s.profile);s.x=w.x;s.y=w.y;s.z=w.z;s.variety=0;bool found=false;
  for(int v=1;v<=16;++v){s.variation=v;if(Generator::pick(s,0)==index){found=true;break;}}if(!found)return 4;}
 if(argc>8&&std::atoi(argv[8])){s.padPattern=PadPulse;s.bassPattern=BassQuarter;}
 if(argc>9)s.follow[kBass]=s.follow[kFlaeche]=std::atoi(argv[9])!=0;
 if(argc>10)s.swing=std::atof(argv[10]);if(argc>11){s.meterNum=std::atoi(argv[11]);s.meterDen=std::atoi(argv[12]);}
 if(argc>14)s.arpFigure=std::atoi(argv[14]);if(argc>15)s.arpRate=std::atoi(argv[15]);
 Generator g;Transport t;t.playing=true;t.bpm=100;EventList es;long long total=static_cast<long long>(bars*4.*s.meterNum/s.meterDen*28800);int last=-2;
 for(long long at=0;at<total;){
  if((path==11||path==12)&&at%7200==0){double phase=at/28800./(path==11?64:8);s.x=.5+.4*std::sin(phase);s.y=.65+.25*std::sin(phase*.7);s.z=.5+.45*std::cos(phase*.8);}
  const int n=static_cast<int>(std::min<long long>({block,total-at,7200-at%7200}));t.ppq=at/28800.;
  if(argc>13&&std::atoi(argv[13])){
   t.playing=!(at>=total/4&&at<total/4+7200);
   if(at>=total/2)t.ppq-=total/2/28800.;
   if(at>=total*3/4)t.ppq+=8.125;
  }
  es.clear();g.process(t,s,n,es);if(es.overflow)return 3;
  if(g.wendung()!=last){last=g.wendung();std::cerr<<"H,"<<at<<','<<(last<0?-1:static_cast<int>(wendungAt(s.genre,last,s.profile).id))<<'\n';}
  for(int i=0;i<es.size;++i){const auto& e=es.events[i];std::cout<<at+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';
#ifdef WILLIAMS_DIAGNOSTICS
   if(e.type==0&&e.velocity&&e.out<=OutBassShort&&g.wendung()>=0)std::cerr<<"A,"<<at+e.offset<<','<<static_cast<int>(wendungAt(s.genre,g.wendung(),s.profile).id)<<','<<int(e.out)<<'\n';
   if(e.type==0&&e.velocity&&(e.out==OutPadShort||e.out==OutBassShort||e.out==OutBassLong))ExecutionTestAccess::trace(g,s,(at+e.offset)/28800.,e.out,at+e.offset);
#endif
  }at+=n;
 }
 t.playing=false;es.clear();g.process(t,s,block,es);for(int i=0;i<es.size;++i){auto e=es.events[i];std::cout<<total+e.offset<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';}
}
