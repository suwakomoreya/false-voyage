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
const int registrypanely = 190;
int registrypanelx(){
    return GetScreenWidth() - 450;
}
void DrawTextCentered(const char* text, int y, int fontsize, Color color){
    DrawText(text, GetScreenWidth()/2 - MeasureText(text, fontsize)/2, y, fontsize, color);
}
void DrawTextCenteredAt(const char* text, int centerx, int y, int fontsize, Color color){
    DrawText(text, centerx - MeasureText(text, fontsize)/2, y, fontsize, color);
}
button getregistryentrybutton(int index){
    int panelx = registrypanelx();
    int panely = registrypanely;
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
    int panelx = registrypanelx();
    int panely = registrypanely;
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
                if(selectedshipindex == i){
                    selectedshipindex = -1;
                }
                else{
                    selectedshipindex = i;
                }
                break;
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
    

    int fontsize = 30;
    if(fontsize > button.bounds.height - 10){
        fontsize = button.bounds.height - 10;
    }
    while(fontsize > 10 && MeasureText(button.texts.c_str(), fontsize) > button.bounds.width - 20){
        fontsize--;
    }
    int textwidth = MeasureText(button.texts.c_str(),fontsize);
    int textX = button.bounds.x + (button.bounds.width-textwidth)/2;
    int textY = button.bounds.y + (button.bounds.height - fontsize)/2;
    DrawText(button.texts.c_str(),textX,textY,fontsize, WHITE);
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
    int buttonwidth = 280;
    int buttonheight = 60;
    int x = GetScreenWidth() - buttonwidth -40;
    int y= 30;
    registrybutton.bounds = {(float)x,(float)y,(float)buttonwidth, (float)buttonheight};
    registrybutton.texts = "Ship Registry";
    
    classificationbutton.bounds = {(float)x,(float)y+80,(float)buttonwidth,(float)buttonheight};
    classificationbutton.texts = "Vessel Classification";

    closeregistrybutton.bounds = {(float)(GetScreenWidth() - 80),(float)(registrypanely + 10),40.0f,40.0f};
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
    int y = 70;
    auto heading = [&](const char* text){
        y += 25;
        DrawText(text, GetScreenWidth()/2 - MeasureText(text, 32)/2, y, 32, YELLOW);
        y += 48;
    };
    auto line = [&](const char* text){
        DrawText(text, GetScreenWidth()/2 - MeasureText(text, 26)/2, y, 26, WHITE);
        y += 38;
    };

    DrawText("How to play", GetScreenWidth()/2 - MeasureText("How to play", 50)/2, y, 50, WHITE);
    y += 60;

    heading("YOUR JOB");
    line("You are the harbor inspector. Ships sail in from the left and stop at the red inspection line.");
    line("Check each ship, then click Authorize if it is real or Reject if it is fake.");

    heading("SPOTTING A FAKE");
    line("The inspection panel shows the ship's name, origin, declared type, cargo and request.");
    line("Watch the ship as it sails in. Its hull color shows what it really is:");
    line("Gray = Cargo     Blue = Fishing     White = Passenger");
    line("If the hull color does not match the declared type, the paperwork is fake.");
    line("A red hull means the ship itself is fake.");

    heading("TOOLS");
    line("Ship Registry lists every known ship and its home port.");
    line("Vessel Classification lists the cargo and requests each ship type should have.");
    line("Close the registry panel before you click Authorize or Reject.");

    heading("RULES");
    line("Each ship has a time limit. Running out of time counts as a mistake.");
    line("Shift 1 has 10 ships and Shift 2 has 20. Finish both shifts to win.");
    line("5 mistakes ends the game. In Shift 2, rejecting a real ship counts as 2 mistakes.");
    line("After each decision, press Enter for the next ship.");

    DrawText("Press ESC to return to menu", GetScreenWidth()/2 - MeasureText("Press ESC to return to menu", 25)/2, 1015, 25, GRAY);
}

void HandleTutorialInput(GameState& currentstate){
    if(IsKeyPressed(KEY_ESCAPE)){
        currentstate = GameState::Menu;
    }
}

