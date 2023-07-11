#pragma once
#include "SubSystem.h"
#include <memory>
#include <vector>
/**
 * @brief subsystem to detect collisions and send messages to actor to react on them
 * 
 */
class PhysicsSubSystem : public SubSystem
{
public:
    friend class GameEngine;
    /**
     * @brief create a new instance of an object
     * @param gamewidth determines game window width
     * @param groundLvl determines game groudn lvl
     */
     
    void Destroy () override; 
    PhysicsSubSystem ( uint32_t gamewidth, uint32_t groundLvl )
    {
        m_GroundLvl = groundLvl;
        m_GameWidth = gamewidth;
        m_GameHeight = 0;
    };
    
    /**
     * @brief method to destroy existing object
     * @param ObjectID id of the object
     * @return bool if object will be destroy in subsystem
     */
    bool DestroyActor( uint32_t ObjectID ) override;
    /**
     * @brief method to register new actor to subsystem
     * @param actor actor to register
     * @return bool if actor was registered
     */
    bool RegisterActor (const std::shared_ptr<Actor> &actor ) override;
    /**
     * @brief method to register new actor component to subsystem
     * @param component actorcomponent to register
     * @return bool if actor was registered
     */
    bool RegisterComponent (const std::shared_ptr<ActorComponent> &component ) override;
    /**
     * @brief method to handle spawn queue and register pending objects
     */
    void HandleSpawnQueue () override;
    /**
     * @brief method to destroy objects that pending kill
     */
    void GarbageCollect () override;
    /**
     * @brief method to update subsystem
     */
    void Update() override;
    /**
     * @brief method to Init subsystem
     * @return bool if subsystem were successfully initialized
     */
    bool Init() override;

    /**
     * @brief Method to check collisions between 2 objects ( AABB collision )
     * @param x first object
     * @param y second object
     * @param ResolveVector ( doesn't calculates )
     * @return bool if there were collision
     */
    bool CheckCollisions ( const SDL_Rect & x, const SDL_Rect & y, std::pair<int,int> & ResolveVector );
    /**
     * @brief Method to determine if objects collides with the world
     * @param physicsBody of the object
     * @param ResolveVector
     * @return bool if there were collision with the world
     */
    bool CheckCollisionWithWorld ( const SDL_Rect & physicsBody , std::pair<int,int> & ResolveVector );
    
private:
    std::vector<std::shared_ptr<Actor>> m_CollisionQuery;
    std::deque<std::shared_ptr<Actor>> m_ActorsPendingSpawn;
    uint32_t m_GroundLvl;
    uint32_t m_GameWidth;
    uint32_t m_GameHeight;
};
