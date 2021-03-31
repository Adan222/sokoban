#include "PlayerConfig.hpp"
#include <fstream>

PlayerConfig::PlayerConfig() : m_hasPlayed(false) {

}

PlayerConfig::PlayerConfig(const std::filesystem::path& path) : m_hasPlayed(false) {
    if(!loadConfig(path)) {
        m_playerConfigJson = R"(
        {
            "player_name" : "Adam",
            "score" : 0,
            "last_map_played" : {
                    "path" : "none",
                    "logic_grid" : []
                }
        })"_json;
    }
}

PlayerConfig:: ~PlayerConfig() {

}

bool PlayerConfig::hasPlayed() const {
    return m_hasPlayed;
}

bool PlayerConfig::loadConfig(const std::filesystem::path& path) {
    using nlohmann::json;
    std::ifstream m_playerConfigStream;
    m_jsonPath = "";
    try {
        //Check if file exist
        if(!std::filesystem::exists(path))
            return false;

        m_playerConfigStream.open(path);

        //Check for errors
        if(m_playerConfigStream.fail())
            return false;

        //can throw parsing error, thats why we are using try catch
        m_playerConfigJson = json::parse(m_playerConfigStream);
        m_jsonPath = path;
        m_hasPlayed = true;
    } 
    catch(std::exception &e) {
        m_hasPlayed = false;
        return false;
    }
    return true;
}

std::filesystem::path PlayerConfig::getLastPlayedLevelPath() const {
    return "../" + m_playerConfigJson.at("last_map_played").at("path").get<std::string>();
}

//returns position of boxes and player on last played map
std::vector<int> PlayerConfig::getSavedLogicGrid() const {
    return m_playerConfigJson.at("last_map_played").at("logic_grid");
}

void PlayerConfig::setScore(const int score) {
    m_playerConfigJson.at("score") = score;
}

void PlayerConfig::setLogicGrid(std::vector<int> logicGrid) {
    m_playerConfigJson.at("last_map_played").at("logic_grid") = logicGrid;
}

void PlayerConfig::saveConfig(const std::string &playerName, const std::filesystem::path& levelConfigPath) {
    std::filesystem::path savePath = "../res/saves/" + playerName + ".json";
    
    m_playerConfigJson.at("player_name") = playerName;
    m_playerConfigJson.at("last_map_played").at("path") = levelConfigPath;
  
    std::ofstream saveStream(savePath);
    saveStream << m_playerConfigJson;
    saveStream.close();
    m_jsonPath = savePath;
}
