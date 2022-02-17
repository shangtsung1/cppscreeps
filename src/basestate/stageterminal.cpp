//
// Created by tsung on 10/02/2022.
//

#include "stageterminal.h"

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include "../flags/source_mine.h"
#include "../flags/mineral_mine.h"
#include "../flags/controller_upgrade.h"

void stageterminal_loop(JSObject room,JSObject baseFlag){
    source_mine_doRoutine(room);
    mineral_mine_doRoutine(room);
    controller_upgrade_doRoutine(room);
}