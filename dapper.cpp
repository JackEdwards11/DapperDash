#include "raylib.h"

int main()
{
    // Window dimesnionss
    const int windowWidth = 512;
    const int windowHeight = 380;
    // Initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // Rectangle dimesnions
    const int width = 50;
    const int height = 80;

    int posY = windowHeight - height;
    int velocity = -10;

    // Set fps
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        // Logic
        DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        if (IsKeyPressed(KEY_SPACE))
        {
            posY += velocity;
        }

        // End Logic

        EndDrawing();


    }
    CloseWindow();

}