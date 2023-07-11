#include "CharacterControllerComponent.h"
/**
 * @brief component to provide ground enemies ability to move ( doesn't used )
 */
class EnemyControllerComponent : public CharacterControllerComponent  {

public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     */
    EnemyControllerComponent ( uint32_t ObjectID,
                               const std::shared_ptr<Actor> & ownerActor,
                               const std::shared_ptr<Character> & ownerCharacter
                             );
    /**
     * @brief method to move
     */
    void Move () override;

    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    void Tick ( float dt ) override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                          const std::pair<int, int> &ResolveVector) override;
};
