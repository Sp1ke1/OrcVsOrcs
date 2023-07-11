#include "Game.h"
int main ( int argc, char ** argv )
{
    if ( argc > 3 )
    {
        std::cerr << "Usage: ./OrcVsOrcs <OPT: MapRelPath> <OPT: PlayerName>" << std::endl;
        return 1;
    }


    std::string mapName;
    std::string playerName;
    argc > 1 ? mapName = argv[1] : mapName = "examples/maps/default_map.txt";
    argc > 2 ? playerName = argv[2] : playerName = "Not_F_BlessRNG";

    Game app;
    if ( app . Init( mapName, playerName ) != 0 )
    {
        return 1;
    }
    if ( app . Start() != 0 )
    {

        std::cerr << "Error during start of the game!" << std::endl;
        std::cerr << "Usage: ./OrcVsOrcs <OPT: MapRelPath> <OPT: PlayerName>" << std::endl;
    }
    return 0;
}