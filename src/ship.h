#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <cmath>
enum ShipType{
    Cargo,
    Fishing,
    Passenger
};  
struct ShipIdentity{
    std::string name;
    std::string origin;
    
};
struct Ship{
    
    ShipIdentity identity;
    std::string cargo;
    std::string request;

    Rectangle bounds;
    float speed;
    ShipType type;
    ShipType declaredtype;
    bool inspected = false;

    bool isfake = false;
    bool decisionmade =false;
    bool playercorrect = false;
    bool paperworkanomaly = false;
    bool visualanomaly = false;
    float resulttimer = 0.0f;
    float inspectiontimer = 0.0f;
    float inspectiontimelimit = 20.0f;
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
bool ispaperworkauthentic(const Ship& ship){
    return ship.type == ship.declaredtype;
}
bool isVisualAuthentic(const Ship& ship){
    return !ship.visualanomaly;
}
bool isShipAuthentic(const Ship& ship){
    return ispaperworkauthentic(ship) && isVisualAuthentic(ship);
}
void ResetShip(Ship& ship, int currentshift =1){
    ship.inspectiontimer = 0.0f;
    if(currentshift ==1){
        ship.inspectiontimelimit = 20.0f;
    }
    else{
        ship.inspectiontimelimit = 15.0f;
    }
    ship.inspectiontimelimit = 20.0f;
    ship.bounds.x = -ship.bounds.width;
    ship.inspected = false;
    ship.decisionmade = false;
    ship.playercorrect = false;
    int anomalytype = GetRandomValue(0,9);
    ship.paperworkanomaly = false;
    ship.visualanomaly = false;
    
    const std::vector<std::string> names = {
        "Southern Baylighte",
        "Central Bakerslite",
        "East Oaklit",
        "West Pacifilis"
    };
    const std::vector<std::string> origins = {
        "San Joe",
        "MiddleOfNowhere",
        "Crimeland",
        "TCBell Cantina"
        
    };


    /*const std::vector<std::string> cargos = {
        "Industrial supplies",
        "Electronics",
        "Medical Equipment",
        "Bits of Coins"
    };
    const std::vector<std::string> requests = {
        "Fuel Refill",
        "Crew Transfer",
        "Emergency Repair",
        "Doomscroll Requests"
    };*/
    const std::vector<std::string> cargoCargo ={
        "Industrial Supplies",
        "Electronics"
    };
    const std::vector<std::string> fishingCargoi = {
        "Fishing nets",
        "Fresh catches"
    };
    const std::vector<std::string> passengerCargo = {
        "Passenger luggage",
        "Food supplies"
    };
    const std::vector<std::string> cargoRequests = {
        "Port Delivery",
        "Fuel Refill"
    };
    const std::vector<std::string> fishingRequets = {
        "Fishing Permit",
        "Catches Unloading"
    };
    const std::vector<std::string> passengerRequests = {
        "Touring",
        "Crew Transfer"
    };
    std::vector<ShipIdentity> identities = {
        {"Northerne BayLighte", "San Joe"},
        {"Central Bakerslite", "Mida 'o No Whe"},
        {"East Oaklits", "Crimeland"},
        {"West Pacificalis", "TCBell Cantina"}
    };
    if(currentshift ==2){
        std::vector<ShipIdentity> extraidentities = {
            //newcities
            {"North York", "New Ballhog"},
            {"Central Kirkland", "Purifie Aqua"},
            {"East Mint", "Alto 'ids'"},
            {"West Tilde", "Above Tabica"}
        };
        identities.insert(identities.end(),extraidentities.begin(),extraidentities.end());
    }
    int identitiesindex = GetRandomValue(0,static_cast<int>(identities.size()-1));
    ship.identity = identities[identitiesindex];
    std::vector<ShipType> types = {
        Cargo,
        Fishing,
        Passenger
    };
    int typeindex = GetRandomValue(0, static_cast<int>(types.size())-1);
    ship.type = types[typeindex];
    ship.declaredtype =ship.type;
    
    //ship.isfake = GetRandomValue(0,1) == 1;
    if(currentshift==1) {
        if(anomalytype <= 4){
        
        }
        else if(anomalytype <=6){
            ship.paperworkanomaly = true;

        }
        else if(anomalytype <=8){
            ship.visualanomaly = true;
        }
        else{
            ship.paperworkanomaly = true;
            ship.visualanomaly = true;
        }
    }
    else if(currentshift ==2){
        if(anomalytype<=2){

        }
        else if(anomalytype<=5){
            ship.paperworkanomaly = true;
        }
        else if(anomalytype <=7){
            ship.visualanomaly = true;
        }
        else{
            ship.paperworkanomaly = true;
            ship.visualanomaly = true;
        }
    }
    
    // ship.isfake = anomalytype !=0;
    if(ship.paperworkanomaly){
        int fakeindextype = GetRandomValue(0,static_cast<int>(types.size())-1);
        while(types[fakeindextype] == ship.type){
            fakeindextype = GetRandomValue(0,static_cast<int>(types.size())-1);
        }
        ship.declaredtype = types[fakeindextype];
    }
    /* if(ship.declaredtype =}= Cargo){
        ship.request + "Cargo Unloading";
    }
    else if(ship.declaredtype == Fishing){
        ship.request = "Fishing supplies";
    }
    else if(ship.declaredtype == Passenger){
        ship.request = "Passenger Dockings";
    } 
        */
    //ship.cargo = cargos[GetRandomValue(0,cargos.size()-1)];
    //ship.request = requests[GetRandomValue(0, static_cast<int>(requests.size())-1)];
    if(ship.declaredtype == Cargo){
        ship.cargo = cargoCargo[GetRandomValue(0, cargoCargo.size()-1)];
        ship.request = cargoRequests[GetRandomValue(0,cargoRequests.size()-1)];
    }
    else if(ship.declaredtype == Fishing){
        ship.cargo = fishingCargoi[GetRandomValue(0,fishingCargoi.size()-1)];
        ship.request = fishingRequets[GetRandomValue(0,fishingRequets.size()-1)];
    }
    else if(ship.declaredtype == Passenger){
        ship.cargo = passengerCargo[GetRandomValue(0,passengerCargo.size()-1)];
        ship.request = passengerRequests[GetRandomValue(0, passengerRequests.size()-1)];
    }
    ship.resulttimer =0.0f;
}

// filled quad (a,b,c,d in order around the shape). Drawn with both windings so
// it shows up regardless of raylib's backface culling.
void DrawQuadAny(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Color color){
    DrawTriangle(a, b, c, color);
    DrawTriangle(a, c, b, color);
    DrawTriangle(a, c, d, color);
    DrawTriangle(a, d, c, color);
}

Color ShadeColor(Color c, float amount){
    return {(unsigned char)(c.r * amount), (unsigned char)(c.g * amount), (unsigned char)(c.b * amount), c.a};
}

void Drawship(const Ship& ship){
    float x = ship.bounds.x;
    float w = ship.bounds.width;
    float h = ship.bounds.height;
    // gentle bob on the waves
    float y = ship.bounds.y + sinf((float)GetTime() * 2.2f + x * 0.01f) * 3.0f;

    // hull colour tells you the real ship type; red means a visual anomaly
    Color shipcolor = DARKGRAY;
    if(ship.type == Cargo){
        shipcolor = GRAY;
    }
    else if(ship.type == Fishing){
        shipcolor = BLUE;
    }
    else if(ship.type == Passenger){
        shipcolor = WHITE;
    }
    if(ship.visualanomaly){
        shipcolor = RED;
    }
    Color dark = ShadeColor(shipcolor, 0.6f);
    Color light = ShadeColor(shipcolor, 0.85f);

    // wake behind the ship while it is moving
    if(!ship.inspected){
        for(int i = 1; i <= 4; i++){
            float fade = 0.25f - i * 0.05f;
            DrawEllipse((int)(x - i * 28), (int)(ship.bounds.y + h + 2), 26 - i * 3, 4, Fade(WHITE, fade));
        }
    }
    // reflection on the water
    DrawRectangle((int)(x + 18), (int)(ship.bounds.y + h + 4), (int)(w - 36), 14, Fade(shipcolor, 0.12f));

    // hull wide deck tapering to a narrower keel, pointed bow on the right
    DrawQuadAny({x, y + 10}, {x + w - 18, y + 10}, {x + w - 30, y + h}, {x + 14, y + h}, shipcolor);
    DrawTriangle({x + w - 18, y + 10}, {x + w - 30, y + h}, {x + w, y + 10}, shipcolor);
    DrawTriangle({x + w - 18, y + 10}, {x + w, y + 10}, {x + w - 30, y + h}, shipcolor);
    // Waterline stripe and deck rail
    DrawQuadAny({x + 8, y + h - 12}, {x + w - 22, y + h - 12}, {x + w - 30, y + h}, {x + 14, y + h}, dark);
    DrawRectangle((int)x, (int)y + 8, (int)w - 12, 3, dark);

    // cabin with lit windows, funnel and mast
    DrawRectangle((int)(x + 40), (int)(y - 25), 70, 35, light);
    DrawRectangle((int)(x + 40), (int)(y - 25), 70, 4, dark);
    for(int i = 0; i < 3; i++){
        DrawRectangle((int)(x + 49 + i * 20), (int)(y - 15), 11, 10, {255, 214, 120, 255});
    }
    DrawRectangle((int)(x + 82), (int)(y - 45), 14, 20, dark);
    DrawRectangle((int)(x + 125), (int)(y - 40), 3, 50, dark);
}