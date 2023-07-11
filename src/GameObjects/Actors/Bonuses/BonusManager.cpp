
#include "BonusManager.h"
#include <iostream>
BonusManager::BonusManager(int32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody,
                           const std::shared_ptr<PlayerCharacter> &PlayerCharacter, float spawnChance, const std::map<EBonusType, std::shared_ptr<Texture>> & bonusesTextures)
:
Actor(id, texture, physicsBody, ECollisionChannel::EIgnore ),
m_PlayerRef ( PlayerCharacter ),
m_SpawnChance ( spawnChance ),
m_BonusesTextures( bonusesTextures )
{
    SetTickEnabled( true );
    SetCollisionEnabled( false );
}

void BonusManager::Tick(float dt) {
    for ( auto bonus = m_SpawnedBonuses . begin(); bonus != m_SpawnedBonuses . end() ; ++ bonus)
    {
        if ( (*bonus)-> isActivated() )
        {
            (*bonus) -> SetCollisionEnabled( false );
            (*bonus) -> SetTickEnabled( false );
            auto objectID = (*bonus) -> GetObjectID();
            m_SpawnedBonuses . erase ( bonus );
            GameEngine::DestroyActor( objectID );
            break;
        }
    }
}

void BonusManager::Render(const Renderer &renderer) const {

}

void BonusManager::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                    const std::pair<int, int> &ResolveVector)
{
}

void BonusManager::OnEnemyDeath(const SDL_Rect &EnemyDeathTransform) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr ( 1, 100 );
    auto GenNumber = distr ( gen );
    if ( GenNumber <= 100 * m_SpawnChance )
    {
        SDL_Rect SpawnTransform { EnemyDeathTransform.x + EnemyDeathTransform.w / 2, EnemyDeathTransform . y + EnemyDeathTransform . h / 2,
                                  GameStatics::BONUS_DEFAULT_WIDTH, GameStatics::BONUS_DEFAULT_HEIGHT};
        auto GenBonus = distr ( gen );
        if ( GenBonus <= 25 )
            SpawnBonus( SpawnTransform, EBonusType::EBulletSpeedBonus );
        else if ( GenBonus <= 50 )
            SpawnBonus ( SpawnTransform, EBonusType::EHPBonus );
        else if ( GenBonus <= 75 )
            SpawnBonus ( SpawnTransform, EBonusType::EScoreBonus );
        else
            SpawnBonus( SpawnTransform, EBonusType::ESuperBonus);
    }
}

void BonusManager::SpawnBonus(const SDL_Rect & SpawnTransform, EBonusType bonusType) {
    switch ( bonusType )
    {
        case ESuperBonus: {
            std::shared_ptr<SuperPowerBonus> newBonus = std::make_shared<SuperPowerBonus>(SuperPowerBonus(GameStatics::AllocObjectID(),
                                                                              m_BonusesTextures.at(ESuperBonus),
                                                                              SpawnTransform,
                                                                              m_PlayerRef ) );
            m_SpawnedBonuses . push_back ( newBonus );
            GameEngine::RegisterActor( newBonus );
            break;
        }
        case EHPBonus: {
            std::shared_ptr<HPBonus> newBonus = std::make_shared<HPBonus>(HPBonus(GameStatics::AllocObjectID(),
                                                                                                          m_BonusesTextures.at(EHPBonus),
                                                                                                          SpawnTransform,
                                                                                                          m_PlayerRef ) );
            m_SpawnedBonuses . push_back ( newBonus );
            GameEngine::RegisterActor( newBonus );
            break;
        }
        case EScoreBonus: {
            std::shared_ptr<ScoreBonus> newBonus = std::make_shared<ScoreBonus>(ScoreBonus(GameStatics::AllocObjectID(),
                                                                                  m_BonusesTextures.at(EScoreBonus),
                                                                                  SpawnTransform,
                                                                                  m_PlayerRef ) );
            m_SpawnedBonuses . push_back ( newBonus );
            GameEngine::RegisterActor( newBonus );
            break;
        }
        case EBulletSpeedBonus: {
            std::shared_ptr<BulletSpeedBonus> newBonus = std::make_shared<BulletSpeedBonus>(BulletSpeedBonus(GameStatics::AllocObjectID(),
                                                                                  m_BonusesTextures.at(EBulletSpeedBonus),
                                                                                  SpawnTransform,
                                                                                  m_PlayerRef ) );
            m_SpawnedBonuses . push_back ( newBonus );
            GameEngine::RegisterActor( newBonus );
            break;
        }
        default:
            break;
    }
}
