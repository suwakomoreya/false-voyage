#pragma once
#include "raylib.h"
#include <string>
#include "game.h"
#include "ship.h"
#include <vector>
struct button {
    Rectangle bounds;
    std::string texts;
    
};
bool IsButtonClicked(const button& button);

button playbutton;
button tutorialbutton;
button exitbutton;
button realbutton;
button fakebutton;



button registrybutton;
button classificationbutton;
button closeregistrybutton;
enum class Registrystate{
    closed,
    shipregistry,
    vesselclassification
};
Registrystate registrystate = Registrystate::closed;
int selectedshipindex=-1;
int selectedvesselindex = -1;
std::vector<ShipIdentity> knownships = {
    {"Northerne BayLighte", "San Joe"},
    {"Central Bakerslite", "Mida 'o No Whe"},
    {"East Oaklits", "Crimeland"},
    {"West Pacificalis", "TCBell Cantina"},

    {"North York", "New Ballhog"},
    {"Central Kirkland", "Purifie Aqua"},
    {"East Mint", "Alto 'ids"},
    {"West Tilde", "Above Tabica"}
};
struct VesselClassification{
    std::string name;
    std::string cargo;
    std::string requests;
};
std::vector<VesselClassification> vesselclassification = {
    {"Cargo", "Industrial Supplies, Electronics"," Port Delivery, Fuel Refill"},
    {"Fishing", "Fishing nets, Fresh Catch"," Fishing Permit, Catch unloading"},
    {"Passenger", "Passenger luggage, food supplies", "Crew transfer, touring"}
};
button getregistryentrybutton(int index){
    int panelx = GetScreenWidth() -450;
    int panely = 150;
    int buttonwidth = 350;
    int buttonheight = 40;
    int buttonx = panelx+25;
    int buttony = panely + 100 + index * 48;

    button entry;
    entry.bounds = {
        (float)buttonx,
        (float)buttony,
        (float)buttonwidth,
        (float)buttonheight
    };
    entry.texts = knownships[index].name;
    return entry;
}
button getvesselentrybutton(int index){
    int panelx = GetScreenWidth()-450;
    int panely = 150;
    int buttonwidth = 350;
    int buttonheight = 50;
    int buttonx = panelx+25;
    int buttony = panely+110 + index * 65;
    button entry;
    entry.bounds = {(float)buttonx,(float)buttony,(float)buttonwidth,(float)buttonheight};
    entry.texts = vesselclassification[index].name;
    return entry;
}
void handleregistryinput(){
    if(registrystate == Registrystate::closed){
        return;
    }
    if(IsButtonClicked(closeregistrybutton)){
        registrystate = Registrystate::closed;
        selectedshipindex = -1;
        selectedvesselindex = -1;
        return;
    }
    if(registrystate == Registrystate::shipregistry){
        for(int i =0; i< knownships.size();i++){
            button entry = getregistryentrybutton(i);
            if(IsButtonClicked(entry)){
                if(selectedvesselindex = -1){
                    selectedshipindex = i;
                    break;
                }
                else{
                    selectedvesselindex =i;
                }
            }
        }
    }
    else if(registrystate == Registrystate::vesselclassification){

        for(int i = 0; i < vesselclassification.size(); i++){
        button entry = getvesselentrybutton(i);

        if(IsButtonClicked(entry)){
            if(selectedvesselindex == i){
                selectedvesselindex = -1;
            }
            else{
                selectedvesselindex = i;
            }
            break;
            }
        }
    }
}
std::string inspectionDecision = "";
int correctships = 0;
int incorrectships =0;
int mistakes =0;
int currentshift=1;
int shipsprocessed =0;
float shiftCompleteTimer = 0.0f;
int getshiftquota(){
    if(currentshift ==1){
        return 10;
    }
    else{
        return 20;
    }
}
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
void initregistrybuttons(){
    int buttonwidth = 220;
    int buttonheight = 60;
    int x = GetScreenWidth() - buttonwidth -40;
    int y= 30;
    registrybutton.bounds = {(float)x,(float)y,(float)buttonwidth, (float)buttonheight};
    registrybutton.texts = "Ship Registry";
    
    classificationbutton.bounds = {(float)x,(float)y+80,(float)buttonwidth,(float)buttonheight};
    classificationbutton.texts = "Vessel Classification";

    closeregistrybutton.bounds = {(float)(GetScreenWidth() - 80),160.0f,40.0f,40.0f};
    closeregistrybutton.texts = "X";
    registrybutton = {registrybutton.bounds, registrybutton.texts};
    classificationbutton = {classificationbutton.bounds, classificationbutton.texts};
    closeregistrybutton = {closeregistrybutton.bounds, closeregistrybutton.texts};
}

