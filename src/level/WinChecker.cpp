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
    int onPlace = 0;
    for(int i = 0; i < m_boxes.size(); i++)
        for(int j = 0; j < m_winPlaces.size(); j++)
            if(m_boxes[i].getGridPos() == m_winPlaces[j])
                onPlace++;
    return (onPlace == m_winPlaces.size()); 
}



