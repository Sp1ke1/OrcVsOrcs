#include "BaseBonus.h"

BaseBonus::BaseBonus(uint32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef )
: Actor ( id, texture, physicsBody, ECollisionChannel::EBonus ), m_PlayerRef( playerRef ){
    SetTickEnabled( true );
    SetCollisionEnabled( true );
}

void BaseBonus::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                 const std::pair<int, int> &ResolveVector) {
    if ( CollisionChannel == ECollisionChannel::EPlayer && !m_Activated )
    {
        m_Activated = true;
        OnBonusPickUp();
    }
    if ( CollisionChannel == ECollisionChannel::EWorld && ResolveVector . second == 1 )
    {
        m_isFalling = false;
        m_PhysicsBody . y -= m_FallingSpeed;
    }

}

void BaseBonus::Render(const Renderer &renderer) const {
    renderer . Render( GetTexture() -> GetTexture(), m_PhysicsBody );
}

bool BaseBonus::isActivated() const {
    return m_Activated;
}

void BaseBonus::Tick(float dt) {
    if ( m_isFalling )
    {
        m_PhysicsBody . y += m_FallingSpeed;
    }
}


