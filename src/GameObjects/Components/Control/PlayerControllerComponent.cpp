#include "PlayerControllerComponent.h"

PlayerControllerComponent::PlayerControllerComponent(uint32_t ObjectID, const std::shared_ptr<PlayerCharacter> &ownerActor,
                                                     const std::shared_ptr<PlayerCharacter> &ownerCharacter,
                                                     const std::shared_ptr<PlayerCharacter> &ownerPlayerCharacter,
                                                     const std::shared_ptr<InputManager> &inputManager,
                                                     const std::shared_ptr<PlayerRangeAttackComponent> & attackComponent )
: CharacterControllerComponent ( ObjectID, ownerActor, ownerCharacter ), m_OwnerPlayerCharacterRef( ownerPlayerCharacter ),
m_AttackComponentRef( attackComponent ), m_InputManagerRef( inputManager )
{
    SetTickEnabled( true );
}

void PlayerControllerComponent::Tick(float dt)
{
    Move();
    if ( m_CharacterJumping )
        UpdateJumping();
    if ( m_CharacterFalling )
        UpdateFalling();
}

void PlayerControllerComponent::Move()
{
    if ( m_InputManagerRef->isLeftPressed() )
    {
        m_OwnerCharacterRef -> Move( std::pair<int,int> ( -1, 0 )  );
    }
    else if ( m_InputManagerRef->isRightPressed() )
    {
        m_OwnerCharacterRef -> Move( std::pair<int,int> ( 1, 0 )  );
    }
    if ( m_InputManagerRef -> isJumpPressed() )
    {
        if ( m_OwnerPlayerCharacterRef -> Jump () ) {
            m_OwnerPlayerCharacterRef -> GetJumpParameters( m_InitialJumpHeight, m_TargetJumpHeight );
            m_CharacterJumping = true;
        }
    }
    if ( m_InputManagerRef -> isAttackPressed() )
    {
        m_AttackComponentRef -> Attack();
    }
    if ( m_InputManagerRef -> isSuperPressed() )
    {
        m_AttackComponentRef -> ActivateSuperPower();
    }
}

void PlayerControllerComponent::UpdateJumping() {
    if ( m_OwnerCharacterRef -> GetPhysicsBody().y <= m_TargetJumpHeight )
    {
        m_CharacterJumping = false;
        m_CharacterFalling = m_OwnerPlayerCharacterRef->Fall();
        return;
    }
    m_OwnerCharacterRef-> Move(std::pair<int, int>(0, 1));
}

void PlayerControllerComponent::UpdateFalling() {
    if ( m_OwnerCharacterRef -> GetPhysicsBody().y >= m_GroundLvl )
    {
        m_CharacterFalling = false;
        m_OwnerPlayerCharacterRef -> Land();
        return;
    }
    m_OwnerCharacterRef->Move(std::pair<int, int>(0, -1));
}

void
PlayerControllerComponent::ReactToCollision(const std::shared_ptr<Actor> &other, ECollisionChannel CollisionChannel,
                                            const std::pair<int, int> &ResolveVector) {
    if ( ResolveVector . first == -1 )
        m_OwnerCharacterRef -> Move( std::pair<int,int> ( -1, 0 ) );
    else if ( ResolveVector . first == 1 )
        m_OwnerCharacterRef -> Move( std::pair<int,int> ( 1, 0 ) );
    if ( m_CharacterFalling && ResolveVector . second == 1 )
    {
        m_OwnerPlayerCharacterRef -> Move ( std::pair<int,int> ( 0, 1 ) );
        m_CharacterFalling = false;
        m_OwnerPlayerCharacterRef -> Land();

    }
    else if ( m_CharacterJumping && ResolveVector . second == -1 )
    {
        m_OwnerPlayerCharacterRef -> Move ( std::pair<int,int> ( 0, -1 ) );
        m_CharacterJumping = false;
        m_CharacterFalling = m_OwnerPlayerCharacterRef -> Fall();
    }
}
