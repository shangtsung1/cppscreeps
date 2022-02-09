#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <stdio.h>

#include <cppreeps.hpp>
#include <Constants.hpp>
#include <api.hpp>

using namespace screeps;

String getExceptionMessage(intptr_t exceptionPtr) {
  return String(reinterpret_cast<Exception *>(exceptionPtr)->what());
}

void init() {
  INIT();
  if(tick->Memory["rooms"].isUndefined()){
    tick->Memory.set("rooms",val::object());
  }
  if(tick->Memory["creeps"].isUndefined()){
    tick->Memory.set("creeps",val::object());
  }
  if(tick->Memory["war"].isUndefined()){
    tick->Memory.set("war",val::object());
  }
  if(tick->Memory["nameCounter"].isUndefined()){
    tick->Memory.set("nameCounter",0);
  }
  printf("Init Routine Called\n");
}

void mem_gc(){
    Map<String,JSObject> flags_map = js_object_to_map(tick->Memory["creeps"]);
    for(auto const& kv : flags_map) {
        String const &creepName = kv.first;
        if(!Util_creepExists(creepName)){
            Util_deleteProperty(tick->Memory["creeps"],creepName);
        }
    }
}

void loop() {
    INIT();
    mem_gc();
    printf("\nLoop Done\n");
}

EMSCRIPTEN_BINDINGS(loop) {
    emscripten::function("init", &init);
    emscripten::function("loop", &loop);
    emscripten::function("except", &getExceptionMessage);
}
