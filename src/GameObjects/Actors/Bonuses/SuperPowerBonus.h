#include "BaseBonus.h"
/**
 * @brief bonus that allows player to use super power
 * 
 */
class SuperPowerBonus : public BaseBonus {
public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param playerRef Reference to the player
     */
    SuperPowerBonus (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef );
    /**
     * @Brief default destructor
     */
    ~SuperPowerBonus () {};

    /**
    * @brief method to apply bonus on player
    */
    void OnBonusPickUp () override;
};
