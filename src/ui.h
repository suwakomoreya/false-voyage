#pragma once
#include "raylib.h"
#include <string>
#include "game.h"
#include "ship.h"
struct button {
    Rectangle bounds;
    std::string texts;
};

button playbutton;
button tutorialbutton;
button exitbutton;
button realbutton;
button fakebutton;
std::string inspectionDecision = "";
int correctships = 0;
int incorrectships =0;
int mistakes =0;
const int mistakelimit =5;
void DrawButton(const button& button){
    Vector2 mousepos = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mousepos, button.bounds);
    Color buttonColor = hovering ? DARKGRAY : GRAY;
    DrawRectangleRounded(button.bounds,0.15f,8,buttonColor);
    

    int textwidth = MeasureText(button.texts.c_str(),30);
    int textX = button.bounds.x + (button.bounds.width-textwidth)/2;
    int textY = button.bounds.y + (button.bounds.height - 30)/2;
    DrawText(button.texts.c_str(),textX,textY,30, WHITE);
};

bool IsButtonClicked(const button& button){
    Vector2 mousepos = GetMousePosition();
    bool hovering = CheckCollisionPointRec(mousepos, button.bounds);
    return hovering&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
};
void InitMenuButtons(){
    float buttonwidth = 300;
    float buttonheight =75;
    float centerx = GetScreenWidth()/2;
    float starty =450;

    playbutton = button{{centerx-buttonwidth/2,starty,buttonwidth,buttonheight},"PLAY"};
    tutorialbutton = button{{centerx-buttonwidth/2,starty+100,buttonwidth,buttonheight},"TUTORIAL"};
    exitbutton = button{{centerx-buttonwidth/2,starty+200,buttonwidth,buttonheight}, "EXIT"};
    
    realbutton ={{600,700,300,75}, "Authorize"};
    fakebutton ={{1020,700,300,75}, "Reject"};
}

void DrawMainMenu(){
    DrawText("fake voyage", GetScreenWidth()/2-MeasureText("fake voyage",60)/2,250,60,WHITE);
    DrawButton(playbutton);
    DrawButton(tutorialbutton);
    DrawButton(exitbutton);
};

void HandleMenuInput(GameState& currentstate, Ship& ship){
    if(IsButtonClicked(playbutton)){
        inspectionDecision ="";
        ResetShip(ship);
        currentstate = GameState::Playing;
    }
    if(IsButtonClicked(tutorialbutton)){
        currentstate = GameState::Tutorial;
    }
    if(IsButtonClicked(exitbutton)){
        currentstate = GameState::Exit;
    }
}

void DrawTutorialScreen(){
    DrawText("How to play", GetScreenWidth()/2 - MeasureText("How to play", 50)/2, 200, 50 , WHITE);
    DrawText("Inspect incoming ships. ", 650, 400, 30, WHITE);
    DrawText("Decide if a ship is real or not.", 500, 460, 30, WHITE);
    DrawText("Press ESC to return to menu",600,600,25,GRAY);

}

void HandleTutorialInput(GameState& currentstate){
    if(IsKeyPressed(KEY_ESCAPE)){
        currentstate = GameState::Menu;
    }
}

void DrawGameScreen(){
    DrawText("Ship Inspection", GetScreenWidth()/2 - MeasureText("Ship Inspection", 50)/2, 200 ,50 ,WHITE);
    DrawText("Waiting for incoming ships...", GetScreenWidth()/2 - MeasureText("Waiting for incoming ships...", 30)/2,450,30,GRAY);
    DrawText("Esc - Return to menu", 20, 20 ,20,GRAY);

    DrawLine(1100,350,1100,800,RED);
    DrawText("Inspection point", 1000,350,25,RED);
    DrawText(TextFormat("Correct: %d", correctships), 1550,30, 25,GREEN);
    DrawText(TextFormat("Incorrect: %d", incorrectships), 1550, 65,25, RED);
}
void HandleGameInput(GameState& currentstate, Ship& ship){
    if(IsKeyPressed(KEY_ESCAPE)){
        currentstate = GameState::Menu;
        inspectionDecision = "";
        ResetShip(ship);
    }
}

