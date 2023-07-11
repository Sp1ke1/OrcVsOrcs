
#include "EnemyControlComponent.h"

EnemyControllerComponent::EnemyControllerComponent(uint32_t ObjectID, const std::shared_ptr<Actor> &ownerActor,
                                                   const std::shared_ptr<Character> &ownerCharacter)
: CharacterControllerComponent(ObjectID, ownerActor,ownerCharacter ) {
    SetTickEnabled( false );
    SetCollisionEnabled( false );
}

// dummy implemenation. Will need it to make actually moving enemy
void EnemyControllerComponent::Tick(float dt) {

}
// dummy implemenation. Will need it to make actually moving enemy
void EnemyControllerComponent::Move() {

}
// dummy implemenation. Will need it to make actually moving enemy
void
EnemyControllerComponent::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                           const std::pair<int, int> &ResolveVector) {

}

