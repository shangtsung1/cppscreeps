//
// Created by tsung on 17/02/2022.
//

#include "emergency_dude.h"
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include <creep.hpp>


void emergency_dude_doTaskW(JSObject flag,JSObject creep){
    JSObject roomSpawnedIn = tick->Game["rooms"][creep["memory"]["roomSpawnedIn"].as<String>()].as<JSObject>();
    JSObject flagMem = flag["memory"].as<JSObject>();
    JSObject src = creep["pos"].call<JSObject>("findClosestByPath",FIND_SOURCES_ACTIVE);
    if(creep["memory"]["full"].isUndefined()){
        creep["memory"].set("full",false);
    }
    else if(creep["store"].call<number>("getFreeCapacity") == 0){
        creep["memory"].set("full",true);
    }
    else if(creep["store"].call<number>("getUsedCapacity") == 0){
        creep["memory"].set("full",false);
    }
    if(creep["memory"]["full"].as<bool>()){
        //TODO: optimise
        String stackLocalString = RESOURCE_ENERGY;
        JSArray toFill = flag["room"].call<JSArray>("getEmptySpawnContainers");
        if(LENGTH(toFill) > 0){
            JSObject fillin = creep["pos"].call<JSObject>("findClosestByPath",toFill);
            if (!creep["pos"].call<bool>("isNearTo", fillin)) {
                creep.call<void>("moveTo", fillin);
            } else {
                creep.call<void>("transfer",fillin,stackLocalString);
            }
        }
    }
    else{
        if(!creep["pos"].call<bool>("isNearTo",src)){
            creep.call<void>("moveTo",src);
        }
        else{
            creep.call<void>("harvest",src);
        }
    }
}

void emergency_dude_doTaskH(JSObject flag,JSObject creep){
    JSObject roomSpawnedIn = tick->Game["rooms"][creep["memory"]["roomSpawnedIn"].as<String>()].as<JSObject>();
    JSObject flagMem = flag["memory"].as<JSObject>();
    if(creep["memory"]["full"].isUndefined()){
        creep["memory"].set("full",false);
    }
    else if(creep["store"].call<number>("getFreeCapacity") == 0){
        creep["memory"].set("full",true);
    }
    else if(creep["store"].call<number>("getUsedCapacity") == 0){
        creep["memory"].set("full",false);
    }
    //if(flag["room"]["storage"].isUndefined()){
        String stackLocalString = RESOURCE_ENERGY;
        if(creep["memory"]["full"].as<bool>()) {
            //TODO: optimise
            JSArray toFill = flag["room"].call<JSArray>("getEmptySpawnContainers");
            if(LENGTH(toFill) > 0){
                JSObject fillin = creep["pos"].call<JSObject>("findClosestByPath",toFill);
                if (!creep["pos"].call<bool>("isNearTo", fillin)) {
                    creep.call<void>("moveTo", fillin);
                } else {
                    creep.call<void>("transfer",fillin,stackLocalString);
                }
            }
        }
        else {
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

void emergency_dude_setupMemory(JSObject room,JSObject flag) {
    bool hasEnergyInContainers = true;//TODO
    JSObject flagMem = flag["memory"].as<JSObject>();
    if (LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 0) {
        CreepDefinition def;
        def.bodyType = "worker";
        def.offRoad = true;
        def.maxSize = 1;
        def.priority = 1;
        flagMem["spawnDefs"].call<void>("push", def);
    }
    if(hasEnergyInContainers) {
        if (LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 1) {
            CreepDefinition def;
            def.bodyType = "hauler";
            def.offRoad = true;
            def.maxSize = 3;
            def.priority = 1;
            flagMem["spawnDefs"].call<void>("push", def);
        }
    }
}

void emergency_dude_doRoutine(JSObject room){

    if(room["controller"]["level"].as<number>() <= 1){
        //at lvl 1, do nothing
        return;
    }
    JSArray creepsInRoom = room.call<JSArray>("find",FIND_MY_CREEPS);
    JSArray flags = Util_flagsInRoomPS(NAME(room), COLOR_YELLOW,COLOR_RED);
    int i = 0;
    JS_FOREACH(flags,i)
    {
        emergency_dude_setupMemory(room, flags[i]);
    }
    if(LENGTH(creepsInRoom) < 3){
        //Eek!
        if(LENGTH(flags) == 0){
            //no emergencyFlag+
            room.call<number>("createFlag", 1, 1,null, COLOR_YELLOW,COLOR_RED);
        }
    }
    else{
        if(LENGTH(flags) > 0){
            i = 0;
            JS_FOREACH(flags,i)
            {
                flags[i].call<void>("remove");
            }
        }
    }
}