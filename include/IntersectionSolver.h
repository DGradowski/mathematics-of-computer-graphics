#pragma once
#include "Vector3f.h"

class IntersectionSolver
{
public:
    static bool FindIntersection_LineLine(const Vector3f& P1, const Vector3f& V1, const Vector3f& P2, const Vector3f& V2, float& t, float& s);

    static float AngleBetweenVectors_Deg(const Vector3f& V1, const Vector3f& V2);
    static float AngleLinePlane_Deg(const Vector3f& V_line, const Vector3f& N_plane);

    static bool FindIntersection_LinePlane(const Vector3f& P_line, const Vector3f& V_line, const Vector3f& N_plane, float D_plane, Vector3f& intersectionPoint);

    static Vector3f LineOfIntersection_Direction(const Vector3f& N1, const Vector3f& N2);
    static bool LineOfIntersection_Point(const Vector3f& N1, float D1, const Vector3f& N2, float D2, Vector3f& point);

    static int FindIntersection_LineSphere(const Vector3f& P_line, const Vector3f& V_line, const Vector3f& C_sphere, float R_sphere, Vector3f& intersect1, Vector3f& intersect2);
};