#pragma once
#include <math.h>
#include "../../Actors/Character.h"
#include "../../../GameEngine.h"

/**
 * @brief abstract class for range attack components
 */
class RangeAttackComponent : public ActorComponent {
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     * @param BulletTexture texture of the bullet to spawn
     * @param bulletSizes sizes of the bullet to spawn
     * @param AttackCooldown cooldown of the attacks
     */
    RangeAttackComponent (uint32_t ObjectID, const std::shared_ptr<Actor> & ownerActor, const std::shared_ptr<Character> & ownerCharacter,
    const std::shared_ptr<Texture> & BulletTexture, const std::pair<uint32_t,uint32_t> & bulletSizes, float AttackCooldown );
    /**
     * @brief vurtual destructor
     */
    virtual ~RangeAttackComponent() {};
    /**
     * @brief Tick method. Called every frame by engine.
     * @param dt delta seconds elapsed from last frame
    */
    virtual void Tick ( float dt ) = 0;

    /**
     * @brief Method to make attack on the target
     */
    virtual bool Attack () = 0;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    virtual void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) = 0;
    /**
     * @brief calculates bullet spawn transform
     * @return SDL_Rect representing bullet spawn transform
     */
    virtual SDL_Rect CalculateBulletSpawnTransform() const = 0;
    /**
     * @brief calculates spawning bullet direction vector
     * @return direction vector
     */
    virtual std::pair<float,float> CalculateBulletDirection () const = 0;

protected:
    std::shared_ptr<Character> m_PlayerRef;
    float m_CoolDown;
    std::shared_ptr<Texture> m_BulletTexture;
    const std::pair<uint32_t, uint32_t> m_BulletSizes;
    uint32_t m_TargetTick = 0;
    bool m_CanAttack = true;

};
