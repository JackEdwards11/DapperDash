#include "raylib.h"

int main()
{
    // Window dimesnions
    const int windowWidth = 512;
    const int windowHeight = 380;
    // Initialize window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    // Acceleration due to gravity picels per second per second
    const int gravity = 1000;

    // Scarfy Set up
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // Nebula set up
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // Using arguments to declare rectangle rather than changing after creation
    Rectangle nebulaRec{ 0.0, 0.0, nebula.width/8, nebula.height/8 };
    // Using arguments to declare rectangle rather than changing after creation
    Vector2 nebulaPos{ windowWidth, windowHeight - nebulaRec.height };

    // nebula x velocity (pixels per second)
    int nebVelocity = -600;

    int velocity = 0;

    bool isInAir = false;
    // pixels per second
    const int jumpVelocity = -600;

    const float updateTime = 1.0/12.0;
    float runningTime = 0;


    int frame = 0; // animation frame
    // Set fps
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        // Logic
        
        // Delta time (time since last frame)
        float DT = GetFrameTime();

        isInAir = scarfyPos.y < windowHeight - scarfyRec.height;

        // Ground check
        if (!isInAir)
        {
            // On ground
            velocity = 0;
        }
        else
        {
            // In air
            velocity += gravity * DT;
        }
        // Jump on space press
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // Apply movement
        scarfyPos.y += velocity * DT;   
        nebulaPos.x  += nebVelocity * DT;

        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        

        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        // Changing texture after a certain amount of time;
        if (!isInAir)
        {
            runningTime += DT;
            if (runningTime >= updateTime)
            {
                frame++;
                runningTime = 0.0;
                if (frame > 5)
                {
                    frame = 0;
                }
                // Update animation frame
                scarfyRec.x = frame * scarfyRec.width;
            }
        }
        

        // End Logic

        EndDrawing();


    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}