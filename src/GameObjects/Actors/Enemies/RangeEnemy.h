#include "Enemy.h"
#include <iostream>
/**
 * @brief Main enemy class in the game
 */
class RangeEnemy : public Enemy {
public:
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param target reference to enemy target
     * @param HP enemy HP
     * @param Damage enemy damage
     * @param speed enemy speed
     */
    RangeEnemy (uint32_t id,
                const std::shared_ptr<Texture> & texture,
                SDL_Rect & physicsBody,
                const std::shared_ptr<Character> & target,
                int HP,
                int Damage,
                int Speed
    );
    /**
     * @brief Default destructor
     */
    ~RangeEnemy () { };
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    void Tick ( float dt ) override;

    /**
     * @brief Method to make attack on the target
     */
    void Attack () override;
    /**
     * @brief Method to move character
     * @param dir direction to move
     */
    void Move ( std::pair<int,int> dir ) override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                          const std::pair<int, int> &ResolveVector) override;
    /**
     * @brief Render the object. Called every frame by engine
     * @param renderer Target renderer
     */
    void Render ( const Renderer & renderer ) const override;
    /**
     * @brief method to take damage
     * @param damage to take
     */
    void TakeDamage ( int damage ) override;
};
