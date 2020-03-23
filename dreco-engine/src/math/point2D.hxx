#pragma once

namespace dreco
{
template <typename T>
struct point2D
{
	point2D() : x(0), y(0)
	{
	}

	point2D(const T& _v) : x(_v), y(_v)
	{
	}

	point2D(const T& _x, const T& _y) : x(_x), y(_y)
	{
	}

	point2D<T>& operator++()
	{
		++x;
		++y;
        return *this;
	}

	point2D<T>& operator--()
	{
		--x;
		--y;
        return *this;
	}

	point2D<T> operator+(const point2D<T>& _o)
	{
		return point2D<T>(this->x + _o.x, this->y + _o.y);
	}

	point2D<T> operator-(const point2D<T>& _o)
	{
		return point2D<T>(this->x - _o.x, this->y - _o.y);
	}

	point2D<T> operator+=(const point2D<T>& _o) 
	{
		this->x += _o.x;
		this->y += _o.y;
		return *this;
	}

	point2D<T> operator+=(const T& _v) 
	{
		this->x += _v;
		this->y += _v;
		return *this;
	}

	T x;
	T y;
};
}	 // namespace dreco
