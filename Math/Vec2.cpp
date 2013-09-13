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


#include "Vec2.h"

namespace ck {

// Constructors
Vec2::Vec2() {}
Vec2::Vec2(const Vec2 &a) : x(a.x), y(a.y) {}
Vec2::Vec2(float nx, float ny) : x(nx), y(ny) {}

Vec2 &Vec2::operator =(const Vec2 &a) {
	x = a.x; y = a.y;
	return *this;
}
bool Vec2::operator ==(const Vec2 &a) const {
	return x == a.x && y == a.y;
}
bool Vec2::operator !=(const Vec2 &a) const {
	return x != a.x || y != a.y;
}
void Vec2::zero() { x = y = 0.0f; }
Vec2 Vec2::operator -() const { return Vec2(-x,-y); }
Vec2 Vec2::operator +(const Vec2 &a) const {
	return Vec2(x + a.x, y + a.y);
}
Vec2 Vec2::operator -(const Vec2 &a) const {
	return Vec2(x - a.x, y - a.y);
}
Vec2 Vec2::operator *(float a) const {
	return Vec2(x*a, y*a);
}
Vec2 Vec2::operator /(float a) const {
	float oneOverA = 1.0f / a;
	return Vec2(x*oneOverA, y*oneOverA);
}
Vec2 &Vec2::operator +=(const Vec2 &a) {
	x += a.x; y += a.y;
	return *this;
}
Vec2 &Vec2::operator -=(const Vec2 &a) {
	x-= a.x; y -= a.y;
	return *this;
}
Vec2 &Vec2::operator *=(float a) {
	x *= a; y *= a;
	return *this;
}
Vec2 &Vec2::operator /=(float a) {
	float oneOverA = 1.0f / a;
	x *= oneOverA; y *= oneOverA;
	return *this;
}
void Vec2::normalize() {
	float magSq = x*x + y*y;
	if(magSq > 0.0f) {
	float oneOverMag = 1.0f / sqrt(magSq);
	x *= oneOverMag;
	y *= oneOverMag;
	}
}
float Vec2::operator *(const Vec2 &a) const {
	return x*a.x + y*a.y;
}

//Nonmember functions
/*inline float vectorMag(const Vec2 &a) {
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
}*/

}
