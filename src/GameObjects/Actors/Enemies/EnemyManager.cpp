#include "EnemyManager.h"
#include <iostream>

EnemyManager::EnemyManager(uint32_t id, uint32_t SpawnCoolDown,
                           const std::shared_ptr<BonusManager> &playerBonusManager,
                           const std::vector<std::shared_ptr<Texture>> & AirEnemyAnimations,
                           const std::vector<std::shared_ptr<Texture>> & GroundenemiesAnimations,
                           const std::shared_ptr<Texture> & bulletTexture )
// Architecture badly works with actors that don't need render part. Maybe make enemyManager component and add it to player?
        : Actor ( id, std::shared_ptr<Texture>(nullptr), {0, 0, 0, 0},
                  ECollisionChannel::EIgnore ),
          m_PlayerBonusManager(playerBonusManager),
          m_AirEnemiesAnimations ( AirEnemyAnimations ),
          m_GroundEnemiesAnimations ( GroundenemiesAnimations ),
          m_SpawnCoolDown ( SpawnCoolDown ),
          m_BulletTexture( bulletTexture )
{
}


void EnemyManager::Tick(float dt) {
    uint32_t currentTick = SDL_GetTicks();
    if ( currentTick > m_TargetSpawnTick ) {
        m_TargetSpawnTick = SDL_GetTicks() + m_SpawnCoolDown * 1000;
        SpawnGroundEnemy();
    }
    for ( auto x = m_EnemiesAlive.begin(); x != m_EnemiesAlive . end(); ++ x )
    {
        if ( (*x) -> isDead() )
        {
            GameEngine::GetPlayer() -> AddScore( GameStatics::GROUND_ENEMY_DEFAULT_SCORE );
            m_PlayerBonusManager -> OnEnemyDeath( (*x) -> GetPhysicsBody() );
            for ( auto & comp : (*x) -> GetComponents() )
            {
                comp -> SetCollisionEnabled( false );
                comp -> SetTickEnabled( false );
            }
            (*x) -> GetComponents() . clear(); 
            (*x) -> SetCollisionEnabled( false );
            (*x) -> SetTickEnabled( false );
            auto objectID = (*x) -> GetObjectID();
            m_EnemiesAlive . erase ( x );
            GameEngine::DestroyActor( objectID );
            break;
        }
    }
    for ( auto x = m_AirEnemiesAlive.begin(); x != m_AirEnemiesAlive . end(); ++ x )
    {
        if ( (*x) -> isDead() )
        {
            GameEngine::GetPlayer() -> AddScore( GameStatics::PLATFORM_ENEMY_DEFAULT_SCORE );
            m_PlayerBonusManager -> OnEnemyDeath( (*x) -> GetPhysicsBody() );
            for ( auto & comp : (*x) -> GetComponents() )
            {
                comp -> SetPendingKill();
                comp -> SetCollisionEnabled( false );
                comp -> SetTickEnabled( false );
            }
            (*x) -> GetComponents() . clear();
            (*x) -> SetCollisionEnabled( false );
            (*x) -> SetTickEnabled( false );
            auto objectID = (*x) -> GetObjectID();
            m_AirEnemiesAlive . erase ( x );
            GameEngine::DestroyActor( objectID );
            break;
        }
    }
}

