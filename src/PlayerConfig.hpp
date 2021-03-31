#pragma once
#include <filesystem>
#include <nlohmann/json.hpp>


class PlayerConfig {
    nlohmann::json m_playerConfigJson;
    std::filesystem::path m_jsonPath;
    bool m_exists;

    void setScore(const int score);
public:
    std::filesystem::path getLastPlayedLevelPath() const;
    std::vector<int> getSavedLogicGrid() const;

    bool saveConfig();
    
    bool exists() const;
    bool loadConfig(const std::filesystem::path& path);
    PlayerConfig(const std::filesystem::path& path);
    PlayerConfig();
    ~PlayerConfig();
};