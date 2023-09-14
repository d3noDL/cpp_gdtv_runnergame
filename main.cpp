#include "raylib.h"

int main() {
    const int WINDOW_WIDTH{512};
    const int WINDOW_HEIGHT{380};
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Runner Game");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        /* BEGIN LOGIC */
        
        

        /* END LOGIC */
        EndDrawing();
    }
    CloseWindow(); // Shuts down the window properly.
}