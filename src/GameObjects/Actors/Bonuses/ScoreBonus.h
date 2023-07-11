#include "BaseBonus.h"
/**
 * @brief bonus that boosts player score
 * 
 */
class ScoreBonus : public BaseBonus
{
public:
    /**
     * @Brief Creates new instance of the object
     * @param id Object unique identifier
     * @param texture Object texture
     * @param physicsBody Object physics body that determinates location, collision body and render body
     * @param playerRef Reference to the player
     */
    ScoreBonus (uint32_t id, const std::shared_ptr<Texture> & texture, const SDL_Rect & physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef );
    /**
     * @Brief default destructor
     */
    ~ScoreBonus () {};

    void OnBonusPickUp () override;
private:
    uint32_t m_ScoreBonus = GameStatics::BONUS_DEFAULT_SCORE_BONUS;
};
