//
// Created by tsung on 17/02/2022.
//

#include "bodybuilder.h"
#include <Constants.hpp>
#include <creep.hpp>
#include <cppreeps.hpp>
#include <stdio.h>
#include <string.h>

using namespace screeps;

JSArray BodyBuilder_getBody(JSObject room,CreepDefinition def){
    JSArray body = val::array();
    if (strcmp(def.bodyType.c_str(), "miner") == 0){
        number energyAvailable = room["energyCapacityAvailable"].as<number>()-100;
        body.call<void>("push",std::string(CARRY));
        body.call<void>("push",std::string(MOVE));
        for(int i = 0 ; (i < ((energyAvailable/100)-1) && i < def.maxSize);i++){
            body.call<void>("push",std::string(WORK));
        }
    }
    else if (strcmp(def.bodyType.c_str(), "hauler") == 0){
        number energyAvailable = room["energyCapacityAvailable"].as<number>();
        for(int i = 0 ; (i < ((energyAvailable/100)-1) && i < def.maxSize);i++){
            body.call<void>("push",std::string(CARRY));
            body.call<void>("push",std::string(MOVE));
        }
    }
    else if (strcmp(def.bodyType.c_str(), "upgrader") == 0){
        number energyAvailable = room["energyCapacityAvailable"].as<number>();
        for(int i = 0 ; (i < ((energyAvailable/250)-1) && i < def.maxSize);i++){
            body.call<void>("push",std::string(CARRY));
            body.call<void>("push",std::string(MOVE));
            body.call<void>("push",std::string(MOVE));
            body.call<void>("push",std::string(WORK));
        }
    }
    else if (strcmp(def.bodyType.c_str(), "worker") == 0){
        number energyAvailable = room["energyCapacityAvailable"].as<number>();
        for(int i = 0 ; (i < ((energyAvailable/250)-1) && i < def.maxSize);i++){
            body.call<void>("push",std::string(CARRY));
            body.call<void>("push",std::string(MOVE));
            body.call<void>("push",std::string(MOVE));
            body.call<void>("push",std::string(WORK));
        }
    }
    else{
        printf("Cant find body for creep");
    }
    return body;
}