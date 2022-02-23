//
// Created by tsung on 22/02/2022.
//

#include "building.h"

#include <cppreeps.hpp>
#include <Constants.hpp>
#include <api.hpp>
#include <terrain_utils.hpp>
#include <creep.hpp>

#include <vector>

struct Point{
    int x;
    int y;
    number dist;
};

bool isValidSpotForBase(int x, int y, JSObject room, JSArray terrain){
    //base size = 7x7(9x9, create a bufferzone)
    int k = (x+4);
    int l = (y+4);
    number res = 0;
    for(int i = x-4;i<=k;i++){
        for(int j = y-4;j<=l;j++) {
            //res = terrain.call<number>("get", i, j);
            res = TerrainUtils_get(terrain,i, j);
            if(res == TERRAIN_MASK_WALL){
                return false;
            }
        }
    }
    return true;
}

bool isValidSpotForBunker(int x, int y, JSObject room, JSArray terrain, int bx, int by){
    //bunker size = 9x9(11x11, create a bufferzone)
    if(!(x+5 <= bx-4 ||   // left
         y+5 <= by-4 ||   // bottom
         x-5 >= bx+4 ||   // right
         y-5 >= by+4)){
        return false;
    }

    int k = (x+5);
    int l = (y+5);
    number res = 0;
    for(int i = x-5;i<=k;i++){
        for(int j = y-5;j<=l;j++) {
            //res = terrain.call<number>("get", i, j);
            res = TerrainUtils_get(terrain,i, j);
            if(res == TERRAIN_MASK_WALL){
                return false;
            }
        }
    }
    return true;
}

void building_setFlags(JSObject room){
    //JSObject terrain = tick->Game["map"].call<JSObject>("getRoomTerrain",NAME(room));
    String rName = NAME(room);
    if(LENGTH(Util_flagsInRoomPS(rName, COLOR_CYAN, COLOR_PURPLE)) == 0){
        JSArray terrain = TerrainUtils_getRoom(rName);
        //TODO: convert string to char array, use it, faster.
        //std::string as = TerrainUtils_getRoom(NAME(room)).as<std::string>();
        std::vector<Point> v = {};
        for(int x = 8; x < 42;x++){
            for(int y = 8; y < 42;y++){
                if(isValidSpotForBase(x,y,room,terrain)){
                    Point p;
                    p.x = x;
                    p.y = y;
                    p.dist = room["controller"]["pos"].as<JSObject>().call<number>("getPathRangeTo",x,y,rName);
                    v.push_back(p);
                }
            }
        }
        Point closest = v[0];
        for (Point p : v){
            if(closest.dist > p.dist){
                closest = p;
            }
        }
        room["visual"].call<void>("rect",closest.x-3.5,closest.y-3.5,7,7);
        createFlag(room,closest.x,closest.y,COLOR_CYAN, COLOR_PURPLE);
        //energyBunker
        std::vector<Point> v2 = {};
        for(int x = 10; x < 40;x++){
            for(int y = 10; y < 40;y++){
                if(isValidSpotForBunker(x,y,room,terrain,closest.x,closest.y)){
                    Point p;
                    p.x = x;
                    p.y = y;
                    p.dist = NEWPOS(x,y,rName).call<number>("getPathRangeTo",closest.x,closest.y,rName);
                    v2.push_back(p);
                }
            }
        }
        if(v2.size() == 0){
            return;
        }
        Point closest2 = v2[0];
        for (Point p : v2){
            if(closest2.dist > p.dist){
                closest2 = p;
            }
        }
        room["visual"].call<void>("rect",closest2.x-4.5,closest2.y-4.5,9,9);
        createFlag(room,closest2.x,closest2.y,COLOR_CYAN, COLOR_BLUE);
    }
}

void building_bunkerlayout(JSObject room,JSObject flag){

}

void building_energylayout(JSObject room,JSObject flag){

}

void building_build(JSObject room){
    String rName = NAME(room);
    building_setFlags(room);
    JSArray baseFlags = Util_flagsInRoomPS(rName, COLOR_CYAN, COLOR_PURPLE);
    if(LENGTH(baseFlags) > 0){
        building_bunkerlayout(room,baseFlags[0]);
    }
    JSArray bunkerFlags = Util_flagsInRoomPS(rName, COLOR_CYAN, COLOR_BLUE);
    if(LENGTH(bunkerFlags) > 0){
        building_bunkerlayout(room,bunkerFlags[0]);
    }
}
