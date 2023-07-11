#pragma once
#include <vector>
#include <memory>
#include "SubSystems/RenderSubSystem.h"
#include "SubSystems/UpdateSubSystem.h"
#include "SubSystems/PhysicsSubSystem.h"
#include "Render/AssetManager.h"
#include "InputManager.h"
#include <map>
class PlayerCharacter;
/**
 * @brief main backend class for the game. Uses abstract subystems to update game.
 * 
 */
class GameEngine
{
public:
    friend class Game;
	
	static void Destroy(); 
    /**
     * @brief method to register new actor to engine
     * @param actor actor to register
     * @return bool if actor was registered
     */
    static bool RegisterActor ( const std::shared_ptr <Actor> & actor );
    /**
     * @brief method to register new actor component to engine
     * @param component to register
     * @return bool if actor was registered
     */
    static bool RegisterComponent ( const std::shared_ptr <ActorComponent> & component );
    /**
      * @brief method to destroy existing object
      * @param ObjectID id of the object
      * @return bool if object will be destroy in subsystem
      */
    static bool DestroyActor( const uint32_t ObjectID );
    /**
     * @brief method to update engine
     */
    static void Update();
    /**
     * @brief method to initialize engine subsystems
     * @return true for success
     */
    static bool Init();
    /**
     * @brief Getter for input manager
     * @return input manager class
     */
    static const std::shared_ptr<InputManager> GetInputManager ();
    /**
     * @brief Getter for player
     * @return current player
     */
    static std::shared_ptr<PlayerCharacter> GetPlayer ();
    static const std::map<std::string, std::string> m_AssetsPaths;
    /**
     * @brief loads texture using AssetManager class and asset paths map
     * @param assetName
     * @return smart pointer to texture
     */
    static std::shared_ptr <Texture> LoadTexture ( const std::string & assetName );
    /**
     * @brief gets current renderer
     */
    static std::shared_ptr <Renderer> GetRenderer ();

private:
    /**
     * @brief Sets new player
     * @param player
     */
    static void SetPlayer ( const std::shared_ptr<PlayerCharacter> & player );
    static std::shared_ptr<PlayerCharacter> m_Player;
    static std::vector<std::unique_ptr<SubSystem>> m_SubSystems;
    static std::shared_ptr<Renderer> m_Renderer;
    static std::shared_ptr<InputManager> m_InputManager;
    static bool m_Initialized;
};
