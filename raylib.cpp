#include "raylib.h"

int main() {
    // Create a window
    InitWindow(800, 600, "My First Raylib Program");

    // Set FPS limit
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {

        // Drawing
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello, Raylib!", 300, 250, 30, BLACK);

        DrawCircle(400, 350, 50, RED);

        EndDrawing();
    }

    // Close window
    CloseWindow();

    return 0;
}