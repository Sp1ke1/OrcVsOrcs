#pragma once
#include "../Character.h"
/**
 * @brief abstract enemy class
 */
class Enemy : public Character
{
public:
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param target Reference to enemy target
     * @param HP enemy health points
     * @param damage enemy damage
     * @param speed enemy speed
     */
    Enemy (uint32_t id,
           const std::shared_ptr<Texture> & texture,
           SDL_Rect & physicsBody,
           const std::shared_ptr<Character> & target,
           int HP,
           int Damage,
           int Speed
           );
           
    ~Enemy () {};
    /**
     * @brief virtual Tick method. Called every frame by engine.
     * @param dt delta seconds elampes from last frame
    */
    virtual void Tick ( float dt ) = 0;

    /**
     * @brief virtual Method to make attack on the target
     */
    virtual void Attack () = 0;
    /**
     * @brief virtual Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    virtual void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) = 0;
    /**
     * @brief virtual method to take damage
     * @param damage to take
     */
    virtual void TakeDamage ( int damage ) = 0;
private:
    std::shared_ptr<Character> m_Target;
};
