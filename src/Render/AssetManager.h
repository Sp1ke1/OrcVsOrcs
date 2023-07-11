
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include "Texture.h"

/**
 * @brief Class used for wrapping exceptions of AssetManager
*/
class AssetManagerException : public std::exception
{
public:
    /**
     * @brief Create a new instance of the object.
     * @param message by programmer
    */
    AssetManagerException ( const std::string & message )
    : m_Message ( message )
    {};
private:
    const std::string m_Message;
public:
    /**
     * @brief Message getter.
     * @return Exception context.
    */
    const std::string GetMessage () const { return m_Message; }
    /**
     * @brief Exception specifier.
     * @return Exception specifier.
    */
    const char * what() const noexcept override { return "AssetManager exception"; }
};

/**
 * @brief class for loading textures assets from the disc
 * 
 */
class AssetManager {
public:
    /**
     * @brief Load texture from the disc
     * @param path File path.
     * @param renderer SDL_Renderer to load the texture.
     * @return shared_ptr to the Texture object
    */
    static std::shared_ptr<Texture> LoadTexture ( const std::string & path, SDL_Renderer * renderer );
};
