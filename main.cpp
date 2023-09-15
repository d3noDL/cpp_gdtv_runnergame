#include "raylib.h"

int main() {
    const int WINDOW_WIDTH{512};
    const int WINDOW_HEIGHT{380};
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Runner Game");
    
    // Rectangle directions
    const int REC_WIDTH{50};
    const int REC_HEIGHT{80};

    int pos_y{WINDOW_HEIGHT - REC_HEIGHT};
    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        /* BEGIN LOGIC */
        
        if (IsKeyPressed(KEY_SPACE)) {
            velocity -= 10;
        }

        pos_y += velocity;

        DrawRectangle(WINDOW_WIDTH/2, pos_y, REC_WIDTH, REC_HEIGHT, BLUE);

        /* END LOGIC */
        EndDrawing();
    }
    CloseWindow(); // Shuts down the window properly.
}