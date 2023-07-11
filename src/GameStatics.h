#pragma once
#include <cstdint>
#include <assert.h>
#include <SDL2/SDL_rect.h>
#include <memory>
#include <vector>

class ActorComponent;
class Actor;

/**
 * @brief static class to hold game constants
 */
class GameStatics {

public:
    /**
     * @brief read the config and initialize all variables ( uses default config path )
     * @param playerName
     * @return true on success
     */
    static bool Init( const std::string & playerName );
    /**
     * @brief read the config and initialize the variables
     * 
     * @param playerName 
     * @param configPath path to config file on the disk
     * @return if initializing was successfull 
     */
    static bool Init ( const std::string & playerName, const std::string & configPath );

    // project consts
    constexpr static const char * DEFAULT_CONFIG_FILE_PATH = "examples/config.txt";
    static const uint32_t GAME_WIDTH = 1280;
    static const uint32_t GAME_HEIGHT = 720;
    static const int GROUND_LVL = 620;
    constexpr static const SDL_Rect PLAYER_DEFAULT_PHYSICS_BODY{500, 502, 84, 118};

    static std::string PLAYER_NAME;
    static uint32_t TARGET_FPS;
    static uint32_t FRAME_DELAY;
    // game window settings


    static uint32_t RESOLUTION_X;
    static uint32_t RESOLUTION_Y;
    // background hardcoded ground lvl


    static std::string APP_NAME;


    // player spawn position and default settings
    static int PLAYER_DEFAULT_HP;
    static int PLAYER_DEFAULT_SPEED;
    static int PLAYER_DEFAULT_ATTACK;
    static int PLAYER_DEFAULT_JUMP_HEIGHT;
    static float PLAYER_DEFAULT_ATTACK_COOL_DOWN;
    static uint32_t PLAYER_DEFAULT_BULLET_SPEED;

    // platform defaults
    static int PLATFORM_ENEMY_DEFAULT_ROWS;
    static int PLATFORM_ENEMY_DEFAULT_COLMS;
    static int PLATFORM_ENEMY_DEFAULT_Y_OFFSET;
    static int PLATFORM_ENEMY_DEFAULT_X_OFFSET;
    static int PLATFORM_ENEMY_DEFAULT_HP;
    static int PLATFORM_ENEMY_DEFAULT_WIDTH;
    static int PLATFORM_ENEMY_DEFAULT_HEIGHT;
    static int PLATFORM_ENEMY_BULLET_SPEED;
    static float PLATFORM_ENEMY_SPAWN_COOL_DOWN;
    static int PLATFORM_ENEMY_DEFAULT_SCORE;


    // enemies defaults
    constexpr static const std::pair<int,int> ENEMY_DEFAULT_SIZE { 84, 118 };
    static int GROUND_ENEMY_DEFAULT_SPAWN_Y;
    static int GROUND_ENEMY_DEFAULT_HP;
    static int GROUND_ENEMY_DEFAULT_DAMAGE;
    static int GROUND_ENEMY_SPAWN_DELAY;
    static int GROUND_ENEMY_BULLET_SPEED;
    static float GROUND_ENEMY_ATTACK_COOLDOWN;
    static int GROUND_ENEMY_DEFAULT_SCORE;

    // bonuses defaults
    static uint32_t BONUS_DEFAULT_BULLET_SPEED;
    static uint32_t BONUS_DEFAULT_HP_BONUS;
    static uint32_t BONUS_DEFAULT_SCORE_BONUS;
    static float BONUS_DEFAULT_SPAWN_CHANCE;
    static int BONUS_DEFAULT_WIDTH;
    static int BONUS_DEFAULT_HEIGHT;

    // bullet defaults
    static constexpr const std::pair<int,int> BULLET_SIZE { 18, 18 };

    /**
     * @brief allocates new unique object ID ( just bumps the counter )
     * @return objectID
     */
    static uint32_t AllocObjectID () { return ++ObjectIDCnt; }
    static uint32_t ObjectIDCnt;

private:
    static bool isInitialized;
    static void InternalCheck () {
        assert (strcmp ( DEFAULT_CONFIG_FILE_PATH, "examples/config.txt" ) == 0 );
        assert (GAME_HEIGHT == 720);
        assert (GAME_WIDTH == 1280);
        assert (GROUND_LVL == 620);
        assert (PLAYER_DEFAULT_PHYSICS_BODY.y == 502);
        assert ( PLAYER_DEFAULT_PHYSICS_BODY . x == 500 );
        assert ( PLAYER_DEFAULT_PHYSICS_BODY . y == 502 );
        assert ( PLAYER_DEFAULT_PHYSICS_BODY . w == 84 );
        assert ( PLAYER_DEFAULT_PHYSICS_BODY . h == 118 );
        assert ( BULLET_SIZE . first == 18 );
        assert ( BULLET_SIZE . second == 18 );
    }

};
