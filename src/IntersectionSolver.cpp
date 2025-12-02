#include "IntersectionSolver.h"
#include <cmath>
#include <iostream>

using namespace std;

bool IntersectionSolver::FindIntersection_LineLine(const Vector3f& P1, const Vector3f& V1, const Vector3f& P2, const Vector3f& V2, float& t, float& s)
{
    Vector3f R = P2 - P1;
    
    Vector3f V1xV2 = V1.cross(V2);
    float det = V1xV2.length() * V1xV2.length();
    
    if (std::abs(det) < 1e-6) {
        return false;
    }

    t = R.cross(V2).dotProduct(V1xV2) / det;

    s = R.cross(V1).dotProduct(V1xV2) / det;

    Vector3f Intersection1 = P1 + V1 * t;
    Vector3f Intersection2 = P2 + V2 * s;
    
    if ((Intersection1 - Intersection2).length() < 1e-5) {
        return true;
    }
    
    return false;
}

float IntersectionSolver::AngleBetweenVectors_Deg(const Vector3f& V1, const Vector3f& V2)
{
    return V1.degAngle(V2);
}

float IntersectionSolver::AngleLinePlane_Deg(const Vector3f& V_line, const Vector3f& N_plane)
{
    return 90.0f - AngleBetweenVectors_Deg(V_line, N_plane);
}

bool IntersectionSolver::FindIntersection_LinePlane(const Vector3f& P_line, const Vector3f& V_line, const Vector3f& N_plane, float D_plane, Vector3f& intersectionPoint)
{
    float dot_N_V = N_plane.dotProduct(V_line);
    
    if (std::abs(dot_N_V) < 1e-6) {
        return false;
    }
    
    float dot_N_P = N_plane.dotProduct(P_line);

    float t = -(dot_N_P + D_plane) / dot_N_V;

    intersectionPoint = P_line + V_line * t;
    return true;
}

Vector3f IntersectionSolver::LineOfIntersection_Direction(const Vector3f& N1, const Vector3f& N2)
{
    return N1.cross(N2);
}

bool IntersectionSolver::LineOfIntersection_Point(const Vector3f& N1, float D1, const Vector3f& N2, float D2, Vector3f& point)
{
    float a1 = N1.getX(), b1 = N1.getY(), c1 = -D1;
    float a2 = N2.getX(), b2 = N2.getY(), c2 = -D2;

    float det = a1 * b2 - a2 * b1;
    
    if (std::abs(det) < 1e-6) {
        return false; 
    }
    
    float x = (c1 * b2 - c2 * b1) / det;
    float y = (a1 * c2 - a2 * c1) / det;
    
    point = Vector3f(x, y, 0.0f);
    return true;
}

int IntersectionSolver::FindIntersection_LineSphere(const Vector3f& P_line, const Vector3f& V_line, const Vector3f& C_sphere, float R_sphere, Vector3f& intersect1, Vector3f& intersect2)
{
    Vector3f O = P_line - C_sphere;

    float A = V_line.dotProduct(V_line);

    float B = 2.0f * O.dotProduct(V_line);

    float C = O.dotProduct(O) - R_sphere * R_sphere;

    float delta = B * B - 4.0f * A * C;
    
    if (delta < 0.0f) {
        return 0;
    }
    
    float sqrt_delta = std::sqrt(delta);
    
    if (std::abs(delta) < 1e-6) {
        float t = -B / (2.0f * A);
        intersect1 = P_line + V_line * t;
        return 1;
    }

    float t1 = (-B - sqrt_delta) / (2.0f * A);
    float t2 = (-B + sqrt_delta) / (2.0f * A);
    
    intersect1 = P_line + V_line * t1;
    intersect2 = P_line + V_line * t2;
    
    return 2;
}