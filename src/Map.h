#pragma once
#include <string>
#include <exception>
#include <vector>
#include <cassert>
/**
 * @brief wrapper class around map exceptions
 */
class MapException : public std::exception
{
private:
    std::string m_Message;

public:
    /**
     * @brief Create a new instance of the object.
     * @param message Programmer given context.
    */
    MapException(const std::string & message) : m_Message(message) { }
    /**
     * @brief Message getter.
     * @return Exception context.
    */
    std::string GetMessage() const { return m_Message; }
    /**
     * @brief Exception specifier.
     * @return Exception specifier.
    */
    const char* what() const noexcept override { return "MapLoaderException"; }
};
/**
 * @brief class to load and validate map data from disc
 */
class Map
{
public:
    /**
     * @briefLoads new map from disk using default map path
     * @param mapCols
     * @param mapRows
     */
    void LoadMap ( uint32_t mapCols, uint32_t mapRows );
    /**
     * @brief Loads new map from disk using custom map path
     * @param mapCols
     * @param mapRows
     */
    void LoadMap (uint32_t mapCols, uint32_t mapRows , const std::string & mapPath );
    /**
     * @brief Getter for map name
     * @return map path
     */
    std::string GetMapName () const { return m_MapName; }
    std::vector <std::vector<int>> m_Layout;
private:
    void InternalCheck () { assert ( DEFAULT_MAP_PATH == "examples/maps/default_map.txt" ); }
    bool isLoaded = false;
    uint32_t m_MapCols;
    uint32_t m_MapRows;
    std::string m_MapName;
    bool isValid( const std::vector<std::vector<int>> & layout );
    const std::string DEFAULT_MAP_PATH = "examples/maps/default_map.txt";

};
