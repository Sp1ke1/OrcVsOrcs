#include "CharacterAnimationComponent.h"

CharacterAnimationComponent::CharacterAnimationComponent(uint32_t ObjectID, const std::shared_ptr<Actor> &ownerActor,
                                                         const std::shared_ptr<Character> &ownerCharacter,
                                                         const std::vector<std::shared_ptr<Texture>> &textures)
: ActorComponent ( ObjectID, ownerActor ), m_OwnerCharacter ( ownerCharacter ), m_Animations( textures ), m_CurrentDirection( m_OwnerCharacter -> GetDirectionVector() )
{
    if ( m_Animations . size() < 2 )
        throw std::invalid_argument( "Animation array is to small ( min size == 2 )");
    SetTickEnabled( true );
}

void CharacterAnimationComponent::Tick(float dt) {
    if ( m_CurrentDirection . first != m_OwnerCharacter -> GetDirectionVector() . first )
    {
        if ( m_OwnerCharacter -> GetDirectionVector() . first == 1 )
        {
            m_CurrentDirection . first = 1;
            m_OwnerCharacter -> SetTexture( m_Animations [ 0 ] );
        }
        else if ( m_OwnerCharacter -> GetDirectionVector() . first == -1 )
        {
            m_CurrentDirection . first = -1;
            m_OwnerCharacter -> SetTexture( m_Animations [ 1 ] );
        }
    }
}

void CharacterAnimationComponent::ReactToCollision(const std::shared_ptr<Actor> &otherActor,
                                                   ECollisionChannel CollisionChannel,
                                                   const std::pair<int, int> &ResolveVector) {
}
