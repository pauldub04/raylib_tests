#include "raylib.h"
#include "raymath.h"
#include "ball.h"
#include "physics.h"
#include <stdio.h>
#include <math.h>


#define printVector2(vector_name, vec)                                  \
    if (1)                                                              \
        printf(vector_name " = {%f, %f}\n", vec.x, vec.y);



int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - bouncing ball");

    Ball ball = {
        .radius = 20,
        .position = { GetScreenWidth()/2.0f, GetScreenHeight()-20.0f},
        .velocity = Vector2Zero(),
        .color = MAROON
    };

    bool pause = 0;

    Vector2 startMousePosition = Vector2Zero();
    Vector2 velocity = Vector2Zero();
    bool isMousePressed = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;
        }

        if (!pause) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                startMousePosition = GetMousePosition();
                isMousePressed = 1;
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                velocity = Vector2Subtract(GetMousePosition(), startMousePosition);

                float length = Vector2Length(velocity);
                // 100 -> 3
                // len -> ?
                // ? = len/100*3
                length /= screenWidth*8.0f;
                length *= ball.radius/20.f;
                velocity = Vector2Scale(velocity, length);
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                ball.velocity = Vector2Negate(velocity);
                velocity = startMousePosition = Vector2Zero();
                isMousePressed = 0;
            }

            BallMove(&ball);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BallDraw(&ball);

            if (pause) {
                DrawText("PAUSED", GetScreenWidth()/2-100, GetScreenHeight()/2-50, 30, GRAY);
            }
            
            if (isMousePressed) {
                Vector2 arrow = velocity;
                float length = Vector2Length(arrow);
                arrow = Vector2Scale(arrow, 10);
                Vector2 endPos = Vector2Add(ball.position, arrow);
                // arrow = Vector2Negate(arrow);

                // float angle = asinf((float)ball.radius / length);
                // Vector2 point1 = Vector2Add(endPos, Vector2Rotate(arrow, angle));
                // printf("angle = %f\n", angle);

                DrawLineEx(ball.position, endPos, 5, GREEN);
                DrawCircleV(endPos, 7, ball.color);
                // DrawCircleV(point1, 7, YELLOW);

                // DrawTriangle(endPos, point1, ball.position, BLUE);
            }

            DrawFPS(10, 10);
        EndDrawing();
        //-----------------------------------------------------
    }

    CloseWindow();
    return 0;
}