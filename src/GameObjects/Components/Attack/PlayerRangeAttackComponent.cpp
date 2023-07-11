

#include "PlayerRangeAttackComponent.h"

void PlayerRangeAttackComponent::Tick(float dt) {
    if ( !m_CanAttack )
    {
        uint32_t currentTick = SDL_GetTicks();
        if ( currentTick > m_TargetTick )
            m_CanAttack = true;
    }
}

PlayerRangeAttackComponent::PlayerRangeAttackComponent(uint32_t ObjectID, const std::shared_ptr<Actor> &ownerActor,
                                                       const std::shared_ptr<PlayerCharacter> & ownerCharacter,
                                                       const std::shared_ptr<Texture> & BulletTexture,
                                                       const std::pair<uint32_t, uint32_t> & bulletSizes,
                                                       float AttackCooldown )
: RangeAttackComponent( ObjectID, ownerActor, ownerCharacter, BulletTexture, bulletSizes, AttackCooldown ), m_PlayerRef( ownerCharacter )
{
    SetTickEnabled( true );
}


bool PlayerRangeAttackComponent::Attack() {
    if ( !m_CanAttack )
        return false;
    m_CanAttack = false;
    m_TargetTick = SDL_GetTicks() + ( m_CoolDown * 1000 );
    SDL_Rect BulletPhysicsBody = CalculateBulletSpawnTransform();
    std::pair<float,float> BulletDirection = CalculateBulletDirection();
    SpawnBullet( BulletPhysicsBody, BulletDirection );
    return true;
}

void PlayerRangeAttackComponent::SpawnBullet(const SDL_Rect &BulletPhysicsBody, const std::pair<float,float> & BulletDirection ) const {
    std::shared_ptr<PlayerBullet> newBullet = std::make_shared <PlayerBullet> (PlayerBullet (GameStatics::AllocObjectID(),
                                                                                                       m_BulletTexture,
                                                                                                       BulletPhysicsBody,
                                                                                                       BulletDirection,
                                                                                                       m_PlayerRef-> GetBulletSpeed() ) );
    GameEngine::RegisterActor( newBullet );
}

void PlayerRangeAttackComponent::ReactToCollision(const std::shared_ptr<Actor> &otherActor,
                                                  ECollisionChannel CollisionChannel,
                                                  const std::pair<int, int> &ResolveVector) {

}

SDL_Rect PlayerRangeAttackComponent::CalculateBulletSpawnTransform() const {
    SDL_Rect PlayerTransform = m_PlayerRef -> GetPhysicsBody();
    std::pair<int,int> PlayerCenter = { PlayerTransform.x + PlayerTransform.w / 2, PlayerTransform.y + PlayerTransform.h / 2 };
    std::pair<int,int> DirVector = m_PlayerRef -> GetDirectionVector();
    std::pair<int,int> SpawnPoint { PlayerCenter . first + ( DirVector . first * PlayerTransform.w / 1.5 ), PlayerCenter. second + m_BulletSizes . second };
    return SDL_Rect { SpawnPoint . first, SpawnPoint . second, (int)m_BulletSizes . first, (int)m_BulletSizes.second };
}

std::pair<float, float> PlayerRangeAttackComponent::CalculateBulletDirection() const {
    return std::pair<float, float>(m_PlayerRef -> GetDirectionVector() . first, m_PlayerRef -> GetDirectionVector() . second );
}

void PlayerRangeAttackComponent::ActivateSuperPower() {

    if ( m_PlayerRef -> GetIsSuperActive() ) {
        SDL_Rect BulletTransform{m_PlayerRef->GetPhysicsBody().x + m_PlayerRef->GetPhysicsBody().w / 2,
                                 m_PlayerRef->GetPhysicsBody().y - m_PlayerRef->GetPhysicsBody().y / 5,
                                 (int) m_BulletSizes.first,
                                 (int) m_BulletSizes.second};
        std::pair<float, float> dirFirst{-0.3, 1};
        std::pair<float, float> dirSecond{0, 1};
        std::pair<float, float> dirThird{0.3, 1};
        SpawnBullet(BulletTransform, dirFirst);
        SpawnBullet(BulletTransform, dirSecond);
        SpawnBullet(BulletTransform, dirThird);
        m_PlayerRef -> SetIsSuperActive( false );
    }
}

