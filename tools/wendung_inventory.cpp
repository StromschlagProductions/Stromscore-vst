// Export actual compiled catalog data, not a second manually maintained catalog.
#include "ScoreEngine.h"
#include "WendungInfo.h"
#include <iostream>
#include <iomanip>
#include <string>
static void quote(const char* value)
{
    std::cout<<'"';
    for(const unsigned char c:std::string(value))
    {
        if(c=='"'||c=='\\')std::cout<<'\\'<<c;
        else if(c<32)std::cout<<"\\u00"<<std::hex<<std::setw(2)<<std::setfill('0')<<static_cast<int>(c)<<std::dec;
        else std::cout<<c;
    }
    std::cout<<'"';
}
int main()
{
    using namespace stromscore;
    const char* types[]={"Maj","Min","Maj7","Min7","Dom7","MinMaj7","MinMaj9","Dim7","HalfDim","Sus4","Quartal","Add9","Min9","Aug","Min6","Dom7b9","Sus2","Fifth"};
    static_assert(std::size(types)==kNumChordTypes);
    std::cout<<std::setprecision(6)<<'[';bool first=true;
    for(int genre=0;genre<kNumGenres;++genre)for(int index=0;index<wendungCount(genre);++index)
    {
        const auto& w=wendungAt(genre,index);const auto& info=genre==GenreScore?kScoreInfo[index]:kPopInfo[index];
        if(!first)std::cout<<',';first=false;
        std::cout<<"{\"id\":"<<static_cast<unsigned>(w.id)<<",\"catalog\":";quote(genre==GenreScore?"score":"pop_rock");
        std::cout<<",\"catalog_index\":"<<index<<",\"name\":";quote(w.name);
        std::cout<<",\"xyz\":["<<w.x<<','<<w.y<<','<<w.z<<"],\"chords\":[";
        for(int i=0;i<w.n;++i)
        {
            if(i)std::cout<<',';const auto& c=w.ch[i];const auto& shape=kShapes[c.type];char name[96];chordName(0,c.root,c.type,name,96);
            std::cout<<"{\"root_pc_relative_to_key\":"<<c.root<<",\"type\":";quote(types[c.type]);
            std::cout<<",\"bars\":"<<c.bars<<",\"bass_pc_relative_to_key\":";
            if(c.bass<0)std::cout<<"null";else std::cout<<c.bass;
            std::cout<<",\"example_in_c\":";quote(name);std::cout<<",\"intervals\":[";
            for(int j=0;j<shape.n;++j){if(j)std::cout<<',';std::cout<<shape.iv[j];}std::cout<<"]}";
        }
        std::cout<<"],\"description\":";quote(info.idea);std::cout<<",\"description_source\":";quote(info.source);std::cout<<'}';
    }
    std::cout<<"]\n";
}
