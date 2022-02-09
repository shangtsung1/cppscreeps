#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>
#include <map>
#define SPair std::make_pair<std::string,std::string>

inline std::map<std::string,std::string> makeResourceCollectionRoomsMap(){
  std::map<std::string,std::string> m;
  m.insert(SPair("U","W1S15"));
  m.insert(SPair("H","E1S19"));
  m.insert(SPair("X","E4S18"));

  return m;
}

inline std::map<std::string,std::string> resourceCollectionRooms = makeResourceCollectionRoomsMap();


  #include <emscripten.h>
  #include <emscripten/val.h>
  #include <emscripten/bind.h>

  #define Map std::map
  #define String std::string
  #define Exception std::exception
  #define JSObject emscripten::val
  #define JSArray emscripten::val

  #define RESOURCE_SCORE "score"
  #define FIND_SCORE_CONTAINERS 10011
  #define FIND_SCORE_COLLECTORS 10012
  #define WALLS_RADIUS 5
  #define SCORE_CONTAINER_SPAWN_CHANCE 0.01
  #define SCORE_CONTAINER_SPAWN_INTERVAL 500
  #define SCORE_COLLECTOR_SINK 20
  #define SCORE_COLLECTOR_MAX_CAPACITY 20000

  #define ROOM_CROSSROAD 0
  #define ROOM_HIGHWAY 1
  #define ROOM_CENTER 2
  #define ROOM_SOURCE_KEEPER 3
  #define ROOM_STANDARD 4

  #define BASE_MAIN 0
  #define BASE_OUTPOST 1
  #define BASE_RESERVED 2
  #define BASE_STEPPING_STONE 3
  #define BASE_SCOUT 4
  #define OK 0
  #define ERR_NOT_OWNER -1
  #define ERR_NO_PATH -2
  #define ERR_NAME_EXISTS -3
  #define ERR_BUSY -4
  #define ERR_NOT_FOUND -5
  #define ERR_NOT_ENOUGH_ENERGY -6
  #define ERR_NOT_ENOUGH_RESOURCES -6
  #define ERR_INVALID_TARGET -7
  #define ERR_FULL -8
  #define ERR_NOT_IN_RANGE -9
  #define ERR_INVALID_ARGS -10
  #define ERR_TIRED -11
  #define ERR_NO_BODYPART -12
  #define ERR_NOT_ENOUGH_EXTENSIONS -6
  #define ERR_RCL_NOT_ENOUGH -14
  #define ERR_GCL_NOT_ENOUGH -15
  #define FIND_EXIT_TOP 1
  #define FIND_EXIT_RIGHT 3
  #define FIND_EXIT_BOTTOM 5
  #define FIND_EXIT_LEFT 7
  #define FIND_EXIT 10
  #define FIND_CREEPS 101
  #define FIND_MY_CREEPS 102
  #define FIND_HOSTILE_CREEPS 103
  #define FIND_SOURCES_ACTIVE 104
  #define FIND_SOURCES 105
  #define FIND_DROPPED_RESOURCES 106
  #define FIND_STRUCTURES 107
  #define FIND_MY_STRUCTURES 108
  #define FIND_HOSTILE_STRUCTURES 109
  #define FIND_FLAGS 110
  #define FIND_CONSTRUCTION_SITES 111
  #define FIND_MY_SPAWNS 112
  #define FIND_HOSTILE_SPAWNS 113
  #define FIND_MY_CONSTRUCTION_SITES 114
  #define FIND_HOSTILE_CONSTRUCTION_SITES 115
  #define FIND_MINERALS 116
  #define FIND_NUKES 117
  #define FIND_TOMBSTONES 118
  #define FIND_POWER_CREEPS 119
  #define FIND_MY_POWER_CREEPS 120
  #define FIND_HOSTILE_POWER_CREEPS 121
  #define FIND_DEPOSITS 122
  #define FIND_RUINS 123

  #define TOP 1
  #define TOP_RIGHT 2
  #define RIGHT 3
  #define BOTTOM_RIGHT 4
  #define BOTTOM 5
  #define BOTTOM_LEFT 6
  #define LEFT 7
  #define TOP_LEFT 8

  #define COLOR_RED 1
  #define COLOR_PURPLE 2
  #define COLOR_BLUE 3
  #define COLOR_CYAN 4
  #define COLOR_GREEN 5
  #define COLOR_YELLOW 6
  #define COLOR_ORANGE 7
  #define COLOR_BROWN 8
  #define COLOR_GREY 9
  #define COLOR_WHITE 10

  #define LOOK_CREEPS "creep"
  #define LOOK_ENERGY "energy"
  #define LOOK_RESOURCES "resource"
  #define LOOK_SOURCES "source"
  #define LOOK_MINERALS "mineral"
  #define LOOK_DEPOSITS "deposit"
  #define LOOK_STRUCTURES "structure"
  #define LOOK_FLAGS "flag"
  #define LOOK_CONSTRUCTION_SITES "constructionSite"
  #define LOOK_NUKES "nuke"
  #define LOOK_TERRAIN "terrain"
  #define LOOK_TOMBSTONES "tombstone"
  #define LOOK_POWER_CREEPS "powerCreep"
  #define LOOK_RUINS "ruin"
  #define MOVE "move"
  #define WORK "work"
  #define CARRY "carry"
  #define ATTACK "attack"
  #define RANGED_ATTACK "ranged_attack"
  #define TOUGH "tough"
  #define HEAL "heal"
  #define CLAIM "claim"

  #define MOVE_COST 50
  #define WORK_COST 100
  #define CARRY_COST 80
  #define ATTACK_COST 50
  #define HEAL_COST 250
  #define RANGED_ATTACK_COST 150
  #define TOUGH_COST 10
  #define CLAIM_COST 600

  #define CREEP_LIFE_TIME 1500
  #define CREEP_CLAIM_LIFE_TIME 600
  #define CREEP_CORPSE_RATE 0.2
  #define CREEP_PART_MAX_ENERGY 125

  #define CARRY_CAPACITY 50
  #define HARVEST_POWER 2
  #define HARVEST_MINERAL_POWER 1
  #define HARVEST_DEPOSIT_POWER 1
  #define REPAIR_POWER 100
  #define DISMANTLE_POWER 50
  #define BUILD_POWER 5
  #define ATTACK_POWER 30
  #define UPGRADE_CONTROLLER_POWER 1
  #define RANGED_ATTACK_POWER 10
  #define HEAL_POWER 12
  #define RANGED_HEAL_POWER 4
  #define REPAIR_COST 0.01
  #define DISMANTLE_COST 0.005

  #define RAMPART_DECAY_AMOUNT 300
  #define RAMPART_DECAY_TIME 100

  #define ENERGY_REGEN_TIME 300
  #define ENERGY_DECAY 1000

  #define SPAWN_HITS 5000
  #define SPAWN_ENERGY_START 300
  #define SPAWN_ENERGY_CAPACITY 300
  #define CREEP_SPAWN_TIME 3
  #define SPAWN_RENEW_RATIO 1.2

  #define SOURCE_ENERGY_CAPACITY 3000
  #define SOURCE_ENERGY_NEUTRAL_CAPACITY 1500
  #define SOURCE_ENERGY_KEEPER_CAPACITY 4000
  #define ROAD_HITS 5000
  #define ROAD_WEAROUT 1
  #define ROAD_WEAROUT_POWER_CREEP 100
  #define ROAD_DECAY_AMOUNT 100
  #define ROAD_DECAY_TIME 1000

  #define LINK_HITS 1000
  #define LINK_HITS_MAX 1000
  #define LINK_CAPACITY 800
  #define LINK_COOLDOWN 1
  #define LINK_LOSS_RATIO 0.03

  #define STORAGE_CAPACITY 1000000
  #define STORAGE_HITS 10000
  #define STRUCTURE_SPAWN "spawn"
  #define STRUCTURE_EXTENSION "extension"
  #define STRUCTURE_ROAD "road"
  #define STRUCTURE_WALL "constructedWall"
  #define STRUCTURE_RAMPART "rampart"
  #define STRUCTURE_KEEPER_LAIR "keeperLair"
  #define STRUCTURE_PORTAL "portal"
  #define STRUCTURE_CONTROLLER "controller"
  #define STRUCTURE_LINK "link"
  #define STRUCTURE_STORAGE "storage"
  #define STRUCTURE_TOWER "tower"
  #define STRUCTURE_OBSERVER "observer"
  #define STRUCTURE_POWER_BANK "powerBank"
  #define STRUCTURE_POWER_SPAWN "powerSpawn"
  #define STRUCTURE_EXTRACTOR "extractor"
  #define STRUCTURE_LAB "lab"
  #define STRUCTURE_TERMINAL "terminal"
  #define STRUCTURE_CONTAINER "container"
  #define STRUCTURE_NUKER "nuker"
  #define STRUCTURE_FACTORY "factory"
  #define STRUCTURE_INVADER_CORE "invaderCore"


  #define CONTROLLER_DOWNGRADE_RESTORE 100
  #define CONTROLLER_DOWNGRADE_SAFEMODE_THRESHOLD 5000
  #define CONTROLLER_CLAIM_DOWNGRADE 300
  #define CONTROLLER_RESERVE 1
  #define CONTROLLER_RESERVE_MAX 5000
  #define CONTROLLER_MAX_UPGRADE_PER_TICK 15
  #define CONTROLLER_ATTACK_BLOCKED_UPGRADE 1000
  #define CONTROLLER_NUKE_BLOCKED_UPGRADE 200

  #define SAFE_MODE_DURATION 20000
  #define SAFE_MODE_COOLDOWN 50000
  #define SAFE_MODE_COST 1000

  #define TOWER_HITS 3000
  #define TOWER_CAPACITY 1000
  #define TOWER_ENERGY_COST 10
  #define TOWER_POWER_ATTACK 600
  #define TOWER_POWER_HEAL 400
  #define TOWER_POWER_REPAIR 800
  #define TOWER_OPTIMAL_RANGE 5
  #define TOWER_FALLOFF_RANGE 20
  #define TOWER_FALLOFF 0.75

  #define OBSERVER_HITS 500
  #define OBSERVER_RANGE 10

  #define POWER_BANK_HITS 2000000
  #define POWER_BANK_CAPACITY_MAX 5000
  #define POWER_BANK_CAPACITY_MIN 500
  #define POWER_BANK_CAPACITY_CRIT 0.3
  #define POWER_BANK_DECAY 5000
  #define POWER_BANK_HIT_BACK 0.5

  #define POWER_SPAWN_HITS 5000
  #define POWER_SPAWN_ENERGY_CAPACITY 5000
  #define POWER_SPAWN_POWER_CAPACITY 100
  #define POWER_SPAWN_ENERGY_RATIO 50

  #define EXTRACTOR_HITS 500
  #define EXTRACTOR_COOLDOWN 5

  #define LAB_HITS 500
  #define LAB_MINERAL_CAPACITY 3000
  #define LAB_ENERGY_CAPACITY 2000
  #define LAB_BOOST_ENERGY 20
  #define LAB_BOOST_MINERAL 30
  #define LAB_REACTION_AMOUNT 5
  #define LAB_UNBOOST_ENERGY 0
  #define LAB_UNBOOST_MINERAL 15

  #define GCL_POW 2.4
  #define GCL_MULTIPLY 1000000
  #define GCL_NOVICE 3

  #define TERRAIN_MASK_WALL 1
  #define TERRAIN_MASK_SWAMP 2
  #define TERRAIN_MASK_LAVA 4

  #define MAX_CONSTRUCTION_SITES 100
  #define MAX_CREEP_SIZE 50
  #define DENSITY_LOW 1
  #define DENSITY_MODERATE 2
  #define DENSITY_HIGH 3
  #define DENSITY_ULTRA 4

  #define DEPOSIT_EXHAUST_MULTIPLY 0.001
  #define DEPOSIT_EXHAUST_POW 1.2
  #define DEPOSIT_DECAY_TIME 50000

  #define TERMINAL_CAPACITY 300000
  #define TERMINAL_HITS 3000
  #define TERMINAL_SEND_COST 0.1
  #define TERMINAL_MIN_SEND 100
  #define TERMINAL_COOLDOWN 10

  #define CONTAINER_HITS 250000
  #define CONTAINER_CAPACITY 2000
  #define CONTAINER_DECAY 5000
  #define CONTAINER_DECAY_TIME 100
  #define CONTAINER_DECAY_TIME_OWNED 500

  #define NUKER_HITS 1000
  #define NUKER_COOLDOWN 100000
  #define NUKER_ENERGY_CAPACITY 300000
  #define NUKER_GHODIUM_CAPACITY 5000
  #define NUKE_LAND_TIME 50000
  #define NUKE_RANGE 10
  #define FACTORY_HITS 1000
  #define FACTORY_CAPACITY 50000

  #define TOMBSTONE_DECAY_PER_PART 5
  #define TOMBSTONE_DECAY_POWER_CREEP 500
  #define PORTAL_DECAY 30000

  #define ORDER_SELL "sell"
  #define ORDER_BUY "buy"

  #define MARKET_FEE 0.05

  #define MARKET_MAX_ORDERS 300
  //#define MARKET_ORDER_LIFE_TIME 1000*60*60*24*30

  #define FLAGS_LIMIT 10000
  #define SUBSCRIPTION_TOKEN "token"
  #define CPU_UNLOCK "cpuUnlock"
  #define PIXEL "pixel"
  #define ACCESS_KEY "accessKey"

  #define PIXEL_CPU_COST 5000

  #define RESOURCE_ENERGY "energy"
  #define RESOURCE_POWER "power"

  #define RESOURCE_HYDROGEN "H"
  #define RESOURCE_OXYGEN "O"
  #define RESOURCE_UTRIUM "U"
  #define RESOURCE_LEMERGIUM "L"
  #define RESOURCE_KEANIUM "K"
  #define RESOURCE_ZYNTHIUM "Z"
  #define RESOURCE_CATALYST "X"
  #define RESOURCE_GHODIUM "G"

  #define RESOURCE_SILICON "silicon"
  #define RESOURCE_METAL "metal"
  #define RESOURCE_BIOMASS "biomass"
  #define RESOURCE_MIST "mist"

  #define RESOURCE_HYDROXIDE "OH"
  #define RESOURCE_ZYNTHIUM_KEANITE "ZK"
  #define RESOURCE_UTRIUM_LEMERGITE "UL"

  #define RESOURCE_UTRIUM_HYDRIDE "UH"
  #define RESOURCE_UTRIUM_OXIDE "UO"
  #define RESOURCE_KEANIUM_HYDRIDE "KH"
  #define RESOURCE_KEANIUM_OXIDE "KO"
  #define RESOURCE_LEMERGIUM_HYDRIDE "LH"
  #define RESOURCE_LEMERGIUM_OXIDE "LO"
  #define RESOURCE_ZYNTHIUM_HYDRIDE "ZH"
  #define RESOURCE_ZYNTHIUM_OXIDE "ZO"
  #define RESOURCE_GHODIUM_HYDRIDE "GH"
  #define RESOURCE_GHODIUM_OXIDE "GO"

  #define RESOURCE_UTRIUM_ACID "UH2O"
  #define RESOURCE_UTRIUM_ALKALIDE "UHO2"
  #define RESOURCE_KEANIUM_ACID "KH2O"
  #define RESOURCE_KEANIUM_ALKALIDE "KHO2"
  #define RESOURCE_LEMERGIUM_ACID "LH2O"
  #define RESOURCE_LEMERGIUM_ALKALIDE "LHO2"
  #define RESOURCE_ZYNTHIUM_ACID "ZH2O"
  #define RESOURCE_ZYNTHIUM_ALKALIDE "ZHO2"
  #define RESOURCE_GHODIUM_ACID "GH2O"
  #define RESOURCE_GHODIUM_ALKALIDE "GHO2"

  #define RESOURCE_CATALYZED_UTRIUM_ACID "XUH2O"
  #define RESOURCE_CATALYZED_UTRIUM_ALKALIDE "XUHO2"
  #define RESOURCE_CATALYZED_KEANIUM_ACID "XKH2O"
  #define RESOURCE_CATALYZED_KEANIUM_ALKALIDE "XKHO2"
  #define RESOURCE_CATALYZED_LEMERGIUM_ACID "XLH2O"
  #define RESOURCE_CATALYZED_LEMERGIUM_ALKALIDE "XLHO2"
  #define RESOURCE_CATALYZED_ZYNTHIUM_ACID "XZH2O"
  #define RESOURCE_CATALYZED_ZYNTHIUM_ALKALIDE "XZHO2"
  #define RESOURCE_CATALYZED_GHODIUM_ACID "XGH2O"
  #define RESOURCE_CATALYZED_GHODIUM_ALKALIDE "XGHO2"

  #define RESOURCE_OPS "ops"

  #define RESOURCE_UTRIUM_BAR "utrium_bar"
  #define RESOURCE_LEMERGIUM_BAR "lemergium_bar"
  #define RESOURCE_ZYNTHIUM_BAR "zynthium_bar"
  #define RESOURCE_KEANIUM_BAR "keanium_bar"
  #define RESOURCE_GHODIUM_MELT "ghodium_melt"
  #define RESOURCE_OXIDANT "oxidant"
  #define RESOURCE_REDUCTANT "reductant"
  #define RESOURCE_PURIFIER "purifier"
  #define RESOURCE_BATTERY "battery"

  #define RESOURCE_COMPOSITE "composite"
  #define RESOURCE_CRYSTAL "crystal"
  #define RESOURCE_LIQUID "liquid"

  #define RESOURCE_WIRE "wire"
  #define RESOURCE_SWITCH "switch"
  #define RESOURCE_TRANSISTOR "transistor"
  #define RESOURCE_MICROCHIP "microchip"
  #define RESOURCE_CIRCUIT "circuit"
  #define RESOURCE_DEVICE "device"

  #define RESOURCE_CELL "cell"
  #define RESOURCE_PHLEGM "phlegm"
  #define RESOURCE_TISSUE "tissue"
  #define RESOURCE_MUSCLE "muscle"
  #define RESOURCE_ORGANOID "organoid"
  #define RESOURCE_ORGANISM "organism"

  #define RESOURCE_ALLOY "alloy"
  #define RESOURCE_TUBE "tube"
  #define RESOURCE_FIXTURES "fixtures"
  #define RESOURCE_FRAME "frame"
  #define RESOURCE_HYDRAULICS "hydraulics"
  #define RESOURCE_MACHINE "machine"

  #define RESOURCE_CONDENSATE "condensate"
  #define RESOURCE_CONCENTRATE "concentrate"
  #define RESOURCE_EXTRACT "extract"
  #define RESOURCE_SPIRIT "spirit"
  #define RESOURCE_EMANATION "emanation"
  #define RESOURCE_ESSENCE "essence"

  #define PORTAL_UNSTABLE 10*24*3600*1000
  #define PORTAL_MIN_TIMEOUT 12*24*3600*1000
  #define PORTAL_MAX_TIMEOUT 22*24*3600*1000

  #define POWER_BANK_RESPAWN_TIME 50000

  #define INVADERS_ENERGY_GOAL 100000

  #define SYSTEM_USERNAME "Screeps"
  #define SIGN_PLANNED_AREA "A new Novice or Respawn Area is being planned somewhere in this sector. Please make sure all important rooms are reserved."

  #define EVENT_ATTACK 1
  #define EVENT_OBJECT_DESTROYED 2
  #define EVENT_ATTACK_CONTROLLER 3
  #define EVENT_BUILD 4
  #define EVENT_HARVEST 5
  #define EVENT_HEAL 6
  #define EVENT_REPAIR 7
  #define EVENT_RESERVE_CONTROLLER 8
  #define EVENT_UPGRADE_CONTROLLER 9
  #define EVENT_EXIT 10
  #define EVENT_POWER 11
  #define EVENT_TRANSFER 12

  #define EVENT_ATTACK_TYPE_MELEE 1
  #define EVENT_ATTACK_TYPE_RANGED 2
  #define EVENT_ATTACK_TYPE_RANGED_MASS 3
  #define EVENT_ATTACK_TYPE_DISMANTLE 4
  #define EVENT_ATTACK_TYPE_HIT_BACK 5
  #define EVENT_ATTACK_TYPE_NUKE 6

  #define EVENT_HEAL_TYPE_MELEE 1
  #define EVENT_HEAL_TYPE_RANGED 2

  #define POWER_LEVEL_MULTIPLY 1000
  #define POWER_LEVEL_POW 2
  #define POWER_CREEP_SPAWN_COOLDOWN 8*3600*1000
  #define POWER_CREEP_DELETE_COOLDOWN 24*3600*1000
  #define POWER_CREEP_MAX_LEVEL 25
  #define POWER_CREEP_LIFE_TIME 5000

  #define PWR_GENERATE_OPS 1
  #define PWR_OPERATE_SPAWN 2
  #define PWR_OPERATE_TOWER 3
  #define PWR_OPERATE_STORAGE 4
  #define PWR_OPERATE_LAB 5
  #define PWR_OPERATE_EXTENSION 6
  #define PWR_OPERATE_OBSERVER 7
  #define PWR_OPERATE_TERMINAL 8
  #define PWR_DISRUPT_SPAWN 9
  #define PWR_DISRUPT_TOWER 10
  #define PWR_DISRUPT_SOURCE 11
  #define PWR_SHIELD 12
  #define PWR_REGEN_SOURCE 13
  #define PWR_REGEN_MINERAL 14
  #define PWR_DISRUPT_TERMINAL 15
  #define PWR_OPERATE_POWER 16
  #define PWR_FORTIFY 17
  #define PWR_OPERATE_CONTROLLER 18
  #define PWR_OPERATE_FACTORY 19

  #define EFFECT_INVULNERABILITY 1001
  #define EFFECT_COLLAPSE_TIMER 1002

  #define INVADER_CORE_HITS 100000
#endif
