#include "WinChecker.hpp"

WinChecker::WinChecker(Boxes &boxes, const Positions winPlaces) : 
    m_boxes(boxes),
    m_winPlaces(winPlaces)
{}

WinChecker::~WinChecker() {}

bool WinChecker::check() const{
    /**
     * We assume that amount of boxes is 
     * equal to win places
     */
    for(int i = 0; i < m_boxes.get().size(); i++){
        if(m_boxes.get()[i].getGridPos() != m_winPlaces[i])
            return false;
    }
    return true; 
}



