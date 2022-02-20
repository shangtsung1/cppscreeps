//
// Created by tsung on 17/02/2022.
//

#ifndef SCREEPS_SOURCE_MINE_H
#define SCREEPS_SOURCE_MINE_H

#include <cppreeps.hpp>
#include <Constants.hpp>
#include <api.hpp>

void source_mine_doRoutine(JSObject room);
//void source_mine_setFlags(JSObject room);

void source_mine_workerTask(JSObject flag,JSObject creep);
void source_mine_haulerTask(JSObject flag,JSObject creep);

#endif //SCREEPS_SOURCE_MINE_H
