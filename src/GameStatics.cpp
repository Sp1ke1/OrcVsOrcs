#include "GameStatics.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::string GameStatics::PLAYER_NAME;
uint32_t GameStatics::TARGET_FPS;
uint32_t GameStatics::FRAME_DELAY;

uint32_t GameStatics::RESOLUTION_X;
uint32_t GameStatics::RESOLUTION_Y;
std::string GameStatics::APP_NAME;

int GameStatics::PLAYER_DEFAULT_HP;
int GameStatics::PLAYER_DEFAULT_SPEED;
int GameStatics::PLAYER_DEFAULT_ATTACK;
int GameStatics::PLAYER_DEFAULT_JUMP_HEIGHT;
float GameStatics::PLAYER_DEFAULT_ATTACK_COOL_DOWN;
uint32_t GameStatics::PLAYER_DEFAULT_BULLET_SPEED;

int GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS;
int GameStatics::PLATFORM_ENEMY_DEFAULT_COLMS;
int GameStatics::PLATFORM_ENEMY_DEFAULT_Y_OFFSET;
int GameStatics::PLATFORM_ENEMY_DEFAULT_X_OFFSET;
int GameStatics::PLATFORM_ENEMY_DEFAULT_HP;
int GameStatics::PLATFORM_ENEMY_DEFAULT_WIDTH;
int GameStatics::PLATFORM_ENEMY_DEFAULT_HEIGHT;
int GameStatics::PLATFORM_ENEMY_BULLET_SPEED;
float GameStatics::PLATFORM_ENEMY_SPAWN_COOL_DOWN;
int GameStatics::PLATFORM_ENEMY_DEFAULT_SCORE;

uint32_t GameStatics::ObjectIDCnt = 0;
int GameStatics::GROUND_ENEMY_DEFAULT_SPAWN_Y;
int GameStatics::GROUND_ENEMY_DEFAULT_HP;
int GameStatics::GROUND_ENEMY_DEFAULT_DAMAGE;
int GameStatics::GROUND_ENEMY_SPAWN_DELAY;
int GameStatics::GROUND_ENEMY_BULLET_SPEED;
float GameStatics::GROUND_ENEMY_ATTACK_COOLDOWN;
int GameStatics::GROUND_ENEMY_DEFAULT_SCORE;

// bonuses defaults
uint32_t GameStatics::BONUS_DEFAULT_BULLET_SPEED;
uint32_t GameStatics::BONUS_DEFAULT_HP_BONUS;
uint32_t GameStatics::BONUS_DEFAULT_SCORE_BONUS;
float GameStatics::BONUS_DEFAULT_SPAWN_CHANCE;
int GameStatics::BONUS_DEFAULT_WIDTH;
int GameStatics::BONUS_DEFAULT_HEIGHT;


