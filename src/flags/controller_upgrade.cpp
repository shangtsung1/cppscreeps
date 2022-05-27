//
// Created by tsung on 17/02/2022.
//

#include "controller_upgrade.h"
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include <creep.hpp>

void controller_upgrade_setFlags(JSObject room){
    JSObject src = room["controller"].as<JSObject>();
    if(!Util_flagAtPS(room["name"].as<String>(),src["pos"]["x"].as<number>(), src["pos"]["y"].as<number>(), COLOR_PURPLE, COLOR_GREEN)){
        createFlag(room,src["pos"]["x"].as<number>(), src["pos"]["y"].as<number>(),COLOR_PURPLE, COLOR_GREEN);
    }
}

void controller_upgrade_setupMemory(JSObject room,JSObject flag) {
    JSObject flagMem = flag["memory"].as<JSObject>();
    if (LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 0) {
        CreepDefinition def;
        def.bodyType = "upgrader";
        def.offRoad = true;
        def.maxSize = 20;
        def.priority = 3;
        flagMem["spawnDefs"].call<void>("push", def);
    }
    if (LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 1) {
        CreepDefinition def;
        def.bodyType = "upgrader";
        def.offRoad = true;
        def.maxSize = 20;
        def.priority = 3;
        flagMem["spawnDefs"].call<void>("push", def);
    }
}

void controller_upgrade_upgradeTask(JSObject flag,JSObject creep){
    if(creep["memory"]["full"].isUndefined()){
        creep["memory"].set("full",false);
    }
    else if(creep["store"].call<number>("getFreeCapacity") == 0){
        creep["memory"].set("full",true);
    }
    else if(creep["store"].call<number>("getUsedCapacity") == 0){
        creep["memory"].set("full",false);
    }
    //if(!flag["room"]["storage"].isUndefined()){

   // }
   // else {
        String stackLocalString = RESOURCE_ENERGY;
        if(creep["memory"]["full"].as<bool>()) {
            //upgrade
            JSObject controller = flag["room"]["controller"].as<JSObject>();
            if (!creep["pos"].call<bool>("isNearTo", controller)) {
                creep.call<void>("moveTo", controller);
            } else {
                creep.call<void>("upgradeController",controller);
            }
        }
        else{
            //withdraw
            //TODO: optimise with memory
            JSArray containers = flag["room"].call<JSArray>("getContainersWithEnergy2",creep);
            if (!creep["pos"].call<bool>("isNearTo", containers[0].as<JSObject>())) {
                creep.call<void>("moveTo", containers[0].as<JSObject>());
            } else {
                creep.call<void>("withdraw",containers[0].as<JSObject>(),stackLocalString);
            }
        }
   // }
}


void controller_upgrade_doRoutine(JSObject room){
    controller_upgrade_setFlags(room);
    //really should only be one, but if a room has 2 or more controllers(this isnt a thing 3/2022), it is supported i guess.
    JSArray flags = Util_flagsInRoomPS(NAME(room), COLOR_PURPLE, COLOR_GREEN);
    int i = 0;
    JS_FOREACH(flags,i){
        controller_upgrade_setupMemory(room,flags[i].as<JSObject>());
    }
}