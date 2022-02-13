//
// Created by tsung on 9/02/2022.
//

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

using namespace screeps;

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

number Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts){
    return spawn.call<number>("spawnCreep",spawn,body,name,opts);
}

number Util_spawnCreep(JSObject spawn,JSArray body, String name){
    return spawn.call<number>("spawnCreep",spawn,body,name);
}