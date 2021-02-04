#include <Level.hpp>


Level::Level(const std::string& filename) : m_levelConfigStream(filename) {
    if(!m_levelConfigStream)
        throw std::runtime_error(filename + ": " + std::strerror(errno));
    
    m_levelConfigStream >> m_levelConfig;

    t1.createMap(m_levelConfig);
}


Level::~Level() {

}