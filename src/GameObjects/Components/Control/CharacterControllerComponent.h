#pragma once
#include <memory>
#include "../../Actors/Actor.h"
#include "../../../GameEngine.h"

class Character;
/**
 * @brief abstract component to provide ground characters ability to move
 */
class CharacterControllerComponent : public ActorComponent
{
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     */
    CharacterControllerComponent ( uint32_t ObjectID,
                                 const std::shared_ptr<Actor> & ownerActor,
                                 const std::shared_ptr<Character> & ownerCharacter);
    /**
     * @brief virtual method to move
     */
    virtual void Move () = 0;

    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    virtual void Tick ( float dt ) = 0;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    virtual void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) = 0;
protected:
    std::shared_ptr<Character> m_OwnerCharacterRef;
    int m_GroundLvl = GameStatics::GROUND_LVL;
};