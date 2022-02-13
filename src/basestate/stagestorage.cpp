//
// Created by tsung on 10/02/2022.
//

#include "stagestorage.h"

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>
#include "stageterminal.h"

void stagestorage_loop(JSObject room,JSObject baseFlag){
    if(!room["terminal"].isUndefined() && !room["storage"].isUndefined()
        /* && !controllerLink.isUndefined() && !storageLink.isUndefined()*/){
        baseFlag.call<void>("setColor",COLOR_BLUE,COLOR_BLUE);
        stageterminal_loop(room,baseFlag);
        return;
    }
}