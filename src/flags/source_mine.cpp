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

struct bestSpot{
    number dist;
    number x;
    number y;
};

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
    if(room["controller"]["level"].as<number>() >= 2 && leng == 1){
        CreepDefinition def2;
        def2.bodyType = "hauler";
        def2.offRoad = true;
        def2.maxSize = 10;//TODO: pathfind to check optimal max size
        def2.priority = 3;
        flagMem["spawnDefs"].call<void>("push", def2);
    }
    if(room["controller"]["level"].as<number>() >= 7 && leng == 2){
        //remove hauler, we should have links
        flagMem["spawnDefs"].call<void>("pop");
    }
    String rN = NAME(room);
    //set the id of the container/link to the flag if we can, or
    //place a build command flag for a container/link if we can
    JSObject container = tick->Game.call<JSObject>("getObjectById",flagMem["containerId"]);
    if(container.isNull()){
        ///find spot
        JSArray conFlags = Util_flagsInRoomNearPS(NAME(room),flag["pos"]["x"].as<number>(), flag["pos"]["y"].as<number>(),2, COLOR_GREEN, COLOR_GREY);
        if(conFlags.isUndefined() || LENGTH(conFlags) == 0) {
            number X = flag["pos"]["x"].as<number>();
            number Y = flag["pos"]["y"].as<number>();
            Vector<bestSpot> vv;
            for(int ii = (X-2);ii<(X+3);ii++){
                for(int jj = (Y-2);jj<(Y+3);jj++){
                    if(tick->Game["map"].call<JSObject>("getRoomTerrain",rN).call<number>("get",ii,jj) != 0){
                        continue;
                    }
                    struct bestSpot bs;
                    bs.x = ii;
                    bs.y = jj;
                    bs.dist = Util_distanceByPathBetween(X, Y, rN, room["controller"]["pos"]["x"].as<number>(), room["controller"]["pos"]["y"].as<number>(),rN ,1,true);
                    vv.push_back(bs);
                }
            }
            bestSpot bbs = vv[0];
            for(bestSpot bs : vv){
                if(bs.dist < bbs.dist){
                    bbs = bs;
                }
            }
            createFlag(NEWPOS(bbs.x,bbs.y,rN),COLOR_GREEN, COLOR_GREY);
        }
        else{
            JSObject conFlag = conFlags[0].as<JSObject>();
            number fx = conFlag["pos"]["x"].as<number>();
            number fy = conFlag["pos"]["y"].as<number>();
            String sT = STRUCTURE_CONTAINER;
            if(isStructureAt(room,fx,fy,sT)){
                JSObject jo = structureAt(room, fx, fy, sT);
                flagMem.set("containerId",jo["id"].as<String>());
            }
            else if(!isConstructionAt(room,fx , fy, sT)){
                room.call<number>("createConstructionSite",NEWPOS(fx,fy,rN),sT);
            }
            else{
                JSObject jo = constructionAt(room, fx, fy, sT);
                flagMem.set("containerId",jo["id"].as<String>());
            }
        }
    }
    else{
        if(!container["progressTotal"].isUndefined()){
            //construction site
        }
        else{
            //container.
        }
    }
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
    JSObject flagMem = flag["memory"].as<JSObject>();
    JSObject src = flag.call<JSObject>("getSource");
    number cLevel = roomSpawnedIn["controller"]["level"].as<number>();
    //upgrade
    if(creep["memory"]["full"].isUndefined()){
        creep["memory"].set("full",false);
    }
    else if(creep["store"].call<number>("getFreeCapacity") == 0){
        creep["memory"].set("full",true);
    }
    else if(creep["store"].call<number>("getUsedCapacity") == 0){
        creep["memory"].set("full",false);
    }
    if(cLevel == 1){
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
        if(creep["memory"]["full"].as<bool>()) {
            JSObject container = tick->Game.call<JSObject>("getObjectById", flagMem["containerId"]);
            if (container.isNull()) {
                //wait around for the con site to be placed?
            } else {
                if (!container["progressTotal"].isUndefined()) {
                    if (!creep["pos"].call<bool>("inRangeTo", container, 3)) {
                        creep.call<void>("moveTo", container);
                    } else {
                        creep.call<void>("build",container);
                    }
                } else {

                    if(container["hits"].as<number>() < container["hitsMax"].as<number>()){
                        if (!creep["pos"].call<bool>("inRangeTo", container,3)) {
                            creep.call<void>("moveTo", container);
                        }
                        else {
                            creep.call<void>("repair", container);
                        }
                    }
                    else {
                        if (!creep["pos"].call<bool>("isNearTo", container)) {
                            creep.call<void>("moveTo", container);
                        }
                        else {
                            String stackLocalString = RESOURCE_ENERGY;
                            creep.call<void>("transfer",container, stackLocalString);
                        }
                    }
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
    //link
    else{

    }
}
void source_mine_haulerTask(JSObject flag,JSObject creep){
    JSObject roomSpawnedIn = tick->Game["rooms"][creep["memory"]["roomSpawnedIn"].as<String>()].as<JSObject>();
    JSObject flagMem = flag["memory"].as<JSObject>();
    JSObject src = flag.call<JSObject>("getSource");
    number cLevel = roomSpawnedIn["controller"]["level"].as<number>();
    if(creep["memory"]["full"].isUndefined()){
        creep["memory"].set("full",false);
    }
    else if(creep["store"].call<number>("getFreeCapacity") == 0){
        creep["memory"].set("full",true);
    }
    else if(creep["store"].call<number>("getUsedCapacity") == 0){
        creep["memory"].set("full",false);
    }
    if(cLevel < 6){
        if(creep["memory"]["full"].as<bool>()) {

        }
        else {
            JSObject container = tick->Game.call<JSObject>("getObjectById", flagMem["containerId"]);
            if (container.isNull()) {
                //wait around for the con site to be placed?
            } else {
                if (!creep["pos"].call<bool>("isNearTo", container)) {
                    creep.call<void>("moveTo", container);
                } else {
                    String stackLocalString = RESOURCE_ENERGY;
                    creep.call<void>("withdraw",container,stackLocalString);
                }
            }
        }
    }
}
