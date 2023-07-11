#include "UI.h"

UI::UI(uint32_t id, const SDL_Rect & HPBox, const SDL_Rect & ScoreBox, const std::shared_ptr<PlayerCharacter> & playerRef )
: Actor(id, std::shared_ptr<Texture>(),
        SDL_Rect(),
        ECollisionChannel::EIgnore ),
        m_HPBox( HPBox ),
        m_ScoreBox( ScoreBox ),
        m_PlayerRef( playerRef )
{
    SetTickEnabled( true );
    SetCollisionEnabled( false );
}

void UI::Tick(float dt) {
    m_HPText = std::to_string(m_PlayerRef -> GetHP() );
    m_ScoreText = std::to_string ( m_PlayerRef -> GetScore() );
}

void UI::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                          const std::pair<int, int> &ResolveVector) {

}

void UI::Render(const Renderer &renderer) const {
    renderer . RenderText( m_HPText, m_HPBox, HPColor);
    renderer . RenderText( m_ScoreText, m_ScoreBox, ScoreColor );
}