bool ReadAndCheckArg ( std::ifstream & in, const char * argName )
{
    std::string buffer;
    if ( !(in >> buffer) || buffer . size () < 3  ) {
        return false;
    }
    std::string argRead ( buffer.begin() + 1, buffer . end() - 1);
    if ( argRead != argName )
        return false;
    else
        return true;
}
bool GameStatics::Init ( const std::string & playerName )
{
    return Init ( playerName, DEFAULT_CONFIG_FILE_PATH );
}
bool GameStatics::Init( const std::string & playerName, const std::string & configPath ) {
    InternalCheck();
    std::ifstream in ( configPath );
    std::string argBuffer;
    if ( in . fail() )
        return false;
    PLAYER_NAME = playerName;
    if ( !ReadAndCheckArg( in, "TARGET_FPS" ) )
        return false;
    if ( !(in >> TARGET_FPS ) || TARGET_FPS < 10 || TARGET_FPS > 120 )
        return false;
    FRAME_DELAY = 1000 / TARGET_FPS;
    if ( !ReadAndCheckArg( in, "RESOLUTION_X" ) )
        return false;
    if ( !(in >> RESOLUTION_X ) || RESOLUTION_X < 1280 )
        return false;
    if ( !ReadAndCheckArg( in, "RESOLUTION_Y") )
        return false;
    if ( !(in >> RESOLUTION_Y) || RESOLUTION_Y < 720 )
        return false;
    if ( !ReadAndCheckArg( in, "APPNAME" ) )
        return false;
    if ( !(in >> APP_NAME ) )
        return false;
    // ----------------- LOAD PLAYER DEFAULTS --------------------- //
    if ( !ReadAndCheckArg( in, "PLAYER_DEFAULT_HP") )
        return false;
    if (!(in >> PLAYER_DEFAULT_HP ) || PLAYER_DEFAULT_HP <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLAYER_DEFAULT_SPEED") )
        return false;
    if (!(in >> PLAYER_DEFAULT_SPEED) || PLAYER_DEFAULT_SPEED <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLAYER_DEFAULT_ATTACK") )
        return false;
    if (!(in >> PLAYER_DEFAULT_ATTACK ) || PLAYER_DEFAULT_ATTACK <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLAYER_DEFAULT_JUMP_HEIGHT") )
        return false;
    if (!(in >> PLAYER_DEFAULT_JUMP_HEIGHT ) || PLAYER_DEFAULT_JUMP_HEIGHT <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLAYER_DEFAULT_ATTACK_COOL_DOWN") )
        return false;
    if (!(in >> PLAYER_DEFAULT_ATTACK_COOL_DOWN ) || PLAYER_DEFAULT_ATTACK_COOL_DOWN <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLAYER_DEFAULT_BULLET_SPEED") )
        return false;
    if (!(in >> PLAYER_DEFAULT_BULLET_SPEED ) || PLAYER_DEFAULT_BULLET_SPEED <= 0 )
        return false;
    // ----------------- LOAD PLATFORM_ENEMY DEFAULTS --------------------- //
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_ROWS") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_ROWS ) || PLATFORM_ENEMY_DEFAULT_ROWS <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_COLMS") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_COLMS) || PLATFORM_ENEMY_DEFAULT_COLMS <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_Y_OFFSET") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_Y_OFFSET ) || PLATFORM_ENEMY_DEFAULT_Y_OFFSET <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_X_OFFSET") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_X_OFFSET ) || PLATFORM_ENEMY_DEFAULT_X_OFFSET <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_HP") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_HP ) || PLATFORM_ENEMY_DEFAULT_HP <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_WIDTH") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_WIDTH ) || PLATFORM_ENEMY_DEFAULT_WIDTH <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_HEIGHT") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_HEIGHT ) || PLATFORM_ENEMY_DEFAULT_HEIGHT <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_BULLET_SPEED") )
        return false;
    if (!(in >> PLATFORM_ENEMY_BULLET_SPEED ) || PLATFORM_ENEMY_BULLET_SPEED <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_SPAWN_COOL_DOWN") )
        return false;
    if (!(in >> PLATFORM_ENEMY_SPAWN_COOL_DOWN ) || PLATFORM_ENEMY_SPAWN_COOL_DOWN <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "PLATFORM_ENEMY_DEFAULT_SCORE") )
        return false;
    if (!(in >> PLATFORM_ENEMY_DEFAULT_SCORE ) || PLATFORM_ENEMY_DEFAULT_SCORE <= 0 )
        return false;
    // ----------------- LOAD GROUND_ENEMY DEFAULTS --------------------- //
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_DEFAULT_SPAWN_Y") )
        return false;
    if (!(in >> GROUND_ENEMY_DEFAULT_SPAWN_Y ) || GROUND_ENEMY_DEFAULT_SPAWN_Y <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_DEFAULT_HP") )
        return false;
    if (!(in >> GROUND_ENEMY_DEFAULT_HP ) || GROUND_ENEMY_DEFAULT_HP <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_DEFAULT_DAMAGE") )
        return false;
    if (!(in >> GROUND_ENEMY_DEFAULT_DAMAGE ) || GROUND_ENEMY_DEFAULT_DAMAGE <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_SPAWN_DELAY") )
        return false;
    if (!(in >> GROUND_ENEMY_SPAWN_DELAY ) || GROUND_ENEMY_SPAWN_DELAY <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_BULLET_SPEED") )
        return false;
    if (!(in >> GROUND_ENEMY_BULLET_SPEED ) || GROUND_ENEMY_BULLET_SPEED <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_ATTACK_COOLDOWN") )
        return false;
    if (!(in >> GROUND_ENEMY_ATTACK_COOLDOWN ) || GROUND_ENEMY_ATTACK_COOLDOWN <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "GROUND_ENEMY_DEFAULT_SCORE") )
        return false;
    if (!(in >> GROUND_ENEMY_DEFAULT_SCORE ) || GROUND_ENEMY_DEFAULT_SCORE <= 0 )
        return false;
    // ----------------- LOAD BONUSES DEFAULTS --------------------- //
    if ( !ReadAndCheckArg( in, "BONUS_DEFAULT_BULLET_SPEED") )
        return false;
    if (!(in >> BONUS_DEFAULT_BULLET_SPEED ) || BONUS_DEFAULT_BULLET_SPEED <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "BONUS_DEFAULT_HP_BONUS") )
        return false;
    if (!(in >> BONUS_DEFAULT_HP_BONUS ) || BONUS_DEFAULT_HP_BONUS <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "BONUS_DEFAULT_SCORE_BONUS") )
        return false;
    if (!(in >> BONUS_DEFAULT_SCORE_BONUS ) || BONUS_DEFAULT_SCORE_BONUS <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "BONUS_DEFAULT_SPAWN_CHANCE") )
        return false;
    if (!(in >> BONUS_DEFAULT_SPAWN_CHANCE ) || BONUS_DEFAULT_SPAWN_CHANCE <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "BONUS_DEFAULT_WIDTH") )
        return false;
    if (!(in >> BONUS_DEFAULT_WIDTH ) || BONUS_DEFAULT_WIDTH <= 0 )
        return false;
    if ( !ReadAndCheckArg( in, "BONUS_DEFAULT_HEIGHT") )
        return false;
    if (!(in >> BONUS_DEFAULT_HEIGHT ) || BONUS_DEFAULT_HEIGHT <= 0 )
        return false;
    if ( !( in . eof() ) )
        return false;
    in.close();
    return true;
}