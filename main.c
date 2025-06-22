#include "raylib.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    float rx;
    float ry;
    float vx;
    float vy;
    float radius;
    int screenwidth;
    int screenheight;
} Ball;

Ball *init_ball(float rx, float ry, float vy, float vx, float radius, int screenwidth, int screenheight) {
    Ball *ball = (Ball*)malloc(sizeof(Ball));
    ball -> rx = rx;
    ball -> ry = ry;
    ball -> vy = vy;
    ball -> vx = vx;
    ball -> radius = radius;
    ball -> screenheight = screenheight;
    ball -> screenwidth = screenwidth;
    return ball;
}

void move(Ball *ball, float dt) {
    if ((ball -> rx + ball -> vx * dt < ball->radius) || (ball->rx + ball->vx * dt > ball->screenwidth - ball->radius)) ball->vx = -ball->vx;
    if ((ball -> ry + ball -> vy * dt < ball->radius) || (ball->ry + ball->vy * dt > ball->screenheight - ball->radius)) ball->vy = -ball->vy;
    ball->rx += ball->vx * dt;
    ball->ry += ball->vy * dt;
}

void draw(Ball *ball) {
    DrawCircle((int)ball->rx, (int)ball->ry, (int)ball->radius, BLACK);
}

int main() {
    const int screenWidth  = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Ball Bouncing");
    SetTargetFPS(60);
    const int max_balls = 100;

    // seed RNG
    srand((unsigned int)time(NULL));
    Ball **balls = malloc(sizeof(Ball *) * max_balls);

    for (int i = 0; i < max_balls; i++) {
        float x = rand() / (float)RAND_MAX * screenWidth;
        float y = rand() / (float)RAND_MAX * screenHeight;
        float speed = 200.0f;
        float ang = rand() / (float)RAND_MAX * 2 * PI;
        balls[i] = init_ball(x, y, cosf(ang) * speed, sinf(ang) * speed, 5.0f,screenWidth, screenHeight);
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // 1) update
        for (int i = 0; i < max_balls; i++) {
            move(balls[i], dt);
        }

        // 2) draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, DARKGRAY);

        for (int i = 0; i < max_balls; i++) {
            draw(balls[i]);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}