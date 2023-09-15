#include "raylib.h"

struct AnimationData {
    Rectangle rect;
    Vector2 position;
    int frame;
    float update_time;
    float running_time;
};

int main() {
    const int WINDOW_WIDTH{512};
    const int WINDOW_HEIGHT{380};
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Runner Game");
    
    // Acceleration due to gravity (pixels/frame)/frame
    const int GRAVITY{1'000};
    const int JUMP_VELOCITY{-600};
    
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimationData nebula_data {
        rect: {0.0, 0.0, nebula.width/8, nebula.height/8},
        position: {WINDOW_WIDTH, WINDOW_HEIGHT - nebula.height/8},
        frame: {0},
        update_time: {1.0/12.0},
        running_time: {0}
    };

    AnimationData *anim_data = new AnimationData();

    AnimationData nebulae[2]{
        nebula_data,
        nebula_data
    };

    for (AnimationData neb : nebulae){
        neb.frame = 2;
    }
    

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimationData scarfy_data {
        rect: {scarfy.width/6, scarfy.height, 0, 0},
        position: {WINDOW_WIDTH/2 - scarfy.width/2, WINDOW_HEIGHT - scarfy.height},
        frame: {0},
        update_time: {1.0/12.0},
        running_time: {0}
    };
    
    

    bool is_grounded{true};
    
    int velocity{0};
    int nebula_velocity{-200};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        /* BEGIN LOGIC */

        // Delta time (Time since last frame)
        const float DT{GetFrameTime()};

        // Check if on ground.
        if (scarfy_data.position.y >= WINDOW_HEIGHT - scarfy_data.rect.height) {
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
        nebula_data.position.x += nebula_velocity * DT;


        // Update scarfy position.
        scarfy_data.position.y += velocity * DT;

        // Update scarfy anim frame
        if (is_grounded) {
            // Update running time.
            scarfy_data.running_time += DT;
            if (scarfy_data.running_time >= scarfy_data.update_time) {
                scarfy_data.running_time = 0.0;

                // Update animation frame.
                scarfy_data.rect.x = scarfy_data.frame * scarfy_data.rect.width;
                scarfy_data.frame++;

                if (scarfy_data.frame > 5) {
                    scarfy_data.frame = 0;
                }
            }
        }

        // Update nebula anim frame
        nebula_data.running_time += DT;
        if (nebula_data.running_time >= nebula_data.update_time) {
            nebula_data.running_time = 0.0;
            nebula_data.rect.x = nebula_data.frame * nebula_data.rect.width;
            nebula_data.frame++;

            if (nebula_data.frame > 7) {
                nebula_data.frame = 0;
            }
        }
        
        // Draw nebula
        DrawTextureRec(nebula, nebula_data.rect, nebula_data.position, WHITE);
        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfy_data.rect, scarfy_data.position, WHITE);

        /* END LOGIC */
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow(); // Shuts down the window properly.
}