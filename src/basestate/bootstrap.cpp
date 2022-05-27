//
// Created by tsung on 10/02/2022.
//

#include "bootstrap.h"

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include "stagestorage.h"
#include "../flags/source_mine.h"
#include "../flags/mineral_mine.h"
#include "../flags/controller_upgrade.h"
#include "../flags/builder.h"
#include "../flags/repair.h"
#include "../flags/emergency_dude.h"

void bootstrap_loop(JSObject room,JSObject baseFlag){
    if(!room["storage"].isUndefined()){
        //we have a storage, we should change the flag color.
        baseFlag.call<void>("setColor",COLOR_BLUE,COLOR_PURPLE);
        //immediately call the next stage so we dont miss a turn
        stagestorage_loop(room,baseFlag);
        return;
    }
    source_mine_doRoutine(room);
    mineral_mine_doRoutine(room);
    controller_upgrade_doRoutine(room);
    builder_doRoutine(room);
    repair_doRoutine(room);
    emergency_dude_doRoutine(room);

}