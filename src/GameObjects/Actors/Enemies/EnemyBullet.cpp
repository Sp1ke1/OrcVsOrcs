//
// Created by Черкасов Андрей on 20.05.2022.
//

#include "EnemyBullet.h"
EnemyBullet::EnemyBullet(uint32_t ObjectID, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody,
                         const std::pair<float, float> &direction, const uint32_t speed)
: Bullet (ObjectID, texture, physicsBody, ECollisionChannel::EBulletEnemy, direction, speed )
{
}


void EnemyBullet::Move()
{
    m_PhysicsBody . x += ( m_Dir.first * m_BaseSpeed );
    m_PhysicsBody . y -= ( m_Dir.second * m_BaseSpeed );
}

void EnemyBullet::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                   const std::pair<int, int> &ResolveVector) {
    if ( CollisionChannel == ECollisionChannel::EPlayer || CollisionChannel == ECollisionChannel::EWorld ) {
        SetCollisionEnabled(false);
        SetTickEnabled(false);
        GameEngine::DestroyActor(m_ObjectID);
    }
}


