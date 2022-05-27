//
// Created by tsung on 18/03/2022.
//
#include "repair.h"
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include <creep.hpp>


void repair_setupMemory(JSObject room,JSObject flag) {
    JSObject flagMem = flag["memory"].as<JSObject>();
    if (LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 0) {
        CreepDefinition def;
        def.bodyType = "worker";
        def.offRoad = true;
        def.maxSize = 20;
        def.priority = 4;
        flagMem["spawnDefs"].call<void>("push", def);
    }
}

void repair_setFlags(JSObject room){
    //if flag count < 2
    //check flags, move if complete.
    //if nowhere to move, delete.
}

void repair_repairTask(JSObject flag,JSObject creep){
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

    //}
    //else {
        String stackLocalString = RESOURCE_ENERGY;
        if(creep["memory"]["full"].as<bool>()) {

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
    //}
}

void repair_doRoutine(JSObject room){
    repair_setFlags(room);
    JSArray flags = Util_flagsInRoomPS(NAME(room), COLOR_GREEN, COLOR_GREEN);
    int i = 0;
    JS_FOREACH(flags,i){
        repair_setupMemory(room,flags[i].as<JSObject>());
    }
}