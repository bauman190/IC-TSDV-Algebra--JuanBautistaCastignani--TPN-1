#include <iostream>
#include "raylib.h"
#include <vector>
#include "math.h"

using namespace std;

struct line
{
    Vector2 start;
    Vector2 end;
};


void ballMovement(float& ballX, float& ballY, int speed, float radius);
int colLineLine(line line, vector<Vector2> vector);
float pitagoras(Vector2 p1, Vector2 p2);

int main(void)
{
    InitWindow(1366, 768, "raylib [core] example - basic window");

    float ballX = 75;
    float ballY = 150;
    int speed = 1200;
    int ballSpeed = 600;
    Color ballColor = RED;
    float ballRadius = 25;

    bool poligonClosed = false;


    vector <Vector2> Mouse;

    line right;
    line left;
    line top;
    line bot;



    while (!WindowShouldClose())
    {
        ballMovement(ballX, ballY, speed, ballRadius);

        right.start.x = ballX;
        right.start.y = ballY;
        right.end.x = GetScreenWidth();
        right.end.y = ballY;

        left.start.x = 0;
        left.start.y = ballY;
        left.end.x = ballX;
        left.end.y = ballY;

        top.start.x = ballX;
        top.start.y = 0;
        top.end.x = ballX;
        top.end.y = ballY;

        bot.start.x = ballX;
        bot.start.y = ballY;
        bot.end.x = ballX;
        bot.end.y = GetScreenHeight();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !poligonClosed) //agrego la pos del mouse y se toca el boton iz
        {
            //Mouse.push_back(GetMousePosition()); 
            if (Mouse.size() > 1 && pitagoras(Mouse[0], GetMousePosition()) < 50)
            {
                Mouse.push_back(Mouse[0]);
                poligonClosed = true;
            }
            else
            {
                Mouse.push_back(GetMousePosition());
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) // se borra lo dibujado
        {
            Mouse.clear();
            poligonClosed = false;
        }

        if (colLineLine(right, Mouse) % 2 != 0 && colLineLine(left, Mouse) % 2 != 0 && colLineLine(bot, Mouse) % 2 != 0
            && colLineLine(top, Mouse) % 2 != 0 && poligonClosed) //si en todas las dirc las lineas se cortan existe colicion
        {
            ballColor = BLUE;
        }
        else
        {
            ballColor = RED;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircle(ballX, ballY, ballRadius, ballColor);

        if (Mouse.size() > 1)
        {
            for (int j = 1; j != Mouse.size(); j++)
            {
                DrawLine(Mouse[j - 1].x, Mouse[j - 1].y, Mouse[j].x, Mouse[j].y, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ballMovement(float& ballX, float& ballY, int speed, float radius)// movimiento de la pelota
{
    if (IsKeyDown(KEY_W))
    {
        if (ballY - radius >= 0)
        {
            ballY -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_S))
    {
        if (ballY + radius <= GetScreenHeight())
        {
            ballY += speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_A))
    {
        if (ballX - radius >= 0)
        {
            ballX -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_D))
    {
        if (ballX + radius <= GetScreenWidth())
        {
            ballX += speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_UP))
    {
        if (ballY - radius >= 0)
        {
            ballY -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        if (ballY + radius <= GetScreenHeight())
        {
            ballY += speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        if (ballX - radius >= 0)
        {
            ballX -= speed * GetFrameTime();
        }
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        if (ballX + radius <= GetScreenWidth())
        {
            ballX += speed * GetFrameTime();
        }
    }
}


//http://www.jeffreythompson.org/collision-detection/line-line.php
//calcula si las lineas se cortan
int colLineLine(line line, vector<Vector2> vector)
{
    float a;
    float b;

    int counter = 0;

    if (vector.size() > 4)
    {


        for (int i = 1; i != vector.size(); i++)
        {
            a = (((vector[i].x - vector[i - 1].x) * (line.start.y - vector[i - 1].y)) - ((vector[i].y - vector[i - 1].y) * (line.start.x - vector[i - 1].x)))
                / (((vector[i].y - vector[i - 1].y) * (line.end.x - line.start.x)) - ((vector[i].x - vector[i - 1].x) * (line.end.y - line.start.y)));

            b = ((line.end.x - line.start.x) * (line.start.y - vector[i - 1].y) - (line.end.y - line.start.y) * (line.start.x - vector[i - 1].x))
                / (((vector[i].y - vector[i - 1].y) * (line.end.x - line.start.x)) - ((vector[i].x - vector[i - 1].x) * (line.end.y - line.start.y)));

            if (a >= 0 && a <= 1 && b >= 0 && b <= 1)
            {
                counter++;
            }

        }
        return counter;
    }
}

float pitagoras(Vector2 p1, Vector2 p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}