#pragma once
#include "raylib.h"
#include <string>
struct button {
    Rectangle bounds;
    std::string texts;
};
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

bool IsButtonClicked(const button& button);
