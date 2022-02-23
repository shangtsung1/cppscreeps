//
// Created by tsung on 15/02/2022.
//

#include <terrain_utils.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include <string.h>

using namespace screeps;


JSArray TerrainUtils_getRoom(String roomName){
    return tick->Utils.call<JSArray>("getRoom",roomName);
}

unsigned char TerrainUtils_get(JSArray buffer, number x, number y){
    return buffer[((int)y * 50 + (int)x)].as<unsigned char>();
}
