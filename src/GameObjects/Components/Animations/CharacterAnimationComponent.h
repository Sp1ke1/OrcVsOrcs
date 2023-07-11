#pragma once
#include "../../Actors/Player/PlayerCharacter.h"

/**
 * @brief character animation components animates character with 2 different animations based on character dir.vector
 */
class CharacterAnimationComponent : public ActorComponent {
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     * @param textures array of textures to animate the character
     */
    CharacterAnimationComponent (uint32_t ObjectID, const std::shared_ptr<Actor> & ownerActor, const std::shared_ptr<Character> & ownerCharacter, const std::vector<std::shared_ptr<Texture>> & textures );
    /**
     * @brief default destructor
     */
    ~CharacterAnimationComponent () {};
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
private:
    std::shared_ptr<Character> m_OwnerCharacter;
    std::vector<std::shared_ptr<Texture>> m_Animations;
    std::pair<int,int> m_CurrentDirection;
};


