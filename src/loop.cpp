#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>

#include <cppreeps.hpp>
#include <Constants.hpp>
#include <api.hpp>
#include <terrain_utils.hpp>
#include <creep.hpp>

#include "./basestate/bootstrap.h"
#include "./basestate/stagestorage.h"
#include "./basestate/stageterminal.h"
#include "./basestate/stage7.h"
#include "./basestate/stage8.h"

#include "./creep/bodybuilder.h"

using namespace screeps;

String getExceptionMessage(intptr_t exceptionPtr) {
  return String(reinterpret_cast<Exception *>(exceptionPtr)->what());
}

//on wasm load
void init() {
  INIT();
  if(tick->Memory["rooms"].isUndefined()){
    tick->Memory.set("rooms",val::object());
  }
  if(tick->Memory["creeps"].isUndefined()){
    tick->Memory.set("creeps",val::object());
  }
  if(tick->Memory["flags"].isUndefined()){
      tick->Memory.set("flags",val::object());
  }
  if(tick->Memory["war"].isUndefined()){
    tick->Memory.set("war",val::object());
  }
  if(tick->Memory["nameCounter"].isUndefined()){
    tick->Memory.set("nameCounter",0);
  }
  printf("Init Routine Called\n");
}

void determineBaseState(JSObject room,JSObject controller,number controllerLevel){
    printf("determineBaseState\n");
    if(controllerLevel < 4 || room["storage"].isUndefined()){
        createFlag(room,25,25,COLOR_BLUE,COLOR_RED);
    }
    else if(controllerLevel < 6 || room["terminal"].isUndefined()){
        createFlag(room,25,25,COLOR_BLUE,COLOR_PURPLE);
    }
    else if(controllerLevel < 7){
        createFlag(room,25,25,COLOR_BLUE,COLOR_BLUE);
    }
    else if(controllerLevel < 8){
        createFlag(room,25,25,COLOR_BLUE,COLOR_CYAN);
    }
    else if(controllerLevel == 8){
        createFlag(room,25,25,COLOR_BLUE,COLOR_GREEN);
    }
    else{
        printf("Fuck.\n");
    }
}

void setupFlags(){
    Map<String,JSObject> rooms_map = rooms();
    for(auto const& kv : rooms_map) {
        String const &roomName = kv.first;
        JSObject const &room = kv.second;
        if (!room["controller"].isUndefined()) {
            JSObject controller = room["controller"].as<JSObject>();
            if (controller["my"].as<bool>()) {
                number controllerLevel = controller["level"].as<number>();
                if (controllerLevel == 0) {
                    //reserved room
                } else {
                    //claimed room, blue flag = base states
                    JSArray baseStateFlags = Util_flagsInRoomP(roomName, COLOR_BLUE);
                    number baseStateFlagCount = baseStateFlags["length"].as<number>();
                    if(baseStateFlagCount > 1){
                        //too many flags, remove all and redetermine which we need.
                        Vector<JSObject> arr = js_array_to_vector(baseStateFlags);
                        for (auto &flag : arr){
                            flag.call<void>("remove");
                        }
                        baseStateFlagCount=0;
                    }
                    if(baseStateFlagCount == 0){
                        //Setup which flag gets placed in this room.
                        determineBaseState(room,controller,controllerLevel);
                        continue;//the flag wont appear till next turn.
                    }
                    JSObject baseStateFlag = baseStateFlags[0].as<JSObject>();
                    int type = baseStateFlag["secondaryColor"].as<int>();

                    switch(type){
                        case COLOR_RED://bootstrap
                            bootstrap_loop(room,baseStateFlag);
                            break;
                        case COLOR_PURPLE://level 4, can build storage
                            stagestorage_loop(room,baseStateFlag);
                            break;
                        case COLOR_BLUE://level 6, storage + terminal allowed, controller link
                            stageterminal_loop(room,baseStateFlag);
                            break;
                        case COLOR_CYAN://level 7, 2 spawns, storage+terminal+all links
                            stage7_loop(room,baseStateFlag);
                            break;
                        case COLOR_GREEN://all things are available
                            stage8_loop(room,baseStateFlag);
                            break;
                    }
                }
            } else {
                if (!controller["reservation"].isUndefined()) {
                    //reserved by enemy/ally
                } else if (!controller["owner"].isUndefined()) {
                    //owned by enemy/ally
                } else {
                    //not owned
                }
            }
        }
        else{
            //room has no controller.
            number roomType = room.call<number>("getRoomType");
            if(roomType == ROOM_CROSSROAD){
                //power, commodoties, convoys, intershard portals
            }
            else if(roomType == ROOM_HIGHWAY){
                //power, commodoties, convoys
            }
            else if(roomType == ROOM_CENTER){
                //center of habitable cluster(3 nodes, 1 mineral, no hostiles, rnd chance portals), chance of invader base
            }
            else if(roomType == ROOM_SOURCE_KEEPER){
                //source keepers, 3 nodes, 1 mineral, chance of invader base
            }
            else{
                //unpossibru
            }
        }
    }
}

