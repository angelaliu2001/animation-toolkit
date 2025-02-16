#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{     
   float x = atan2(-mM[1][2], mM[2][2]);
   float y = asin(mM[0][2]);
   float z = atan2(-mM[0][1], mM[0][0]);
   if(mM[0][2] == 1 || mM[0][2] == -1){
      x = 0.0f;
      z = acos(mM[1][1]);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   float x = atan2(mM[2][1], mM[1][1]);
   float y = atan2(mM[0][2], mM[0][0]);
   float z = asin(-mM[0][1]);
   if (mM[0][1] == 1 || mM[0][1] == -1){
      x = acos(mM[2][2]);
      y = 0.0f;
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   float x = asin(-mM[1][2]);
   float y = atan2(mM[0][2], mM[2][2]);
   float z = atan2(mM[1][0], mM[1][1]);
   if(mM[1][2] == 1 || mM[1][2] == -1){
      y = atan2(-mM[2][0], mM[0][0]);
      z = 0.0f;
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   float x = atan2(-mM[1][2], mM[1][1]);
   float y = atan2(-mM[2][0], mM[0][0]);
   float z = asin(mM[1][0]);
   if(mM[1][0] == 1 || mM[1][0] == -1){
      x = acos(mM[2][2]);
      y = 0.0f;
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   float x = asin(mM[2][1]);
   float y = atan2(-mM[2][0], mM[2][2]);
   float z = atan2(-mM[0][1], mM[1][1]);
   if(mM[2][1] == 1 || mM[2][1] == -1){
      y = 0.0f;
      z = atan2(mM[1][0], mM[0][0]);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZYX() const
{  
   float x = atan2(mM[2][1], mM[2][2]);
   float y = asin(-mM[2][0]);
   float z = atan2(mM[1][0], mM[0][0]);

   if(mM[2][0] == 1 || mM[2][0] == -1){
      x = 0.0f;
      z = acos(mM[1][1]);
   }
   return Vector3(x, y, z);
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{  
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   Matrix3 Rx = Matrix3(1, 0, 0, 
                        0, cos(x), -sin(x), 
                        0, sin(x), cos(x));
   Matrix3 Ry = Matrix3(cos(y), 0, sin(y), 
                        0, 1, 0, 
                        -sin(y), 0, cos(y));
   Matrix3 Rz = Matrix3(cos(z), -sin(z), 0, 
                        sin(z), cos(z), 0, 
                        0, 0, 1);
   *this = Rx * Ry * Rz;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{  
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   Matrix3 Rx = Matrix3(1, 0, 0, 
                        0, cos(x), -sin(x), 
                        0, sin(x), cos(x));
   Matrix3 Ry = Matrix3(cos(y), 0, sin(y), 
                        0, 1, 0, 
                        -sin(y), 0, cos(y));
   Matrix3 Rz = Matrix3(cos(z), -sin(z), 0, 
                        sin(z), cos(z), 0, 
                        0, 0, 1);

   *this = Rx * Rz * Ry;
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{    
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   Matrix3 Rx = Matrix3(1, 0, 0, 
                        0, cos(x), -sin(x), 
                        0, sin(x), cos(x));
   Matrix3 Ry = Matrix3(cos(y), 0, sin(y), 
                        0, 1, 0, 
                        -sin(y), 0, cos(y));
   Matrix3 Rz = Matrix3(cos(z), -sin(z), 0, 
                        sin(z), cos(z), 0, 
                        0, 0, 1);
   *this = Ry * Rx * Rz;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{  
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   Matrix3 Rx = Matrix3(1, 0, 0, 
                        0, cos(x), -sin(x), 
                        0, sin(x), cos(x));
   Matrix3 Ry = Matrix3(cos(y), 0, sin(y), 
                        0, 1, 0, 
                        -sin(y), 0, cos(y));
   Matrix3 Rz = Matrix3(cos(z), -sin(z), 0, 
                        sin(z), cos(z), 0, 
                        0, 0, 1);

   *this = Ry * Rz * Rx;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   Matrix3 Rx = Matrix3(1, 0, 0, 
                        0, cos(x), -sin(x), 
                        0, sin(x), cos(x));
   Matrix3 Ry = Matrix3(cos(y), 0, sin(y), 
                        0, 1, 0, 
                        -sin(y), 0, cos(y));
   Matrix3 Rz = Matrix3(cos(z), -sin(z), 0, 
                        sin(z), cos(z), 0, 
                        0, 0, 1);

   *this = Rz * Rx * Ry;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   Matrix3 Rx = Matrix3(1, 0, 0, 
                        0, cos(x), -sin(x), 
                        0, sin(x), cos(x));
   Matrix3 Ry = Matrix3(cos(y), 0, sin(y), 
                        0, 1, 0, 
                        -sin(y), 0, cos(y));
   Matrix3 Rz = Matrix3(cos(z), -sin(z), 0, 
                        sin(z), cos(z), 0, 
                        0, 0, 1);

   *this = Rz * Ry * Rx;
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   float w2 = 0.25 * (m11 + m22 + m33 + 1);
   float x2 = 0.25 * (1 + m11 - m22 - m33);
   float y2 = 0.25 * (1 - m11 + m22 - m33);
   float z2 = 0.25 * (1 - m11 - m22 + m33);
   float max = std::max(w2, x2);
   max = std::max(max, y2);
   max = std::max(max, z2);
   float w,x,y,z;
   if(max == w2){
      w = sqrt(w2);
      x = 0.25 * (m32 - m23) / w;
      y = 0.25 * (m13 - m31) / w;
      z = 0.25 * (m21 - m12) / w;
   }
   else if(max == x2){
      x = sqrt(x2);
      y = 0.25 * (m21 + m12) / x;
      z = 0.25 * (m13 + m31) / x;
      w = 0.25 * (m32 - m23) / x;
   }
   else if(max == y2){
      y = sqrt(y2);
      x = 0.25 * (m21 + m12) / y;
      z = 0.25 * (m23 + m32) / y;
      w = 0.25 * (m13 - m31) / y;
   } else {
      z = sqrt(z2);
      x = 0.25 * (m13 + m31) / z;
      y = 0.25 * (m23 + m32) / z;
      w = 0.25 * (m21 - m12) / z;
   }

   angleRad = acos(w) * 2;
	axis[0] = x/sin(angleRad/2);
	axis[1] = y/sin(angleRad/2);
	axis[2] = z/sin(angleRad/2);
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   float x = axis[0];
   float y = axis[1];
   float z = axis[2];
   float cT = cos(angleRad);
   float sT = sin(angleRad);
   Matrix3 tmp = Matrix3(cT + (1-cT)*x*x,       -sT*z + (1-cT)*x*y,   y*sT + x*z*(1-cT),
                         -z*sT+(1-cT)*x*y,      cT+(1-cT)*y*y,        -x*sT+(1-cT)*y*z,
                         sT*y + (1-cT)*x*y,     -x*sT+(1-cT)*y*z,     cT + (1-cT)*z*z);
   *this = tmp;
}

}