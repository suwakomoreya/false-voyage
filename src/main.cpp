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
    ResetShip(ship,currentshift);
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
            if(shipsprocessed >= getshiftquota() && !ship.decisionmade == false){
                if(currentshift == 1){
                    currentstate = GameState::ShiftComplete;
                }
                else{
                    currentstate = GameState::Victory;
                }
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
                DrawText(TextFormat("Shift %i", currentshift),50,70,30,WHITE);
                DrawText(TextFormat("Ships: %i/%i", shipsprocessed, getshiftquota()),50,100,25,LIGHTGRAY);
                DrawText(TextFormat("Mistakes: %i", mistakes),50,140,25, RED);
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
                        shipsprocessed++;
                        incorrectships++;
                        mistakes++;
                        inspectionDecision = "Inspection timeout...";
                    }
                    float timemaining = ship.inspectiontimelimit - ship.inspectiontimer;
                    if(timemaining <0.0f){
                        timemaining = 0.0f;
                    }
                    Color timercolor = WHITE;
                    if(timemaining <= 5.0f){
                        timercolor = RED;
                    }
                    DrawText(TextFormat("Time Remaining %.1f", timemaining),50,170,25, timercolor);
                    DrawShipInspection(ship);
                }
            }
        }
        else if(currentstate == GameState::ShiftComplete){
            shiftCompleteTimer += GetFrameTime();
            Shiftcompletescreen();
            if(shiftCompleteTimer>= 2.0f &&IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)){
                currentshift = 2;
                shipsprocessed =0;
                inspectionDecision = "";
                shiftCompleteTimer = 0.0f;
                ResetShip(ship,currentshift);
                currentstate = GameState::Playing;
            }
        }
        else if(currentstate == GameState::Victory){
            DrawVictoryScreen();
            if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)){
                currentstate = GameState::Menu;
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
                currentshift =1;
                shipsprocessed =0;
                inspectionDecision = "";
                ResetShip(ship,currentshift);
                currentstate = GameState::Playing;
            }
        }
        EndDrawing();
    }
    // UnloadTexture(background);
    CloseWindow();
    return 0;
}
