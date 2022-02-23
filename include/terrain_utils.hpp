//
// Created by tsung on 15/02/2022.
//

#ifndef SCREEPS_TERRAIN_UTILS_H
#define SCREEPS_TERRAIN_UTILS_H

#include <Constants.hpp>
#include <cppreeps.hpp>

JSArray TerrainUtils_getRoom(String roomName);
unsigned char TerrainUtils_get(JSArray buffer,number x, number y);

#endif //SCREEPS_TERRAIN_UTILS_H
