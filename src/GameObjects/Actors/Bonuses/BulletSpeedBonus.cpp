#include "BulletSpeedBonus.h"


BulletSpeedBonus::BulletSpeedBonus(uint32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody, const std::shared_ptr<PlayerCharacter> & playerRef)
        : BaseBonus(id, texture, physicsBody, playerRef)
{

}

void BulletSpeedBonus::OnBonusPickUp() {
    m_PlayerRef -> SetBulletSpeed( m_PlayerRef -> GetBulletSpeed() + m_BulletSpeedBonus );
}

