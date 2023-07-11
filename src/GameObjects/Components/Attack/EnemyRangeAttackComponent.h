#include "RangeAttackComponent.h"
#include "../../Actors/Enemies/EnemyBullet.h"
/**
 * @brief enemy components that provides attack logic to the enemies
 */
class EnemyRangeAttackComponent : public RangeAttackComponent {
public:
    /**
     * @brief Creates new instance of the object
     * @param ownerActor actor that owns component
     * @param ownerCharacter character that owns component
     * @param BulletTexture texture of the bullet to spawn
     * @param bulletSizes sizes of the bullet to spawn
     * @param AttackCooldown cooldown of the attacks
     * @param target target to attack
     */
    EnemyRangeAttackComponent (uint32_t ObjectID, const std::shared_ptr<Actor> & ownerActor, const std::shared_ptr<Character> & ownerCharacter,
    const std::shared_ptr<Texture> & BulletTexture, const std::pair<uint32_t,uint32_t> & bulletSizes, float AttackCooldown, const std::shared_ptr<Character> & target );
    /**
     * @brief default destructor
     */
    ~EnemyRangeAttackComponent() {};
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
protected:
    std::shared_ptr<Character> m_Target;
};
