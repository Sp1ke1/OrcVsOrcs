#include "../Bullet.h"
/**
 * @brief class for player projectile bullet
 * 
 */
class PlayerBullet : public Bullet {

public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param direction bullet fly direction vector
     * @param speed bullet fly speed
     */
    PlayerBullet ( uint32_t ObjectID, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::pair<float,float> & direction, const uint32_t Speed );
    ~PlayerBullet () {};

    /**
     * @brief Virtual method that determines how bullet moves
     */
    void Move () override;
    /**
     * @brief Method to react to collisions. Called by engine when collision found
     * @param otherActor collided with
     * @param CollisionChannel otherActor's collision channel
     * @param ResolveVector vector to go out of collision
     */
    void ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) override;

protected:
    uint32_t m_SpeedMultiplier;
};
