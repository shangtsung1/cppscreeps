//
// Created by tsung on 9/02/2022.
//

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

using namespace screeps;

void println(String s){
    printf("%s\n",s.c_str());
}

//TODO: mod createFlag to avoid white flags.
number createFlag(JSObject room,number x,number y,String name,number color,number secondaryColor){
    JSObject jo = room.call<JSObject>("createFlag",x,y,name,color,secondaryColor);
    if(strcmp(jo.typeof().as<String>().c_str(),"number") != 0){
        return 0;
    }
    return jo.as<double>();
}

number createFlag(JSObject room,number x,number y,number color,number secondaryColor){
    JSObject jo = room.call<JSObject>("createFlag",x,y,null,color,secondaryColor);
    if(strcmp(jo.typeof().as<String>().c_str(),"number") != 0){
        return 0;
    }
    return jo.as<double>();
}

number createFlag(JSObject pos,String name,number color,number secondaryColor){
    JSObject jo = pos.call<JSObject>("createFlag",name,color,secondaryColor);
    if(strcmp(jo.typeof().as<String>().c_str(),"number") != 0){
        return 0;
    }
    return jo.as<double>();
}

number createFlag(JSObject pos,number color,number secondaryColor){
    JSObject jo = pos.call<JSObject>("createFlag",null,color,secondaryColor);
    if(strcmp(jo.typeof().as<String>().c_str(),"number") != 0){
        return 0;
    }
    return jo.as<double>();
}

Map<String,JSObject> rooms(){
    return js_object_to_map(tick->Game["rooms"]);
}

Map<String,JSObject> creeps(){
    return js_object_to_map(tick->Game["creeps"]);
}

Map<String,JSObject> flags(){
    return js_object_to_map(tick->Game["flags"]);
}

Map<String,JSObject> roomsMem(){
    return js_object_to_map(tick->Memory["rooms"]);
}

Map<String,JSObject> creepsMem(){
    return js_object_to_map(tick->Memory["creeps"]);
}

Map<String,JSObject> flagsMem(){
    return js_object_to_map(tick->Memory["flags"]);
}

Map<String,JSObject> spawnsMem(){
    return js_object_to_map(tick->Memory["spawns"]);
}

Map<String,JSObject> spawns(){
    return js_object_to_map(tick->Game["spawns"]);
}

JSArray spawnsNotSpawning(String roomName){
    return tick->Utils.call<JSArray>("spawnsNotSpawning",roomName);
}

Map<String,JSObject> structures(){
    return js_object_to_map(tick->Game["structures"]);
}

Map<String,JSObject> constructionSites(){
    return js_object_to_map(tick->Game["constructionSites"]);
}

JSArray sources(String roomName){
    if(tick->Game["rooms"][roomName].isUndefined()){
        return emscripten::val::array();
    }
    return tick->Game["rooms"][roomName].call<JSArray>("find",FIND_SOURCES);
}

JSObject mineral(String roomName){
    if(tick->Game["rooms"][roomName].isUndefined()){
        return null;
    }
    JSArray mins = tick->Game["rooms"][roomName].call<JSArray>("find",FIND_MINERALS);
    if(mins["length"].as<number>() == 0){
        return null;
    }
    return mins[0].as<JSObject>();
}

bool Util_creepExists(String name){
    return tick->Utils.call<bool>("creepExists",name);
}

bool Util_flagExists(String name){
    return tick->Utils.call<bool>("flagExists",name);
}

bool Util_roomVisible(String name){
    return tick->Utils.call<bool>("roomVisible",name);
}

number Util_keyLength(JSObject object){
    return tick->Utils.call<number>("keyLength",object);
}

bool Util_deleteProperty(JSObject obj, String property){
    return tick->Utils.call<bool>("DeleteProperty",obj,property);
}

JSArray Util_flagsInRoom(String roomName){
    return tick->Utils.call<JSArray>("flagsInRoom",roomName);
}

JSArray Util_flagsInRoomP(String roomName, number primaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomP",roomName,primaryColor);
}

JSArray Util_flagsInRoomS(String roomName, number secondaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomS",roomName,secondaryColor);
}

JSArray Util_flagsInRoomPS(String roomName, number primaryColor, number secondaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomPS",roomName,primaryColor,secondaryColor);
}

JSArray Util_flagsInRoomNearPS(String roomName,number x, number y,number range, number primaryColor, number secondaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomNearPS",roomName,x,y,range,primaryColor,secondaryColor);
}

bool Util_flagAt(String roomName,number x, number y){
    return tick->Utils.call<bool>("flagAt",roomName,x,y);
}

bool Util_flagAtP(String roomName,number x, number y, number primaryColor){
    return tick->Utils.call<bool>("flagAtP",roomName,x,y,primaryColor);
}

bool Util_flagAtS(String roomName,number x, number y, number secondaryColor){
    return tick->Utils.call<bool>("flagAtS",roomName,x,y,secondaryColor);
}

