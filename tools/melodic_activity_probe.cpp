// Offline measurement only. Compile against isolated header snapshots; never linked into the plugin.
#include "ScoreEngine.h"
#include <array>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace stromscore;
#ifndef ACTIVITY_V21
namespace stromscore {
struct ActivityAccess {
 struct Snapshot{bool complete=false,active=false,eligible=false;int64_t epoch=-1,begin=0,end=0;int notes=0;bool flexible=false,adapted=false,shortened=false;composition::MotifOccurrence plan;composition::RememberedMotif material;};
 static Snapshot read(Generator& g,int output,const Settings& s){const auto& v=g.voice(output);Snapshot r;r.complete=v.motif.material(g.motifCatalog).complete;
#ifdef ACTIVITY_PRE_SCHEDULER
  const auto& p=v.recurrencePlan;r.epoch=v.recurrenceEpoch;
#else
  const auto& p=v.recurrence.plan;r.epoch=v.recurrence.epoch;
#endif
  r.plan=p;r.material=v.motif.material(g.motifCatalog);
#ifdef SCORE_REALIZATION_MEASUREMENTS
  r.flexible=p.figure.harmonicRealization;r.adapted=p.figure.harmonicallyAdapted;r.shortened=p.figure.durationAdjusted;
#endif
  r.active=p.active;r.begin=p.begin.value;r.end=p.end.value;r.notes=p.figure.count;
  const auto& policy=s.genre==GenrePopRock?s.policy.popHooks.recurrence:s.policy.motif;
  r.eligible=r.epoch>=1&&composition::recurrenceSlot(policy,r.epoch,Generator::layerY(s,kOutputLayer[output]),s.z).eligible;return r;}
};}
#endif
struct RoleStats{int ons=0;long long busy=0,enabled=0,first=-1,complete=-1;std::set<int> bars;std::vector<std::pair<long long,long long>> intervals;int open=0;long long since=0;};
int main(int argc,char** argv){if(argc!=8)return 2;int genre=std::atoi(argv[1]),path=std::atoi(argv[2]),mode=std::atoi(argv[3]),profile=std::atoi(argv[4]),seed=std::atoi(argv[5]),bars=std::atoi(argv[6]);std::ofstream notes(argv[7]);notes<<"sample,out,channel,note,velocity,type\n";
 Settings s;s.genre=genre;s.key=9;s.x=.5f;s.y=.85f;s.z=.1f;s.inertia=true;s.scene=path==8||path==12;s.motif=mode!=2;s.seed=seed;
#ifndef ACTIVITY_V21
 s.melody=mode!=1&&mode!=4;s.melodyMotif=mode!=2;s.profile=static_cast<composition::ProfileId>(profile);
#else
 (void)profile;
#endif
 if(mode>=3){for(int l=0;l<4;++l)s.mute[l]=true;}
#ifndef ACTIVITY_V21
 if(mode==14)for(int l=0;l<4;++l)s.mute[l]=false;
 if(mode==5){s.solo[kMelodie]=s.solo[kGegenstimme]=true;}
#endif
#ifndef ACTIVITY_V21
 if(mode==8||mode==11)s.mute[kGegenstimme]=true;
 if(mode==9)s.mute[kMelodie]=true;
 if(mode==10)s.solo[kGegenstimme]=true;
 if(mode==11)s.solo[kMelodie]=true;
 if(mode==12)s.layerIntensity[kMelodie]=-1;
#endif
 if(path==7){s.custom=true;s.customChords[0]={0,Maj7,8};}
 Generator g;EventList out;Transport t;t.playing=true;t.bpm=120;std::array<RoleStats,2> stats;std::array<std::map<int,long long>,2> held;std::array<std::set<int64_t>,2> epochs;std::array<int,2> eligible{},activePlans{},plannedNotes{},performedPlanNotes{};std::array<std::vector<std::pair<int64_t,int64_t>>,2> planWindows;std::array<int,2> flexible{},adapted{},shortened{},fragments{};
#ifndef ACTIVITY_V21
 std::array<std::vector<ActivityAccess::Snapshot>,2> examples;
#endif
 std::set<int> ids;int changes=0,prevId=-1;uint64_t accompaniment=1469598103934665603ull;const long long total=static_cast<long long>(bars)*96000;
 auto emit=[&](long long offset){for(int i=0;i<out.size;++i){auto e=out.events[i];long long at=offset+e.offset;notes<<at<<','<<int(e.out)<<','<<int(e.channel)<<','<<int(e.note)<<','<<int(e.velocity)<<','<<int(e.type)<<'\n';if(e.out<7){for(auto x:{at,static_cast<long long>(e.out),static_cast<long long>(e.channel),static_cast<long long>(e.note),static_cast<long long>(e.velocity),static_cast<long long>(e.type)}){accompaniment^=static_cast<uint64_t>(x);accompaniment*=1099511628211ull;}}if(e.type||e.out<7)continue;int role=e.out==7?1:0;auto& r=stats[role];auto& h=held[role];if(e.velocity){for(auto window:planWindows[role])if(at>=window.first&&at<window.second){++performedPlanNotes[role];break;}++r.ons;if(r.first<0)r.first=at;if(h.empty())r.since=at;h[e.note]=at;}else{h.erase(e.note);if(h.empty()&&r.since>=0){if(at>r.since){r.intervals.push_back({r.since,at});r.busy+=at-r.since;for(int b=r.since/96000;b<bars&&b*96000<at;++b)r.bars.insert(b);}r.since=-1;}}}};
 for(long long at=0;at<total;){const int n=std::min<long long>(512,total-at);double q=at/24000.;
  if(path==12){s.x=.75f;s.y=.85f;s.z=.2f;}else if(path==0){s.x=.25f;s.y=.85f;s.z=.1f;}else if(path==1){s.x=.75f;s.y=.85f;s.z=.2f;}else if(path==2){s.x=.5f;s.y=.9f;s.z=.75f;}else{
   double period=path==4?8.:path==5?32.:64.;s.x=.5f+.4f*std::sin(q*6.283185307179586/period);s.y=.85f+.1f*std::sin(q*6.283185307179586/(period*1.3)+.3);s.z=.4f+.35f*std::sin(q*6.283185307179586/(period*1.7)+.7);
   if(path==6)s.z=.1f; // XYZ motion with low unrest, same XY trajectory.
  }
  if(path==9){s.y=1;s.z=1;}
  if(path==13){s.x=q<8?.5f:static_cast<float>(.5+.4*std::sin(q*6.283185307179586/8));s.y=q<8?.85f:1.f;s.z=q<8?.1f:1.f;}
  if(path==10)s.genre=q<240?GenreScore:q<360?GenrePopRock:GenreScore;
#ifndef ACTIVITY_V21
  if(mode==6){s.mute[kMelodie]=s.mute[kGegenstimme]=q<16;}
  if(mode==7)s.melody=q>=16;
  if(mode==13)s.mute[kMelodie]=q>=32&&q<64;
  if(mode==14)s.mute[kMelodie]=q>=80;
#endif
  t.ppq=q;out.clear();g.process(t,s,n,out);if(out.overflow)return 4;int id=g.wendung();ids.insert(id);if(prevId>=0&&prevId!=id)++changes;prevId=id;
  for(int r=0;r<2;++r){const int output=r==0?8:7;
#ifndef ACTIVITY_V21
   if(g.layerPlaying(r==0?kMelodie:kGegenstimme))stats[r].enabled+=n;auto snap=ActivityAccess::read(g,output,s);
   if(snap.complete&&stats[r].complete<0)stats[r].complete=at;
   if(snap.epoch>=1&&epochs[r].insert(snap.epoch).second){eligible[r]+=snap.eligible;activePlans[r]+=snap.active;if(snap.active){flexible[r]+=snap.flexible;adapted[r]+=snap.adapted;shortened[r]+=snap.shortened;fragments[r]+=snap.plan.figure.variation==composition::MotifVariation::fragment;
    if((snap.flexible&&examples[r].size()<8)||examples[r].size()<2)examples[r].push_back(snap);
    plannedNotes[r]+=snap.notes;planWindows[r].push_back({snap.begin*25,snap.end*25});}}
#else
   (void)output;if(r==1&&g.layerPlaying(kGegenstimme))stats[r].enabled+=n;
#endif
  }
  emit(at);at+=n;
 }
 Transport stop;out.clear();g.process(stop,s,512,out);emit(total);
 std::cout<<std::setprecision(10)<<"{\"genre\":"<<genre<<",\"path\":"<<path<<",\"mode\":"<<mode<<",\"profile\":"<<profile<<",\"seed\":"<<seed<<",\"bars\":"<<bars<<",\"seconds\":"<<total/48000.<<",\"template_changes\":"<<changes<<",\"different_templates\":"<<ids.size()<<",\"accompaniment_hash\":\""<<accompaniment<<"\",\"roles\":[";
 for(int r=0;r<2;++r){if(r)std::cout<<',';auto& x=stats[r];long long gap=0,last=0;for(auto interval:x.intervals){gap=std::max(gap,interval.first-last);last=interval.second;}gap=std::max(gap,total-last);
 std::cout<<"{\"role\":\""<<(r==0?"melody":"dialog")<<"\",\"note_ons\":"<<x.ons<<",\"sounding_percent\":"<<100.*x.busy/total<<",\"enabled_percent\":"<<100.*x.enabled/total<<",\"active_bars\":"<<x.bars.size()<<",\"first_ms\":"<<(x.first<0?-1:x.first/48.)<<",\"max_silence_seconds\":"<<gap/48000.<<",\"material_complete_ms\":"<<(x.complete<0?-1:x.complete/48.)<<",\"epochs\":"<<epochs[r].size()<<",\"eligible_epochs\":"<<eligible[r]<<",\"active_recurrence_plans\":"<<activePlans[r]<<",\"planned_recurrence_notes\":"<<plannedNotes[r]<<",\"performed_recurrence_notes\":"<<performedPlanNotes[r]<<",\"flexible_plans\":"<<flexible[r]<<",\"pitch_adapted_plans\":"<<adapted[r]<<",\"shortened_plans\":"<<shortened[r]<<",\"fragment_plans\":"<<fragments[r]<<",\"examples\":[";
#ifndef ACTIVITY_V21
 for(size_t j=0;j<examples[r].size();++j){if(j)std::cout<<',';const auto& e=examples[r][j];
  std::cout<<"{\"begin_tick\":"<<e.begin<<",\"end_tick\":"<<e.end<<",\"source_identity\":\""<<e.material.identity<<"\",\"figure_identity\":\""<<e.plan.figure.sourceIdentity<<"\",\"flexible\":"<<e.flexible<<",\"adapted\":"<<e.adapted<<",\"shortened\":"<<e.shortened<<",\"variation\":"<<static_cast<int>(e.plan.figure.variation)<<",\"source\":[";
  for(int i=0;i<e.material.count;++i){if(i)std::cout<<',';const auto& n=e.material.notes[i];std::cout<<'['<<e.material.origin+n.interval<<','<<n.at.value<<','<<n.length.value<<']';}
  std::cout<<"],\"figure\":[";for(int i=0;i<e.plan.figure.count;++i){if(i)std::cout<<',';const auto& n=e.plan.figure.notes[i];std::cout<<'['<<e.plan.base+n.interval<<','<<n.at.value<<','<<n.length.value<<']';}std::cout<<"]}";}
#endif
 std::cout<<"]}";}std::cout<<"]}\n";
}
