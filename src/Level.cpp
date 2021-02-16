#include <Level.hpp>
#include <exception>


Level::Level(const std::string& filename) : 
    m_levelConfigStream(filename) 
{
    //must be
    try{
        if(!m_levelConfigStream)
            throw std::runtime_error(filename + ": " + std::strerror(errno));
        
        //this is newer and make exceptions
        m_levelConfig = json::parse(m_levelConfigStream);

        m_t1.createMap(m_levelConfig);

    }catch(std::exception &e){
        std::cout << e.what() << "\n";
    }
}

void Level::render(sf::RenderTarget& renderer) {
    renderer.draw(m_t1);
}

Level::~Level() {

}