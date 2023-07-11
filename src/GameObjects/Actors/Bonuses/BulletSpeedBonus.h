#include "BaseBonus.h"
/**
 * @brief bonus that boosts player bullet speed
 */
class BulletSpeedBonus : public BaseBonus
{
public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param playerRef Reference to the player
     */
    BulletSpeedBonus (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef );
    /**
     * @Brief default destructor
     */
    ~BulletSpeedBonus () {};

    /**
     * @brief method to apply bonus on player
     */
    void OnBonusPickUp () override;
private:
    uint32_t m_BulletSpeedBonus = GameStatics::BONUS_DEFAULT_BULLET_SPEED;
};
