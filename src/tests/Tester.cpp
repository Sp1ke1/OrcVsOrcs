#include "../Map.h"
#include "../GameStatics.h"
#include "../GameEngine.h"
#include "../GameObjects/Actors/Player/PlayerCharacter.h"
#include <iostream> 
void MapLoaderTest ()
{
    Map map;
    assert ( GameStatics::Init( "test" ) );

    try { 
        map.LoadMap( GameStatics::PLATFORM_ENEMY_DEFAULT_COLMS, GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS, "examples/maps/wrong_map1.txt" );
        std::cerr <<"Loaded a bad map: examples/maps/wrong_map1" << std::endl;
        exit(1);
    }
    catch ( const MapException & error )
    {
        
    }
    try {
        map.LoadMap ( GameStatics::PLATFORM_ENEMY_DEFAULT_COLMS, GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS, "examples/maps/wrong_map2.txt"); 
        std::cerr <<"Loaded a bad map: examples/maps/wrong_map2" << std::endl;
        exit(1);
    }
    catch ( const MapException & error )
    {

    }
    try {
        map.LoadMap ( GameStatics::PLATFORM_ENEMY_DEFAULT_COLMS, GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS, "examples/maps/wrong_map3.txt"); 
        std::cerr <<"Loaded a bad map: examples/maps/wrong_map3" << std::endl;
        exit(1);
    }
    catch ( const MapException & error )
    {

    }
    try 

    {
        map . LoadMap ( GameStatics :: PLATFORM_ENEMY_DEFAULT_COLMS, GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS, "examples/maps/wrong_map4.txt" );
        std::cerr << "Loaded a bad map: examples/maps/wrong_map4" << std::endl; 
        exit ( 1 );
    }
    catch ( const MapException & error ) {
        
    }
    try {
        map.LoadMap( GameStatics::PLATFORM_ENEMY_DEFAULT_COLMS, GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS );
    }
    catch ( const MapException & error )
    {
        std::cerr << "Erorr during loading of the default map" << std::endl;
        exit ( 1 );
    }
    std::cout << "MapLoaderTest passed" << std::endl;
}

void EngineTest () 
{
    assert ( GameStatics::Init( "test" )); 
    assert ( GameEngine::Init() ); 
    assert ( !GameEngine::Init() ); 
    try {
        GameEngine::LoadTexture ("WrongTexture" ); 
        std::cerr << "No exception with wrong texture" << std::endl; 
        exit ( 1 );
    }
    catch (  const AssetManagerException & error ) {
        
    }
    std::shared_ptr <Texture> playerTex;
    try { playerTex = GameEngine::LoadTexture( "PlayerTexLeft" );
    }
    catch (  const AssetManagerException & error )
    {
        std::cerr << "Wrong exception with valid texture name" << std::endl;
        exit ( 1 );
    }
    auto player = std::make_shared<PlayerCharacter> ( PlayerCharacter( GameStatics::AllocObjectID(),
                                                                        playerTex,
                                                                        SDL_Rect {0,0,0,0},
                                                                        100,
                                                                        100,
                                                                        100,
                                                                        100 ) );
    assert ( GameEngine::RegisterActor ( player ) );
    assert ( ! ( GameEngine::RegisterActor ( player ) ) );
    assert ( GameEngine::DestroyActor ( player -> GetObjectID() ) );
    std::cout << "EngineTest passed" << std::endl;
}
void CollisionsTests ()
{
    auto physX = std::make_unique <PhysicsSubSystem> ( PhysicsSubSystem( 200, 200 ));
    std::pair<int,int> test;
    SDL_Rect first {0,0,100,100};
    SDL_Rect second {50,50,100,100};
    assert ( physX -> CheckCollisions ( first, second, test ) );
    first = {0,0,50,50};
    second = {100,100,50,50}; 
    assert (!physX -> CheckCollisions ( first, second, test ) );

    std::cout << "CollisionTest passed" << std::endl;
}

void GameStaticsTest()

{
    if ( GameStatics::Init ( "testPlayer", "examples/bad_config1.txt") ){
        std::cerr << "Loaded bad config examples/bad_config1.txt" << std::endl;
        exit ( 1 );
    }

    if ( GameStatics::Init ( "testPlayer", "examples/bad_config2.txt") ){
        std::cerr << "Loaded bad config examples/bad_config2.txt" << std::endl;
        exit ( 1 );
    }

    if ( GameStatics::Init ( "testPlayer", "examples/bad_config3.txt") ){
        std::cerr << "Loaded bad config examples/bad_config3.txt" << std::endl;
        exit ( 1 );
    }

    assert ( GameStatics :: Init ( "testPlayer") );
    std::cout <<"GameStaticsTest passed" << std::endl;

}

int main ( void )
{
    GameStaticsTest(); 
    MapLoaderTest();
    EngineTest();
    CollisionsTests();

    return 0;
}