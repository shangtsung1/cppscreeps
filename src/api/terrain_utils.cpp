//
// Created by tsung on 15/02/2022.
//

#include <terrain_utils.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include <string.h>

using namespace screeps;

unsigned char* buffer = (unsigned char*)malloc(2500);

void TerrainUtils_setRoom(String roomName){
    tick->Utils.call<void>("roomMemCopy",roomName,*buffer);
}

unsigned char TerrainUtils_get(number x, number y){
    return *(buffer + ((int)y * 50 + (int)x));
}

RoomTerrain TerrainUtils_loadTerrain(String roomName){
    struct RoomTerrain terrain;
    strcpy(terrain.roomName,roomName.c_str());
    TerrainUtils_setRoom(roomName);
    for(int x = 0; x < 50; x++) {
        for (int y = 0; y < 50; y++) {
            terrain.tiles[x][y] = TerrainUtils_get(x, y);
        }
    }
    return terrain;
}

void TerrainUtils_print(String roomName){
    TerrainUtils_setRoom(roomName);
    unsigned char* pointer = buffer;
    unsigned char tileId = 0;
    for(int i = 0; i < 2500; i++){
        tileId = *pointer;
        printf("isSwamp=%i",tileId & TERRAIN_MASK_SWAMP);
        printf("isWall=%i",tileId & TERRAIN_MASK_WALL);
        printf("isPlain=%i\n",tileId == 0);
        pointer++;
    }
}

void TerrainUtils_print2(String roomName){
    TerrainUtils_setRoom(roomName);
    unsigned char tileId;
    for(int x = 0; x < 50; x++){
        for(int y = 0; y < 50; y++){
            tileId = TerrainUtils_get(x, y);
            printf("isSwamp=%i",tileId & TERRAIN_MASK_SWAMP);
            printf("isWall=%i",tileId & TERRAIN_MASK_WALL);
            printf("isPlain=%i\n",tileId == 0);
        }
    }
}