#pragma once
#include <SDL2/SDL.h>
#include <iostream>
/**
 * @brief wrapper around SDL_Texture to put it in smart pointers
 */
class Texture
{
public:
    /**
     * @brief create a new instance of the object
     * @param texture SDL_Texture
     */
    Texture ( SDL_Texture * texture )
            : m_Texture ( texture )
    {};
    /**
     * @brief destructor uses SDL_Destroy to free texture
     */
    ~Texture ()
    {
        SDL_DestroyTexture( m_Texture );
    }
    SDL_Texture * GetTexture () const { return m_Texture; }
private:
    SDL_Texture * m_Texture;
};
