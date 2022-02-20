//
// Created by tsung on 17/02/2022.
//

#include "source_mine.h"
#include <cppreeps.hpp>
#include <Constants.hpp>
#include <api.hpp>
#include <creep.hpp>

using namespace screeps;

void source_mine_setFlags(JSObject room){
    String roomName = NAME(room);
    JSArray srcs = sources(roomName);
    int length = LENGTH(srcs);
    for(int x = 0; x < length; x++){
        JSObject src = srcs[x].as<JSObject>();
        if(!Util_flagAtPS(POS(src), COLOR_PURPLE, COLOR_PURPLE)){
            createFlag(POS(src),COLOR_PURPLE, COLOR_PURPLE);
        }
    }
}

void source_mine_setupMemory(JSObject room,JSObject flag){
    JSObject flagMem = flag["memory"].as<JSObject>();
    if(flagMem["containerId"].isUndefined()){
        flagMem.set("containerId","");
    }
    //set up spawn decs.
    if(LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 0){
        CreepDefinition def;
        def.bodyType = "miner";
        def.offRoad = true;
        def.maxSize = 6;
        def.priority = 2;
        flagMem["spawnDefs"].call<void>("push",def);
    }

    number leng = LENGTH(flagMem["spawnDefs"].as<JSArray>());
    if(room["controller"]["level"].as<number>() >= 2){
        if(leng == 1) {
            CreepDefinition def2;
            def2.bodyType = "hauler";
            def2.offRoad = true;
            def2.maxSize = 10;//TODO: pathfind to check optimal max size
            def2.priority = 3;
            flagMem["spawnDefs"].call<void>("push", def2);
        }
    }
    if(room["controller"]["level"].as<number>() >= 6 && LENGTH(flagMem["containerId"].as<JSObject>()) > 0){
        //remove hauler, we should have links
        if(leng == 2) {
            flagMem["spawnDefs"].call<void>("pop");
        }
    }
    //set the id of the container/link to the flag if we can, or
    //place a build command flag for a container/link if we can
}

void source_mine_doRoutine(JSObject room){
    source_mine_setFlags(room);
    JSArray flags = Util_flagsInRoomPS(NAME(room), COLOR_PURPLE, COLOR_PURPLE);
    int i = 0;
    JS_FOREACH(flags,i){
        source_mine_setupMemory(room,flags[i].as<JSObject>());
    }
}

void source_mine_workerTask(JSObject flag,JSObject creep){
    JSObject roomSpawnedIn = tick->Game["rooms"][creep["memory"]["roomSpawnedIn"].as<String>()].as<JSObject>();
    JSObject src = flag.call<JSObject>("getSource");
    number cLevel = roomSpawnedIn["controller"]["level"].as<number>();
    //upgrade
    if(cLevel == 1){
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
            JSObject controller = roomSpawnedIn["controller"].as<JSObject>();
            if(!creep["pos"].call<bool>("inRangeTo",controller,3)){
                creep.call<void>("moveTo",controller);
            }
            else{
                creep.call<void>("upgradeController",controller);
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
    //container
    else if(cLevel < 6){

    }
    //link
    else{

    }
}
void source_mine_haulerTask(JSObject flag,JSObject creep){
    JSObject roomSpawnedIn = tick->Game["rooms"][creep["memory"]["roomSpawnedIn"].as<String>()].as<JSObject>();
    number controllerLevel = roomSpawnedIn["controller"]["level"].as<number>();

}
