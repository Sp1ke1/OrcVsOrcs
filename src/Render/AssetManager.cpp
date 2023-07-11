
#include "AssetManager.h"

std::shared_ptr<Texture> AssetManager::LoadTexture(const std::string & path, SDL_Renderer * renderer) {
    SDL_Surface * surface = IMG_Load ( path.c_str() );
    if ( !surface )
        throw AssetManagerException ( "AssetManager::LoadTexture() : Invalid file path to load texture");
    SDL_Texture * texture = SDL_CreateTextureFromSurface( renderer, surface );
    SDL_FreeSurface( surface );
    if ( !texture )
        throw AssetManagerException ( "AssetManager::LoadTexture (): Error in SDL_CreateTextureFromSurface() " );
    return std::make_shared <Texture> ( texture );
}
