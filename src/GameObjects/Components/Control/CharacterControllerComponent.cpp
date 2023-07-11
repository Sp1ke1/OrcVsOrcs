#include "CharacterControllerComponent.h"


CharacterControllerComponent::CharacterControllerComponent(uint32_t ObjectID,
                                                       const std::shared_ptr<Actor> &ownerActor,
                                                       const std::shared_ptr<Character> &ownerCharacter)
: ActorComponent ( ObjectID, ownerActor ),
  m_OwnerCharacterRef ( ownerCharacter )
{}
