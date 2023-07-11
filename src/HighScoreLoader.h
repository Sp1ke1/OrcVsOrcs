#include "cstdint"
#include <string>
#include <vector>

/**
 * @brief wrapper struct for highscore
 */
struct HighScore
{
    uint32_t m_HighScore;
    std::string m_MapName;
    std::string m_PlayerName;
};
/**
 * @brief Class used for loading and writing highscores
*/
class HighScoreLoader
{
private:
    std::string m_FilePath;
    std::vector<HighScore> m_Scores;

public:
    /**
     * @brief Create a new instance of the object
     * @param fileName Score file path
    */
    HighScoreLoader(const std::string & fileName);
    /**
     * @brief Load the highscore table for corresponding map
     * @param map Map file path to filter highscores
    */
    bool Load(const std::string & map);
    /**
     * @brief Print highscores in desc order
     * @param os Output stream.
    */
    void PrintHighScore(std::ostream& os) const;
    /**
     * @brief Append the score.
     * @param highscore to append.
    */
    bool AddNewHighScore(const HighScore & highscore );
};