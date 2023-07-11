#pragma once
#include "CharacterControllerComponent.h"
#include "../Attack/PlayerRangeAttackComponent.h"


/**
 * @brief component that provides player character ability to move
 */
class PlayerControllerComponent : public CharacterControllerComponent {
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     * @param ownerPlayerCharacter player that owns component
     * @param inputManager reference to input subsystem
     * @param attackComponent to communicate with and make attacks
     */
    PlayerControllerComponent (uint32_t ObjectID,
                               const std::shared_ptr<PlayerCharacter> & ownerActor,
                               const std::shared_ptr<PlayerCharacter> & ownerCharacter,
                               const std::shared_ptr<PlayerCharacter> & ownerPlayerCharacter,
                               const std::shared_ptr<InputManager> & inputManager,
                               const std::shared_ptr<PlayerRangeAttackComponent> & attackComponent
    );
    /**
     * @brief default destructor
     */
    ~PlayerControllerComponent() {};

    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    void Tick ( float dt ) override;
    /**
     * @brief method to move
     */
    void Move () override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &other, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) override;
private:
    /**
     * @brief method to update current jump state
     */
    void UpdateJumping ();
    /**
     * @brief method to update current fall state
     */
    void UpdateFalling ();
    std::shared_ptr<PlayerCharacter> m_OwnerPlayerCharacterRef;
    std::shared_ptr<PlayerRangeAttackComponent> m_AttackComponentRef;
    std::shared_ptr<InputManager> m_InputManagerRef;

    int m_InitialJumpHeight = 0;
    int m_TargetJumpHeight = 0;
    bool m_CharacterJumping = false;
    bool m_CharacterFalling = false;
};