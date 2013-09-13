/*
    Copyright (c) 2011 Max Jensen <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef CK_VEC3_H
#define CK_VEC3_H

#include <math.h>

namespace ck {

class Vec3 {
public:
	float x, y, z;
	
	// Constructors
	Vec3();
	Vec3(const Vec3 &a);
	Vec3(float nx, float ny, float nz);
	
	Vec3 &operator =(const Vec3 &a);
	bool operator ==(const Vec3 &a) const;
	bool operator !=(const Vec3 &a) const;
	void zero();
	Vec3 operator -() const;
	Vec3 operator +(const Vec3 &a) const;
	Vec3 operator -(const Vec3 &a) const;
	Vec3 operator *(float a) const;
	Vec3 operator /(float a) const;
	Vec3 &operator +=(const Vec3 &a);
	Vec3 &operator -=(const Vec3 &a);
	Vec3 &operator *=(float a);
	Vec3 &operator /=(float a);
	void normalize();
	float operator *(const Vec3 &a) const;
};

//Nonmember functions
/*float vectorMag(const Vec3 &a);
float vectorMagP2(const Vec3 &a);
Vec3 operator *(float k, const Vec3 &v);
float distance(const Vec3 &a, const Vec3 &b);*/

inline float vectorMag(const Vec3 &a) {
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
/*inline float vectorMagP2(const Vec3 &a) {
    return (a.x*a.x + a.y*a.y);
}*/
inline Vec3 operator *(float k, const Vec3 &v) {
    return Vec3(k*v.x, k*v.y, k*v.z);
}
inline float distance(const Vec3 &a, const Vec3 &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
	float dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
inline float distance2D(const Vec3 &a, const Vec3 &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
inline Vec3 cross(const Vec3 &a, const Vec3 &b) {
	return Vec3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}
inline Vec3 vectorRot2D(const Vec3 &v, const Vec3 &rotCenter, float rotation) {
	float s = sin(rotation);
	float c = cos(rotation);
	Vec3 result;
	result.x = (v.x-rotCenter.x)*c - (v.y-rotCenter.y)*s + rotCenter.x;
	result.y = (v.x-rotCenter.x)*s + (v.y-rotCenter.y)*c + rotCenter.y;
	result.z = v.z;
	return result;
}

}

#endif // CK_VEC3_H
