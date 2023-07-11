#pragma once
#include "Actor.h"
/**
 *
 * @brief main abstract class to make moving actors that can attack ( unfortunatly enemies doesn't use moving and attack functionality )
 */
class Character : public Actor
{
public:
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body ( used for determine transform, rendering and collisions )
     * @param CollisionChannel Object collision channel
     * @param HP health points
     * @param Damage damage of the character
     * @param speed moving speed of the character
     */
    Character (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, ECollisionChannel CollisionChannel, int HP, int Damage, int Speed );
    /**
     * @brief virtual destructor
     */
    virtual ~Character() {};
    /**
     * @brief virtual Method to make attack
     */
    virtual void Attack () = 0;
    /**
     * @brief Method to move character
     * @param dir direction to move
     */
    virtual void Move ( std::pair<int,int> dir ) = 0;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    virtual void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) = 0;
    /**
     * @brief gets if character is dead
     * @return is dead
     */
    bool isDead () const;
    /**
     * @brief method to take damage
     * @param damage to take
     */
    virtual void TakeDamage ( int damage ) = 0;
    /**
     * @brief gets direction vector of the character
     * @return direction vector
     */
    std::pair<int,int> GetDirectionVector () const;
    /**
     * @brief sets direction vector of the character
     * @param dir direction vector
     */
    void SetDirectionVector ( const std::pair<int,int> & dir );
    /**
     * @breif gets HP
     * @return current HP
     */
    int GetHP () const;
    /**
     * @brief heals character with parameter amount of hp
     * @param heal amount of HP to heal
     */
    void Heal ( uint32_t heal );

protected:
    int m_HP;
    bool m_IsDead = false;
    int m_BaseDamage;
    int m_DamageMultiplier = 1;
    int m_BaseSpeed;
    int m_SpeedMultiplier = 1;
    std::pair<int, int> m_DirectionVector { 1, 0 };
};