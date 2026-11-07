#include "raylib.h"
#include <bits/stdc++.h>

#include "game.h"
#include "ui.h"
#include "ship.h"

const int screenwidth = 1920;
const int screenheight = 1080;
Vector2 mousepos = GetMousePosition();
GameState currentstate = GameState::Menu;


int main(){
    InitWindow(screenwidth,screenheight, "falsevoyage");
    SetExitKey(KEY_NULL);
    SetTargetFPS(30);
    Texture2D background = LoadTexture("assets/img/lighthouse.png");
    InitMenuButtons();
    Ship ship = {{-160,600,160,50}, 180.0f};
    while(!WindowShouldClose() && currentstate != GameState::Exit){
        mousepos = GetMousePosition();
        if(currentstate == GameState::Menu){
            HandleMenuInput(currentstate);
        }
        else if(currentstate == GameState::Tutorial){
            HandleTutorialInput(currentstate);
        }
        else if(currentstate == GameState::Playing){
            HandleGameInput(currentstate);
            UpdateShip(ship);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        // DrawTexture(background,0,0,WHITE);
        if(currentstate == GameState::Menu){
            DrawMainMenu();
        }
        else if(currentstate == GameState::Tutorial){
            DrawTutorialScreen();
        }
        else if(currentstate == GameState::Playing){
            DrawGameScreen();
            Drawship(ship);            
        }
        EndDrawing();
    }
    // UnloadTexture(background);
    CloseWindow();
    return 0;
}
