#include "TextBox.hpp"

TextBox::TextBox(std::string& text) :
    m_text(text),
    m_isFocus(true),
    m_textOnScreen(),
    m_label(),
    m_frame({300, 64})
{
    m_frame.setFillColor(sf::Color::Transparent);
    m_frame.setOutlineThickness(3.0f);
    m_frame.setOutlineColor(sf::Color::Yellow);

    m_label.setString("Your name:");
    m_textOnScreen.setString("");
}

TextBox::~TextBox() {}

void TextBox::handleTextInput(sf::Event e) {
    if(e.type == sf::Event::TextEntered){
        if(m_isFocus){
            uint8_t key = e.text.unicode;
            if(isValidCharacter(key)){
                if(m_textOnScreen.getWidth() + 30 <= 
                    m_frame.getGlobalBounds().width){
                        m_text.push_back(key);
                    }
            }
            else if(m_text.size() > 0)
                if(isBackspace(key))
                    m_text.pop_back();
            
            m_textOnScreen.setString(m_text);
            update();
        }
    }
}

void TextBox::handleClick(sf::Event e, const sf::RenderWindow &window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);

    if(m_frame.getGlobalBounds().contains(float(pos.x), float(pos.y))){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            m_isFocus = true;
    }
    
    else{
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            m_isFocus = false;
    }
}

void TextBox::update() {
    sf::Vector2f fpos = m_frame.getPosition();

    float x = fpos.x +
        (m_frame.getGlobalBounds().width - m_textOnScreen.getWidth()) / 2;
    float y = fpos.y +
        (m_frame.getGlobalBounds().height - m_textOnScreen.getHeight()) / 2.5;
    m_textOnScreen.setPosition({x, y});
}

bool TextBox::isValidCharacter(const uint8_t keyCode)
{
    return (keyCode >= 48 && keyCode <= 57) ||  // Numbers
           (keyCode >= 65 && keyCode <= 90) ||  // Uppercase
           (keyCode >= 97 && keyCode <= 122) || // Lowercase
           (keyCode == 32);                     // Space
}

bool TextBox::isBackspace(const uint8_t keyCode)
{
    return keyCode == 8;
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(m_label);
    target.draw(m_frame);
    target.draw(m_textOnScreen);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow &window){
    handleClick(e, window);
    handleTextInput(e);
}

void TextBox::setPosition(const sf::Vector2f pos) {
    sf::Vector2f rel = m_relativePos + pos;

    m_label.setPosition(rel);
    float y = rel.y + m_label.getHeight() + 20;
    m_frame.setPosition({rel.x, y});
    update();
}

sf::Vector2f TextBox::getPos() const {
    return m_label.getPosition();
}

uint32_t TextBox::getWidth() const {
    /**
     * We assume thatt frame is the bigest element here
     */
    return m_frame.getGlobalBounds().width;
}

uint32_t TextBox::getHeight() const {
    return 
        m_label.getGlobalBounds().height + 
        m_frame.getGlobalBounds().height;
}



