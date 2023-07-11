
#include "HighScoreLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


HighScoreLoader::HighScoreLoader(const std::string& fileName)
        : m_FilePath(fileName ) { }

bool HighScoreLoader::Load(const std::string& mapFilter)
{
    std::ifstream ifs( m_FilePath , std::ios::in);

    if (ifs.fail())
       return false;

    uint32_t score;
    std::string mapName;
    std::string playerName;
    std::string buffer;
    while (std::getline(ifs, buffer) && !buffer.empty())
    {
        std::istringstream iss(buffer, std::ios::in);

        if (!(iss >> mapName >> playerName >> score) || iss.peek() != -1)
            return false;

        if (mapName != mapFilter)
            continue;

        m_Scores.push_back({ score, mapName, playerName });
    }

    std::sort(m_Scores.begin(),m_Scores.end(), [](const HighScore & l, const HighScore & r) -> bool { return l.m_HighScore > r.m_HighScore; });
    return true;
}

void HighScoreLoader::PrintHighScore(std::ostream& os) const
{
    for ( auto & elem : m_Scores )
        os << elem.m_HighScore << "\t" << elem.m_PlayerName << std::endl;
}

bool HighScoreLoader::AddNewHighScore(const HighScore & highScore )
{
    std::ofstream ofs(m_FilePath, std::ios::out | std::ios::app);

    if (ofs.fail())
        return false;

    if (!(ofs << highScore.m_MapName << "\t" << highScore.m_PlayerName << "\t" << highScore.m_HighScore << std::endl))
        return false;

    return true;
}
