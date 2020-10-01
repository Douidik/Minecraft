#ifndef MINECRAFT_MATHS_H
#define MINECRAFT_MATHS_H

using DoubleVector2 = glm::dvec2;
using DoubleVector3 = glm::dvec3;
using DoubleVector4 = glm::dvec4;

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

using Coordinates2D = glm::ivec2;
using Coordinates3D = glm::ivec3;

using Matrix3 = glm::mat3;
using Matrix4 = glm::mat4;

/*
 * Contiguous structure of position, rotation, scale for Matrix 4 Generation
 */
struct Transform
{
	static Ref<Transform> Create(Vector3 _position = {0, 0, 0}, Vector3 _rotation = {0, 0, 0}, Vector3 _scale = { 1, 1, 1});
	Transform(Vector3 _position = {0, 0, 0}, Vector3 _rotation = {0, 0, 0}, Vector3 _scale = {1, 1, 1});
	Ref<Matrix4> CreateMatrix() const;

	Vector3 position, rotation, scale;
};

/* General functions */
template<typename T>
static T SafeDivision(T a, T b, T def = 0)
{
	if(b == 0)
	{
		return def;
	}
	else
	{
		return a / b;
	}
};

template<typename T>
static T SmoothStep(T x, T a, T b)
{
	x = std::clamp(SafeDivision((x - a), (a - b)), 0, 1);
	return x*x*x*(x*(x*6 - 15) + 10);
}

/* Hashing function */
static size_t HashString(const unsigned char *str, size_t size)
{
	size_t hash = 2166136261;

	for(unsigned int i = 0; i < size; i++)
	{
		hash = (hash * 16777619) ^ str[i];
	}

	return hash;
}

struct Key2D
{
	Key2D(int _x, int _y)
		: x(_x), y(_y)
	{}

	Key2D(const Coordinates2D &coords)
		: x(coords.x), y(coords.y)
	{}

	Key2D(const Coordinates3D &coords)
		: x(coords.x), y(coords.y)
	{}

	inline float SquaredLength() const { return pow(x,2) + pow(y,2); }
	inline float Length() const { return sqrt(SquaredLength()); }

	/* Type-casting */
	operator Coordinates3D() const { return Coordinates3D(x, y, 0); }
	operator Coordinates2D() const { return Coordinates2D(x, y); }
	operator Vector3() const { return Vector3(x, y, 0); }
	operator Vector2() const { return Vector2(x, y); }

	/* Arithmetic operators */
	friend Key2D operator*(Key2D a, Key2D b) { return { a.x * b.x, a.y * b.y }; }
	friend void operator*=(Key2D a, Key2D b) {a.x*=b.x; a.y*=b.y; }
	friend Key2D operator/(Key2D a, Key2D b) { return { a.x / b.x, a.y / b.y }; }
	friend void operator/=(Key2D a, Key2D b) {a.x/=b.x; a.y/=b.y; }
	friend Key2D operator+(Key2D a, Key2D b) { return { a.x + b.x, a.y + b.y }; }
	friend void operator+=(Key2D a, Key2D b) {a.x+=b.x; a.y+=b.y; }
	friend Key2D operator-(Key2D a, Key2D b) { return { a.x - b.x, a.y - b.y }; }
	friend void operator-=(Key2D a, Key2D b) {a.x-=b.x; a.y-=b.y; }
	friend Key2D operator%(Key2D a, Key2D b) { return { a.x % b.x, a.y % b.y }; }
	friend void operator%=(Key2D a, Key2D b) { a.x%=b.x; a.y%=b.y; }

	template<typename T>
	friend Key2D operator*(Key2D a, T b) { return { a.x * b, a.y * b }; }
	template<typename T>
	friend void operator*=(Key2D a, T b) {a.x*=b; a.y*=b; }
	template<typename T>
	friend Key2D operator/(Key2D a, T b) { return { a.x / b, a.y / b }; }
	template<typename T>
	friend void operator/=(Key2D a, T b) {a.x/=b; a.y/=b; }
	template<typename T>
	friend Key2D operator+(Key2D a, T b) { return { a.x + b, a.y + b }; }
	template<typename T>
	friend void operator+=(Key2D a, T b) {a.x+=b; a.y+=b; }
	template<typename T>
	friend Key2D operator-(Key2D a, T b) { return { a.x - b, a.y - b }; }
	template<typename T>
	friend void operator-=(Key2D a, T b) {a.x-=b; a.y-=b; }
	template<typename T>
	friend Key2D operator%(Key2D a, T b) { return { a.x % b, a.y % b }; }
	template<typename T>
	friend void operator%=(Key2D a, T b) { a.x%=b; a.y%=b; }

	/* Logical operators */
	friend bool operator==(const Key2D &a, const Key2D &b) { return (a.x == b.x && a.y == b.y); }
	friend bool operator< (const Key2D &a, const Key2D &b) { return (a.SquaredLength() <  b.SquaredLength()); }
	friend bool operator> (const Key2D &a, const Key2D &b) { return (a.SquaredLength() >  b.SquaredLength()); }

