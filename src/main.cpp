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
            if(mistakes >= mistakelimit){
                currentstate = GameState::Gameover;
            }
            else{
                DrawGameScreen();
                DrawText(TextFormat("Mistakes: %i", mistakes),50,120,25, RED);
                Drawship(ship);
                if(ship.inspected){
                    if(!ship.decisionmade && ship.inspectiontimer < ship.inspectiontimelimit){
                        ship.inspectiontimer += GetFrameTime();
                        if(ship.inspectiontimer > ship.inspectiontimelimit){
                            ship.inspectiontimer = ship.inspectiontimelimit;
                        }
                    }
                    if(!ship.decisionmade && ship.inspectiontimer >= ship.inspectiontimelimit){
                        ship.playercorrect = false;
                        ship.decisionmade = true;
                        incorrectships++;
                        mistakes++;
                        inspectionDecision = "Inspection timeout...";
                    }
                    float timemaining = ship.inspectiontimelimit - ship.inspectiontimer;
                    if(timemaining <0.0f){
                        timemaining = 0.0f;
                    }
                    DrawText(TextFormat("Time Remaining %.1f", timemaining),50,170,25, YELLOW);
                    DrawShipInspection(ship);
                }
            }
        }
        else if(currentstate == GameState::Gameover){
            GameOverScreen();
            if(IsKeyPressed(KEY_ENTER)|| IsKeyPressed(KEY_KP_ENTER)){
                currentstate = GameState::Menu;
                
            }
            else if(IsKeyPressed(KEY_R)){
                correctships =0;
                incorrectships =0;
                mistakes =0;
                ResetShip(ship);
                currentstate = GameState::Playing;
            }
        }
        EndDrawing();
    }
    // UnloadTexture(background);
    CloseWindow();
    return 0;
}
