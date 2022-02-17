//
// Created by tsung on 17/02/2022.
//

#include "mineral_mine.h"
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

void mineral_mine_setFlags(JSObject room){
    JSObject src = mineral(room["name"].as<String>());
    if(!Util_flagAtPS(room["name"].as<String>(),src["pos"]["x"].as<number>(), src["pos"]["y"].as<number>(), COLOR_PURPLE, COLOR_RED)){
        createFlag(room,src["pos"]["x"].as<number>(), src["pos"]["y"].as<number>(),COLOR_PURPLE, COLOR_RED);
    }
}

void mineral_mine_doRoutine(JSObject room){
    mineral_mine_setFlags(room);
}