#include "LevelConfig.hpp"

LevelConfig::LevelConfig(const std::string& fileConfigPath) {
    using json = nlohmann::json;
    using std::cout;

    try {
        m_levelConfigStream.open(fileConfigPath, std::ifstream::in);
        if(!m_levelConfigStream.good()) //TODO: not throwing error if file was not found
            throw std::runtime_error(fileConfigPath + ": " + std::strerror(errno));

        m_levelConfig = json::parse(m_levelConfigStream); //can throw parsing error, thats why we are using try catch
    } catch(std::exception &e){
        cout << e.what() << "\n";
    }
   
}

nlohmann::json LevelConfig::getJSON() const {
    return m_levelConfig;
}


LevelConfig::~LevelConfig() {
    
}