#pragma once
#include <math.h>
#include <Windows.h>


class KVec2
{
public:
	union
	{
		float s[2];

		struct
		{
			float x;
			float y;
		};

		struct
		{
			float m1;
			float m2;
		};
	};


public:
	KVec2() : x(.0f), y(.0f) {}
	KVec2(int _Value) : x((float)_Value), y((float)_Value) {}
	KVec2(float _Value) : x(_Value), y(_Value) {}
	KVec2(int _x, float _y) : x((float)_x), y(_y) {}
	KVec2(float _x, int _y) : x(_x), y((float)_y) {}
	KVec2(float _x, float _y) : x(_x), y(_y) {}
	KVec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	KVec2(const KVec2& _Other) 
	{
		x = _Other.x;
		y = _Other.y;
	}


public:
	const static KVec2 Zero;
	const static KVec2 Left;
	const static KVec2 Right;
	const static KVec2 Up;
	const static KVec2 Down;


	void set_vector2(const float& _X, const float& _Y) { x = _X; y = _Y; }
	float x_part() const { return x * .5f; }
	float y_part() const { return y * .5f; }
	KVec2 operator + (const KVec2& _Other)
	{
		return{ x + _Other.x, y + _Other.y };
	}

	KVec2& operator = (const KVec2& _Value)
	{
		x = _Value.x;
		y = _Value.y;
		return *this;
	}

	KVec2& operator = (const POINT& _Value)
	{
		x = (float)_Value.x;
		y = (float)_Value.y;
		return *this;
	}

	KVec2 operator + (const KVec2& _Value) const
	{
		return KVec2(x + _Value.x, y + _Value.y);
	}
	KVec2 operator * (const KVec2& _Value) const
	{
		return KVec2(x * _Value.x, y * _Value.y);
	}
	KVec2 operator - (const KVec2& _Value) const
	{
		return KVec2(x - _Value.x, y - _Value.y);
	}
	KVec2 operator / (const KVec2& _Value) const
	{
		return KVec2(x / _Value.x, y / _Value.y);
	}


	KVec2 operator + (const float& _Value) const
	{
		return KVec2(x + _Value, y + _Value);
	}
	KVec2 operator * (const float& _Value)const
	{
		return KVec2(x * _Value, y * _Value);
	}
	KVec2 operator - (const float& _Value)const
	{
		return KVec2(x - _Value, y - _Value);
	}
	KVec2 operator / (const float& _Value)const
	{
		return KVec2(x / _Value, y / _Value);
	}



	KVec2& operator += (const KVec2& _Value)
	{
		x += _Value.x;
		y += _Value.y;

		return *this;
	}
	KVec2& operator -= (const KVec2& _Value)
	{
		x -= _Value.x;
		y -= _Value.y;

		return *this;
	}
	KVec2& operator *= (const KVec2& _Value)
	{
		x *= _Value.x;
		y *= _Value.y;

		return *this;
	}
	KVec2& operator /= (const KVec2& _Value)
	{
		x /= _Value.x;
		y /= _Value.y;

		return *this;
	}

	bool operator == (const KVec2& _Value) const
	{
		return (x == _Value.x && y == _Value.y);
	}
	bool operator != (const KVec2& _Value) const
	{
		return (x != _Value.x || y != _Value.y);
	}
	bool operator >= (const KVec2& _Value) const
	{
		return (x >= _Value.x && y >= _Value.y);
	}
	bool operator <= (const KVec2& _Value) const
	{
		return (x <= _Value.x && y <= _Value.y);
	}
	bool operator > (const KVec2& _Value) const
	{
		return (x > _Value.x && y > _Value.y);
	}
	bool operator < (const KVec2& _Value) const
	{
		return (x < _Value.x && y < _Value.y);
	}

	float distance() const
	{
		return sqrtf((x) * (x)+(y) * (y));
	}

	KVec2& reverse_ref()
	{
		float Tmp = x;
		x = y;
		y = Tmp;

		return *this;
	}
	KVec2& abs()
	{
		x = fabsf(x);
		y = fabsf(y);
		return *this;
	}

	KVec2 reverse()
	{
		float Tx = x;
		float Ty = y;
		float Tmp = Tx;
		Tx = Ty;
		Ty = Tmp;

		return KVec2(Tx, Ty);
	}


	KVec2 normalize()
	{
		float Tx = x;
		float Ty = y;
		Tx /= x + y;
		Ty /= x + y;

		return KVec2(Tx, Ty);
	}

	void normalize_ref()
	{
		x /= x + y;
		y /= x + y;
	}
};
typedef KVec2 KPoint;
typedef KVec2 KSize2;
typedef KVec2 KPos2;


class KRect 
{
public:
	KPos2 Start;
	KPos2 End;
};