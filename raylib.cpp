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
    
    bool Button(const char* text, Rectangle rect) {

    Vector2 mouse = GetMousePosition();

    bool hovered = CheckCollisionPointRec(mouse, rect);

    Color color = hovered ? DARKGRAY : GRAY;

    DrawRectangleRec(rect, color);

    DrawText(text, rect.x + 20, rect.y + 20, 25, WHITE);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
};
    // Close window
    CloseWindow();

    return 0;
}