#pragma once
#include "../Character.h"
#include <iostream>
/**
 * @brief Main player class to control the main character
 */
class PlayerCharacter : public Character {
public:
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param HP player HP
     * @param Damage player damage
     * @param speed player speed
     * @param JumpHeight player jump height
     */
    PlayerCharacter( uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, int HP, int Damage, int Speed, int JumpHeight );
    /**
     * @brief default destructor
     */
    ~PlayerCharacter() {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    void Tick ( float dt ) override;

    /**
     * @brief Method to make attack
     */
    void Attack () override;
    /**
     * @brief method to move character
     * @param dir direction to move
     */
    void Move ( std::pair<int,int> dir ) override;
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
     * @brief method to take damage
     * @param damage to take
     */
    void TakeDamage ( int damage ) override;
    /**
     * @brief Method to make jump
     * @return is player jumped
     */
    bool Jump ();
    /**
     * @brief Method to start falling
     * @return is player started falling
     */
    bool Fall ();
    /**
     * @brief Method to land the playerr
     * @return is player landed
     */
    bool Land();
    /**
     * enum to determine player states
     */
    enum State { ONGROUND, ATTACK, JUMP, FALLING };
    /**
     * @brief Gets jump parameters before making jump
     * @param initialHeight out param to get initial height of the jump
     * @param targetHeight out param to get target height of the jump
     */
    void GetJumpParameters ( int & initialHeight, int & targetHeight );
    /**
     * @brief Set player bullet speed
     * @param speed
     */
    void SetBulletSpeed ( uint32_t speed );
    /**
     * @brief Gets current bullet speed
     * @return speed
     */
    uint32_t GetBulletSpeed () const;
    /**
     * @brief Gets current player score
     * @return current score
     */
    uint32_t GetScore () const;
    /**
     * @brief Adds score to current player score
     * @param score to add
     */
    void AddScore ( uint32_t score );
    /**
     * @breif Gets is super power is active now
     * @return is super active
     */
    bool GetIsSuperActive () const;
    /**
     * @breif Sets activness of super power
     * @param isActive
     */
    void SetIsSuperActive ( bool isActive );
    /**
     *@brief Gets current state of the player
     * @return player state
     */
    State GetState() const { return m_State; }
private:
    State m_State = State::ONGROUND;
    int m_JumpHeight;
    uint32_t m_BulletSpeed = GameStatics::PLAYER_DEFAULT_BULLET_SPEED;
    uint32_t m_Score = 0;
    bool m_IsSuperActive = false;
};