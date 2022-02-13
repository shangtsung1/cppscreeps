//
// Created by tsung on 10/02/2022.
//

#include "bootstrap.h"

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include "stagestorage.h"

void bootstrap_loop(JSObject room,JSObject baseFlag){
    if(!room["storage"].isUndefined()){
        //we have a storage, we should change the flag color.
        baseFlag.call<void>("setColor",COLOR_BLUE,COLOR_PURPLE);
        //immediately call the next stage so we dont miss a turn
        stagestorage_loop(room,baseFlag);
        return;
    }
}