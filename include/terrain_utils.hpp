//
// Created by tsung on 15/02/2022.
//

#ifndef SCREEPS_TERRAIN_UTILS_H
#define SCREEPS_TERRAIN_UTILS_H

#include <Constants.hpp>
#include <cppreeps.hpp>

struct RoomTerrain{
    char roomName[8];
    unsigned char tiles[50][50];
};
//setRoom, pack roomName & tiles into struct.
RoomTerrain TerrainUtils_loadTerrain(String roomName);

//copy raw terrain data from js to heap
void TerrainUtils_setRoom(String roomName);
//get tile from heap
unsigned char TerrainUtils_get(number x, number y);

//debug poop
void TerrainUtils_print(String roomName);
void TerrainUtils_print2(String roomName);

#endif //SCREEPS_TERRAIN_UTILS_H
