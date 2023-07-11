
#include "PlayerCharacter.h"
#include <iostream>

PlayerCharacter::PlayerCharacter (uint32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody, int HP, int Damage, int Speed, int JumpHeight ) :
        Character(id, texture, physicsBody, ECollisionChannel::EPlayer, HP, Damage, Speed ), m_JumpHeight (JumpHeight ), m_Score (0 )
{
    SetTickEnabled( true );
    SetCollisionEnabled( true );
}

void PlayerCharacter::Tick( float dt )
{
//    std::cout << "State: " << m_State << std::endl;
    //std::cout << "x: " <<  m_PhysicsBody.x << "y: " << m_PhysicsBody .y << std::endl;
}

// dummy implemenation. PlayerCharacter right now doesn't need "attack" state
void PlayerCharacter::Attack() {


}
bool PlayerCharacter::Jump() {
    if ( m_State != State::FALLING && m_State != State::JUMP && m_State != State::ATTACK )
    {
        m_State = State::JUMP;
        return true;
    }
    return false;
}
void PlayerCharacter::Move( std::pair<int,int> dir ) {
    if ( m_State != State::ATTACK )
    {
        if ( dir.first == 1 ) {
            m_PhysicsBody.x += (m_BaseSpeed * m_SpeedMultiplier);
            m_DirectionVector . first = 1;
        }
        else if ( dir.first == -1 ) {
            m_PhysicsBody.x -= (m_BaseSpeed * m_SpeedMultiplier);
            m_DirectionVector . first = -1;
        }
        // SDL has inverted Y but I not
        if (dir.second == 1)
            m_PhysicsBody.y -= (m_BaseSpeed * m_SpeedMultiplier);
        else if ( dir.second == -1 )
            m_PhysicsBody.y += (m_BaseSpeed * m_SpeedMultiplier);
        if ( m_State != State::JUMP && m_State != State::FALLING )
            m_State = State::ONGROUND;
    }
}

bool PlayerCharacter::Fall() {
    if ( m_State == State::JUMP ) {
        m_State = State::FALLING;
        return true;
    }
    return false;
}
void PlayerCharacter::Render(const Renderer &renderer) const {
    renderer.Render( m_Tex->GetTexture(), m_PhysicsBody );
}

bool PlayerCharacter::Land() {
    if ( m_State == State::FALLING ) {
        m_State = State::ONGROUND;
        return true;
    }
    return false;
}
void PlayerCharacter::GetJumpParameters ( int & initialHeight, int & targetHeight )
{
    // SDL has inverted Y
    initialHeight = m_PhysicsBody.y;
    targetHeight = initialHeight - m_JumpHeight;
}

void PlayerCharacter::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                       const std::pair<int, int> &ResolveVector) {
    if ( CollisionChannel == ECollisionChannel::EBulletEnemy )
    {
        TakeDamage( GameStatics::GROUND_ENEMY_DEFAULT_DAMAGE );
    }
}

void PlayerCharacter::TakeDamage(int damage) {
    m_HP -= damage;
    if ( m_HP <= 0 )
        m_IsDead = true;
}

uint32_t PlayerCharacter::GetBulletSpeed() const {
    return m_BulletSpeed;
}

void PlayerCharacter::SetBulletSpeed ( uint32_t speed ) {
    m_BulletSpeed = speed;
}

uint32_t PlayerCharacter::GetScore() const {
    return m_Score;
}
void PlayerCharacter::AddScore(uint32_t score) {
    m_Score += score;
}

bool PlayerCharacter::GetIsSuperActive() const {
    return m_IsSuperActive;
}

void PlayerCharacter::SetIsSuperActive(bool isActive) {
    m_IsSuperActive = isActive;
}

