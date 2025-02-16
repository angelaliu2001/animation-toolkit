#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using atk::Transform;
using glm::quat;
using glm::vec3;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}

   virtual void setup() {
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);

      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint2, joint1);

      Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint3, joint2);

      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint4, joint3);
      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      quat tmp;
      Joint* someJoint;
      for(int i = 0; i<5; i++){
         tmp = glm::angleAxis((float) (sin(elapsedTime() * i)), vec3(0,0,1));
         someJoint = _tentacle.getByID(i);
         someJoint->setLocalRotation(tmp);
      }
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(0,1,0));

      // todo: loop over all joints and draw
      Joint* parent = NULL;
      Joint* child = NULL;
      for(int i = 0; i < _tentacle.getNumJoints()-1; i++){
         parent = _tentacle.getByID(i);
         child = _tentacle.getByID(i+1);
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = child->getGlobalTranslation();
         drawEllipsoid(globalParentPos, globalPos, 5);
      }
   }

protected:
   Skeleton _tentacle;
      Motion motion;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

