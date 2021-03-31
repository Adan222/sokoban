#pragma once
#include <filesystem>
#include <nlohmann/json.hpp>


class PlayerConfig {
    nlohmann::json m_playerConfigJson;
    std::filesystem::path m_jsonPath;
    bool m_hasPlayed;
public:
    std::filesystem::path getLastPlayedLevelPath() const;
    std::vector<int> getSavedLogicGrid() const;
    std::string getPlayerName();
    void setScore(const int score);
    void setLogicGrid(std::vector<int> logicGrid);
    void saveConfig(const std::string &playerName, const std::filesystem::path& levelConfigPath);
    
    bool hasPlayed() const;
    bool loadConfig(const std::filesystem::path& path);
    PlayerConfig(const std::filesystem::path& path);
    PlayerConfig();
    ~PlayerConfig();
};