void EnemyManager::SpawnGroundEnemy ()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr ( GameStatics::ENEMY_DEFAULT_SIZE.first, GameStatics::GAME_WIDTH-GameStatics::ENEMY_DEFAULT_SIZE.first );
    SDL_Rect SpawnTransform {distr ( gen ), GameStatics::GROUND_ENEMY_DEFAULT_SPAWN_Y, GameStatics::ENEMY_DEFAULT_SIZE.first, GameStatics::ENEMY_DEFAULT_SIZE.second };
    std::shared_ptr<RangeEnemy> newEnemy = std::move ( std::make_shared<RangeEnemy> ( GameStatics::AllocObjectID(),
                                                                                       m_GroundEnemiesAnimations[0],
                                                                                       SpawnTransform,
                                                                                       GameEngine::GetPlayer(),
                                                                                       GameStatics::GROUND_ENEMY_DEFAULT_HP,
                                                                                       GameStatics::GROUND_ENEMY_DEFAULT_DAMAGE,
                                                                                       1
    																					) );
    auto newEnemyAnimationComponent = std::make_shared<CharacterAnimationComponent> (GameStatics::AllocObjectID(),
                                                                                               newEnemy,
                                                                                               newEnemy,
                                                                                               m_GroundEnemiesAnimations );

    auto newEnemyAttackComponent = std::make_shared<EnemyRangeAttackComponent> ( GameStatics::AllocObjectID(),
                                                                                           newEnemy,
                                                                                           newEnemy,
                                                                                           m_BulletTexture,
                                                                                           GameStatics::BULLET_SIZE,
                                                                                           GameStatics::GROUND_ENEMY_ATTACK_COOLDOWN,
                                                                                           GameEngine::GetPlayer()
																			             ) ;
																			    
																			    
	newEnemy -> AddComponent ( newEnemyAnimationComponent );
	newEnemy -> AddComponent ( newEnemyAttackComponent ); 
    GameEngine::RegisterActor( newEnemy );
    m_EnemiesAlive . push_back ( std::move(newEnemy) );
}

void EnemyManager::SpawnAirEnemy(size_t i, size_t j) {
    int y = GameStatics::PLATFORM_ENEMY_DEFAULT_Y_OFFSET + ( i * GameStatics::PLATFORM_ENEMY_DEFAULT_Y_OFFSET );
    int x = j * GameStatics::PLATFORM_ENEMY_DEFAULT_X_OFFSET;

    SDL_Rect SpawnTransform { x, y, GameStatics::PLATFORM_ENEMY_DEFAULT_WIDTH, GameStatics::PLATFORM_ENEMY_DEFAULT_HEIGHT  };
    std::shared_ptr<RangeEnemy> newAirEnemy = std::move ( std::make_shared<RangeEnemy> ( GameStatics :: AllocObjectID(),
                                                                                          m_AirEnemiesAnimations [ 0 ],
                                                                                          SpawnTransform,
                                                                                          GameEngine::GetPlayer(),
                                                                                          GameStatics::GROUND_ENEMY_DEFAULT_HP,
                                                                                          GameStatics::GROUND_ENEMY_DEFAULT_DAMAGE,
                                                                                          1
    																		              ) );

    auto newEnemyAnimationComponent = std::make_shared<CharacterAnimationComponent> (GameStatics::AllocObjectID(),
                                                                                     newAirEnemy,
                                                                                     newAirEnemy,
                                                                                     m_AirEnemiesAnimations );

    auto newEnemyAttackComponent =  std::make_shared<EnemyRangeAttackComponent> ( GameStatics::AllocObjectID(),
                                                                                  newAirEnemy,
                                                                                  newAirEnemy,
                                                                                  m_BulletTexture,
                                                                                  GameStatics::BULLET_SIZE,
                                                                                  GameStatics::PLATFORM_ENEMY_SPAWN_COOL_DOWN,
                                                                                  GameEngine::GetPlayer()
                                                                                  );
    newAirEnemy -> AddComponent( newEnemyAnimationComponent );
    newAirEnemy -> AddComponent( newEnemyAttackComponent  );
    GameEngine::RegisterActor( newAirEnemy );
    m_AirEnemiesAlive . push_back ( std::move ( newAirEnemy ) );
}
void EnemyManager::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                    const std::pair<int, int> &ResolveVector) {

}

void EnemyManager::Render(const Renderer &renderer) const {

}


void EnemyManager::Init( const std::vector<std::vector<int>> & map_layout )
{
    m_TargetSpawnTick =  ( SDL_GetTicks() + ( m_SpawnCoolDown * 1000 ) );
    for ( size_t i = 0; i < map_layout . size(); ++ i )
        for ( size_t j = 0; j < map_layout [ i ] . size(); ++j )
        {
            if ( map_layout [ i ] [ j ] == 1 )
                SpawnAirEnemy ( i, j );
        }

}