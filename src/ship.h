#pragma once
#include "raylib.h"
#include <string>
#include <vector>
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

void Drawship(const Ship& ship){
    float x = ship.bounds.x;
    float y=  ship.bounds.y;
    float w =ship.bounds.width;
    float h = ship.bounds.height;

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
    DrawRectangle(x+10,y+10,w-20,h-10, shipcolor);
    DrawTriangle({x+w-10,y+10},{x+w,y+h},{x+w-10,y+h},shipcolor);
    DrawRectangle(x+40,y-25,65,25,shipcolor);
    for(int i=0;i<3;i++){
        DrawRectangle(x+48 + i *20,y-18,10,10,shipcolor);
    }
}
