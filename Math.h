/*
 * Math.h
 *
 *  Created on: Aug 11, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#include <cmath>
#include <limits>
#include <memory.h>
namespace Math
{
    const float PI = 3.1415926535f;
    const float TWOPI = PI * 2.0f;
    const float PIOVER2 = PI / 2.0f;
    const float Infinity = std::numeric_limits<float>::infinity();
    const float NegativeInfinity = -std::numeric_limits<float>::infinity();
    inline float ToRadians(float degrees)
    {
        return degrees * PI / 180.0f;
    }
    inline float ToDegrees(float radians)
    {
        return radians * 180.0f / PI;
    }
    inline bool IsNearZero(float value, float epsilon = 0.001f)
    {
        if (fabs(value) <= epsilon)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    template <typename T>
    T MaxValue(const T &a, const T &b)
    {
        return (a < b ? b : a);
    }
    template <typename T>
    T MinValue(const T &a, const T &b)
    {
        return (a < b ? a : b);
    }
    inline float AbsoluteValue(float value)
    {
        return fabs(value);
    }
    inline float Cosine(float angle)
    {
        return cosf(angle);
    }
    inline float Sine(float angle)
    {
        return sinf(angle);
    }
    inline float Tangent(float angle)
    {
        return tanf(angle);
    }
    inline float Arccosine(float value)
    {
        return acosf(value);
    }
    inline float Arctangent2(float y, float x)
    {
        return atan2f(y, x);
    }
    inline float Cotangent(float angle)
    {
        return 1.0f / Tangent(angle);
    }
    inline float LinearInterpolation(float a, float b, float f)
    {
        return (a + f * (b - a));
    }
    inline float SquareRoot(float value)
    {
        return sqrtf(value);
    }
    inline float FloatingPointRemainder(float numerator, float denomiator)
    {
        return fmod(numerator, denomiator);
    }
} // namespace Math
// 2D Vector
class Vector2
{
public:
    float x;
    float y;
    Vector2() : x(0.0f), y(0.0f)
    {
    }
    explicit Vector2(float inX, float inY) : x(inX), y(inY)
    {
    }
    // Set both components
    void Set(float inX, float inY)
    {
        this->x = inX;
        this->y = inY;
    }
    // Vector addition (a + b)
    friend Vector2 operator+(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(a.x + b.x, a.y + b.y);
    }
    // Vector subtraction (a - b)
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    // Component-wise multiplication
    // (a.x * b.x, ...)
    friend Vector2 operator*(const Vector2 &a, const Vector2 &b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }
    // Scalar multiplication
    friend Vector2 operator*(const Vector2 &vec, float scalar)
    {
        return Vector2(vec.x * scalar, vec.y * scalar);
    }
    // Scalar multiplication
    friend Vector2 operator*(float scalar, const Vector2 &vec)
    {
        return Vector2(vec.x * scalar, vec.y * scalar);
    }
    // Scalar *=
    Vector2 &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }
    // Vector +=
    Vector2 &operator+=(const Vector2 &vec)
    {
        this->x += vec.x;
        this->y += vec.y;
        return *this;
    }
    // Vector -=
    Vector2 &operator-=(const Vector2 &vec)
    {
        this->x -= vec.x;
        this->y -= vec.y;
        return *this;
    }
    // Length Squared of a vector
    float LengthSquared() const
    {
        return (this->x * this->x + this->y * this->y);
    }
    // Length of vector
    float Length() const
    {
        return (Math::SquareRoot(LengthSquared()));
    }
    // Normalize this vector
    void Normalize()
    {
        float vectorLength = Length();
        this->x /= vectorLength;
        this->y /= vectorLength;
    }
    // Normalize a passed in vector
    static Vector2 Normalize(const Vector2 &vec)
    {
        Vector2 tempVector = vec;
        tempVector.Normalize();
        return tempVector;
    }
    // Dot product between two vectors (a dot b)
    static float DotProduct(const Vector2 &a, const Vector2 &b)
    {
        return ((a.x * b.x) + (a.y * b.y));
    }
    // LinearInterpolation from A to B by f
    static Vector2 LinearInterpolation(const Vector2 &a, const Vector2 &b, float f)
    {
        return Vector2(a + f * (b - a));
    }
    // Reflect Vector about normalized
    static Vector2 Reflect(const Vector2 &vec, const Vector2 &normal)
    {
        return (vec - 2.0f * Vector2::DotProduct(vec, normal) * normal);
    }
    // Transform vec by matrix
    static Vector2 Transform(const Vector2 &vec, const class Matrix3 &matrix, float w = 1.0f);
    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 NegativeUnitX;
    static const Vector2 NegativeUnitY;
};
// 3D Vector
class Vector3
{
public:
    float x;
    float y;
    float z;
    Vector3() : x(0.0f), y(0.0f), z(0.0f)
    {
    }
    explicit Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ)
    {
    }
    // Cast to a const float pointer
    const float *GetAsFloatPtr() const
    {
        return reinterpret_cast<const float *>(&x);
    }
    // Set all three components in one line
    void Set(float inX, float inY, float inZ)
    {
        x = inX;
        y = inY;
        z = inZ;
    }
    // Vector addition (a + b)
    friend Vector3 operator+(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    // Vector subtraction (a - b)
    friend Vector3 operator-(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    // Component-wise multiplication
    friend Vector3 operator*(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    // Scalar multiplication
    friend Vector3 operator*(const Vector3 &vec, float scalar)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    // Scalar multiplication
    friend Vector3 operator*(float scalar, const Vector3 &vec)
    {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    // Scalar *=
    Vector3 &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }
    // Vector +=
    Vector3 &operator+=(const Vector3 &vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }
    // Vector -=
    Vector3 &operator-=(const Vector3 &vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }
    // Length Squared of a vector
    float LengthSquared() const
    {
        return (this->x * this->x + this->y * this->y + this->z * this->z);
    }
    // Length of vector
    float Length() const
    {
        return (Math::SquareRoot(LengthSquared()));
    }
    // Normalize this vector
    void Normalize()
    {
        float vectorLength = this->Length();
        x /= vectorLength;
        y /= vectorLength;
        z /= vectorLength;
    }
    // Normalized the proved vector
    static Vector3 Normalize(const Vector3 &vec)
    {
        Vector3 tempVector = vec;
        tempVector.Normalize();
        return tempVector;
    }
    static float DotProduct(const Vector3 &a, const Vector3 &b)
    {
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }
    // Cross Product between two vectors (a cross b)
    static Vector3 CrossProduct(const Vector3 &a, const Vector3 &b)
    {
        Vector3 tempVector;
        tempVector.x = a.y * b.z - a.z * b.y;
        tempVector.y = a.z * b.x - a.x * b.z;
        tempVector.z = a.x * b.y - a.y * b.x;
        return tempVector;
    }
    // LinearInterpolation from A to B by f
    static Vector3 LinearInterpolation(const Vector3 &a, const Vector3 &b, float f)
    {
        return Vector3(a + f * (b - a));
    }
    static Vector3 Transform(const Vector3 &vec, const class Matrix4 &mat, float w = 1.0f);
    // This will transform the vector and renormalize the w component
    static Vector3 TransformWithPerspDiv(const Vector3 &vec, const class Matrix4 &mat, float w = 1.0f);
    // Transform a Vector3 by a quaternion
    static Vector3 Transform(const Vector3 &v, const class Quaternion &q);
    static const Vector3 Zero;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    static const Vector3 NegativeUnitX;
    static const Vector3 NegativeUnitY;
    static const Vector3 NegativeUnitZ;
    static const Vector3 Infinity;
    static const Vector3 NegativeInfinity;
};
// 3x3 Matrix
class Matrix3
{
public:
    float matrix[3][3];
    Matrix3()
    {
        *this = Matrix3::Identity;
    }
    explicit Matrix3(float inMatrix[3][3])
    {
        memcpy(this->matrix, inMatrix, 9 * sizeof(float));
    }
    // Cast to a const float pointer
    const float *GetAsFloatPointer() const
    {
        return reinterpret_cast<const float *>(&this->matrix[0][0]);
    }
    // Matrix multiplication
    friend Matrix3 operator*(const Matrix3 &left, const Matrix3 &right)
    {
        Matrix3 returnValue;
        // row 0
        returnValue.matrix[0][0] = left.matrix[0][0] * right.matrix[0][0] + left.matrix[0][1] * right.matrix[1][0] + left.matrix[0][2] * right.matrix[2][0];
        returnValue.matrix[0][1] = left.matrix[0][0] * right.matrix[0][1] + left.matrix[0][1] * right.matrix[1][1] + left.matrix[0][2] * right.matrix[2][1];
        returnValue.matrix[0][2] = left.matrix[0][0] * right.matrix[0][2] + left.matrix[0][1] * right.matrix[1][2] + left.matrix[0][2] * right.matrix[2][2];
        // row 1
        returnValue.matrix[1][0] = left.matrix[1][0] * right.matrix[0][0] + left.matrix[1][1] * right.matrix[1][0] + left.matrix[1][2] * right.matrix[2][0];
        returnValue.matrix[1][1] = left.matrix[1][0] * right.matrix[0][1] + left.matrix[1][1] * right.matrix[1][1] + left.matrix[1][2] * right.matrix[2][1];
        returnValue.matrix[1][2] = left.matrix[1][0] * right.matrix[0][2] + left.matrix[1][1] * right.matrix[1][2] + left.matrix[1][2] * right.matrix[2][2];
        // row 2
        returnValue.matrix[2][0] = left.matrix[2][0] * right.matrix[0][0] + left.matrix[2][1] * right.matrix[1][0] + left.matrix[2][2] * right.matrix[2][0];
        returnValue.matrix[2][1] = left.matrix[2][0] * right.matrix[0][1] + left.matrix[2][1] * right.matrix[1][1] + left.matrix[2][2] * right.matrix[2][1];
        returnValue.matrix[2][2] = left.matrix[2][0] * right.matrix[0][2] + left.matrix[2][1] * right.matrix[1][2] + left.matrix[2][2] * right.matrix[2][2];
        return returnValue;
    }
    Matrix3 &operator*=(const Matrix3 &right)
    {
        *this = *this * right;
        return *this;
    }
    // Create a scale Matrix with a X and Y scales
    static Matrix3 CreateScale(float xScale, float yScale)
    {
        float tempMatrix[3][3] = {
            {xScale, 0.0f, 0.0f},
            {0.0f, yScale, 0.0f},
            {0.0f, 0.0f, 1.0f},
        };
        return Matrix3(tempMatrix);
    }
    static Matrix3 CreateScale(const Vector2 &scaleVector)
    {
        return CreateScale(scaleVector.x, scaleVector.y);
    }
    // Create a rotation Matrix about the Z axis
    // theta is in radians
    static Matrix3 CreateRotation(float thetaInRadians)
    {
        float tempMatrix[3][3] = {
            {Math::Cosine(thetaInRadians), Math::Sine(thetaInRadians), 0.0f},
            {-Math::Sine(thetaInRadians), Math::Cosine(thetaInRadians), 0.0},
            {0.0f, 0.0f, 1.0f},
        };
        return Matrix3(tempMatrix);
    }
    // Create a translation matrix (on the xy-plane)
    static Matrix3 CreateTranslation(const Vector2 &translation)
    {
        float tempMatrix[3][3] =
            {
                {1.0f, 0.0f, 0.0f},
                {0.0f, 1.0f, 0.0f},
                {translation.x, translation.y, 1.0f},
            };
        return Matrix3(tempMatrix);
    }
    static const Matrix3 Identity;
};
// 4x4 Matrix
class Matrix4
{
public:
    float matrix[4][4];
    Matrix4()
    {
        *this = Matrix4::Identity;
    }
    explicit Matrix4(float inMat[4][4])
    {
        memcpy(matrix, inMat, 16 * sizeof(float));
    }
    // Cast to a const float pointer
    const float *GetAsFloatPtr() const
    {
        return reinterpret_cast<const float *>(&matrix[0][0]);
    }
    // Matrix multiplication (a * b)
    friend Matrix4 operator*(const Matrix4 &a, const Matrix4 &b)
    {
        Matrix4 returnValue;
        returnValue.matrix[0][0] = a.matrix[0][0] * b.matrix[0][0] + a.matrix[0][1] * b.matrix[1][0] + a.matrix[0][2] * b.matrix[2][0] + a.matrix[0][3] * b.matrix[3][0];
        returnValue.matrix[0][1] = a.matrix[0][0] * b.matrix[0][1] + a.matrix[0][1] * b.matrix[1][1] + a.matrix[0][2] * b.matrix[2][1] + a.matrix[0][3] * b.matrix[3][1];
        returnValue.matrix[0][2] = a.matrix[0][0] * b.matrix[0][2] + a.matrix[0][1] * b.matrix[1][2] + a.matrix[0][2] * b.matrix[2][2] + a.matrix[0][3] * b.matrix[3][2];
        returnValue.matrix[0][3] = a.matrix[0][0] * b.matrix[0][3] + a.matrix[0][1] * b.matrix[1][3] + a.matrix[0][2] * b.matrix[2][3] + a.matrix[0][3] * b.matrix[3][3];
        returnValue.matrix[1][0] = a.matrix[1][0] * b.matrix[0][0] + a.matrix[1][1] * b.matrix[1][0] + a.matrix[1][2] * b.matrix[2][0] + a.matrix[1][3] * b.matrix[3][0];
        returnValue.matrix[1][1] = a.matrix[1][0] * b.matrix[0][1] + a.matrix[1][1] * b.matrix[1][1] + a.matrix[1][2] * b.matrix[2][1] + a.matrix[1][3] * b.matrix[3][1];
        returnValue.matrix[1][2] = a.matrix[1][0] * b.matrix[0][2] + a.matrix[1][1] * b.matrix[1][2] + a.matrix[1][2] * b.matrix[2][2] + a.matrix[1][3] * b.matrix[3][2];
        returnValue.matrix[1][3] = a.matrix[1][0] * b.matrix[0][3] + a.matrix[1][1] * b.matrix[1][3] + a.matrix[1][2] * b.matrix[2][3] + a.matrix[1][3] * b.matrix[3][3];
        returnValue.matrix[2][0] = a.matrix[2][0] * b.matrix[0][0] + a.matrix[2][1] * b.matrix[1][0] + a.matrix[2][2] * b.matrix[2][0] + a.matrix[2][3] * b.matrix[3][0];
        returnValue.matrix[2][1] = a.matrix[2][0] * b.matrix[0][1] + a.matrix[2][1] * b.matrix[1][1] + a.matrix[2][2] * b.matrix[2][1] + a.matrix[2][3] * b.matrix[3][1];
        returnValue.matrix[2][2] = a.matrix[2][0] * b.matrix[0][2] + a.matrix[2][1] * b.matrix[1][2] + a.matrix[2][2] * b.matrix[2][2] + a.matrix[2][3] * b.matrix[3][2];
        returnValue.matrix[2][3] = a.matrix[2][0] * b.matrix[0][3] + a.matrix[2][1] * b.matrix[1][3] + a.matrix[2][2] * b.matrix[2][3] + a.matrix[2][3] * b.matrix[3][3];
        returnValue.matrix[3][0] = a.matrix[3][0] * b.matrix[0][0] + a.matrix[3][1] * b.matrix[1][0] + a.matrix[3][2] * b.matrix[2][0] + a.matrix[3][3] * b.matrix[3][0];
        returnValue.matrix[3][1] = a.matrix[3][0] * b.matrix[0][1] + a.matrix[3][1] * b.matrix[1][1] + a.matrix[3][2] * b.matrix[2][1] + a.matrix[3][3] * b.matrix[3][1];
        returnValue.matrix[3][2] = a.matrix[3][0] * b.matrix[0][2] + a.matrix[3][1] * b.matrix[1][2] + a.matrix[3][2] * b.matrix[2][2] + a.matrix[3][3] * b.matrix[3][2];
        returnValue.matrix[3][3] = a.matrix[3][0] * b.matrix[0][3] + a.matrix[3][1] * b.matrix[1][3] + a.matrix[3][2] * b.matrix[2][3] + a.matrix[3][3] * b.matrix[3][3];
        return returnValue;
    }
    Matrix4 &operator*=(const Matrix4 &right)
    {
        *this = *this * right;
        return *this;
    }
    // Invert the matrix - super slow
    void Invert();
    // Get the translation component of the matrix
    Vector3 GetTranslation() const
    {
        return Vector3(matrix[3][0], matrix[3][1], matrix[3][2]);
    }
    // Get the X axis of the matrix (forward)
    Vector3 GetXAxis() const
    {
        return Vector3::Normalize(Vector3(matrix[0][0], matrix[0][1], matrix[0][2]));
    }
    // Get the Y axis of the matrix (left)
    Vector3 GetYAxis() const
    {
        return Vector3::Normalize(Vector3(matrix[1][0], matrix[1][1], matrix[1][2]));
    }
    // Get the Z axis of the matrix (up)
    Vector3 GetZAxis() const
    {
        return Vector3::Normalize(Vector3(matrix[2][0], matrix[2][1], matrix[2][2]));
    }
    // Extract the scale component from the matrix
    Vector3 GetScale() const
    {
        Vector3 returnValue;
        returnValue.x = Vector3(matrix[0][0], matrix[0][1], matrix[0][2]).Length();
        returnValue.y = Vector3(matrix[1][0], matrix[1][1], matrix[1][2]).Length();
        returnValue.z = Vector3(matrix[2][0], matrix[2][1], matrix[2][2]).Length();
        return returnValue;
    }
    // Create a scale matrix with x, y, and z scales
    static Matrix4 CreateScale(float xScale, float yScale, float zScale)
    {
        float temp[4][4] =
            {
                {xScale, 0.0f, 0.0f, 0.0f},
                {0.0f, yScale, 0.0f, 0.0f},
                {0.0f, 0.0f, zScale, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}};
        return Matrix4(temp);
    }
    static Matrix4 CreateScale(const Vector3 &scaleVector)
    {
        return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
    }
    // Create a scale matrix with a uniform factor
    static Matrix4 CreateScale(float scale)
    {
        return CreateScale(scale, scale, scale);
    }
    // Rotation about x-axis
    static Matrix4 CreateRotationX(float theta)
    {
        float temp[4][4] =
            {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, Math::Cosine(theta), Math::Sine(theta), 0.0f},
                {0.0f, -Math::Sine(theta), Math::Cosine(theta), 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f},
            };
        return Matrix4(temp);
    }
    // Rotation about y-axis
    static Matrix4 CreateRotationY(float theta)
    {
        float temp[4][4] =
            {
                {Math::Cosine(theta), 0.0f, -Math::Sine(theta), 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {Math::Sine(theta), 0.0f, Math::Cosine(theta), 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f},
            };
        return Matrix4(temp);
    }
    // Rotation about z-axis
    static Matrix4 CreateRotationZ(float theta)
    {
        float temp[4][4] =
            {
                {Math::Cosine(theta), Math::Sine(theta), 0.0f, 0.0f},
                {-Math::Sine(theta), Math::Cosine(theta), 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f},
            };
        return Matrix4(temp);
    }
    // Create a rotation matrix from a quaternion
    static Matrix4 CreateFromQuaternion(const class Quaternion &q);
    static Matrix4 CreateTranslation(const Vector3 &trans)
    {
        float temp[4][4] =
            {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {trans.x, trans.y, trans.z, 1.0f},
            };
        return Matrix4(temp);
    }
    static Matrix4 CreateLookAt(const Vector3 &eye, const Vector3 &target, const Vector3 &up)
    {
        Vector3 zAxis = Vector3::Normalize(target - eye);
        Vector3 xAxis = Vector3::Normalize(Vector3::CrossProduct(up, zAxis));
        Vector3 yAxis = Vector3::Normalize(Vector3::CrossProduct(zAxis, xAxis));
        Vector3 trans;
        trans.x = -Vector3::DotProduct(xAxis, eye);
        trans.y = -Vector3::DotProduct(yAxis, eye);
        trans.z = -Vector3::DotProduct(zAxis, eye);
        float temp[4][4] =
            {
                {xAxis.x, yAxis.x, zAxis.x, 0.0f},
                {xAxis.y, yAxis.y, zAxis.y, 0.0f},
                {xAxis.z, yAxis.z, zAxis.z, 0.0f},
                {trans.x, trans.y, trans.z, 1.0f},
            };
        return Matrix4(temp);
    }
    static Matrix4 CreateOrtho(float width, float height, float near, float far)
    {
        float temp[4][4] =
            {
                {2.0f / width, 0.0f, 0.0f, 0.0f},
                {0.0f, 2.0f / height, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f / (far - near), 0.0f},
                {0.0f, 0.0f, near / (near - far), 1.0f}};
        return Matrix4(temp);
    }
    static Matrix4 CreatePerspectiveFOV(float fovY, float width, float height, float near, float far)
    {
        float yScale = Math::Cotangent(fovY / 2.0f);
        float xScale = yScale * height / width;
        float temp[4][4] =
            {
                {xScale, 0.0f, 0.0f, 0.0f},
                {0.0f, yScale, 0.0f, 0.0f},
                {0.0f, 0.0f, far / (far - near), 1.0f},
                {0.0f, 0.0f, -near * far / (far - near), 0.0f}};
        return Matrix4(temp);
    }
    // Create "Simple" View-Projection Matrix from Chapter 6
    static Matrix4 CreateSimpleViewProj(float width, float height)
    {
        float temp[4][4] =
            {
                {2.0f / width, 0.0f, 0.0f, 0.0f},
                {0.0f, 2.0f / height, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 1.0f}};
        return Matrix4(temp);
    }
    static const Matrix4 Identity;
};
// (Unit) Quaternion
class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;
    Quaternion()
    {
        *this = Quaternion::Identity;
    }
    // This directly sets the quaternion components --
    // don't use for axis/angle
    explicit Quaternion(float inX, float inY, float inZ, float inW)
    {
        Set(inX, inY, inZ, inW);
    }
    // Construct the quaternion from an axis and angle
    // It is assumed that axis is already normalized,
    // and the angle is in radians
    explicit Quaternion(const Vector3 &axis, float angle)
    {
        float scalar = Math::Sine(angle / 2.0f);
        x = axis.x * scalar;
        y = axis.y * scalar;
        z = axis.z * scalar;
        w = Math::Cosine(angle / 2.0f);
    }
    // Directly set the internal components
    void Set(float inX, float inY, float inZ, float inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
    void Conjugate()
    {
        x *= -1.0f;
        y *= -1.0f;
        z *= -1.0f;
    }
    float LengthSquared() const
    {
        return (x * x + y * y + z * z + w * w);
    }
    float Length() const
    {
        return Math::SquareRoot(LengthSquared());
    }
    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }
    // Normalize the provided quaternion
    static Quaternion Normalize(const Quaternion &q)
    {
        Quaternion returnValue = q;
        returnValue.Normalize();
        return returnValue;
    }
    // Linear interpolation
    static Quaternion LinearInterpolation(const Quaternion &a, const Quaternion &b, float f)
    {
        Quaternion returnValue;
        returnValue.x = Math::LinearInterpolation(a.x, b.x, f);
        returnValue.y = Math::LinearInterpolation(a.y, b.y, f);
        returnValue.z = Math::LinearInterpolation(a.z, b.z, f);
        returnValue.w = Math::LinearInterpolation(a.w, b.w, f);
        returnValue.Normalize();
        return returnValue;
    }
    static float Dot(const Quaternion &a, const Quaternion &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }
    // Spherical Linear Interpolation
    static Quaternion SphericalLinearInterpolation(const Quaternion &a, const Quaternion &b, float f)
    {
        float rawCosm = Quaternion::Dot(a, b);
        float cosom = -rawCosm;
        if (rawCosm >= 0.0f)
        {
            cosom = rawCosm;
        }
        float scale0, scale1;
        if (cosom < 0.9999f)
        {
            const float omega = Math::Arccosine(cosom);
            const float invSin = 1.f / Math::Sine(omega);
            scale0 = Math::Sine((1.f - f) * omega) * invSin;
            scale1 = Math::Sine(f * omega) * invSin;
        }
        else
        {
            // Use linear interpolation if the quaternions
            // are collinear
            scale0 = 1.0f - f;
            scale1 = f;
        }
        if (rawCosm < 0.0f)
        {
            scale1 = -scale1;
        }
        Quaternion returnValue;
        returnValue.x = scale0 * a.x + scale1 * b.x;
        returnValue.y = scale0 * a.y + scale1 * b.y;
        returnValue.z = scale0 * a.z + scale1 * b.z;
        returnValue.w = scale0 * a.w + scale1 * b.w;
        returnValue.Normalize();
        return returnValue;
    }
    // Concatenate
    // Rotate by q FOLLOWED BY p
    static Quaternion Concatenate(const Quaternion &q, const Quaternion &p)
    {
        Quaternion returnValue;
        // Vector component is:
        // ps * qv + qs * pv + pv x qv
        Vector3 qv(q.x, q.y, q.z);
        Vector3 pv(p.x, p.y, p.z);
        Vector3 newVec = p.w * qv + q.w * pv + Vector3::CrossProduct(pv, qv);
        returnValue.x = newVec.x;
        returnValue.y = newVec.y;
        returnValue.z = newVec.z;
        // Scalar component is:
        // ps * qs - pv . qv
        returnValue.w = p.w * q.w - Vector3::DotProduct(pv, qv);
        return returnValue;
    }
    static const Quaternion Identity;
};
namespace Color
{
    static const Vector3 Black(0.0f, 0.0f, 0.0f);
    static const Vector3 White(1.0f, 1.0f, 1.0f);
    static const Vector3 Red(1.0f, 0.0f, 0.0f);
    static const Vector3 Green(0.0f, 1.0f, 0.0f);
    static const Vector3 Blue(0.0f, 0.0f, 1.0f);
    static const Vector3 Yellow(1.0f, 1.0f, 0.0f);
    static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
    static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
    static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
    static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
} // namespace Color
