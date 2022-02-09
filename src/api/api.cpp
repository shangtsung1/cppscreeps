//
// Created by tsung on 9/02/2022.
//

#include <api.hpp>
#include <Constants.hpp>
#include <cppreeps.hpp>

using namespace screeps;

bool Util_creepExists(String name){
    return tick->Utils.call<bool>("creepExists",name);
}

bool Util_roomVisible(String name){
    return tick->Utils.call<bool>("roomVisible",name);
}

int Util_keyLength(JSObject object){
    return tick->Utils.call<int>("keyLength",object);
}

bool Util_deleteProperty(JSObject obj, String property){
    return tick->Utils.call<bool>("DeleteProperty",obj,property);
}