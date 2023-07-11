#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
/**
 * @brief class that wraps renderer exceptions
 */
class RendererException : public std :: exception
{
public:
    /**
     * @brief create a new instance of the object
     * @param message by programmer
     */
    RendererException( const std::string & message )
    : m_Message ( message )
    {};
    /**
     * @breif Exception specifier
     * @return exception specifier
     */
    inline const char* what() const noexcept override { return "RendererError"; }
    /**
     * @breif gets exception message
     * @return exception message
     */
    const std::string GetMessage () const { return m_Message; }
private:
    std :: string m_Message;
};
/**
 * @brief wrapper around SDL objects (SDL_Renderer, SDL_Window, TTF_Font ) to provide rendering logic to the game. 
 */
class Renderer {
public:
/**
 * * @brief Default constructor. Init() method must be call to properly initialize a renderer
*/
    Renderer () = default;
/**
 * @brief Destructor to destroy allocated SDL and TTF context data
*/
    ~Renderer();
/**
     * @brief Initialize SDL context.
     * @param title Window title.
     * @param width window.
     * @param height window.
     * @param fullscreen is fullscreen.
*/
    void Init( const std::string & title, uint32_t width, uint32_t height, bool isFullscreen );
/**
 * @brief Render call for texture to rectangle.
 * @param texture Texture to draw.
 * @param rec Rectangle to be drawn to.
 */
    void Render (SDL_Texture * texture, const SDL_Rect & rec ) const;
    /**
     * @brief Render call for text to rectangle.
     * @param text to render
     * @param rec to be drawn to
     * @param color of text
     */
    void RenderText ( const std::string & text, const SDL_Rect & rec, const SDL_Color & color ) const;
/**
  * @brief Sets new draw color.
  * @param color Render color.
 */
    void SetDrawColor ( SDL_Color color ) const;
    /**
     * @breif clears current render target
     */
    void Clear() const ;
    /**
     * @brief renders current target
     */
    void Present() const;
    /**
     * Getter for renderer
     * @return SDL_Renderer * renderer
     */
    SDL_Renderer * GetRenderer () const { return m_Renderer; }
    /**
     * @brief gets current window
     * @return current window
     */
    SDL_Window * GetWindow () const { return m_Window; }
private:


    bool m_IsInitialized = false;
    SDL_Window * m_Window = nullptr;
    SDL_Renderer * m_Renderer = nullptr;
    TTF_Font * m_Font = nullptr;
    SDL_Color m_DefaultDrawColor = { 0, 0, 0, 255 };

};
