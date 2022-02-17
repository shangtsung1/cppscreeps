//
// Created by tsung on 17/02/2022.
//

#ifndef SCREEPS_CREEP_H
#define SCREEPS_CREEP_H

#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

struct CreepDefinition{
        String bodyType;
        bool offRoad;
        number maxSize;
        number priority;//0-5
        String currentCreep;
};

#endif //SCREEPS_CREEP_H
