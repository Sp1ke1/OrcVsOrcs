

#include "EnemyRangeAttackComponent.h"

EnemyRangeAttackComponent::EnemyRangeAttackComponent(uint32_t ObjectID, const std::shared_ptr<Actor> &ownerActor,
                                                     const std::shared_ptr<Character> &ownerCharacter,
                                                     const std::shared_ptr<Texture> &BulletTexture,
                                                     const std::pair<uint32_t, uint32_t> &bulletSizes,
                                                     float AttackCooldown,
                                                     const std::shared_ptr<Character> &target)
: RangeAttackComponent( ObjectID, ownerActor, ownerCharacter, BulletTexture, bulletSizes, AttackCooldown  ), m_Target( target )
{
    m_TargetTick = SDL_GetTicks() + ( m_CoolDown * 1000 );
    SetCollisionEnabled( false );
    SetTickEnabled( true );
}

void EnemyRangeAttackComponent::Tick(float dt) {
    {
        if (m_Target -> GetPhysicsBody() . x <= m_PlayerRef -> GetPhysicsBody() . x )
            m_PlayerRef -> SetDirectionVector({-1, 0 } );
        else
            m_PlayerRef -> SetDirectionVector({1, 0 } );
        uint32_t currentTick = SDL_GetTicks();
        if ( currentTick > m_TargetTick ) {
            m_TargetTick = SDL_GetTicks() + ( m_CoolDown * 1000 );
            Attack();
        }
    }

}

bool EnemyRangeAttackComponent::Attack() {
    std::shared_ptr<EnemyBullet> newBullet = std::make_shared <EnemyBullet> ( EnemyBullet (GameStatics::AllocObjectID(),
                                                                                           m_BulletTexture,
                                                                                           CalculateBulletSpawnTransform(),
                                                                                           CalculateBulletDirection(),
                                                                                           GameStatics::GROUND_ENEMY_BULLET_SPEED ) );
    GameEngine::RegisterActor( newBullet );
    return true;
}

SDL_Rect EnemyRangeAttackComponent::CalculateBulletSpawnTransform() const {
    SDL_Rect PlayerTransform = m_PlayerRef -> GetPhysicsBody();
    std::pair<int,int> PlayerCenter = { PlayerTransform.x + PlayerTransform.w / 2, PlayerTransform.y + PlayerTransform.h / 2 };
    std::pair<int,int> DirVector = m_PlayerRef -> GetDirectionVector();
    std::pair<int,int> SpawnPoint { PlayerCenter . first + ( DirVector . first * PlayerTransform.w / 1.5 ), PlayerCenter. second + m_BulletSizes . second };
    return SDL_Rect { SpawnPoint . first, SpawnPoint . second, (int)m_BulletSizes . first, (int)m_BulletSizes.second };
}

void EnemyRangeAttackComponent::ReactToCollision(const std::shared_ptr<Actor> &otherActor,
                                                 ECollisionChannel CollisionChannel,
                                                 const std::pair<int, int> &ResolveVector)
{

}



std::pair<float,float> EnemyRangeAttackComponent::CalculateBulletDirection () const
{
    std::pair<int,int> PlayerCenter = { m_Target -> GetPhysicsBody() . x  + m_Target -> GetPhysicsBody() . w / 2,
                                        m_Target -> GetPhysicsBody() .y + m_Target -> GetPhysicsBody() . h / 2 };
    std::pair<int,int> SelfCenter = {m_PlayerRef -> GetPhysicsBody() . x + m_PlayerRef -> GetPhysicsBody() . w / 2,
                                     m_PlayerRef -> GetPhysicsBody() .y + m_PlayerRef -> GetPhysicsBody() . h / 2 };
    std::pair<float,float> dirVector = { PlayerCenter . first - SelfCenter . first, PlayerCenter . second - SelfCenter . second };
    float dirVectorLength = sqrt ( dirVector . first * dirVector . first + dirVector . second * dirVector . second );
    std::pair<float,float> dirVectorNorm = { dirVector . first / dirVectorLength, ( dirVector . second / dirVectorLength ) * -1  };
    return dirVectorNorm;
    if (m_Target -> GetPhysicsBody() . x <= m_PlayerRef -> GetPhysicsBody() . x )
        return std::pair<float,float> ( -1, 0 );
    else
        return std::pair<float,float> ( 1, 0 );
}


