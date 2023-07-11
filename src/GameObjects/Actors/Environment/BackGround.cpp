#include "BackGround.h"



BackGround::BackGround( uint32_t ObjectID, const std::shared_ptr<Texture> & texture )
        : Actor ( ObjectID, texture, SDL_Rect { 0, 0, GameStatics::GAME_WIDTH, GameStatics::GAME_HEIGHT }, ECollisionChannel::EIgnore ), m_MainTexture( texture )
{
    SetTickEnabled( false );
    SetCollisionEnabled( false );
}

void BackGround::Render(const Renderer &renderer) const {
    renderer.Render( m_MainTexture->GetTexture(),
                     SDL_Rect { 0, 0, GameStatics::GAME_WIDTH, GameStatics::GAME_HEIGHT } );
}

void BackGround::Tick(float dt) {

}

void BackGround::ReactToCollision(const std::shared_ptr<Actor> &otherActor, ECollisionChannel CollisionChannel,
                                  const std::pair<int, int> &ResolveVector) {

}


