#include "Map.h"
#include <fstream>
void Map::LoadMap( uint32_t mapCols, uint32_t mapRows ) {
    LoadMap ( mapCols, mapRows, DEFAULT_MAP_PATH );
}


void Map::LoadMap(uint32_t mapCols, uint32_t mapRows, const std::string &mapPath) {
    m_MapCols = mapCols;
    m_MapRows = mapRows;
    m_MapName = mapPath;
    m_Layout = std::vector<std::vector<int>>( mapRows, std::vector<int> (mapCols, 0) );
    InternalCheck();
    std::ifstream in ( mapPath );
    if ( in.fail() )
        throw MapException ("Cannot open map file");
    std::string row;
    for ( uint32_t i = 0 ; i < m_MapRows; i ++ )
    {
        if ( !( in >> row ))
            throw MapException ("Invalid number of raws / bad map file");
        if ( row . size () != m_MapCols )
            throw MapException ("Invalid number of columns in the raw in map file");
        for ( uint32_t j = 0; j < m_MapCols; j ++ )
        {
            if ( !isdigit( row [ j ] ))
                throw MapException ("Invalid character in the map file");
            m_Layout [ i ] [ j ] = row [ j ] - '0';
        }
    }
    if ( ! ( in . eof () ) )
       throw MapException ("Invalid map file layout");
    if ( !isValid( m_Layout ) )
        throw MapException ("Invalid map");
    isLoaded = true;
}

bool Map::isValid(const std::vector<std::vector<int>> &layout) {
    for ( auto & y : layout ) {
        for ( auto & x : y )
        {
            if ( x > 2 || x < 0 )
                return false;
        }
    }
    return true;
}
