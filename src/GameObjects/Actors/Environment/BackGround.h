#pragma once
#include "../Actor.h"
/**
 * @brief class to render background of the world
 */
class BackGround : public Actor {
public :
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     */
    BackGround ( uint32_t ObjectID, const std::shared_ptr <Texture> & texture );
    
    ~BackGround () {};
    /**
     * @brief Render the object. Called every frame by engine
     * @param renderer Target renderer
     */
    void Render ( const Renderer & renderer ) const override;
    /**
    * @brief Tick method. Called every frame by engine.
    * @param dt delta seconds elampes from last frame
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
    std::shared_ptr<Texture> m_MainTexture;
};
