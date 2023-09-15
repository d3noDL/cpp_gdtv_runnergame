#include "raylib.h"

int main() {
    const int WINDOW_WIDTH{512};
    const int WINDOW_HEIGHT{380};
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Runner Game");
    
    // Acceleration due to gravity (pixels/frame)/frame
    const int GRAVITY{1'000};
    const int JUMP_VELOCITY{-600};
    
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebula_rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebula_pos{WINDOW_WIDTH, WINDOW_HEIGHT - nebula_rec.height};

    // Nebula X velocity (pixels/second)
    int nebula_velocity{-200};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfy_rec;
        scarfy_rec.width = scarfy.width/6;
        scarfy_rec.height = scarfy.height;
        scarfy_rec.x = 0;
        scarfy_rec.y = 0;
    Vector2 scarfy_pos;
        scarfy_pos.x = WINDOW_WIDTH/2 - scarfy_rec.width/2;
        scarfy_pos.y = WINDOW_HEIGHT - scarfy_rec.height;
    
    // Animation frame
    int frame{};
    // Amount of time before we update the animation frame
    const float UPDATE_TIME{1.0/12.0};
    float running_time{};

    int nebula_frame{};
    const float NEBULA_UPDATE_TIME{1.0/12.0};
    float nebula_running_time{};

    bool is_grounded{true};
    
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        /* BEGIN LOGIC */

        // Delta time (Time since last frame)
        const float DT{GetFrameTime()};

        // Check if on ground.
        if (scarfy_pos.y >= WINDOW_HEIGHT - scarfy_rec.height) {
            // Is on ground
            velocity = 0;
            is_grounded = true;
        }
        else {
            // Apply gravity.
            velocity += GRAVITY * DT;
            is_grounded = false;
        }

        // Check for jumping.
        if (IsKeyPressed(KEY_SPACE) && is_grounded) {
            velocity += JUMP_VELOCITY;
        }
        
        
        // Update nebula position.
        nebula_pos.x += nebula_velocity * DT;


        // Update scarfy position.
        scarfy_pos.y += velocity * DT;

        // Update scarfy anim frame
        if (is_grounded) {
            // Update running time.
            running_time += DT;
            if (running_time >= UPDATE_TIME) {
                running_time = 0.0;

                // Update animation frame.
                scarfy_rec.x = frame * scarfy_rec.width;
                frame++;

                if (frame > 5) {
                    frame = 0;
                }
            }
        }

        // Update nebula anim frame
        nebula_running_time += DT;
        if (nebula_running_time >= NEBULA_UPDATE_TIME) {
            nebula_running_time = 0.0;
            nebula_rec.x = nebula_frame * nebula_rec.width;
            nebula_frame++;

            if (nebula_frame > 7) {
                nebula_frame = 0;
            }
        }
        
        // Draw nebula
        DrawTextureRec(nebula, nebula_rec, nebula_pos, WHITE);
        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfy_rec, scarfy_pos, WHITE);

        /* END LOGIC */
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow(); // Shuts down the window properly.
}