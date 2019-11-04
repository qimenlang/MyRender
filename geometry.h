#pragma once
#include <cmath>
#include <iostream>
#include <vector>
class Matrix;
template<typename t> struct Vec2
{
	t x;//x,y两个引用分别与raw 0 1进行绑定；
	t y;
	Vec2<t>() { x = y = t(); }
	Vec2<t>(t _x, t _y) { x = _x; y = _y; }
	inline Vec2<t> operator+(const Vec2<t>& V)const { return Vec2<t>(x + V.x, y + V.y); }
	inline Vec2<t> operator-(const Vec2<t>& V)const { return Vec2<t>(x - V.x, y - V.y); }
	inline Vec2<t> operator*(float f)const { return Vec2<t>(x * f, y * f); }
	t& operator[](const int i) { return i <= 0 ? x : y; }
	template<class > friend std::ostream& operator<<(std::ostream& os, Vec2<t>& v);
};
template<class t> struct Vec3
{
	t x;
	t y;
	t z;
	Vec3<t>():x(t()),y(t()),z(t()) {}
	Vec3<t>(t _x, t _y, t _z):x(_x),y(_y),z(_z) {}
	Vec3<t>(Matrix m);
	template <class u> Vec3<t>(const Vec3<u>& v);
	inline Vec3<t> operator^(const Vec3<t>& V)const { return Vec3<t>(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x); }
 	inline Vec3<t> operator+(const Vec3<t>& V)const { return Vec3<t>(x + V.x, y + V.y, z + V.z); }
	inline Vec3<t> operator-(const Vec3<t>& V)const { return Vec3<t>(x - V.x, y - V.y, z - V.z); }
	inline Vec3<t> operator*(float f)const { return Vec3<t>(x * f, y * f, z * f); }
	inline t operator*(const Vec3<t>& V)const { return x * V.x + y * V.y + z * V.z; }
	float norm() const { return std::sqrt(x * x + y * y + z * z);}
	Vec3<t>& normalize(t l = 1) { *this = (*this) * (l / norm()); return *this; }
	inline t& operator[](const int i) { return i <= 0 ? x : (1 == i ? y : z); }
	template<class > friend std::ostream& operator<<(std::ostream& os, Vec3<t>& v);
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <> template <> Vec3<int>::Vec3(const Vec3<float>& v);
template <> template <> Vec3<float>::Vec3(const Vec3<int>& v);

template<class t> std::ostream& operator<<(std::ostream& os, Vec2<t>& v)
{
	os << "(" << v.x << ", " << v.y << ")\n";
	return os;
}

template<class t> std::ostream& operator<<(std::ostream& os, Vec3<t>& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z <<")\n";
	return os;
}

const int DEFAULT_ALLOC = 4;

class Matrix
{
public:
	Matrix(int r=DEFAULT_ALLOC,int c=DEFAULT_ALLOC);
	Matrix(Vec3f v);
	inline int nrows();
	inline int ncols();

	static Matrix identity(int demensions);
	std::vector<float>& operator[](const int i);
	Matrix operator*(const Matrix& a);
	Matrix transpose();//?
	Matrix inverse();

	friend std::ostream& operator<<(std::ostream& s,Matrix& m);
private:
	std::vector<std::vector<float>> m;
	int rows, cols;
};
