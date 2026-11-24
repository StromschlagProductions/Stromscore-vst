#include "TestSupport.h"
#include "ScoreEngine.h"
using namespace stromscore;using namespace stromscore::composition;
int main()
{
 const int counts[]={4,4,5,5,4,3,4,5,4};
 const int intervals[9][5]={{0,4,7,9},{0,3,7,14},{0,4,7,11,14},{0,4,7,10,14},{0,5,7,10},{0,3,6},{0,4,8,11},{0,4,7,11,18},{0,2,7,11}};
 int successes=0,rejections=0;
 CHECK(kNumChordTypes==27&&kNumCustomTypes==18);
 for(int t=18;t<27;++t)for(int key=0;key<12;++key)for(int low:{36,60})
 {
  const auto sh=kShapes[t];CHECK(sh.n==counts[t-18]);ChordIntent intent;intent.root=key;intent.bassPitchClass=key+7;intent.count=sh.n;intent.intensity=.8f;intent.padLow=low+12;intent.preservePitchClasses=true;
  unsigned expected=0,required=0;for(int i=0;i<sh.n;++i){CHECK(sh.iv[i]==intervals[t-18][i]);intent.intervals[i]=sh.iv[i];expected|=pitchBit(key+sh.iv[i]);if(sh.iv[i]%12!=0&&sh.iv[i]%12!=7)required|=pitchBit(key+sh.iv[i]);}
  auto anchor=buildAnchor(intent,{low,low+48},true);CHECK(dispositionMask(anchor.pad)==expected);CHECK((anchor.bass%12)==(key+7)%12);
  for(auto strategy:{ChordColoration::flexible,ChordColoration::protectedColor})for(float z:{.1f,.6f,.95f})CHECK(coloredChordType(t,z,strategy)==t);
  for(auto mode:ChordDispositionPolicy{}.cycle)for(int poly=1;poly<=6;++poly)
  {
   ChordDispositionRequest r;r.original=anchor.pad;r.previous=anchor.pad;r.chordMask=expected;r.required=required;r.root=key;r.bass=48+key;r.low=low;r.high=low+48;r.polyphony=poly;r.disposition=mode;
   ChordDispositionResult result;{NoAllocations guard;result=realizeChord(r,{});}
   if(result.insufficientVoices){++rejections;CHECK(result.notes.n==0);}
   else{++successes;CHECK(result.notes.n<=poly);CHECK(!(dispositionMask(result.notes)&~expected));CHECK((dispositionMask(result.notes)&required)==required);}
  }
  auto previous=buildAnchor(intent,{low,low+48},true).pad;auto led=voiceleading::lead(anchor.pad,previous,low,low+48);CHECK(dispositionMask(led)==expected);
  unsigned vocabulary=expected;auto ctx=modalContext(vocabulary,key,true);if(ctx.status==ModalStatus::unique)CHECK(!(expected&~ctx.mask));
 }
 CHECK(successes&&rejections);std::cout<<"New chord definitions: "<<successes<<" valid voice allocations, "<<rejections<<" controlled insufficient-voice rejections\n";
}
