#include "raylib.h"

int main() {
    const int WINDOW_WIDTH{512};
    const int WINDOW_HEIGHT{380};
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Runner Game");
    
    // Acceleration due to gravity (pixels/frame)/frame
    const int GRAVITY{1};
    const int JUMP_VELOCITY{-22};
    
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfy_rec;
    Vector2 scarfy_pos;
    
    // Rectangle directions
    const int REC_WIDTH{50};
    const int REC_HEIGHT{80};

    bool is_grounded{true};

    int pos_y{WINDOW_HEIGHT - REC_HEIGHT};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        /* BEGIN LOGIC */

        // Check if on ground.
        if (pos_y >= WINDOW_HEIGHT - REC_HEIGHT) {
            // Is on ground
            velocity = 0;
            is_grounded = true;
        }
        else {
            // Apply gravity.
            velocity += GRAVITY;
            is_grounded = false;
        }

        // Check for jumping.
        if (IsKeyPressed(KEY_SPACE) && is_grounded) {
            velocity += JUMP_VELOCITY;
        }
        
        // Update position.
        pos_y += velocity;

        DrawRectangle(WINDOW_WIDTH/2, pos_y, REC_WIDTH, REC_HEIGHT, BLUE);

        /* END LOGIC */
        EndDrawing();
    }
    CloseWindow(); // Shuts down the window properly.
}