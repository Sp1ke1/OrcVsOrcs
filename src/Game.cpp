#include "Game.h"
#include <sstream>




int Game::Init( const std::string & mapName, const std::string & playerName ) {
    // fail during initialization of the renderer
    try
    {

        if ( !GameStatics::Init( playerName ) ) {
            std::cerr << "Error during initialization of game config" << std::endl;
            return 1;
        }
        m_Map.LoadMap( GameStatics::PLATFORM_ENEMY_DEFAULT_COLMS, GameStatics::PLATFORM_ENEMY_DEFAULT_ROWS, mapName );
        if ( !GameEngine::Init() ) {
            std::cerr << "Error during initialization of game engine" << std::endl;
            return 2;
        }

        std::shared_ptr <Texture> background_tex = GameEngine::LoadTexture( "BackGroundTex" );
        std::shared_ptr <Texture> player_left_tex = GameEngine::LoadTexture( "PlayerTexLeft" );
        std::shared_ptr <Texture> player_right_tex = GameEngine::LoadTexture( "PlayerTexRight" );
        std::shared_ptr <Texture> enemy_left_tex = GameEngine::LoadTexture( "EnemyTexLeft" );
        std::shared_ptr <Texture> enemy_right_tex = GameEngine::LoadTexture( "EnemyTexRight" );
        std::shared_ptr <Texture> rock_tex = GameEngine::LoadTexture( "RockTex" );
        std::shared_ptr <Texture> platform_enemy_right_tex = GameEngine::LoadTexture ( "PlatformEnemyRight" );
        std::shared_ptr <Texture> platform_enemy_left_tex = GameEngine::LoadTexture ( "PlatformEnemyLeft" );
        std::shared_ptr <Texture> bonus_bullet_speed_tex = GameEngine::LoadTexture ( "BulletSpeedBonus" );
        std::shared_ptr <Texture> bonus_hp_tex = GameEngine::LoadTexture ( "HPBonus" );
        std::shared_ptr <Texture> bonus_score_tex = GameEngine::LoadTexture ( "ScoreBonus" );
        std::shared_ptr <Texture> bonus_super_tex = GameEngine::LoadTexture ( "SuperBonus" );
        m_WinScreen = GameEngine::LoadTexture("WinScreen");
        m_LoseScreen = GameEngine::LoadTexture("LoseScreen");

        // initialize background
        auto background = std::make_shared <BackGround> ( BackGround( GameStatics::AllocObjectID(),
                                                                                            background_tex) );

        GameEngine::RegisterActor ( background );
        // ------- Initialize player and player components -----
        m_Player = std::make_shared <PlayerCharacter> ( GameStatics::AllocObjectID(),
                                                                                        player_right_tex,
                                                                                        GameStatics::PLAYER_DEFAULT_PHYSICS_BODY,
                                                                                        GameStatics::PLAYER_DEFAULT_HP,
                                                                                        GameStatics::PLAYER_DEFAULT_ATTACK,
                                                                                        GameStatics::PLAYER_DEFAULT_SPEED,
                                                                                        GameStatics::PLAYER_DEFAULT_JUMP_HEIGHT );


        auto playerAttackComponent = std::make_shared <PlayerRangeAttackComponent> (GameStatics::AllocObjectID(),
                                                                                                                m_Player,
                                                                                                                m_Player,
                                                                                                                rock_tex,
                                                                                                                GameStatics::BULLET_SIZE,
                                                                                                                GameStatics::PLAYER_DEFAULT_ATTACK_COOL_DOWN );
        auto playerMovementComponent = std::make_shared <PlayerControllerComponent> (GameStatics::AllocObjectID(), m_Player,
                                                                                                                m_Player,
                                                                                                                m_Player,
                                                                                                                GameEngine::GetInputManager(),
                                                                                                                playerAttackComponent );
        auto playerAnimationComponent = std::make_shared <CharacterAnimationComponent> (GameStatics::AllocObjectID(),
                                                                                                                     m_Player,
                                                                                                                     m_Player,
                                                                                                                     std::vector<std::shared_ptr<Texture>> { player_right_tex, player_left_tex }
                                                                                                                 );

        auto playerUIHP = std::make_shared <UI> (UI (GameStatics::AllocObjectID(),
                                                     { 100, GameStatics::GROUND_LVL + 10, 50, 50},
                                                     { 200, GameStatics::GROUND_LVL + 10, 50, 50 },
                                                     m_Player ) );
        GameEngine::RegisterActor( playerUIHP );
        m_Player -> AddComponent( playerMovementComponent  );
        m_Player -> AddComponent( playerAttackComponent );
        m_Player -> AddComponent( playerAnimationComponent  );
        GameEngine::RegisterActor ( m_Player );
        GameEngine::SetPlayer( m_Player );
        // initialize bonus manager
        auto bonusManager = std::make_shared <BonusManager> ( BonusManager ( GameStatics::AllocObjectID(),
                                                                   std::shared_ptr<Texture>(),
                                                                   {0,0,0,0},
                                                                   m_Player,
                                                                   GameStatics::BONUS_DEFAULT_SPAWN_CHANCE,
                                                                   { { EBonusType::EBulletSpeedBonus, bonus_bullet_speed_tex},
                                                                     { EBonusType::EScoreBonus, bonus_score_tex },
                                                                     { EBonusType::EHPBonus, bonus_hp_tex },
                                                                     { EBonusType::ESuperBonus, bonus_super_tex }
                                                                   }
                                                                    ) );
        GameEngine::RegisterActor( bonusManager );
        // initialize enemy manager
        m_EnemyManager = std::make_shared <EnemyManager> ( GameStatics::AllocObjectID(),
                                                                             GameStatics::GROUND_ENEMY_SPAWN_DELAY,
                                                                             bonusManager,
                                                                             std::vector<std::shared_ptr<Texture>> { platform_enemy_right_tex, platform_enemy_left_tex },
                                                                             std::vector<std::shared_ptr<Texture>> { enemy_right_tex, enemy_left_tex },
                                                                             rock_tex
                                                                            );

        m_EnemyManager -> Init( m_Map . m_Layout );
        GameEngine::RegisterActor( m_EnemyManager );
    }
    catch ( const RendererException & error ) {
        std::cerr << error.GetMessage() << std::endl;
        std::cerr << SDL_GetError();
        return 3;
    }
    catch ( const AssetManagerException & error ) {
        std::cerr << error.GetMessage() << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 4;
    }
    catch ( const MapException & error ) {
        std::cerr << error.GetMessage() << std::endl;
        return 5;
    };
    m_isInitialized = true;
    return 0;
}

