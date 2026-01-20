#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Wykrywanie systemu operacyjnego (Cross-platform)
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
#endif

#include "Vector3f.h"
#include "Matrix4x4.h"
#include "IntersectionSolver.h"

using namespace std;

// --- FUNKCJE POMOCNICZE (SYSTEM) ---

char getChar() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

const int WIDTH = 60;
const int HEIGHT = 60;

const Vector3f CUBE_MIN(-1.0f, -1.0f, -1.0f);
const Vector3f CUBE_MAX(1.0f, 1.0f, 1.0f);

void RenderScene(float angleX, float angleY, float angleZ, float zoomDist) {
    Vector4f startPos(0, 0, zoomDist, 1.0f);
    Vector4f startUp(0, 1, 0, 0.0f);

    Matrix4x4 rotX, rotY, rotZ;
    rotX.SetRotationX(angleX);
    rotY.SetRotationY(angleY);
    rotZ.SetRotationZ(angleZ);

    // transformation matrix = RotX * RotY * RotZ
    Matrix4x4 transformation = rotX * rotY;
    transformation = transformation * rotZ;

    Vector4f finalPos4 = transformation * startPos;
    Vector4f finalUp4 = transformation * startUp;

    Vector3f eye(finalPos4.x, finalPos4.y, finalPos4.z);
    Vector3f up(finalUp4.x, finalUp4.y, finalUp4.z);
    Vector3f target(0, 0, 0);


    Vector3f forward = (target - eye).normalized();
    
    up = up.normalized();

    Vector3f right = forward.cross(up).normalized();

    // calculating upright vector
    up = right.cross(forward).normalized();

    char buffer[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            float u = (float)x / WIDTH * 2.0f - 1.0f;
            float v = -((float)y / HEIGHT * 2.0f - 1.0f);

            Vector3f rayDir = (forward + (right * u) + (up * v)).normalized();

            if (IntersectionSolver::FindIntersection_RayBox(eye, rayDir, CUBE_MIN, CUBE_MAX)) {
                buffer[y][x] = '0';
            } else {
                buffer[y][x] = '.';
            }
        }
    }
    clearScreen();
    cout << "STEROWANIE:" << endl;
    cout << "  Obrót X/Y: [W, S, A, D]" << endl;
    cout << "  Obrót Z:   [Z, C]" << endl;
    cout << "  Zoom:      [Q, E]" << endl;
    cout << "  Wyjście:   [ESC]" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Parametry: X=" << angleX << " Y=" << angleY << " Z=" << angleZ << " Dist=" << zoomDist << endl;

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            cout << buffer[y][x];
        }
        cout << '\n';
    }
}

int main() {
    float angleX = 0.0f;
    float angleY = 0.0f;
    float angleZ = 0.0f;
    float distance = 5.0f;

    bool running = true;
    
    RenderScene(angleX, angleY, angleZ, distance);

    while (running) {
        char key = getChar();
        key = tolower(key);

        bool needRender = false;

        switch (key) {
            case 'a': angleY -= 5.0f; needRender = true; break;
            case 'd': angleY += 5.0f; needRender = true; break;
            case 'w': angleX -= 5.0f; needRender = true; break;
            case 's': angleX += 5.0f; needRender = true; break;
            case 'z': angleZ -= 5.0f; needRender = true; break;
            case 'c': angleZ += 5.0f; needRender = true; break;

            case 'q': distance += 0.5f; needRender = true; break;
            case 'e': distance -= 0.5f; needRender = true; break;
            case 27: running = false; break;
        }
        
        if (distance < 2.5f) distance = 2.5f;

        if (needRender && running) {
            RenderScene(angleX, angleY, angleZ, distance);
        }
    }

    return 0;
}