#pragma once
#include <random>
#include "HPBonus.h"
#include "ScoreBonus.h"
#include "SuperPowerBonus.h"
#include "BulletSpeedBonus.h"
#include "EBonusType.h"
#include "../../../GameEngine.h"
#include <map>
/**
 * @brief class to spawn and delete bonuses
 */
class BonusManager : public Actor {

public:
    /**
    * @Brief Creates new instance of the object
    * @param id Object unique identifier
    * @param texture Object texture
    * @param physicsBody Object physics body that determinates location, collision body and render body
    * @param playerRef Reference to the player
    * @param bonusesTextures map with bonuses textures
    */
    BonusManager (int32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::shared_ptr<PlayerCharacter> & PlayerCharacter,  float spawnChance, const std::map<EBonusType, std::shared_ptr<Texture>> & bonusesTextures );
    /**
     * @Brief default destructor
     */
    ~BonusManager() {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elampes from last frame
    */
    void Tick ( float dt ) override;

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
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) override;
    /**
     * @Brief Method to react on enemies deaths. Spawns bonus with determine probability
     * @param EnemyDeathTransform transform used to spawn new bonus
     */
    void OnEnemyDeath ( const SDL_Rect & EnemyDeathTransform );

private:
    /**
     * @Brief spawns new bonus on map
     * @param Transform used to spawn a new bonus
     * @param bonusType bonus type to spawn
     */
    void SpawnBonus ( const SDL_Rect & Transform, EBonusType bonusType );
    const std::shared_ptr<PlayerCharacter> m_PlayerRef;
    float m_SpawnChance;
    const std::map<EBonusType, std::shared_ptr<Texture>> m_BonusesTextures;
    std::vector<std::shared_ptr<BaseBonus>> m_SpawnedBonuses;
};