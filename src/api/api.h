//
// Created by tsung on 9/02/2022.
//

#include "../Constants.hpp"

#ifndef SCREEPS_API_H
#define SCREEPS_API_H

bool Util_creepExists(String name);

bool Util_roomVisible(String name);

int Util_keyLength(JSObject object);

bool Util_DeleteProperty(JSObject obj, String property);

#endif //SCREEPS_API_H
