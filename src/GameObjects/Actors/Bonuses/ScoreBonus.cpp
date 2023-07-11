//
// Created by Черкасов Андрей on 21.05.2022.
//

#include "ScoreBonus.h"

ScoreBonus::ScoreBonus(uint32_t id, const std::shared_ptr<Texture> &texture, const SDL_Rect &physicsBody,
                       const std::shared_ptr<PlayerCharacter> &playerRef) :
BaseBonus(id, texture, physicsBody, playerRef)
{

}


void ScoreBonus::OnBonusPickUp() {
    m_PlayerRef -> AddScore( m_ScoreBonus );
}

