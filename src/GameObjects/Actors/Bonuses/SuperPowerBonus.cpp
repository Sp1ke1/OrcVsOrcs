
#include "SuperPowerBonus.h"

SuperPowerBonus::SuperPowerBonus(uint32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody,
                                 const std::shared_ptr<PlayerCharacter> &playerRef)
: BaseBonus(id, texture, physicsBody, playerRef)
{

}


void SuperPowerBonus::OnBonusPickUp() {
    m_PlayerRef -> SetIsSuperActive( true );
}
