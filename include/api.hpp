//
// Created by tsung on 9/02/2022.
//

#include <Constants.hpp>

#ifndef SCREEPS_API_H
#define SCREEPS_API_H

number createFlag(JSObject room,number x,number y,String name,number color,number secondaryColor);
number createFlag(JSObject room,number x,number y,number color,number secondaryColor);
number createFlag(JSObject pos,String name,number color,number secondaryColor);
number createFlag(JSObject pos,number color,number secondaryColor);

Map<String,JSObject> rooms();
Map<String,JSObject> creeps();
Map<String,JSObject> flags();
Map<String,JSObject> spawns();
Map<String,JSObject> structures();
Map<String,JSObject> constructionSites();


bool Util_creepExists(String name);

bool Util_roomVisible(String name);

number Util_keyLength(JSObject object);

bool Util_deleteProperty(JSObject obj, String property);

JSArray Util_flagsInRoom(String roomName);

JSArray Util_flagsInRoomP(String roomName, number primaryColor);

JSArray Util_flagsInRoomS(String roomName, number secondaryColor);

JSArray Util_flagsInRoomPS(String roomName, number primaryColor, number secondaryColor);

number Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts);

number Util_spawnCreep(JSObject spawn,JSArray body, String name);



#endif //SCREEPS_API_H