void flagPostProcessing(String flagName, JSObject flag){
    //same as preprocessing, but after the rooms done its spawns and creep actions.
}

void flagPreProcessing(String flagName, JSObject flag){
    //anything that needs to occur/be_checked for the flag on a tick by tick basis, that isn't covered by a creep role.
}

void spawnCreeps(String flagName, JSObject flag) {
    int i = 0;
    //is the flag in a claimed room?
    if (!flag["room"].isNull() && !flag["room"]["controller"].isNull() && flag["room"]["controller"]["level"].as<number>() > 0){
        JSObject room = flag["room"].as<JSObject>();
        JSArray spawnCapableSpawns = spawnsNotSpawning(NAME(room));

        JSArray spawnDefs = flag["memory"]["spawnDefs"].as<JSArray>();
        for (int priority = 0; priority < 5; priority++) {
            JS_FOREACH(spawnDefs, i)
            {
                if(LENGTH(spawnCapableSpawns) == 0){
                    return;
                }
                if (spawnDefs[i]["priority"].as<number>() == priority) {
                    if (spawnDefs[i]["currentCreep"].isNull() ||
                        tick->Game["creeps"][spawnDefs[i]["currentCreep"].as<String>()].isUndefined()) {
                        //creep is dead or not alive.
                        //spawn creep
                        JSObject spawn = spawnCapableSpawns[0];
                        String name = getNewCreepName();
                        JSObject anObj = val::object();
                        JSObject memObj = val::object();
                        anObj.set("memory",memObj);
                        memObj.set("bodyType",spawnDefs[i]["bodyType"].as<String>());
                        memObj.set("flagName",NAME(flag));
                        number result = Util_spawnCreep(spawn,BodyBuilder_getBody(room,spawnDefs[i].as<CreepDefinition>()), name, anObj);
                        if(result == OK){
                            flag["memory"]["spawnDefs"][i].set("currentCreep",name);
                        }
                        //set this spawn no longer capable of spawning
                        spawnCapableSpawns.call<void>("shift");
                    }
                }
            }
        }
    }
    else{
        //TODO: spawn for flags outside the base room.
    }
}

void processCreepActions(String flagName, JSObject flag){
    int ii = 0;
    JSArray spawnDefs = flag["memory"]["spawnDefs"].as<JSArray>();
    JS_FOREACH(spawnDefs, ii)
    {
        JSObject creep = tick->Game["creeps"][spawnDefs[ii]["currentCreep"]].as<JSObject>();
        if(!creep.isUndefined() && !creep.isNull()){
            printf("%s\n",creep["name"].as<String>().c_str());
            //creep["memory"]["bodyType"]
        }
    }
}

void processFlags(){
    Map<String,JSObject> flags_map = flags();
    for(auto const& kv : flags_map) {
        String const &flagName = kv.first;
        JSObject const &flag = kv.second;
        flagPreProcessing(flagName, flag);
        spawnCreeps(flagName, flag);
        processCreepActions(flagName, flag);
        flagPostProcessing(flagName, flag);
    }
}

void mem_gc(){
    //TODO: fix
    Map<String,JSObject> creeps_map = creeps();
    for(auto const& kv : creeps_map) {
        String const &creepName = kv.first;
        if(!Util_creepExists(creepName)){
            Util_deleteProperty(tick->Memory["creeps"],creepName);
        }
    }
    Map<String,JSObject> flag_map = flags();
    for(auto const& kv : flag_map) {
        String const &flagName = kv.first;
        if(!Util_flagExists(flagName)){
            Util_deleteProperty(tick->Memory["flags"],flagName);
        }
    }
}

void mem_flag(){
    Map<String,JSObject> flag_map = flags();
    for(auto const& kv : flag_map) {
        String const &flagName = kv.first;
        JSObject const &flag = kv.second;
        if (flag["memory"].isNull()) {
            JSObject flagsM = tick->Memory["flags"].as<JSObject>();
            if (flagsM[flagName].isNull()) {
                flagsM.set(flagName, val::object());
            }
            //reset the flag.memory object.
            flag.as<JSObject>().set("memory",tick->Memory["flags"][flagName].as<JSObject>());
        }
        if (flag["memory"]["spawnDefs"].isUndefined()) {
            flag["memory"].set("spawnDefs",val::array());
        }
    }
}

//on game loop
void loop() {
    INIT();
    mem_flag();
    mem_gc();
    setupFlags();
    processFlags();


    printf("\nLoop Done\n");
}

//export to js
EMSCRIPTEN_BINDINGS(loop) {
    emscripten::function("init", &init);
    emscripten::function("loop", &loop);
    emscripten::function("except", &getExceptionMessage);
    emscripten::value_object<CreepDefinition>("CreepDefinition")
        .field("bodyType", &CreepDefinition::bodyType)
        .field("offRoad", &CreepDefinition::offRoad)
        .field("maxSize", &CreepDefinition::maxSize)
        .field("priority", &CreepDefinition::priority)
        .field("currentCreep", &CreepDefinition::currentCreep)
        ;
}
