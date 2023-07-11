#pragma once
#include <cstdint>
#include <memory>
#include "../GameObjects/Actors/Actor.h"
#include <deque>

/**
 * @brief abstract class of engine subsystem
 */
class SubSystem
{
public:
	virtual ~SubSystem() {};
	
	virtual void Destroy() = 0; 
    /**
     * @brief method to destroy existing object
     * @param ObjectID id of the object
     * @return bool if object will be destroy in subsystem
     */
    virtual bool DestroyActor ( uint32_t ObjectID ) = 0;

    /**
     * @brief method to register new actor to subsystem
     * @param actor actor to register
     * @return bool if actor was registered
     */
    virtual bool RegisterActor (const std::shared_ptr<Actor> &actor ) = 0;
    /**
     * @brief method to register new actor component to subsystem
     * @param component actorcomponent to register
     * @return bool if actor was registered
     */
    virtual bool RegisterComponent (const std::shared_ptr<ActorComponent> &component ) = 0;
    /**
     * @brief method to handle spawn queue and register pending objects
     */
    virtual void HandleSpawnQueue () = 0;
    /**
     * @brief method to destroy objects that pending kill
     */
    virtual void GarbageCollect () = 0;
    /**
     * @brief method to update subsystem
     */
    virtual void Update() = 0;
    /**
     * @brief method to Init subsystem
     * @return bool if subsystem were successfully initialized
     */
    virtual bool Init() = 0;
};
