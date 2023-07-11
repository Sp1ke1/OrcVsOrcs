#pragma once
#include "../../Actors/Player/PlayerBullet.h"
#include "../../Actors/Player/PlayerCharacter.h"
#include "RangeAttackComponent.h"
/**
 * @brief component that provides attack logic to the player
 */
class PlayerRangeAttackComponent : public RangeAttackComponent {
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     * @param BulletTexture texture of the bullet to spawn
     * @param bulletSizes sizes of the bullet to spawn
     * @param AttackCooldown cooldown of the attacks
     */
    PlayerRangeAttackComponent (uint32_t ObjectID, const std::shared_ptr<Actor> & ownerActor, const std::shared_ptr<PlayerCharacter> & ownerPlayer,
                                const std::shared_ptr<Texture> & BulletTexture, const std::pair<uint32_t,uint32_t> & bulletSizes, float AttackCooldown );
    /**
     * @brief default destructor
     */
    ~PlayerRangeAttackComponent() {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    void Tick ( float dt ) override;

    /**
     * @brief Method to make attack on the target
     */
    bool Attack () override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                          const std::pair<int, int> &ResolveVector) override;
    /**
     * @brief calculates bullet spawn transform
     * @return SDL_Rect representing bullet spawn transform
     */
    SDL_Rect CalculateBulletSpawnTransform() const override;
    /**
     * @brief calculates spawning bullet direction vector
     * @return direction vector
     */
    std::pair<float,float> CalculateBulletDirection () const override;
    /**
     * @brief shoots super power if it's availible
     */
    void ActivateSuperPower();
private:
    /**
     * Spawn new bullet
     * @param BulletPhysicsBody
     * @param BulletDirection
     */
    void SpawnBullet(const SDL_Rect &BulletPhysicsBody, const std::pair<float,float> & BulletDirection ) const;
    std::shared_ptr<PlayerCharacter> m_PlayerRef;

};
