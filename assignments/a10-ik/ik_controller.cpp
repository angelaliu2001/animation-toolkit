#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();

  vec3 tmp = goalPos - hip->getLocalTranslation();
  vec3 p2 = knee->getLocalTranslation();
  vec3 p3 = ankle->getLocalTranslation();

  float r = length(tmp);
  float l1 = length(p2);   
  float l2 = length(p3);

  float v = (r * r - l1 * l1 - l2 * l2)/((-2.0f)*l1*l2);
  float value = clamp(v, -1.0f, 1.0f);
  float theta = acos(value);
  float theta2z = theta - M_PI; 
  quat p2Rot = quat(cos(theta2z/2.0f), 0, 0, sin(theta2z/2.0f));
  knee->setLocalRotation(p2Rot);

  float theta1z = asin((-1.0f)*l2*sin(theta2z)/r);
  float gamma = asin((float)goalPos[1]/r);
  float beta = atan2(-(1.0f)*(float)goalPos[2], goalPos[0]);
  quat p1Rot = quat(cos(beta/2.0f), 0, sin(beta/2.0f), 0)
                * quat(cos(gamma/2.0f), 0, 0, sin(gamma/2.0f))
                * quat(cos(theta1z/2.0f), 0, 0, sin(theta1z/2.0f));
  hip->setLocalRotation(p1Rot);

  skeleton.fk();
  return true;
}

// solveIKCCD positions the joint given by jointid so its global position
// is located at goalPos
//
// param skeleton: the character to modify
// param jointid: the ID of the joint to pose
// param goalPos: the target position for jointid (global pos)
// param chain: the list of joints to "nudge" towards the goal
// param threshold: when the given joint is within threshold of the goal, stop iterating
// param maxIters: the max number of iterations to try to reach the goal
//
// return true/false based on whether we could reach the goal
// side effect: skeleton should by posed such that jointid is located at goalPos (or in this direction of
// goalPos if the target is out of reach)
bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;
  vec3 p = skeleton.getByID(jointid)->getGlobalTranslation();
  while(length(goalPos-p) > threshold && numIters < maxIters){
    for(int i = 0; i < chain.size(); i++){
      //compute end effectors position
      vec3 e = goalPos - endPos;
      vec3 r = endPos - chain[i]->getGlobalTranslation();
      float angleRot = nudgeFactor * atan2(length(cross(r,e)), dot(r,r)+dot(r,e));
      vec3 axis = cross(r,e).noramlize();
      quat rot = 
      skeleton.fk();
    }
    p = skeleton.getByID(jointid)->getGlobalTranslation();
    numIters++;
  }
  return false;
}
