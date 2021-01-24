#include <Level.hpp>


Level::Level(const std::string& filename) : m_levelConfigStream(filename) {
    if(!m_levelConfigStream)
        throw std::runtime_error(filename + ": " + std::strerror(errno));
}


Level::~Level() {

}