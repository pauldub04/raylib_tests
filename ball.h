#pragma once
#include <math.h>
#include "raylib.h"
#include "physics.h"

typedef struct Ball {
    int radius;
    Vector2 position;
    Vector2 velocity;
    Color color;
} Ball;


void BallMove(Ball* ball) {
    ball->position.x += ball->velocity.x;
    ball->position.y += ball->velocity.y;

    ball->velocity.y += gravity;

    if (ball->position.x + ball->radius >= GetScreenWidth()) { // right wall
        ball->position.x = GetScreenWidth() - ball->radius;
        ball->velocity.x *= -bounce;
    } else if (ball->position.x - ball->radius <= 0) { // left wall
        ball->position.x = ball->radius;
        ball->velocity.x *= -bounce;
    }

    if ((ball->position.y + ball->radius >= GetScreenHeight())) { // floor
        ball->position.y = GetScreenHeight() - ball->radius;
        ball->velocity.y *= -bounce;
    } else if (ball->position.y <= ball->radius) { // ceil
        ball->position.y = ball->radius;
        ball->velocity.y *= -1.0f;
    }

    if (ball->velocity.y < 0.0f && ball->velocity.y >= -1.85) {
        ball->velocity.y = 0.0f;
    }
    if (fabs(ball->velocity.x) < 0.5f) {
        ball->velocity.x = 0.0f;
    }

    if (ball->velocity.x > 0.0f) {
        ball->velocity.x -= friction;
    } else if (ball->velocity.x < 0.0f) {
        ball->velocity.x += friction;
    }
}

void BallDraw(Ball* ball) {
    DrawCircleV(ball->position, (float)ball->radius, ball->color);
}