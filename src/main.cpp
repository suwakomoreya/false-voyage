#include "raylib.h"
#include <bits/stdc++.h>

#include "game.h"
#include "ui.h"
#include "ship.h"

const int screenwidth = 1920;
const int screenheight = 1080;
// Vector2 mousepos = GetMousePosition();
GameState currentstate = GameState::Menu;


int main(){
    InitWindow(screenwidth,screenheight, "falsevoyage");
    SetExitKey(KEY_NULL);
    SetTargetFPS(30);
    Texture2D background = LoadTexture("assets/img/lighthouse.png");
    InitMenuButtons();
    Ship ship;
    ship.bounds = {-160,600,160,50};
    ship.speed = {180.0f};
    ResetShip(ship);
    while(!WindowShouldClose() && currentstate != GameState::Exit){
        // mousepos = GetMousePosition();
        if(currentstate == GameState::Menu){
            HandleMenuInput(currentstate, ship);
        }
        else if(currentstate == GameState::Tutorial){
            HandleTutorialInput(currentstate);
        }
        else if(currentstate == GameState::Playing){
            HandleGameInput(currentstate,ship);
            if(!ship.inspected){
                UpdateShip(ship);
            }
            if(ship.inspected){
                InspectionInput(ship);
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        // Draw the game
        if(currentstate == GameState::Menu){
            DrawMainMenu();
        }
        else if(currentstate == GameState::Tutorial){
            DrawTutorialScreen();
        }
        else if(currentstate == GameState::Playing){
            DrawGameScreen();
            Drawship(ship);     
            if(ship.inspected){
                DrawShipInspection(ship);
            }       
        }
        EndDrawing();
    }
    // UnloadTexture(background);
    CloseWindow();
    return 0;
}
