

#include "Bullet.h"

Bullet::Bullet(uint32_t ObjectID, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody,
               ECollisionChannel CollisionChannel, const std::pair<float, float> &direction, const uint32_t speed)
               : Actor ( ObjectID, texture, physicsBody, CollisionChannel ), m_Dir( direction ), m_BaseSpeed ( speed )
{
    SetCollisionEnabled( true );
    SetTickEnabled( true );
}

void Bullet::Tick(float dt) {
    Move();
}

void Bullet::Render(const Renderer &renderer) const {
    renderer . Render( m_Tex -> GetTexture(), m_PhysicsBody );
}