int Game::Start() {
    if ( !m_isInitialized )
        return 1;
    m_GameState = RUN;
    this -> GameCycle();
    return 0;
}


void Game::GameCycle() {

    while (m_GameState == RUN) {
        m_CurrentTicks = SDL_GetTicks();
        GameEngine::Update();
        UpdateGame();
        m_ElapsedTicks = SDL_GetTicks() - m_CurrentTicks;
        if (GameStatics::FRAME_DELAY > m_ElapsedTicks)
            SDL_Delay(GameStatics::FRAME_DELAY - m_ElapsedTicks);
    };

}

void Game::UpdateGame() {
    if ( GameEngine::GetInputManager()->GetState() == InputManager::EXIT )
    {
    	//GameEngine::Destroy();
        m_GameState = GameState::QUIT;
        return;
    }
    if ( m_Player -> isDead() )
    {
    	//GameEngine::Destroy();
        m_GameState = GameState::LOSE;
        WriteScoreToFile();
        ShowLoseScreen();
        return;
    }
    else if ( !m_EnemyManager -> isAnyAirEnemyAlive() )
    {
    	//GameEngine::Destroy();
        m_GameState = GameState::WIN;
        WriteScoreToFile();
        ShowWinScreen();
        return; 
    }
}

void Game::ShowLoseScreen() {
    GameEngine::GetRenderer() -> Clear();
    GameEngine::GetRenderer() -> Render(m_LoseScreen -> GetTexture(), {0,0, GameStatics::GAME_WIDTH, GameStatics::GAME_HEIGHT });
    GameEngine::GetRenderer() -> Present();
    SDL_Delay ( 5000);
    m_GameState = GameState::QUIT;
}
void Game::ShowWinScreen() {
    GameEngine::GetRenderer() -> Clear();
    GameEngine::GetRenderer() -> Render(m_WinScreen -> GetTexture(), {0,0, GameStatics::GAME_WIDTH, GameStatics::GAME_HEIGHT });
    GameEngine::GetRenderer() -> Present();
    SDL_Delay ( 5000);
    m_GameState = GameState::QUIT;
}

void Game::WriteScoreToFile ()
{
    std::cout << "-----" << "You scored: " << m_Player -> GetScore() << "-----" << std::endl;
    std::cout << "-----" << "Table of highscores: " << "-----" << std::endl;
    HighScoreLoader highScoreLoader( m_DefaultScorePath );
    highScoreLoader . AddNewHighScore( { m_Player -> GetScore(), m_Map . GetMapName(), GameStatics::PLAYER_NAME } );
    highScoreLoader . Load ( m_Map . GetMapName() );
    highScoreLoader . PrintHighScore( std::cout );
}