	int x, y;
};

struct Key3D
{
	Key3D(int _x, int _y, int _z)
		: x(_x), y(_y), z(_z)
	{}

	Key3D(const Coordinates2D &coords)
		: x(coords.x), y(coords.y), z(0)
	{}

	Key3D(const Coordinates3D &coords)
		: x(coords.x), y(coords.y), z(coords.z)
	{}

	inline float SquaredLength() const { return pow(x,2) + pow(y,2) + pow(z,2); }
	inline float Length() const { return sqrt(SquaredLength()); }

	/* Read-Only Getters */
	inline Key2D yz() const { return { y, z }; }
	inline Key2D xy() const { return { x, y }; }
	inline Key2D xz() const { return { x, z }; }

	/* Type-casting */
	operator Coordinates3D() const { return Coordinates3D(x, y, z); }
	operator Coordinates2D() const { return Coordinates2D(x, y); }
	operator Vector3() const { return Vector3(x, y, z); }
	operator Vector2() const { return Vector2(x, y); }
	operator Key2D() const { return Key2D(x,y); }

	/* Arithmetic operators */
	friend Key3D operator*(Key3D a, Key3D b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }
	friend void operator*=(Key3D a, Key3D b) {a.x*=b.x; a.y*=b.y; a.z*=b.z; }
	friend Key3D operator/(Key3D a, Key3D b) { return { a.x / b.x, a.y / b.y, a.z / b.z }; }
	friend void operator/=(Key3D a, Key3D b) {a.x/=b.x; a.y/=b.y; a.z/=b.z; }
	friend Key3D operator+(Key3D a, Key3D b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
	friend void operator+=(Key3D a, Key3D b) {a.x+=b.x; a.y+=b.y; a.z+=b.z; }
	friend Key3D operator-(Key3D a, Key3D b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
	friend void operator-=(Key3D a, Key3D b) {a.x-=b.x; a.y-=b.y; a.z-=b.z; }
	friend Key3D operator%(Key3D a, Key3D b) { return { a.x % b.x, a.y % b.y, a.z % b.z }; }
	friend void operator%=(Key3D a, Key3D b) {a.x%=b.x; a.y%=b.y; a.z%=b.z; }

	template<typename T>
	friend Key3D operator*(Key3D a, T b) { return { a.x * b, a.y * b, a.z * b }; }
	template<typename T>
	friend void operator*=(Key3D a, T b) {a.x*=b; a.y*=b; a.z*=b; }
	template<typename T>
	friend Key3D operator/(Key3D a, T b) { return { a.x / b, a.y / b, a.z / b }; }
	template<typename T>
	friend void operator/=(Key3D a, T b) {a.x/=b; a.y/=b; a.z/=b; }
	template<typename T>
	friend Key3D operator+(Key3D a, T b) { return { a.x + b, a.y + b, a.z + b }; }
	template<typename T>
	friend void operator+=(Key3D a, T b) {a.x+=b; a.y+=b; a.z+=b; }
	template<typename T>
	friend Key3D operator-(Key3D a, T b) { return { a.x - b, a.y - b, a.z - b }; }
	template<typename T>
	friend void operator-=(Key3D a, T b) {a.x-=b; a.y-=b; a.z-=b; }
	template<typename T>
	friend Key3D operator%(Key3D a, T b) { return { a.x % b, a.y % b, a.z % b }; }
	template<typename T>
	friend void operator%=(Key3D a, T b) {a.x%=b; a.y%=b; a.z%=b; }

	/* Logical operators */
	friend bool operator==(const Key3D &a, const Key3D &b) { return (a.x == b.x && a.y == b.y && a.z == b.z); }
	friend bool operator< (const Key3D &a, const Key3D &b) { return a.x < b.x || (a.x < b.x && a.y < b.y) || (a.x < b.x && a.y < b.y && a.z < b.z); }
	friend bool operator> (const Key3D &a, const Key3D &b) { return a.x > b.x || (a.x > b.x && a.y > b.y) || (a.x > b.x && a.y > b.y && a.z > b.z); }

	int x, y, z;
};

namespace std
{

	template<>
	struct hash<Key2D>
	{
		size_t operator()(const Key2D &key) const
		{
			const unsigned char *str = reinterpret_cast<const unsigned char*>(&key);
			size_t hash = HashString(str, sizeof(key));
			return hash;
		}
	};

	template<>
	struct equal_to<Key2D>
	{
		bool operator()(const Key2D &a, const Key2D &b) const
		{
			return a == b;
		}
	};

	template<>
	struct hash<Key3D>
	{
		size_t operator()(const Key3D &key) const
		{
			const unsigned char *str = reinterpret_cast<const unsigned char*>(&key);
			size_t hash = HashString(str, sizeof(key));
			return hash;
		}
	};

	template<>
	struct equal_to<Key3D>
	{
		bool operator()(const Key3D &a, const Key3D &b) const
		{
			return a == b;
		}
	};

}

#endif //MINECRAFT_MATHS_H
