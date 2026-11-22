#pragma once
#include <array>
#include <algorithm>
#include <cmath>
namespace stromscore {
struct DrivePoint { float x=0,y=0; };
struct DrivePath {
 int count=0;
 std::array<DrivePoint,4> points {};
 std::array<DrivePoint,5> bends {};
 DrivePoint anchor(int i,DrivePoint a,DrivePoint b) const { return i==0?a:i==count+1?b:points[(size_t)i-1]; }
 DrivePoint control(int i,DrivePoint a,DrivePoint b) const {
  auto p=anchor(i,a,b),q=anchor(i+1,a,b),d=bends[(size_t)i];
  return {std::clamp((p.x+q.x)*.5f+d.x,0.f,1.f),std::clamp((p.y+q.y)*.5f+d.y,0.f,1.f)};
 }
 DrivePoint segment(int i,float t,DrivePoint a,DrivePoint b) const {
  auto p=anchor(i,a,b),q=anchor(i+1,a,b),c=control(i,a,b);float u=1-t;
  return {u*u*p.x+2*u*t*c.x+t*t*q.x,u*u*p.y+2*u*t*c.y+t*t*q.y};
 }
 float length(int i,DrivePoint a,DrivePoint b) const {
  float d=0;auto p=segment(i,0,a,b);for(int k=1;k<=32;++k){auto q=segment(i,k/32.f,a,b);d+=std::hypot(q.x-p.x,q.y-p.y);p=q;}return d;
 }
 DrivePoint at(float t,DrivePoint a,DrivePoint b) const {
  t=std::clamp(t,0.f,1.f);float lengths[5]{},sum=0;
  for(int i=0;i<=count;++i)sum+=(lengths[i]=length(i,a,b));
  if(sum<1e-7f)return a;float remaining=t*sum;
  for(int i=0;i<=count;++i){if(remaining<=lengths[i]||i==count){auto p=segment(i,0,a,b);for(int k=1;k<=32;++k){auto q=segment(i,k/32.f,a,b);float d=std::hypot(q.x-p.x,q.y-p.y);if(remaining<=d||k==32){float f=d>1e-7f?std::clamp(remaining/d,0.f,1.f):0;return {p.x+(q.x-p.x)*f,p.y+(q.y-p.y)*f};}remaining-=d;p=q;}}remaining-=lengths[i];}return b;
 }
 bool active() const { if(count)return true;for(int i=0;i<=count;++i)if(bends[(size_t)i].x!=0||bends[(size_t)i].y!=0)return true;return false; }
};
}
