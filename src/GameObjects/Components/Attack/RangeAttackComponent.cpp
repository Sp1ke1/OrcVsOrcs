
#include "RangeAttackComponent.h"

RangeAttackComponent::RangeAttackComponent(uint32_t ObjectID, const std::shared_ptr<Actor> &ownerActor,
                                           const std::shared_ptr<Character> &ownerCharacter,
                                           const std::shared_ptr<Texture> &BulletTexture,
                                           const std::pair<uint32_t, uint32_t> &bulletSizes, float AttackCooldown)
        : ActorComponent( ObjectID, ownerActor ), m_PlayerRef(ownerCharacter ),  m_CoolDown (AttackCooldown ), m_BulletTexture(BulletTexture), m_BulletSizes (bulletSizes )
{
}
