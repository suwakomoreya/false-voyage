#pragma once
#include "raylib.h"
#include <string>
#include "game.h"

struct button {
    Rectangle bounds;
    std::string texts;
};

button playbutton;
button tutorialbutton;
button exitbutton;


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
    
}

void DrawMainMenu(){
    DrawText("fake voyage", GetScreenWidth()/2-MeasureText("fake voyage",60)/2,250,60,WHITE);
    DrawButton(playbutton);
    DrawButton(tutorialbutton);
    DrawButton(exitbutton);
};

void HandleMenuInput(GameState& currentstate){
    if(IsButtonClicked(playbutton)){
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

}
void HandleGameInput(GameState& currentstate){
    if(IsKeyPressed(KEY_ESCAPE)){
        currentstate = GameState::Menu;
    }
}