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


#ifndef CK_VEC2_H
#define CK_VEC2_H

#include <math.h>

namespace ck {

class Vec2 {
public:
	float x, y;
	
	// Constructors
	Vec2();
	Vec2(const Vec2 &a);
	Vec2(float nx, float ny);
	
	Vec2 &operator =(const Vec2 &a);
	bool operator ==(const Vec2 &a) const;
	bool operator !=(const Vec2 &a) const;
	void zero();
	Vec2 operator -() const;
	Vec2 operator +(const Vec2 &a) const;
	Vec2 operator -(const Vec2 &a) const;
	Vec2 operator *(float a) const;
	Vec2 operator /(float a) const;
	Vec2 &operator +=(const Vec2 &a);
	Vec2 &operator -=(const Vec2 &a);
	Vec2 &operator *=(float a);
	Vec2 &operator /=(float a);
	void normalize();
	float operator *(const Vec2 &a) const;
};

//Nonmember functions
/*float vectorMag(const mtVec2 &a);
float vectorMagP2(const mtVec2 &a);
mtVec2 operator *(float k, const mtVec2 &v);
float distance(const mtVec2 &a, const mtVec2 &b);*/

inline float vectorMag(const Vec2 &a) {
    return sqrt(a.x*a.x + a.y*a.y);
}
inline float vectorMagP2(const Vec2 &a) {
    return (a.x*a.x + a.y*a.y);
}
inline Vec2 operator *(float k, const Vec2 &v) {
    return Vec2(k*v.x, k*v.y);
}
inline float distance(const Vec2 &a, const Vec2 &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
// maybe make it not inline
inline Vec2 vectorRot2D(const Vec2 &v, const Vec2 &rotCenter, float rotation) {
	float s = sin(rotation);
	float c = cos(rotation);
	Vec2 result;
	result.x = (v.x-rotCenter.x)*c - (v.y-rotCenter.y)*s;
	result.y = (v.x-rotCenter.x)*s + (v.y-rotCenter.y)*c;
	result += rotCenter;
	return result;
	//return mtVec2(v.x*c - v.y*s, v.x*s - v.y*c);
}

inline Vec2 vmin(const Vec2 &a, const Vec2& b) {
    Vec2 result;
    result.x = (a.x < b.x) ? a.x : b.x;
    result.y = (a.y < b.y) ? a.y : b.y;
    return result;
}

inline Vec2 vmax(const Vec2 &a, const Vec2& b) {
    Vec2 result;
    result.x = (a.x > b.x) ? a.x : b.x;
    result.y = (a.y > b.y) ? a.y : b.y;
    return result;
}

}

#endif // CK_VEC2_H
