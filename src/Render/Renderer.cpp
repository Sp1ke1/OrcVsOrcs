#include "Renderer.h"
#include <iostream>
void Renderer::Init( const std::string &title,
               uint32_t width,
               uint32_t height,
               bool isFullscreen )
{
    if ( this -> m_IsInitialized )
        throw RendererException ("Renderer::Init() => Renderer is already initialized!");
    if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 )
        throw RendererException ("Renderer::Init() => error during SDL_Init() ");
    if ( TTF_Init() != 0 )
        throw RendererException ("Renderer::Init() => error during TTF_Init() ");
    m_Font = TTF_OpenFont( "assets/OpenSans.ttf", 24 );
    if ( !m_Font )
        throw RendererException ("Renderer::Init() => error during opening font ");
    m_Window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0 );
    if ( !m_Window )
        throw RendererException ("Renderer::Init() => error during SDL_CreateWindow()");
    // index = -1 =>  will initialize the first one supporting. flags = 0 => empty flags
    m_Renderer = SDL_CreateRenderer( m_Window, -1, 0);
    if ( !m_Renderer )
        throw RendererException ("Renderer::Init() => error during SDL_CreateRenderer()");
    SetDrawColor( m_DefaultDrawColor );
    m_IsInitialized = true;
}

void Renderer::SetDrawColor( SDL_Color color) const {
    if ( m_IsInitialized )
        SDL_SetRenderDrawColor( m_Renderer, color.r, color.g, color.b, color.a );
}

void Renderer::Render (SDL_Texture * texture, const SDL_Rect &rec) const {
    if ( m_IsInitialized )
        SDL_RenderCopy ( m_Renderer, texture, nullptr, &rec );
}

Renderer::~Renderer() {
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    TTF_CloseFont( m_Font );
    m_IsInitialized = false;
    SDL_Quit();
}

void Renderer::Present() const {
    if ( m_IsInitialized )
        SDL_RenderPresent( m_Renderer );
}

void Renderer::Clear() const {
    if ( m_IsInitialized )
        SDL_RenderClear( m_Renderer );
}

void Renderer::RenderText(const std::string &text, const SDL_Rect &rec, const SDL_Color & color ) const {

    SDL_Surface * surfaceMessage = TTF_RenderText_Solid(m_Font, text.c_str(), color);
    SDL_Texture * Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);
    SDL_RenderCopy ( m_Renderer, Message, NULL, &rec );
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
