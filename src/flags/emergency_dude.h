//
// Created by tsung on 17/02/2022.
//

#ifndef SCREEPS_EMERGENCY_DUDE_H
#define SCREEPS_EMERGENCY_DUDE_H
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

void emergency_dude_doRoutine(JSObject room);

void emergency_dude_doTaskW(JSObject flag,JSObject creep);
void emergency_dude_doTaskH(JSObject flag,JSObject creep);

#endif //SCREEPS_EMERGENCY_DUDE_H
