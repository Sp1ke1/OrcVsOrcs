#include "GameEngine.h"
#include <iostream>
bool GameEngine::m_Initialized = false;
std::shared_ptr<PlayerCharacter> GameEngine::m_Player;
std::vector<std::unique_ptr<SubSystem>> GameEngine::m_SubSystems;
std::shared_ptr<Renderer> GameEngine::m_Renderer;
std::shared_ptr<InputManager> GameEngine::m_InputManager;
const std::map<std::string,std::string> GameEngine::m_AssetsPaths
        {
            {"PlayerTexLeft", "assets/Player_Left.png"},
            {"PlayerTexRight", "assets/Player_Right.png"},
            {"BackGroundTex", "assets/Game_Background.png"},
            {"PlatformTex", "assets/Platform_new.png"},
            {"EnemyTexLeft", "assets/Enemy_Left.png"},
            {"EnemyTexRight", "assets/Enemy_Right.png"},
            {"RockTex", "assets/Rock.png",},
            {"PlatformEnemyRight", "assets/Platform_Enemy_Right.png"},
            {"PlatformEnemyLeft", "assets/Platform_Enemy_Left.png"},
            { "HPBonus", "assets/HPBonus.png"},
            { "SuperBonus", "assets/SuperBonus.png"},
            { "BulletSpeedBonus", "assets/BulletSpeedBonus.png"},
            { "ScoreBonus", "assets/ScoreBonus.png"},
            { "WinScreen", "assets/WinScreen.png"},
            { "LoseScreen", "assets/LoseScreen.png"}
        };


void GameEngine::Destroy() 
{
	for ( auto & elem : m_SubSystems )
	{
		elem -> Destroy(); 
	}

}

bool GameEngine::Init() {
    if ( m_Initialized )
        return false;
    auto renderSubsystem = std::make_unique<RenderSubSystem>();
    auto physicsSubsystem = std::make_unique <PhysicsSubSystem> ( PhysicsSubSystem (GameStatics::GAME_WIDTH,  GameStatics::GROUND_LVL ) );
    auto updateSubsystem = std::make_unique <UpdateSubSystem> ( UpdateSubSystem() );
        if ( !renderSubsystem -> Init() || !physicsSubsystem -> Init() || !updateSubsystem -> Init() )
            return false;
    m_Renderer = renderSubsystem->m_Renderer;
    m_InputManager = std::make_shared<InputManager> ();
    m_SubSystems . push_back ( std::move( updateSubsystem ) );
    m_SubSystems . push_back ( std::move( physicsSubsystem ) );
    m_SubSystems . push_back ( std::move( renderSubsystem ) );
    m_Initialized = true;
    return true;
}

bool GameEngine::RegisterActor(const std::shared_ptr<Actor> &actor) {
    bool flag = false;
    for ( auto & sys : m_SubSystems )
        if (sys->RegisterActor(actor) )
            flag = true;
    return flag;
}

bool GameEngine::RegisterComponent(const std::shared_ptr<ActorComponent> & component ) {
    bool flag = false;
    for ( auto & sys : m_SubSystems )
        if (sys->RegisterComponent( component ) )
            flag = true;
    return flag;
}

void GameEngine::Update() {

    m_InputManager -> Process();
    for ( auto & sys : m_SubSystems )
        sys -> Update();
}

bool GameEngine::DestroyActor( const uint32_t ObjectID ) {
    bool flag = false;
    for ( auto & sys : m_SubSystems )
    {
        if ( sys -> DestroyActor( ObjectID ) ) { 
            flag = true;
        }
    }
    return flag;
}

void GameEngine::SetPlayer(const std::shared_ptr<PlayerCharacter> &player) {
    m_Player = player;
}

std::shared_ptr<PlayerCharacter> GameEngine::GetPlayer() { return m_Player; }

std::shared_ptr<Texture> GameEngine::LoadTexture( const std::string & assetName ) {
    if ( m_AssetsPaths . find ( assetName ) == m_AssetsPaths . end() )
    {
        throw AssetManagerException ("Wrong asset name in GameEngine::LoadTexture() ");
    }
    return AssetManager::LoadTexture( m_AssetsPaths . at ( assetName ), m_Renderer->GetRenderer() );
}

const std::shared_ptr<InputManager> GameEngine::GetInputManager() {
    return m_InputManager;
}

std::shared_ptr<Renderer> GameEngine::GetRenderer() {
    return m_Renderer;
}

