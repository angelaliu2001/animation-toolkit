#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ADancer : public atkui::Framework
{
public:
   ADancer() : atkui::Framework(atkui::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.color = vec3(1,0,0);
   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

      IKController ik;

      _lhandTarget = vec3(0, 40.0f*(sin(3.0f*elapsedTime())+1.0f),0);
      _rhandTarget = vec3(0, 40.0f*(-sin(3.0f*elapsedTime())+1.0f),0);
      _lhandTarget += _skeleton.getByName("Beta:LeftHand")->getGlobalTranslation();
      _rhandTarget += _skeleton.getByName("Beta:RightHand")->getGlobalTranslation();
      // setColor(vec3(0, 1, 0));
      // drawSphere(_lhandTarget, 10);
      // drawSphere(_rhandTarget, 10);
      
   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));
      drawSphere(_lhandTarget, 10);
      drawSphere(_rhandTarget, 10);
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   vec3 _lhandTarget;
   vec3 _rhandTarget;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

