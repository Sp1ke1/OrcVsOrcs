#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include "../../Render/Texture.h"
#include "../../Render/Renderer.h"
#include "../../GameStatics.h"
#include "../../SubSystems/ECollisionChannels.h"
#include <iostream>


class ActorComponent;
/**
 * @brief main class to represent object of the scene
 */
class Actor {
public:
    /**
     * @brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body ( used for determine transform, rendering and collisions )
     * @param CollisionChannel Object collision channel
     */
    Actor(uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, ECollisionChannel CollisionChannel );
    /**
     * @brief virtual destructor
     */
    // virtual ~Actor() { m_Components . clear(); };
    virtual ~Actor() {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    virtual void Tick ( float dt ) = 0;

    /**
     * @brief Render the object. Called every frame by engine
     * @param renderer Target renderer
     */
    virtual void Render ( const Renderer & renderer ) const = 0;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    virtual void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) = 0;

    /**
     * Gets current actor physics body
     * @return SDL_Rect representing physics body
     */
    SDL_Rect GetPhysicsBody () const;
    /**
     * Sets if actor will be processed in physics engine
     * @param enabled
     */
    void SetCollisionEnabled ( bool enabled );
    /**
     * Sets if tick will be calling in engine update system
     * @param enabled
     */
    void SetTickEnabled ( bool enabled );
    /**
     * gets if collision enabled
     * @return enabled
     */
    bool GetCollisionEnabled () const;
    /**
     * gets if tick is enabled
     * @return enabled
     */
    bool GetTickEnabled () const;
    /**
     * @brief gets object unique id
     * @return object id
     */
    uint32_t GetObjectID () const;
    /**
     * @brief gets actor collision channel
     * @return collision channel
     */
    ECollisionChannel GetCollisionChannel () const;
    /**
     * @breif sets actor collision channel
     * @param newChannel
     */
    void SetCollisionChannel ( ECollisionChannel newChannel );
    /**
     * @breif adds new component to the actor
     * @param newComponent
     */
    void AddComponent ( const std::shared_ptr<ActorComponent> & newComponent );
    /**
     * @brief gets all components of the actor
     * @return actor components
     */
    std::vector<std::shared_ptr<ActorComponent>> & GetComponents ();
    /**
     * @brief set ups actor for destroy
     */
    void SetPendingKill ();
    /**
     * gets if actor pending destroy
     * @return is pending destroy
     */
    bool GetPendingKill () const;
    /**
     * @brief Sets actor texture
     * @param texture
     */
    void SetTexture ( const std::shared_ptr <Texture> & texture );
    /**
     * @breif gets actor texture
     * @return current actor texture
     */
    std::shared_ptr<Texture> GetTexture () const;

protected:
    uint32_t m_ObjectID;
    std::shared_ptr <Texture> m_Tex;
    SDL_Rect m_PhysicsBody;
    ECollisionChannel m_CollisionChannel;
    std::vector<std::shared_ptr<ActorComponent>>  m_Components;
    bool m_HasCollision = false;
    bool m_TickEnabled = true;
    bool m_PendingKill = false;
};
/**
 * @brief abstract class for logic components of the actor
 */
class ActorComponent
{
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     */
    ActorComponent ( uint32_t ObjectID, const std::shared_ptr<Actor> & ownerActor );
    /**
     * @brief virtual destructor
     */
    virtual ~ActorComponent () = default;
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
    /**
     * @brief gets actor collision channel
     * @return collision channel
     */
    uint32_t GetObjectID ();
    /**
     * @brief gets component owner
     * @return owner actor
     */
    std::shared_ptr<Actor> GetOwner () const;
    /**
     * gets if collision enabled
     * @return enabled
     */
    void SetTickEnabled ( bool enabled );
    /**
     * gets if tick is enabled
     * @return enabled
     */
    bool GetTickEnabled () const;
    /**
     * Sets if component will be processed in physics engine
     * @param enabled
     */
    void SetCollisionEnabled ( bool enabled );
    /**
     * gets if collision enabled
     * @return enabled
     */
    bool GetCollisionEnabled () const;
    /**
     * @brief set ups component for destroy
     */
    void SetPendingKill ();
    /**
     * gets if actor pending destroy
     * @return is pending destroy
     */
    bool GetPendingKill () const;
protected:
    uint32_t m_ObjectID;
    std::shared_ptr<Actor> m_OwnerActor;
    bool m_TickEnabled = true;
    bool m_CollisionEnabled = false;
    bool m_PendingKill = false;
};
