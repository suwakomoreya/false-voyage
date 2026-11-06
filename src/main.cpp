#include "raylib.h"
#include <bits/stdc++.h>

#include "game.h"


const int screenwidth = 1920;
const int screenheight = 1080;
Vector2 mousepos = GetMousePosition();
GameState currentstate = GameState::Menu;


int main(){
    InitWindow(screenwidth,screenheight, "falsevoyage");
    SetTargetFPS(30);
    Texture2D background = LoadTexture("assets/img/lighthouse.png");
    
    while(!WindowShouldClose() && currentstate != GameState::Exit){
        mousepos = GetMousePosition();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background,0,0,WHITE);
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
