//
// Created by tsung on 9/02/2022.
//

#include <Constants.hpp>
#include <cppreeps.hpp>

#ifndef SCREEPS_API_H
#define SCREEPS_API_H

    using namespace screeps;

void println(String s);

inline static String NAME(JSObject obj){return obj["name"].as<String>();}
inline static String ID(JSObject obj){return obj["id"].as<String>();}
inline static JSObject POS(JSObject obj){return obj["pos"].as<JSObject>();}
inline static number LENGTH(JSArray arr){return arr["length"].as<number>();}



static inline JSObject NEWPOS(number x, number y, String roomName){ return tick->Utils.call<JSObject>("newPos",x,y,roomName);}

#define JS_FOREACH(jsArray,iterator) \
     int _arrLen = jsArray["length"].as<int>();  \
     for (iterator = 0; iterator < _arrLen; iterator++)

number createFlag(JSObject room,number x,number y,String name,number color,number secondaryColor);
number createFlag(JSObject room,number x,number y,number color,number secondaryColor);
number createFlag(JSObject pos,String name,number color,number secondaryColor);
number createFlag(JSObject pos,number color,number secondaryColor);

bool Util_flagAt(String roomName,number x, number y);
bool Util_flagAtP(String roomName,number x, number y, number primaryColor);
bool Util_flagAtS(String roomName,number x, number y, number secondaryColor);
bool Util_flagAtPS(String roomName,number x, number y, number primaryColor, number secondaryColor);

bool Util_flagAt(JSObject roomPos);
bool Util_flagAtP(JSObject roomPos, number primaryColor);
bool Util_flagAtS(JSObject roomPos, number secondaryColor);
bool Util_flagAtPS(JSObject roomPos, number primaryColor, number secondaryColor);

JSObject Util_getFirstFlagAt(String roomName,number x, number y);
JSObject Util_getFirstFlagAtP(String roomName,number x, number y, number primaryColor);
JSObject Util_getFirstFlagAtS(String roomName,number x, number y, number secondaryColor);
JSObject Util_getFirstFlagAtPS(String roomName,number x, number y, number primaryColor, number secondaryColor);

JSArray Util_getFlagsAt(String roomName,number x, number y);
JSArray Util_getFlagsAtP(String roomName,number x, number y, number primaryColor);
JSArray Util_getFlagsAtS(String roomName,number x, number y, number secondaryColor);
JSArray Util_getFlagsAtPS(String roomName,number x, number y, number primaryColor, number secondaryColor);

number Util_distanceByPathBetween(number x, number y, String roomName, number x2, number y2, String roomName2,number range,bool swamps);


Map<String,JSObject> rooms();
Map<String,JSObject> creeps();
inline static JSArray creepsArray(){
    JSObject creepsMap = tick->Game["creeps"].as<JSObject>();
    return val::global("Object").call<JSArray>("values",creepsMap);
};
Map<String,JSObject> flags();
Map<String,JSObject> roomsMem();
Map<String,JSObject> creepsMem();
Map<String,JSObject> flagsMem();
Map<String,JSObject> spawnsMem();
Map<String,JSObject> spawns();
JSArray spawnsNotSpawning(String roomName);
Map<String,JSObject> structures();
Map<String,JSObject> constructionSites();
JSArray sources(String roomName);
JSObject mineral(String roomName);

bool Util_creepExists(String name);
bool Util_flagExists(String name);
bool Util_roomVisible(String name);
number Util_keyLength(JSObject object);
bool Util_deleteProperty(JSObject obj, String property);

JSArray Util_flagsInRoom(String roomName);
JSArray Util_flagsInRoomP(String roomName, number primaryColor);
JSArray Util_flagsInRoomS(String roomName, number secondaryColor);
JSArray Util_flagsInRoomPS(String roomName, number primaryColor, number secondaryColor);
JSArray Util_flagsInRoomNearPS(String roomName,number x, number y,number dist, number primaryColor, number secondaryColor);

number Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts);
static inline String getNewCreepName(){
    //increment counter;
    number counter = tick->Memory["nameCounter"].as<number>();
    tick->Memory.set("nameCounter",counter+1);
    return "C-"+TO_STRING((int)counter)+"-"+(tick->Game["shard"]["name"].as<String>());
}
static inline String getNewSpawnName(){
    //increment counter;
    number counter = tick->Memory["nameCounter"].as<number>();
    tick->Memory.set("nameCounter",counter+1);
    return "S-"+TO_STRING((int)counter);
}

bool isStructureAt(JSObject room, int x, int y, String structureType);
bool isConstructionAt(JSObject room, int x, int y, String structureType);
JSObject structureAt(JSObject room, int x, int y, String structureType);
JSObject constructionAt(JSObject room, int x, int y, String structureType);


#endif //SCREEPS_API_H
