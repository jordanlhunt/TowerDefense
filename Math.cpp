/*
 * Math.cpp
 *
 *  Created on: Aug 11, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "Math.h"
const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::NegativeUnitX(-1.0f, 0.0f);
const Vector2 Vector2::NegativeUnitY(0.0f, -1.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NegativeUnitX(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NegativeUnitY(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::NegativeUnitZ(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Infinity(Math::Infinity, Math::Infinity, Math::Infinity);
const Vector3 Vector3::NegativeInfinity(Math::NegativeInfinity,
                                        Math::NegativeInfinity, Math::NegativeInfinity);
static float matrix3Identity[3][3] = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
};
static float matrix4Identity[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f,
     0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};
const Matrix3 Matrix3::Identity(matrix3Identity);
const Matrix4 Matrix4::Identity(matrix4Identity);
const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);
Vector2 Vector2::Transform(const Vector2 &vec, const Matrix3 &matrix, float w)
{
    Vector2 returnValue;
    returnValue.x = vec.x * matrix.matrix[0][0] + vec.y * matrix.matrix[1][0] + w + matrix.matrix[2][0];
    returnValue.y = vec.y * matrix.matrix[0][1] + vec.y * matrix.matrix[1][1] + w * matrix.matrix[2][1];
    return returnValue;
}
Vector3 Vector3::Transform(const Vector3 &vec, const Matrix4 &matrix, float w)
{
    Vector3 returnValue;
    returnValue.x = vec.x * matrix.matrix[0][0] + vec.y + matrix.matrix[1][0] + vec.z * matrix.matrix[2][0] + w * matrix.matrix[3][0];
    returnValue.y = vec.x * matrix.matrix[0][1] + vec.y + matrix.matrix[1][1] + vec.z * matrix.matrix[2][1] + w * matrix.matrix[3][1];
    returnValue.z = vec.x * matrix.matrix[0][2] + vec.y + matrix.matrix[1][2] + vec.z * matrix.matrix[2][2] + w * matrix.matrix[3][2];
    return returnValue;
}
// This will transform the vector and renormalize the w component
Vector3 Vector3::TransformWithPerspDiv(const Vector3 &vec,
                                       const Matrix4 &matrix, float w)
{
    Vector3 returnValue;
    returnValue.x = vec.x * matrix.matrix[0][0] + vec.y * matrix.matrix[1][0] + vec.z * matrix.matrix[2][0] + w * matrix.matrix[3][0];
    returnValue.y = vec.x * matrix.matrix[0][1] + vec.y * matrix.matrix[1][1] + vec.z * matrix.matrix[2][1] + w * matrix.matrix[3][1];
    returnValue.z = vec.x * matrix.matrix[0][2] + vec.y * matrix.matrix[1][2] + vec.z * matrix.matrix[2][2] + w * matrix.matrix[3][2];
    float transformedW = vec.x * matrix.matrix[0][3] + vec.y * matrix.matrix[1][3] + vec.z * matrix.matrix[2][3] + w * matrix.matrix[3][3];
    if (!Math::IsNearZero(Math::AbsoluteValue(transformedW)))
    {
        transformedW = 1.0f / transformedW;
        returnValue *= transformedW;
    }
    return returnValue;
}
// Transform a Vector3 by a quaternion
Vector3 Vector3::Transform(const Vector3 &vec, const Quaternion &quaterion)
{
    Vector3 qV(quaterion.x, quaterion.y, quaterion.z);
    Vector3 returnValue = vec;
    returnValue += 2.0f * Vector3::CrossProduct(qV,
                                                Vector3::CrossProduct(qV, vec) + quaterion.w * vec);
    return returnValue;
}
void Matrix4::Invert()
{
    float tmp[12];
    float src[16];
    float dst[16];
    float determinant;
    src[0] = matrix[0][0];
    src[4] = matrix[0][1];
    src[8] = matrix[0][2];
    src[12] = matrix[0][3];
    src[1] = matrix[1][0];
    src[5] = matrix[1][1];
    src[9] = matrix[1][2];
    src[13] = matrix[1][3];
    src[2] = matrix[2][0];
    src[6] = matrix[2][1];
    src[10] = matrix[2][2];
    src[14] = matrix[2][3];
    src[3] = matrix[3][0];
    src[7] = matrix[3][1];
    src[11] = matrix[3][2];
    src[15] = matrix[3][3];
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];
    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    determinant = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];
    determinant = 1 / determinant;
    for (int j = 0; j < 16; j++)
    {
        dst[j] *= determinant;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = dst[i * 4 + j];
        }
    }
}
Matrix4 Matrix4::CreateFromQuaternion(const class Quaternion &quaternion)
{
    float matrix[4][4];
    matrix[0][0] = 1.0f - 2.0f * quaternion.y * quaternion.y - 2.0f * quaternion.z * quaternion.z;
    matrix[0][1] = 2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.w * quaternion.z;
    matrix[0][2] = 2.0f * quaternion.x * quaternion.z - 2.0f * quaternion.w * quaternion.y;
    matrix[0][3] = 0.0f;
    matrix[1][0] = 2.0f * quaternion.x * quaternion.y - 2.0f * quaternion.w * quaternion.z;
    matrix[1][1] = 1.0f - 2.0f * quaternion.x * quaternion.x - 2.0f * quaternion.z * quaternion.z;
    matrix[1][2] = 2.0f * quaternion.y * quaternion.z + 2.0f * quaternion.w * quaternion.x;
    matrix[1][3] = 0.0f;
    matrix[2][0] = 2.0f * quaternion.x * quaternion.z + 2.0f * quaternion.w * quaternion.y;
    matrix[2][1] = 2.0f * quaternion.y * quaternion.z - 2.0f * quaternion.w * quaternion.x;
    matrix[2][2] = 1.0f - 2.0f * quaternion.x * quaternion.x - 2.0f * quaternion.y * quaternion.y;
    matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    return Matrix4(matrix);
}
