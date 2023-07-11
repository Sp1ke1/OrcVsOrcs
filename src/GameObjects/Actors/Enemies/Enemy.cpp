
#include "Enemy.h"
#include <random>

Enemy::Enemy(uint32_t id, const std::shared_ptr<Texture> &texture, SDL_Rect &physicsBody, const std::shared_ptr<Character> & target, int HP, int Damage, int Speed )
: Character (id, texture, physicsBody, ECollisionChannel::EEnemy, HP, Damage, Speed ), m_Target(target )
{
}

void Enemy::TakeDamage(int damage) {
    m_HP -= damage;
}
