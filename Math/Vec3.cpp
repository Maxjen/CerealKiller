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


#include "Vec3.h"

namespace ck {

// Constructors
Vec3::Vec3() {}
Vec3::Vec3(const Vec3 &a) : x(a.x), y(a.y), z(a.z) {}
Vec3::Vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

Vec3 &Vec3::operator =(const Vec3 &a) {
	x = a.x; y = a.y, z = a.z;
	return *this;
}
bool Vec3::operator ==(const Vec3 &a) const {
	return x == a.x && y == a.y && z == a.z;
}
bool Vec3::operator !=(const Vec3 &a) const {
	return x != a.x || y != a.y || z != a.z;
}
void Vec3::zero() { x = y = z = 0.0f; }
Vec3 Vec3::operator -() const { return Vec3(-x,-y, -z); }
Vec3 Vec3::operator +(const Vec3 &a) const {
	return Vec3(x + a.x, y + a.y, z + a.z);
}
Vec3 Vec3::operator -(const Vec3 &a) const {
	return Vec3(x - a.x, y - a.y, z - a.z);
}
Vec3 Vec3::operator *(float a) const {
	return Vec3(x*a, y*a, z*a);
}
Vec3 Vec3::operator /(float a) const {
	float oneOverA = 1.0f / a;
	return Vec3(x*oneOverA, y*oneOverA, z*oneOverA);
}
Vec3 &Vec3::operator +=(const Vec3 &a) {
	x += a.x; y += a.y; z += a.z;
	return *this;
}
Vec3 &Vec3::operator -=(const Vec3 &a) {
	x-= a.x; y -= a.y; z -= a.z;
	return *this;
}
Vec3 &Vec3::operator *=(float a) {
	x *= a; y *= a; z *= a;
	return *this;
}
Vec3 &Vec3::operator /=(float a) {
	float oneOverA = 1.0f / a;
	x *= oneOverA; y *= oneOverA; z *= oneOverA;
	return *this;
}
void Vec3::normalize() {
	float magSq = x*x + y*y + z*z;
	if(magSq > 0.0f) {
	float oneOverMag = 1.0f / sqrt(magSq);
	x *= oneOverMag;
	y *= oneOverMag;
	z *= oneOverMag;
	}
}
float Vec3::operator *(const Vec3 &a) const {
	return x*a.x + y*a.y + z*a.z;
}

}
