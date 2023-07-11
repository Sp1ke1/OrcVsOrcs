//
// Created by Черкасов Андрей on 21.05.2022.
//

#include "HPBonus.h"

HPBonus::HPBonus(uint32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody,
                 const std::shared_ptr<PlayerCharacter> &playerRef)
        : BaseBonus(id, texture, physicsBody, playerRef)
{

}

void HPBonus::OnBonusPickUp() {
    m_PlayerRef -> Heal ( m_HPBonus );
}


