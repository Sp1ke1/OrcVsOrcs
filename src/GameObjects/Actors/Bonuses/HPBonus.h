#include "BaseBonus.h"
/**
 * @brief bonus that boosts player HP
 */
class HPBonus : public BaseBonus
{
public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param playerRef Reference to the player
     */
    HPBonus (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef );
    /**
     * @Brief default destructor
     */
    ~HPBonus () {};

    /**
    * @brief method to apply bonus on player
    */
    void OnBonusPickUp () override;
private:
    uint32_t m_HPBonus = GameStatics::BONUS_DEFAULT_HP_BONUS;
};