bool Util_flagAtPS(String roomName,number x, number y, number primaryColor, number secondaryColor){
    return tick->Utils.call<bool>("flagAtPS",roomName,x,y,primaryColor,secondaryColor);
}

bool Util_flagAt(JSObject roomPos){
    return tick->Utils.call<bool>("flagAtRP",roomPos);
}

bool Util_flagAtP(JSObject roomPos, number primaryColor){
    return tick->Utils.call<bool>("flagAtRPP",roomPos,primaryColor);
}

bool Util_flagAtS(JSObject roomPos, number secondaryColor){
    return tick->Utils.call<bool>("flagAtRPS",roomPos,secondaryColor);
}

bool Util_flagAtPS(JSObject roomPos, number primaryColor, number secondaryColor){
    return tick->Utils.call<bool>("flagAtRPPS",roomPos,primaryColor,secondaryColor);
}

JSObject Util_getFirstFlagAt(String roomName,number x, number y){
    return tick->Utils.call<JSObject>("getFirstFlagAt",roomName,x,y);
}

JSObject Util_getFirstFlagAtP(String roomName,number x, number y, number primaryColor){
    return tick->Utils.call<JSObject>("getFirstFlagAtP",roomName,x,y,primaryColor);
}

JSObject Util_getFirstFlagAtS(String roomName,number x, number y, number secondaryColor){
    return tick->Utils.call<JSObject>("getFirstFlagAtS",roomName,x,y,secondaryColor);
}

JSObject Util_getFirstFlagAtPS(String roomName,number x, number y, number primaryColor, number secondaryColor){
    return tick->Utils.call<JSObject>("getFirstFlagAtPS",roomName,x,y,primaryColor,secondaryColor);
}

JSArray Util_getFlagsAt(String roomName,number x, number y){
    return tick->Utils.call<JSArray>("getFlagsAt",roomName,x,y);
}

JSArray Util_getFlagsAtP(String roomName,number x, number y, number primaryColor){
    return tick->Utils.call<JSArray>("getFlagsAtP",roomName,x,y,primaryColor);
}

JSArray Util_getFlagsAtS(String roomName,number x, number y, number secondaryColor){
    return tick->Utils.call<JSArray>("getFlagsAtS",roomName,x,y,secondaryColor);
}

JSArray Util_getFlagsAtPS(String roomName,number x, number y, number primaryColor, number secondaryColor){
    return tick->Utils.call<JSArray>("getFlagsAtPS",roomName,x,y,primaryColor,secondaryColor);
}

number Util_distanceByPathBetween(number x, number y, String roomName, number x2, number y2, String roomName2,number range,bool swamps){
    return tick->Utils.call<number>("distanceByPathBetween",x, y, roomName, x2, y2, roomName2,range,swamps);
}

number Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts){
    tick->Utils.call<void>("setSpawning",spawn);
    if(opts["memory"].isUndefined()){
        opts.set("memory",val::object());
    }
    opts["memory"].as<JSObject>().set("roomSpawnedIn",spawn["room"]["name"].as<String>());
    return spawn.call<number>("spawnCreep",body,name,opts);
}

bool isStructureAt(JSObject room, int x, int y, String structureType){
    String localStackTempString = LOOK_STRUCTURES;
    JSArray arr = room.call<JSArray>("lookForAt",localStackTempString,x,y);
    int iter=0;
    JS_FOREACH(arr,iter){
        if(strcmp(arr[iter]["structureType"].as<String>().c_str(),structureType.c_str()) == 0){
            return true;
        }
    }
    return false;
}

bool isConstructionAt(JSObject room, int x, int y, String structureType){
    String localStackTempString = LOOK_CONSTRUCTION_SITES;
    JSArray arr = room.call<JSArray>("lookForAt",localStackTempString,x,y);
    int iter=0;
    JS_FOREACH(arr,iter){
        if(strcmp(arr[iter]["structureType"].as<String>().c_str(),structureType.c_str()) == 0){
            return true;
        }
    }
    return false;
}

JSObject constructionAt(JSObject room, int x, int y, String structureType){
    String localStackTempString = LOOK_CONSTRUCTION_SITES;
    JSArray arr = room.call<JSArray>("lookForAt",localStackTempString,x,y);
    int iter=0;
    JS_FOREACH(arr,iter){
        if(strcmp(arr[iter]["structureType"].as<String>().c_str(),structureType.c_str()) == 0){
            return arr[iter];
        }
    }
    return null;
}

JSObject structureAt(JSObject room, int x, int y, String structureType){
    String localStackTempString = LOOK_STRUCTURES;
    JSArray arr = room.call<JSArray>("lookForAt",localStackTempString,x,y);
    int iter=0;
    JS_FOREACH(arr,iter){
        if(strcmp(arr[iter]["structureType"].as<String>().c_str(),structureType.c_str()) == 0){
            return arr[iter];
        }
    }
    return null;
}