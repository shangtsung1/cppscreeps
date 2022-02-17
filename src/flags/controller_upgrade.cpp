//
// Created by tsung on 17/02/2022.
//

#include "controller_upgrade.h"
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

void controller_upgrade_setFlags(JSObject room){
    JSObject src = room["controller"].as<JSObject>();
    if(!Util_flagAtPS(room["name"].as<String>(),src["pos"]["x"].as<number>(), src["pos"]["y"].as<number>(), COLOR_PURPLE, COLOR_GREEN)){
        createFlag(room,src["pos"]["x"].as<number>(), src["pos"]["y"].as<number>(),COLOR_PURPLE, COLOR_GREEN);
    }
}



void controller_upgrade_doRoutine(JSObject room){
    controller_upgrade_setFlags(room);
}