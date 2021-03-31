#include "PlayerConfig.hpp"
#include <fstream>

PlayerConfig::PlayerConfig() : m_exists(false) {

}

PlayerConfig::PlayerConfig(const std::filesystem::path& path) : m_exists(false) {
    loadConfig(path);
}

PlayerConfig:: ~PlayerConfig() {

}

bool PlayerConfig::exists() const {
    return m_exists;
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
        m_exists = true;
    } 
    catch(std::exception &e) {
        m_exists = false;
        return false;
    }

    return true;
}

std::filesystem::path PlayerConfig::getLastPlayedLevelPath() const {
    return "../res/levels/official/" + m_playerConfigJson.at("last_map_played").at("path").get<std::string>();
}

//returns position of boxes and player on last played map
std::vector<int> PlayerConfig::getSavedLogicGrid() const {
    return m_playerConfigJson.at("last_map_played").at("logic_grid");
}
