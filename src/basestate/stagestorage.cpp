//
// Created by tsung on 10/02/2022.
//

#include "stagestorage.h"

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include "stageterminal.h"
#include "../flags/source_mine.h"
#include "../flags/mineral_mine.h"
#include "../flags/controller_upgrade.h"

void stagestorage_loop(JSObject room,JSObject baseFlag){
    if(!room["terminal"].isUndefined() && !room["storage"].isUndefined()
        /* && !controllerLink.isUndefined() && !storageLink.isUndefined()*/){
        baseFlag.call<void>("setColor",COLOR_BLUE,COLOR_BLUE);
        stageterminal_loop(room,baseFlag);
        return;
    }

    source_mine_doRoutine(room);
    mineral_mine_doRoutine(room);
    controller_upgrade_doRoutine(room);
}