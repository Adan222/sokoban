#include "WinChecker.hpp"

WinChecker::WinChecker(Boxes &boxes, const Positions winPlaces) : 
    m_boxes(boxes),
    m_winPlaces(winPlaces)
{}

WinChecker::~WinChecker() {}

bool WinChecker::check() const{
    /**
     * We assume that amount of boxes is 
     * equal amount of win palces
     */
    int am = m_boxes.size();
    for(int i = 0; i < am; i++){
        sf::Vector2i pos = m_boxes[i].getGridPos();
        if(pos != m_winPlaces[i])
            return false;
    }
    return true; 
}



