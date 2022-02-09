//
// Created by tsung on 9/02/2022.
//

#include <Constants.hpp>

#ifndef SCREEPS_API_H
#define SCREEPS_API_H

bool Util_creepExists(String name);

bool Util_roomVisible(String name);

int Util_keyLength(JSObject object);

bool Util_deleteProperty(JSObject obj, String property);

JSArray Util_flagsInRoom(String roomName);

JSArray Util_flagsInRoomP(String roomName, int primaryColor);

JSArray Util_flagsInRoomS(String roomName, int secondaryColor);

JSArray Util_flagsInRoomPS(String roomName, int primaryColor, int secondaryColor);

int Util_spawnCreep(JSObject spawn,JSArray body, String name, JSObject opts);

int Util_spawnCreep(JSObject spawn,JSArray body, String name);



#endif //SCREEPS_API_H
