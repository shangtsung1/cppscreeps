//
// Created by tsung on 18/02/2022.
//
//included into method body in loop.cpp

//PARAM{String flagName, JSObject flag}
//LOCAL{JSObject creep,String bodyType,JSArray spawnDefs, int ii}

int primaryColor = flag["color"].as<int>();
int secondaryColor = flag["secondaryColor"].as<int>();

switch(primaryColor){
    case COLOR_RED://military
        #if __FRUMP__
            #include "../military/combat_actions.cpp"
        #endif
        break;
    case COLOR_PURPLE://ECON
        switch(secondaryColor){
            case COLOR_PURPLE://Base mining node.
                if(strcmp(bodyType.c_str(), "hauler") == 0){
                    source_mine_haulerTask(flag,creep);
                }
                else if(strcmp(bodyType.c_str(), "miner") == 0){
                    source_mine_workerTask(flag,creep);
                }
                break;
            default:
                printf("Unhandled ECON Flag Color (%i,%i)\n",primaryColor,secondaryColor);
                break;
        }
        break;
    case COLOR_BLUE://BaseStage
        break;
    //case COLOR_CYAN://
        //break;
    case COLOR_GREEN://BaseTask
        switch(secondaryColor){
            default:
                printf("Unhandled BaseTask Flag Color (%i,%i)\n",primaryColor,secondaryColor);
                break;
        }
    break;
    //case COLOR_YELLOW://
        //break;
    //case COLOR_ORANGE://
        //break;
    //case COLOR_BROWN://SEASONAL
        //break;
    //case COLOR_GREY://
        //break;
    case COLOR_WHITE://Debug/override
        switch(secondaryColor){
            default:
                printf("Unhandled Debug Flag Color (%i,%i)\n",primaryColor,secondaryColor);
                break;
        }
        break;
    default:
        printf("Unhandled Flag Color (%i,%i)\n",primaryColor,secondaryColor);
        break;
}