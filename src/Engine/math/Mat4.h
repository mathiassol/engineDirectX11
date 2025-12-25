#pragma once
#include <cmath>

namespace EngineCore {

    struct Mat4 {
        float m[4][4]{};

        static Mat4 Identity() {
            Mat4 r{};
            for (int i = 0; i < 4; ++i)
                r.m[i][i] = 1.0f;
            return r;
        }

        static Mat4 Translation(float x, float y, float z) {
            Mat4 r = Identity();
            r.m[3][0] = x;
            r.m[3][1] = y;
            r.m[3][2] = z;
            return r;
        }

        static Mat4 Scale(float x, float y, float z) {
            Mat4 r = Identity();
            r.m[0][0] = x;
            r.m[1][1] = y;
            r.m[2][2] = z;
            return r;
        }

        static Mat4 RotationXYZ(float pitch, float yaw, float roll) {
            float cp = cosf(pitch), sp = sinf(pitch);
            float cy = cosf(yaw),   sy = sinf(yaw);
            float cr = cosf(roll),  sr = sinf(roll);

            Mat4 r = Identity();

            r.m[0][0] = cy * cr;
            r.m[0][1] = sp * sy * cr - cp * sr;
            r.m[0][2] = cp * sy * cr + sp * sr;

            r.m[1][0] = cy * sr;
            r.m[1][1] = sp * sy * sr + cp * cr;
            r.m[1][2] = cp * sy * sr - sp * cr;

            r.m[2][0] = -sy;
            r.m[2][1] = sp * cy;
            r.m[2][2] = cp * cy;

            return r;
        }

        static Mat4 Perspective(float fov, float aspect, float zn, float zf) {
            Mat4 r{};
            float f = 1.0f / tanf(fov * 0.5f);

            r.m[0][0] = f / aspect;
            r.m[1][1] = f;
            r.m[2][2] = zf / (zf - zn);
            r.m[2][3] = 1.0f;
            r.m[3][2] = (-zn * zf) / (zf - zn);

            return r;
        }

        Mat4 operator*(const Mat4& o) const {
            Mat4 r{};
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    for (int k = 0; k < 4; k++)
                        r.m[i][j] += m[i][k] * o.m[k][j];
            return r;
        }
    };

}