void DrawGameScreen(){
    DrawText("Ship Inspection", GetScreenWidth()/2 - MeasureText("Ship Inspection", 50)/2, 200 ,50 ,WHITE);
    DrawTextCentered("Waiting for incoming ships...", 290, 30, GRAY);
    DrawText("Esc - Return to menu", 20, 20 ,20,GRAY);

    DrawLine(1100,395,1100,920,RED);
    DrawText("Inspection point", 1100 - MeasureText("Inspection point", 25)/2, 360, 25, RED);

    int counterright = (int)registrybutton.bounds.x - 30;
    const char* correcttext = TextFormat("Correct: %d", correctships);
    DrawText(correcttext, counterright - MeasureText(correcttext, 25), 30, 25, GREEN);
    const char* incorrecttext = TextFormat("Incorrect: %d", incorrectships);
    DrawText(incorrecttext, counterright - MeasureText(incorrecttext, 25), 65, 25, RED);

    DrawButton(registrybutton);
    DrawButton(classificationbutton);
}
void drawregistrysidebar(){
    if(registrystate == Registrystate::closed){
        return;
    }
    int panelx = registrypanelx();
    int panely = registrypanely;
    int panelwidth = 410;
    int panelheight = 750;

    DrawRectangle(panelx,panely,panelwidth,panelheight,DARKGRAY);
    DrawRectangleLines(panelx,panely,panelwidth,panelheight,WHITE);

    DrawButton(closeregistrybutton);
    if(registrystate == Registrystate::shipregistry){
        DrawText("Ship Registry", panelx+25,panely+30,28,WHITE);
        for(int i = 0; i < knownships.size(); i++){
            button entry = getregistryentrybutton(i);

            Vector2 mousepos = GetMousePosition();
            bool hovering = CheckCollisionPointRec(mousepos, entry.bounds);

            Color entrycolor = (selectedshipindex == i) ? GOLD : WHITE;

            if(hovering && selectedshipindex != i){
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
        int infoy = panely + 520;
        if(selectedshipindex == -1){
            DrawText("Select a ship to view its information.", panelx + 25, infoy, 18 ,LIGHTGRAY);
        }
        else{
            DrawText("Selected ship", panelx + 25, infoy, 20, YELLOW);
            DrawText(knownships[selectedshipindex].name.c_str(),panelx+25,infoy+30,20,WHITE);
            DrawText(("Origin: " + knownships[selectedshipindex].origin).c_str(),panelx+25,infoy+60,18,LIGHTGRAY);
        }
    }
    else if(registrystate == Registrystate::vesselclassification){
        DrawText("Vessel Classification", panelx+25,panely+30,24,WHITE);
        for(int i=0;i<vesselclassification.size();i++){
            button entry = getvesselentrybutton(i);
            Color entrycolor = (selectedvesselindex == i) ? GOLD : WHITE;
            DrawRectangleRec(entry.bounds, entrycolor);
            DrawRectangleLinesEx(entry.bounds,2,BLACK);
            int textwidth = MeasureText(entry.texts.c_str(),20);
            DrawText(entry.texts.c_str(),entry.bounds.x + (entry.bounds.width - textwidth)/2, entry.bounds.y + 10, 20, BLACK);
        
            
        
        }
        int infoy = panely +400;
        if(selectedvesselindex == -1){
            DrawText("Select a vessel type to view its details", panelx+25,infoy,18,LIGHTGRAY);
        }
        else{
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
    DrawText(TextFormat("Cargo: %s", ship.cargo.c_str()), panelX + 40, panely+340,25,LIGHTGRAY);
    DrawText(TextFormat("Request: %s", ship.request.c_str()), panelX +40,panely+380,22,YELLOW);

    DrawButton(realbutton);
    DrawButton(fakebutton);
    if(!inspectionDecision.empty()){
        DrawTextCenteredAt(inspectionDecision.c_str(), 760, 820, 30, YELLOW);
    }
    if(ship.decisionmade){
        if(inspectionDecision == "Inspection timeout..."){
            DrawTextCenteredAt("TIME EXPIRED", 760, 865, 35, RED);
        }
        else if(ship.playercorrect){
            DrawTextCenteredAt("CORRECT", 760, 865, 35, GREEN);
        }
        else{
            DrawTextCenteredAt("INCORRECT!", 760, 865, 35, RED);
        }
        DrawTextCenteredAt("Press enter for the next ship", 760, 925, 25, WHITE);

    }
}
void GameOverScreen(){
    ClearBackground(BLACK);
    DrawTextCentered("Game Over", 250, 70, RED);
    DrawTextCentered(TextFormat("You reached Shift %i", currentshift), 380, 30, WHITE);
    DrawTextCentered(TextFormat("Correct Inspections: %i", correctships), 460, 30, WHITE);
    DrawTextCentered(TextFormat("Incorrect Inspections: %i", incorrectships), 520, 30, WHITE);
    DrawTextCentered(TextFormat("Total Mistakes: %i", mistakes), 580, 30, RED);
    DrawTextCentered("Press enter to return to menu", 750, 25, LIGHTGRAY);
    DrawTextCentered("R - Restart game", 800, 25, LIGHTGRAY);
}
void Shiftcompletescreen(){
    ClearBackground(BLACK);
    DrawTextCentered("Shift 1 COMPLETE", 250, 60, GREEN);
    DrawTextCentered(TextFormat("Ships Processed: %i/%i", shipsprocessed, getshiftquota()), 430, 30, WHITE);
    DrawTextCentered(TextFormat("Correct Inspections: %i", correctships), 490, 30, WHITE);
    DrawTextCentered(TextFormat("Incorrect Inspections: %i", incorrectships), 550, 30, WHITE);
    DrawTextCentered("Press Enter to begin Shift 2", 800, 30, LIGHTGRAY);
}
void DrawVictoryScreen(){
    ClearBackground(BLACK);
    DrawTextCentered("Day is over!", 220, 65, GREEN);
    DrawTextCentered("You have successfully completed both shifts", 350, 30, WHITE);
    DrawTextCentered(TextFormat("Ships Processed: %i", correctships + incorrectships), 470, 30, WHITE);
    DrawTextCentered(TextFormat("Correct Inspections: %i", correctships), 530, 30, WHITE);
    DrawTextCentered(TextFormat("Incorrect Inspections: %i", incorrectships), 590, 30, WHITE);
    DrawTextCentered("Press enter to return to the menu", 850, 25, LIGHTGRAY);
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
            mistakes++;
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