void DrawMainMenu(){
    DrawText("fake voyage", GetScreenWidth()/2-MeasureText("fake voyage",60)/2,250,60,WHITE);
    DrawButton(playbutton);
    DrawButton(tutorialbutton);
    DrawButton(exitbutton);
};

void HandleMenuInput(GameState& currentstate, Ship& ship){
    if(IsButtonClicked(playbutton)){
        registrystate = Registrystate::closed;
        selectedshipindex = -1;
        selectedvesselindex = -1;

        inspectionDecision ="";
        shiftCompleteTimer = 0.0f;
        correctships =0;
        incorrectships =0;
        mistakes=0;
        currentshift =1;
        shipsprocessed =0;

        ResetShip(ship,currentshift);
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

    DrawButton(registrybutton);
    DrawButton(classificationbutton);
}
void drawregistrysidebar(){
    if(registrystate == Registrystate::closed){
        return;
    }
    int panelx = GetScreenWidth()-450;
    int panely = 150;
    int panelwidth = 410;
    int panelheight = 750;

    DrawRectangle(panelx,panely,panelwidth,panelheight,DARKGRAY);
    DrawRectangleLines(panelx,panely,panelwidth,panelheight,WHITE);

    DrawButton(closeregistrybutton);
    if(registrystate == Registrystate::shipregistry){
        DrawText("Ship Registry", panelx+25,panely+30,28,WHITE);
        for(int i = 0; i < vesselclassification.size(); i++){
            button entry = getvesselentrybutton(i);

            Vector2 mousepos = GetMousePosition();
            bool hovering = CheckCollisionPointRec(mousepos, entry.bounds);

            Color entrycolor = (selectedvesselindex == i) ? GOLD : WHITE;

            if(hovering && selectedvesselindex != i){
                entrycolor = LIGHTGRAY;
            }

            DrawRectangleRec(entry.bounds, entrycolor);
            DrawRectangleLinesEx(entry.bounds, 2, BLACK);

            int textwidth = MeasureText(entry.texts.c_str(), 20);

            DrawText(
                entry.texts.c_str(),
                entry.bounds.x + (entry.bounds.width - textwidth) / 2,
                entry.bounds.y + 10,
                20,
                BLACK
            );
        }
        if(selectedshipindex != -1){
            int infoy = panely + 520;
            if(selectedshipindex == -1){
                DrawText("Select a ship to view its information.", panelx + 25, panely + 520, 18 ,LIGHTGRAY);
            }
            DrawText("Selected ship", panelx + 25, infoy, 20, YELLOW);
            DrawText(knownships[selectedshipindex].name.c_str(),panelx+25,infoy+30,20,WHITE);
            DrawText(("Origin: " + knownships[selectedshipindex].origin).c_str(),panelx+25,infoy+60,18,LIGHTGRAY);
        }
    }
    else if(registrystate == Registrystate::vesselclassification){
        DrawText("VesselClassification", panelx+25,panely+30,24,WHITE);
        for(int i=0;i<vesselclassification.size();i++){
            button entry = getvesselentrybutton(i);
            Color entrycolor = (selectedvesselindex == i) ? GOLD : WHITE;
            DrawRectangleRec(entry.bounds, entrycolor);
            DrawRectangleLinesEx(entry.bounds,2,BLACK);
            int textwidth = MeasureText(entry.texts.c_str(),20);
            DrawText(entry.texts.c_str(),entry.bounds.x + (entry.bounds.width - textwidth)/2, entry.bounds.y + 10, 20, BLACK);
        
            
        
        }
        if(selectedvesselindex != -1){
            int infoy = panely +400;
            if(selectedvesselindex == -1){
                DrawText("Select a vessel type to view its details", panelx+25,panely+400,18,LIGHTGRAY);
            }
            DrawText(vesselclassification[selectedvesselindex].name.c_str(),panelx+25,infoy,25,YELLOW);
            DrawText("Associated Cargo: ", panelx+25,infoy+50,20,WHITE);
            DrawText(vesselclassification[selectedvesselindex].cargo.c_str(),panelx+25,infoy+80,18,LIGHTGRAY);
            DrawText("Associated Requests:", panelx+25,infoy+130,20,WHITE);
            DrawText(vesselclassification[selectedvesselindex].requests.c_str(),panelx+25,infoy+160,18,LIGHTGRAY);

        }
    }
}

void HandleGameInput(GameState& currentstate, Ship& ship){
    if(IsKeyPressed(KEY_ESCAPE)){
        currentstate = GameState::Menu;
        inspectionDecision = "";
        registrystate = Registrystate::closed;
        selectedshipindex = -1;
        selectedvesselindex = -1;

        ResetShip(ship,currentshift);
    }
    if(IsButtonClicked(registrybutton)){
        if(registrystate== Registrystate::shipregistry){
            registrystate = Registrystate::closed;
        }
        else{
            registrystate = Registrystate::shipregistry;
            selectedvesselindex = -1;
        }
        
    }
    if(IsButtonClicked(classificationbutton)){
        if(registrystate == Registrystate::vesselclassification){
            registrystate = Registrystate::closed;
        }
        else{
            registrystate = Registrystate::vesselclassification;
            selectedshipindex = -1;
        }
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
       // DrawText("anomaly in paperwork", panelX+200,panely+280,25, RED); // REMOVE LATER
    }
    if(ship.visualanomaly){
       // DrawText("anomaly in visuala", panelX+200,panely+310,25, RED); // REMOVE LATERR
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
    DrawText(TextFormat("You reached Shift %i", currentshift), 750,380,30,WHITE);
    DrawText(TextFormat("Correct Inspections %i", correctships),750,460,30,WHITE);
    DrawText(TextFormat("Incorrect Inspections %i", incorrectships),750,520,30, WHITE);
    DrawText(TextFormat("Total Mistakes %i", mistakes),750,580,30,RED);
    DrawText("Press enter to return to menu",650,750,25,LIGHTGRAY);
    DrawText("R - Restart game",650,800,25, LIGHTGRAY);
}
void Shiftcompletescreen(){
    ClearBackground(BLACK);
    DrawText("Shift 1 COMPLETE", 620,250,60,GREEN);
    DrawText(TextFormat("Ships Processed%i/%i", shipsprocessed, getshiftquota()),700,430,30,WHITE);
    DrawText(TextFormat("Correct inspections: %i", correctships),700,490,30,WHITE);
    DrawText(TextFormat("Incorrect Inspections: %i", incorrectships),700,550,30,WHITE);
    DrawText("Press Enter to begin Shift 2", 650,800,30,LIGHTGRAY);
}
void DrawVictoryScreen(){
    ClearBackground(BLACK);
    DrawText("Day is over!", 570,220, 65, GREEN);
    DrawText("You have successsfully completed both shifts",570,350,30,WHITE);
    DrawText(TextFormat("Ships Processed %i", shipsprocessed + 10), 700,470,30,WHITE);
    DrawText(TextFormat("Correct inspections: %i", correctships), 700,530,30,WHITE);
    DrawText(TextFormat("Incorrect Inspections: %i", incorrectships), 700,590,30,WHITE);
    DrawText("Press enter to return to the menu",650,850,25,LIGHTGRAY);
}
void InspectionInput(Ship& ship){
    
    if(ship.decisionmade){
        //ship.resulttimer += GetFrameTime();
        // bool skip = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER);
        
        if(IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)){
            inspectionDecision = "";
            ResetShip(ship,currentshift);
        }

        return;
    }
   

    if(IsButtonClicked(realbutton)){
        inspectionDecision = "You authorized the ship";
        ship.playercorrect = isShipAuthentic(ship);
        ship.decisionmade = true;
        shipsprocessed++;
        if(ship.playercorrect){
            correctships++;
        }
        else{
            incorrectships++;
            if(currentshift == 2 && isShipAuthentic(ship)){
                mistakes +=2;
            }
            else{
                mistakes++;
            }
        }
    }
    else if(IsButtonClicked(fakebutton)){
        inspectionDecision = "You rejected the ship";
        ship.playercorrect = !isShipAuthentic(ship);
        ship.decisionmade = true;
        shipsprocessed++;
        if(ship.playercorrect){
            correctships++;
        }
        else{
            incorrectships++;
            if(currentshift == 2 && isShipAuthentic(ship)){
                mistakes +=2;
            }
            else{
            mistakes++;
            }
        }
        
    }
}