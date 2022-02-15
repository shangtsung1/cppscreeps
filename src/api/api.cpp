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
    return room.call<number>("createFlag",x,y,name,color,secondaryColor);
}

number createFlag(JSObject room,number x,number y,number color,number secondaryColor){
    return room.call<number>("createFlag",x,y,null,color,secondaryColor);
}

number createFlag(JSObject pos,String name,number color,number secondaryColor){
    return pos.call<number>("createFlag",name,color,secondaryColor);
}

number createFlag(JSObject pos,number color,number secondaryColor){
    return pos.call<number>("createFlag",null,color,secondaryColor);
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

Map<String,JSObject> spawns(){
    return js_object_to_map(tick->Game["spawns"]);
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

number Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts){
    return spawn.call<number>("spawnCreep",spawn,body,name,opts);
}

number Util_spawnCreep(JSObject spawn,JSArray body, String name){
    return spawn.call<number>("spawnCreep",spawn,body,name);
}