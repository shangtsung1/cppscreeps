//
// Created by tsung on 18/03/2022.
//
#include "builder.h"
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include <creep.hpp>


void builder_setupMemory(JSObject room,JSObject flag) {
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

void builder_setFlags(JSObject room){
    JSArray flags = Util_flagsInRoomPS(NAME(room), COLOR_GREEN, COLOR_YELLOW);
    int i = 0;
    JS_FOREACH(flags,i){
        if(LENGTH(flags[i].call<JSArray>("getConstructionSites")) == 0){
            //need to move the fuckjer
            JSArray cons = room.call<JSArray>("find",FIND_MY_CONSTRUCTION_SITES);
            int index = 0;
            if(LENGTH(cons) == 0){
                flags[i].call<void>("remove");
                return;
            }
            while(Util_flagAtPS(cons[index]["pos"].as<JSObject>(), COLOR_GREEN, COLOR_YELLOW)){
                index++;
                if(index >= LENGTH(cons)){
                    flags[i].call<void>("remove");
                    return;
                }
            }
            flags[i].call<void>("setPosition",cons[index]["pos"]["x"].as<number>(), cons[index]["pos"]["y"].as<number>());
        }
    }
    if(LENGTH(flags) < 2){
        JSArray cons = room.call<JSArray>("find",FIND_MY_CONSTRUCTION_SITES);
        int index = 0;
        if(LENGTH(cons) == 0){
            return;
        }
        while(Util_flagAtPS(cons[index]["pos"].as<JSObject>(), COLOR_GREEN, COLOR_YELLOW)){
            index++;
            if(index >= LENGTH(cons)){
                return;
            }
        }
        room.call<number>("createFlag", cons[index]["pos"]["x"].as<number>(), cons[index]["pos"]["y"].as<number>(),null,COLOR_GREEN, COLOR_YELLOW);
    }
}

void builder_builderTask(JSObject flag,JSObject creep){
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
            JSArray cons = flag.call<JSArray>("getConstructionSites");
            number consL = LENGTH(cons);
            if(consL > 1){
                //??
            }
            else if(consL == 1){
                if (!creep["pos"].call<bool>("isNearTo", cons[0].as<JSObject>())) {
                    creep.call<void>("moveTo", cons[0].as<JSObject>());
                } else {
                    creep.call<void>("build",cons[0].as<JSObject>());
                }
            }
            else{
                //flag should be gone next tick??
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
    //}
}

void builder_doRoutine(JSObject room){
    builder_setFlags(room);
    JSArray flags = Util_flagsInRoomPS(NAME(room), COLOR_GREEN, COLOR_YELLOW);
    int i = 0;
    JS_FOREACH(flags,i){
        builder_setupMemory(room,flags[i].as<JSObject>());
    }
}