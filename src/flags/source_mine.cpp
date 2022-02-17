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
    //set up spawn decs.
    if(LENGTH(flagMem["spawnDefs"].as<JSArray>()) == 0){
        CreepDefinition def;
        def.bodyType = "miner";
        def.offRoad = true;
        def.maxSize = 6;
        def.priority = 2;
        CreepDefinition def2;
        def2.bodyType = "hauler";
        def2.offRoad = true;
        def2.maxSize = 10;//TODO: pathfind to check optimal max size
        def2.priority = 3;
        flagMem["spawnDefs"].call<void>("push",def);
        flagMem["spawnDefs"].call<void>("push",def2);
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
