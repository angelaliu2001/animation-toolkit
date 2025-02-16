#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void setup(){
    //setting all booleans to be false
    isOne = false;
    isTwo = false;
    size = 0.001; //difference
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);
    
    vec3 a;
    vec3 b;
    if(isOne){
      for (float t = 0; t < 1; t+=size){
        // I am changing the color vector so that a difference could be seen
        setColor(vec3(1,1,0)); 
        a = bernstein(t);
        b = bernstein(t + size);
        drawLine(a, b);
      }
    }
    if (isTwo){
      for (float t = 0; t < 1; t+=size){
        setColor(vec3(0,0,1));
        a = deC(t);
        b = deC(t + size);
        drawLine(a, b);
      }
    }
  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      isOne = true;
    }
    else if (key == GLFW_KEY_2) {
      isTwo = true;
    }
  }

  //helper for computing a single lerp
  vec3 lerpC(vec3 v1, vec3 v2, float t){
    return v1*(1-t) + v2*t;
  }

  //compute de casteljau's algorithm
  vec3 deC(float t){
    vec3 b01 = lerpC(B0, B1, t);
    vec3 b11 = lerpC(B1, B2, t);
    vec3 b21 = lerpC(B2, B3, t);
    vec3 b02 = lerpC(b01, b11, t);
    vec3 b12 = lerpC(b11, b21, t);
    vec3 b = lerpC(b02, b12, t);
    return b;
  }
  
  //compute bernstein formula
  vec3 bernstein(float t){
    return (1-t)*(1-t)*(1-t)*B0 + 3.0f*(1-t)*(1-t)*t* B1 + 3.0f*t*t*(1-t)* B2 + t*t*t* B3;
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
  bool isOne; //record true if press 1
  bool isTwo; //record true if press 2
  float size;
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
