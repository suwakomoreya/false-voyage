#include "raylib.h"
#include <bits/stdc++.h>
const int screenwidth = 1920;
const int screenheight = 1080;


void tutorial(bool &showtutorial){
    if(IsKeyPressed(KEY_ESCAPE)){
        showtutorial = false;
    }
    
}
int main(){

    InitWindow(screenwidth, screenheight, "False Voyage");
    Texture2D background = LoadTexture("assets/img/lighthouse.png");
    SetTargetFPS(30);
    std::vector<std::string> options = {
        "Play",
        "Settings",
        "How to play",
        "Exit"  
    };

    int selected =0;
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_DOWN)){
            selected++;
            if(selected >= options.size()){
                selected =0;
            }
        }
        if(IsKeyPressed(KEY_UP)){
            selected--;
            if(selected<0){
                selected =options.size()-1;
            }

        }
        if(IsKeyPressed(KEY_ENTER)){
            if(selected==0){}
            else if(selected==1){}
            else if(selected==2){
                break;
            }
            else if(selected ==3){
                break;
            }
        }
        //draw ui
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background,0,0,WHITE);
        DrawText("False Voyage", 250,80,90,WHITE);
        for(int i=0;i<options.size();i++){
            Color color = (i==selected) ? YELLOW : GRAY;
            int y= 250+i*70;
            DrawText(
                options[i].c_str(),
                340,
                y,
                50,
                color
            );
            if(i==selected){
                DrawText(">", 300, y, 40 , YELLOW);
            }
        }
        
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
    return 0;
}