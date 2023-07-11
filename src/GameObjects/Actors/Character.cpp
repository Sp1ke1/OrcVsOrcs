#include "Character.h"
Character::Character (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, ECollisionChannel CollisionChannel, int HP, int Damage, int Speed )
: Actor (id, texture,  physicsBody, CollisionChannel ), m_HP ( HP ), m_BaseDamage ( Damage ), m_BaseSpeed ( Speed )
{
    if ( m_HP <= 0 || m_BaseDamage <= 0 || m_BaseSpeed <= 0 )
        throw std::invalid_argument( "Character() : invalid character characteristics ");
}

std::pair<int, int> Character::GetDirectionVector() const {
    return m_DirectionVector;
}

void Character::SetDirectionVector(const std::pair<int, int> &dir) {
    m_DirectionVector = dir;
}

void Character::TakeDamage( int damage ) {
    m_HP -= damage;
}

bool Character::isDead() const {
    return m_IsDead;
}

void Character::Heal( uint32_t heal ) {
    m_HP += heal;
}

int Character::GetHP() const {
    return m_HP;
}