std::string ShipTypeName(ShipType type){
    if(type==Cargo){
        return "Cargo";
    }
    if(type==Fishing){
        return "Fishing";
    }
    if(type==Passenger) {
        return "Passenger";
    }
    return "unknown";

}
void DrawShipInspection(const Ship& ship){
    DrawText(TextFormat("Inspected: %d", ship.inspected), 50, 100, 25, WHITE);
    DrawText(TextFormat("Decision made: %d", ship.decisionmade), 50, 130, 25, WHITE); //delete these 2 later
    int panelX = 450;
    int panely = 250;
    int panelw = 1020;
    int panelh = 550;

    DrawRectangle(panelX, panely,panelw,panelh,DARKGRAY);
    DrawRectangleLines(panelX,panely,panelw,panelh,WHITE);
    DrawText("Vessel inspectabiliticationimaybe", panelX+30,panely + 30,35,WHITE);
    DrawLine(panelX+30,panely+85,panelX+panelw-30,panely+85,GRAY);
    DrawText(TextFormat("Vessel: %s", ship.identity.name.c_str()),panelX + 40, panely + 120,35,LIGHTGRAY);

    DrawText(TextFormat("Origin: %s", ship.identity.origin.c_str()), panelX + 40,panely+200,25,LIGHTGRAY);
    
    DrawText(TextFormat("Declared type: %s", ShipTypeName(ship.declaredtype).c_str()),panelX+40,panely +240, 25, LIGHTGRAY);
    if(ship.paperworkanomaly){
        DrawText("anomaly in paperwork", panelX+200,panely+280,25, RED); // REMOVE LATER
    }
    if(ship.visualanomaly){
        DrawText("anomaly in visuala", panelX+200,panely+310,25, RED); // REMOVE LATERR
    }

    DrawLine(panelX+30,panely+285,panelX+panelw-30,panely+285,GRAY);
    DrawText("Vessel Details",panelX+40,panely+310,20,GRAY);
    DrawText(TextFormat("Cargo: %s", ship.cargo.c_str()), panelX + 40, panely+280,25,LIGHTGRAY);
    DrawText(TextFormat("Request: %s", ship.request.c_str()), panelX +40,panely+380,22,YELLOW);

    DrawButton(realbutton);
    DrawButton(fakebutton);
    if(!inspectionDecision.empty()){
        DrawText(inspectionDecision.c_str(),750,850,30,YELLOW);
        
    }
    if(ship.decisionmade){
        if(inspectionDecision == "Inspection timeout..."){
            DrawText("TIME EXPIRED", 800,850, 35, RED);
        }
        else
        if(ship.playercorrect){
            DrawText("CORRECT",850,850,35,GREEN);

        }
        else{
            DrawText("INCORRECT!",850,850,35,RED);
        }
        DrawText("Press enter for the next ship", 650, 950,25,WHITE);

    }
}
void GameOverScreen(){
    ClearBackground(BLACK);
    DrawText("Game Over",700,250,70,RED);
    DrawText(TextFormat("Correct Inspections %i", correctships),750,450,30,WHITE);
    DrawText(TextFormat("Incorrect Inspections %i", incorrectships),750,500,30, WHITE);
    DrawText(TextFormat("Total Mistakes %i", mistakes),750,550,30,RED);
    DrawText("Press enter to return to menu",650,750,25,LIGHTGRAY);
}
void InspectionInput(Ship& ship){
    
    if(ship.decisionmade){
        //ship.resulttimer += GetFrameTime();
        // bool skip = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER);
        
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)){
            inspectionDecision = "";
            ResetShip(ship);
        }

        return;
    }
   

    if(IsButtonClicked(realbutton)){
        inspectionDecision = "You authorized the ship";
        ship.playercorrect = isShipAuthentic(ship);
        ship.decisionmade = true;
        if(ship.playercorrect){
            correctships++;
        }
        else{
            incorrectships++;
            mistakes++;
        }
    }
    else if(IsButtonClicked(fakebutton)){
        inspectionDecision = "You rejected the ship";
        ship.playercorrect = !isShipAuthentic(ship);
        ship.decisionmade = true;
        if(ship.playercorrect){
            correctships++;
        }
        else{
            incorrectships++;
            mistakes++;
        }
        
    }
}