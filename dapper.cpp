#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{

    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    // Initialize window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // Acceleration due to gravity picels per second per second
    const int gravity = 1000;

    // Scarfy Set up
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // Nebula set up
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Anim data for nebula
    AnimData nebData{ 
        { 0.0, 0.0, nebula.width/8, nebula.height/8 },  // Rectangle
        { windowDimensions[0], windowDimensions[1] - nebula.height/8 }, // Vector 2
        0, //  Frame
        1.0/12.0, // Update time
        0.0 // running Time
    };

    AnimData neb2Data{ 
        { 0.0, 0.0, nebula.width/8, nebula.height/8 },  // Rectangle
        { windowDimensions[0]*3, windowDimensions[1] - nebula.height/8 }, // Vector 2
        0, //  Frame
        1.0/16.0, // Update time
        0.0 // running Time
    };
    // nebula x velocity (pixels per second)
    int nebVelocity = -400;

    int velocity = 0;

    bool isInAir = false;
    // pixels per second
    const int jumpVelocity = -600;

    // Set fps
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        // Logic
        
        // Delta time (time since last frame)
        float DT = GetFrameTime();

        isInAir = scarfyData.pos.y < windowDimensions[1] - scarfyData.rec.height;

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
        scarfyData.pos.y += velocity * DT;   
        nebData.pos.x  += nebVelocity * DT;
        neb2Data.pos.x += nebVelocity * DT;

        // draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // draw nebula 2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        

        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        // Changing texture after a certain amount of time;
        if (!isInAir)
        {
            scarfyData.runningTime += DT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.frame++;
                scarfyData.runningTime = 0.0;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            }
        }

        // Change nebulas texture
        nebData.runningTime += DT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.frame;
            nebData.runningTime = 0;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
            nebData.rec.x = nebData.frame * nebData.rec.width;
        }

        neb2Data.runningTime += DT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.frame;
            neb2Data.runningTime = 0;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
        }

        

        // End Logic

        EndDrawing();


    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}