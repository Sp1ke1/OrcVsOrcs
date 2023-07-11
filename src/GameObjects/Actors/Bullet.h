#pragma once
#include "../../GameEngine.h"
#include "Actor.h"
/**
 * @brief base class for all bullet-particles in the game
 * 
 */
class Bullet : public Actor {
public:
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body ( used for determine transform, rendering and collisions )
     * @param CollisionChannel Object collision channel
     * @param direction bullet direction to fly
     * @param speed bullet speed to fly
     */
    Bullet ( uint32_t ObjectID, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, ECollisionChannel CollisionChannel, const std::pair<float,float> & direction, const uint32_t speed  );
    /**
     * @brief vurtual destructor
     */
    virtual ~Bullet () {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    void Tick ( float dt ) override;

    virtual void Move () = 0;
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
protected:
    const std::pair<float,float> m_Dir;
    const uint32_t m_BaseSpeed;
    
};
