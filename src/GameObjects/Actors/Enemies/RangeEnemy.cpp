#include "RangeEnemy.h"
#include <iostream>
RangeEnemy::RangeEnemy(uint32_t id, const std::shared_ptr<Texture> &texture, SDL_Rect &physicsBody,
                       const std::shared_ptr<Character> &target, int HP, int Damage, int Speed ) :
        Enemy(id, texture, physicsBody, target , HP,  Damage, Speed )
{
    SetCollisionEnabled( true );
    SetTickEnabled( true );
}

void RangeEnemy::Tick(float dt)
{
}

void RangeEnemy::Attack()
{

}

void RangeEnemy::TakeDamage(int damage) {
    m_HP -= damage;
    if ( m_HP <= 0 )
        m_IsDead = true;
}

void RangeEnemy::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) {
    if ( CollisionChannel == EBulletPlayer )
        TakeDamage( GameStatics::PLAYER_DEFAULT_ATTACK );
}

void RangeEnemy::Move(std::pair<int, int> dir) {

}

void RangeEnemy::Render ( const Renderer & renderer ) const
{
    renderer . Render( GetTexture()->GetTexture(), GetPhysicsBody() );
}
