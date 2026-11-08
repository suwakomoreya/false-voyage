#pragma once
#include "raylib.h"
struct Ship{
    Rectangle bounds;
    float speed;
    bool inspected = false;

    bool isfake = false;
    bool decisionmade =false;
    bool playercorrect = false;
    float resulttimer = 0.0f;
};
void UpdateShip(Ship& ship){
    if(ship.inspected) return;
    ship.bounds.x += ship.speed*GetFrameTime();
    float inspectionX = 1100.0f;
    if(ship.bounds.x >= inspectionX){
        ship.bounds.x =inspectionX;
        ship.inspected =true;
    }
}
void ResetShip(Ship& ship){
    ship.bounds.x = -ship.bounds.width;
    ship.inspected = false;

    ship.isfake = GetRandomValue(0,1) ==1;
    ship.decisionmade = false;
    ship.playercorrect = false;
    ship.resulttimer =0.0f;
}

void Drawship(const Ship& ship){
    float x = ship.bounds.x;
    float y=  ship.bounds.y;
    float w =ship.bounds.width;
    float h = ship.bounds.height;

    DrawRectangle(x+ 10, y + 10, w- 20, h-10,DARKGRAY);
    DrawTriangle({x+w-10,y+10},{x+w,y+h},{x+w-10,y+h},DARKGRAY);
    DrawRectangle(x+40,y-25,65,25,GRAY);
    for(int i=0;i<3;i++){
        DrawRectangle(x+48 + i *20,y-18,10,10,LIGHTGRAY);
    }
}
