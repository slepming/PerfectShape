#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>


class PerfectShape
{
private:
    double pi = 3.14159265358979323846264338327950288419716939937510;

public:

    int drawTimeDown = 10000;

    void DrawCircle(int dx, int dy) // dx - x mouse position, dy y mouse position
    {
        double radius = 300; 
        double angle = 0;
        int degree = 360;
        int stepDegree = 3; // steps

        bool firstMove = true;



        for (int i = 0; i < degree; i+=(degree / stepDegree))
        {
            angle = i * (pi / 180);
            double new_x = 823 + radius * cos(angle); // +- center, you can edit this(823 -> dx)
            double new_y = 446 + radius * sin(angle); // +- center, you can edit this(446 -> dy)
            if (firstMove)
            {
                MouseMove(static_cast<int>(new_x), static_cast<int>(new_y));
                PressLeftMouseButton(); 
                firstMove = false;
            }
            MouseMove(static_cast<int>(new_x), static_cast<int>(new_y));
            std::this_thread::sleep_for(std::chrono::nanoseconds(drawTimeDown)); 
        }
    }

    void PressLeftMouseButton()
    {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));

    }
    void ReleaseMouseButton(int button)
    {
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    void MouseMove(int x, int y) {
        POINT mousePosition;
        GetCursorPos(&mousePosition);
        POINT point;
        point.x = x;
        point.y = y;
        ClientToScreen(GetActiveWindow(), &point);
        SetCursorPos(point.x, point.y);
    }
};

int main()
{
    PerfectShape shape;
    POINT mousePosition;
    while (true)
    {
        if (GetAsyncKeyState('E') & 0x8000) exit;
        GetCursorPos(&mousePosition);
        if (GetAsyncKeyState('S') & 0x8000)
        {
            shape.DrawCircle(mousePosition.x, mousePosition.y);
        }
        std::this_thread::sleep_for(std::chrono::nanoseconds(shape.drawTimeDown));
    }



    return 0;
}