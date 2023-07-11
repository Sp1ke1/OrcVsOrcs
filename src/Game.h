#include <cstdint>
#include "GameEngine.h"
#include "GameObjects/Actors/Environment/BackGround.h"
#include "GameObjects/Actors/Environment/UI.h"
#include "GameObjects/Components/Control/PlayerControllerComponent.h"
#include "GameObjects/Components/Attack/PlayerRangeAttackComponent.h"
#include "GameObjects/Components/Animations/CharacterAnimationComponent.h"
#include "GameObjects/Actors/Enemies/EnemyManager.h"
#include "GameObjects/Actors/Bonuses/BonusManager.h"
#include "HighScoreLoader.h"
#include "Map.h"

/**
 * @brief main game class
 */
class Game {
public:
    /**
     * @brief creates a new instance of an object . ( Init() must be called! )
     */
    Game () { };

    /**
     * @brief default destructor
     */
    ~Game() = default;
    Game ( const Game & ) = delete;
    Game & operator = ( const Game & ) = delete;
    /**
     * @brief Initialize a new instance of the game.
     * @param mapName to load
     * @param playerName to play
     * @return 0 if game was initialized, else otherwise
     */
    int Init( const std::string & mapName, const std::string & playerName );
    /**
     * @brief starts the game
     * @return exit code ( 0 if exited properly )
     */
    int Start();
    enum GameState
    {
        INIT,
        RUN,
        LOSE,
        WIN,
        QUIT,
    };
private:
    /**
     * @brief Method that calls engine update and game logic update every frame
     */
    void GameCycle ();
    /**
     * @brief Method to control game rules
     */
    void UpdateGame();
    /**
     * @brief Shows win screen after player won
     */
    void ShowWinScreen();

    /**
     * @brief Shows lose screen after player lose
     */
    void ShowLoseScreen();
    /**
     * Writes current player score to appropriate file
     */
    void WriteScoreToFile();

    bool m_isInitialized = false;
    GameState m_GameState = INIT;


    // FPS limiter settings;

    uint32_t m_CurrentTicks = 0;
    uint32_t m_ElapsedTicks = 0;
    // Update subsystem
    const char * m_DefaultScorePath = "examples/highscores.txt";
    // map
    Map m_Map;
    // gameObjects
    std::shared_ptr<BackGround> m_GameBackGround;
    std::shared_ptr<PlayerCharacter> m_Player;
    std::shared_ptr<EnemyManager> m_EnemyManager;

    std::shared_ptr<Texture> m_LoseScreen;
    std::shared_ptr<Texture> m_WinScreen;
};
