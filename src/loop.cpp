#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>

#include <cppreeps.hpp>
#include <Constants.hpp>
#include <api.hpp>

#include "./basestate/bootstrap.h"
#include "./basestate/stagestorage.h"
#include "./basestate/stageterminal.h"
#include "./basestate/stage7.h"
#include "./basestate/stage8.h"

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
  if(tick->Memory["war"].isUndefined()){
    tick->Memory.set("war",val::object());
  }
  if(tick->Memory["nameCounter"].isUndefined()){
    tick->Memory.set("nameCounter",0);
  }
  printf("Init Routine Called\n");
}

void determineBaseState(JSObject room,JSObject controller,int controllerLevel){
    if(controllerLevel < 4 || room["storage"].isUndefined()){
        createFlag(room,25,25,COLOR_PURPLE,COLOR_RED);
    }
    else if(controllerLevel < 6 || room["terminal"].isUndefined()){
        createFlag(room,25,25,COLOR_PURPLE,COLOR_PURPLE);
    }
    else if(controllerLevel < 7){
        createFlag(room,25,25,COLOR_PURPLE,COLOR_BLUE);
    }
    else if(controllerLevel < 8){
        createFlag(room,25,25,COLOR_PURPLE,COLOR_CYAN);
    }
    else if(controllerLevel == 8){
        createFlag(room,25,25,COLOR_PURPLE,COLOR_GREEN);
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
                int controllerLevel = controller["level"].as<int>();
                if (controllerLevel == 0) {
                    //reserved room
                } else {
                    //claimed room, blue flag = base states
                    JSArray baseStateFlags = Util_flagsInRoomP(roomName, COLOR_BLUE);
                    int baseStateFlagCount = baseStateFlags["length"].as<int>();
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
                    int type = baseStateFlag["color"].as<int>();
                    switch(type){
                        case COLOR_RED://bootstrap
                            bootstrap_loop(room);
                            break;
                        case COLOR_PURPLE://level 4, can build storage
                            stagestorage_loop(room);
                            break;
                        case COLOR_BLUE://level 6, storage + terminal allowed, controller link
                            stageterminal_loop(room);
                            break;
                        case COLOR_CYAN://level 7, 2 spawns, storage+terminal+all links
                            stage7_loop(room);
                            break;
                        case COLOR_GREEN://all things are available
                            stage8_loop(room);
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
            int roomType = room.call<int>("getRoomType");
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

void spawnCreeps(String flagName, JSObject flag){
    //spawn the creeps the flag wants.
    //check if the flags current creeps the flag has are alive, if not replace the dead ones.
}

void processCreepActions(String flagName, JSObject flag){
    //perform the creeps task, if task complete, assign new task from the flag,
    //or if flag removed, sacrifice creep to spawn
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
    Map<String,JSObject> creeps_map = creeps();
    for(auto const& kv : creeps_map) {
        String const &creepName = kv.first;
        if(!Util_creepExists(creepName)){
            Util_deleteProperty(tick->Memory["creeps"],creepName);
        }
    }
}

//on game loop
void loop() {
    INIT();
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
}
