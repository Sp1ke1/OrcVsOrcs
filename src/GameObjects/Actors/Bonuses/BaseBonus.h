#pragma once
#include "../Player/PlayerCharacter.h"


/**
 * @brief Base class for all bonuses in the game
 */
class BaseBonus : public Actor
{
public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param playerRef Reference to the player
     */
    BaseBonus (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef );
    /**
     * @brief Virtual destructor. This class is meant to be inherited.
    */
    virtual ~BaseBonus () {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elampes from last frame
    */
    void Tick ( float dt ) override;

    /**
     * @brief Render the object. Called every frame by engine
     * @param renderer Target renderer
     */
    void Render ( const Renderer & renderer ) const override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) override;
    /**
     * @brief virtual method to apply bonus on player
     */
    virtual void OnBonusPickUp () = 0;
    /**
     * Flag is bonus was activated
     * @return is bonus was activated
     */
    bool isActivated () const;

protected:
    const std::shared_ptr<PlayerCharacter> m_PlayerRef;
    const int m_FallingSpeed = 3;
    bool m_Activated = false;
    bool m_isFalling = true;
};