//
// Created by tsung on 9/02/2022.
//

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

using namespace screeps;

int createFlag(JSObject room,int x,int y,String name,int color,int secondaryColor){
    return room.call<int>("createFlag",x,y,name,color,secondaryColor);
}

int createFlag(JSObject room,int x,int y,int color,int secondaryColor){
    return room.call<int>("createFlag",x,y,null,color,secondaryColor);
}

int createFlag(JSObject pos,String name,int color,int secondaryColor){
    return pos.call<int>("createFlag",name,color,secondaryColor);
}

int createFlag(JSObject pos,int color,int secondaryColor){
    return pos.call<int>("createFlag",null,color,secondaryColor);
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

bool Util_creepExists(String name){
    return tick->Utils.call<bool>("creepExists",name);
}

bool Util_roomVisible(String name){
    return tick->Utils.call<bool>("roomVisible",name);
}

int Util_keyLength(JSObject object){
    return tick->Utils.call<int>("keyLength",object);
}

bool Util_deleteProperty(JSObject obj, String property){
    return tick->Utils.call<bool>("DeleteProperty",obj,property);
}

JSArray Util_flagsInRoom(String roomName){
    return tick->Utils.call<JSArray>("flagsInRoom",roomName);
}

JSArray Util_flagsInRoomP(String roomName, int primaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomP",roomName,primaryColor);
}

JSArray Util_flagsInRoomS(String roomName, int secondaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomS",roomName,secondaryColor);
}

JSArray Util_flagsInRoomPS(String roomName, int primaryColor, int secondaryColor){
    return tick->Utils.call<JSArray>("flagsInRoomPS",roomName,primaryColor,secondaryColor);
}

int Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts){
    return spawn.call<int>("spawnCreep",spawn,body,name,opts);
}

int Util_spawnCreep(JSObject spawn,JSArray body, String name){
    return spawn.call<int>("spawnCreep",spawn,body,name);
}