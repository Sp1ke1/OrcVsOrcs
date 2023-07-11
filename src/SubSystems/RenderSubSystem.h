
#include "SubSystem.h"
#include "../Render/Renderer.h"
#include <vector>
class Actor;
/**
 * @brief subystems that sends messages to all actors every frame to render them on the screen
 * 
 */
class RenderSubSystem : public SubSystem
{
public:
    friend class GameEngine;
    /**
     * @brief method to destroy existing object
     * @param ObjectID id of the object
     * @return bool if object will be destroy in subsystem
     */
    
    void Destroy() override;
    bool DestroyActor ( uint32_t ObjectID ) override;
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

    std::vector<std::shared_ptr<Actor>> m_RenderTargets;
    std::shared_ptr<Renderer> m_Renderer;
    std::deque<std::shared_ptr<Actor>> m_ActorsPendingSpawn;
};
