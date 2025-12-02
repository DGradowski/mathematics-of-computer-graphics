#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Vector3f.h"
#include "Matrix4x4.h"
#include "Quaterion.h"
#include "Vector4f.h"
#include "IntersectionSolver.h"

using namespace std;

void printResult(const string& task, const string& result) {
    cout << "==========================================================" << endl;
    cout << "ZADANIE " << task << endl;
    cout << "ROZWIAZANIE:" << endl;
    cout << result << endl;
}

int main()
{
    // Ustawienie precyzji wyświetlania
    cout << fixed << setprecision(3);

    cout << "--- Laboratorium 5: Obliczanie przeciec i katow ---" << endl;

    // ZADANIE 1
    Vector3f P1_A(-2.0f, 4.0f, 0.0f);
    Vector3f V1_A(3.0f, 1.0f, 5.0f);
    Vector3f P2_B(-2.0f, 4.0f, 0.0f);
    Vector3f V2_B(1.0f, -5.0f, 3.0f);

    float t_A, s_B;
    bool intersects1 = IntersectionSolver::FindIntersection_LineLine(P1_A, V1_A, P2_B, V2_B, t_A, s_B);

    string result1;
    if (intersects1) {
        Vector3f P_intersect = P1_A + V1_A * t_A;
        result1 = "Proste sie przecinaja.\n";
        result1 += "Parametry: t = " + to_string(t_A) + ", s = " + to_string(s_B) + "\n";
        result1 += "Punkt przeciecia P: (" + to_string(P_intersect.getX()) + ", " + to_string(P_intersect.getY()) + ", " + to_string(P_intersect.getZ()) + ")";
    } else {
        result1 = "Proste sa rownolegle lub skosne.";
    }
    printResult("1 (Przeciecie prostych)", result1);

    // ZADANIE 2
    float angle2 = IntersectionSolver::AngleBetweenVectors_Deg(V1_A, V2_B);
    string result2 = "Kat miedzy prostymi: " + to_string(angle2) + " stopni.";
    printResult("2 (Kat miedzy prostymi)", result2);

    // ZADANIE 3
    Vector3f P3_line(-2.0f, 2.0f, -1.0f);
    Vector3f V3_line(3.0f, -1.0f, 2.0f);
    Vector3f N3_plane(2.0f, 3.0f, 3.0f);
    float D3_plane = -8.0f;

    Vector3f P_intersect3;
    bool intersects3 = IntersectionSolver::FindIntersection_LinePlane(P3_line, V3_line, N3_plane, D3_plane, P_intersect3);

    string result3;
    if (intersects3) {
        result3 = "Punkt przeciecia P: (" + to_string(P_intersect3.getX()) + ", " + to_string(P_intersect3.getY()) + ", " + to_string(P_intersect3.getZ()) + ")";
    } else {
        result3 = "Prosta jest rownolegla do plaszczyzny.";
    }
    printResult("3 (Przeciecie prosta-plaszczyzna)", result3);

    // ZADANIE 4
    float angle4 = IntersectionSolver::AngleLinePlane_Deg(V3_line, N3_plane);
    string result4 = "Kat miedzy prosta a plaszczyzna: " + to_string(angle4) + " stopni.";
    printResult("4 (Kat prosta-plaszczyzna)", result4);

    // ZADANIE 5
    Vector3f N5_A(2.0f, -1.0f, 1.0f);
    float D5_A = -8.0f;
    Vector3f N5_B(4.0f, 3.0f, 1.0f);
    float D5_B = 14.0f;

    Vector3f V5_line = IntersectionSolver::LineOfIntersection_Direction(N5_A, N5_B);
    Vector3f P5_line;
    bool found_point = IntersectionSolver::LineOfIntersection_Point(N5_A, D5_A, N5_B, D5_B, P5_line);

    string result5;
    if (found_point) {
        Vector3f V5_simplified = V5_line / 2.0f;
        result5 = "Wektor kierunkowy V': (" + to_string(V5_simplified.getX()) + ", " + to_string(V5_simplified.getY()) + ", " + to_string(V5_simplified.getZ()) + ")\n";
        result5 += "Punkt na prostej P (dla z=0): (" + to_string(P5_line.getX()) + ", " + to_string(P5_line.getY()) + ", " + to_string(P5_line.getZ()) + ")\n";
        result5 += "Równania parametryczne L:\n";
        result5 += "  x = " + to_string(P5_line.getX()) + " + " + to_string(V5_simplified.getX()) + "t\n";
        result5 += "  y = " + to_string(P5_line.getY()) + " + " + to_string(V5_simplified.getY()) + "t\n";
        result5 += "  z = " + to_string(P5_line.getZ()) + " + " + to_string(V5_simplified.getZ()) + "t";
    } else {
        result5 = "Płaszczyzny są równoległe lub błąd w rozwiązywaniu (spróbuj zmienić stałą współrzędną)";
    }
    printResult("5 (Prosta przecięcia płaszczyzn)", result5);

    // ZADANIE 6
    float angle6 = IntersectionSolver::AngleBetweenVectors_Deg(N5_A, N5_B);
    string result6 = "Kat miedzy plaszczyznami: " + to_string(angle6) + " stopni.";
    printResult("6 (Kat miedzy plaszczyznami)", result6);

    // ZADANIE 7
    Vector3f A(5.0f, 5.0f, 4.0f); Vector3f Ap(10.0f, 10.0f, 6.0f);
    Vector3f B(5.0f, 5.0f, 5.0f); Vector3f Bp(10.0f, 10.0f, 3.0f);

    Vector3f V7_A = Ap - A;
    Vector3f V7_B = Bp - B;

    float t_seg, s_seg;
    bool intersects7 = IntersectionSolver::FindIntersection_LineLine(A, V7_A, B, V7_B, t_seg, s_seg);

    string result7;
    if (intersects7 && t_seg >= 0.0f && t_seg <= 1.0f && s_seg >= 0.0f && s_seg <= 1.0f) {
        Vector3f P_intersect = A + V7_A * t_seg;
        result7 = "Odcinki sie przecinaja.\n";
        result7 += "Parametry: t = " + to_string(t_seg) + ", s = " + to_string(s_seg) + "\n";
        result7 += "Punkt przeciecia P: (" + to_string(P_intersect.getX()) + ", " + to_string(P_intersect.getY()) + ", " + to_string(P_intersect.getZ()) + ")";
    } else {
        result7 = "Odcinki nie przecinaja sie (mimo że proste moga sie przecinac).";
    }
    printResult("7 (Przeciecie odcinkow)", result7);

    // ZADANIE 8
    Vector3f P1s_line(3.0f, -1.0f, -2.0f);
    Vector3f V1s_line = Vector3f(5.0f, 3.0f, -4.0f) - P1s_line;

    Vector3f C1s_sphere(0.0f, 0.0f, 0.0f);
    float R1s_sphere = sqrt(26.0f);

    Vector3f P_intersect_s1, P_intersect_s2;
    int num_intersects = IntersectionSolver::FindIntersection_LineSphere(P1s_line, V1s_line, C1s_sphere, R1s_sphere, P_intersect_s1, P_intersect_s2);

    string result1s;
    if (num_intersects == 2) {
        result1s = "Dwa punkty przeciecia:\n";
        result1s += "P1: (" + to_string(P_intersect_s1.getX()) + ", " + to_string(P_intersect_s1.getY()) + ", " + to_string(P_intersect_s1.getZ()) + ")\n";
        result1s += "P2: (" + to_string(P_intersect_s2.getX()) + ", " + to_string(P_intersect_s2.getY()) + ", " + to_string(P_intersect_s2.getZ()) + ")";
    } else if (num_intersects == 1) {
        result1s = "Jeden punkt przeciecia (styczna):\n";
        result1s += "P: (" + to_string(P_intersect_s1.getX()) + ", " + to_string(P_intersect_s1.getY()) + ", " + to_string(P_intersect_s1.getZ()) + ")";
    } else {
        result1s = "Brak punktow przeciecia.";
    }
    printResult("8 (Przeciecie prosta-sfera)", result1s);

    cout << "==========================================================" << endl;

    return 0;
}