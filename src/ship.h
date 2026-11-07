#pragma once
#include "raylib.h"
struct Ship{
    Rectangle bounds;
    float speed;
};
void UpdateShip(Ship& ship){
    ship.bounds.x += ship.speed*GetFrameTime();

    if(ship.bounds.x > GetScreenWidth()){
        ship.bounds.x = -ship.bounds.width;
    }
}
void Drawship(const Ship& ship){
    DrawRectangleRec(ship.bounds,DARKGRAY);
    DrawRectangle(ship.bounds.x +30, ship.bounds.x - 25, ship.bounds.width -60,25, GRAY);
}