#pragma once
#include "SequencePlan.h"
namespace stromscore::composition {
// A finite role-plan request. Immutable source data and actual performed material
// are distinct; neither contains a MIDI channel nor another voice's progress.
struct FigureEventPlan {
 SequenceSource figure{};Tick begin{};int base=0,replyTo=-1;bool ready=false,record=false;Tick replyBegin{},replyEnd{};
 SequenceUse use()const{return {ready?&figure:nullptr,begin,base};}
 Tick end()const{return begin+figure.period;}
};
struct PerformedFigureTone {Tick at{},length{};int pitch=0,velocity=0,output=-1,base=0;char intent='A';unsigned context=0;bool major=false;};
struct FigureHistory {
 std::array<PerformedFigureTone,3> tones{};int count=0;
 void observe(PerformedFigureTone n){if(count&&(tones[count-1].output!=n.output||tones[count-1].base!=n.base||tones[count-1].context!=n.context||tones[count-1].major!=n.major))count=0;if(count==3){tones[0]=tones[1];tones[1]=tones[2];--count;}tones[count++]=n;}
};
}
