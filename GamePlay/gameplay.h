#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Figure/figure.h"
#include "GameField/gamefield.h"
#include "Action/action.h"


class Figure;
class GameField;
class Action;
class DrawInterface;

class GamePlay
{
public:
    GamePlay(DrawInterface*);
    ~GamePlay();

    void run();
    DrawInterface* m_drawInt;
private:
    Figure* m_nextFigure ;
    GameField* m_field ;
    Action* m_action ;
    int m_linesDestroyed = 0 ;
    int m_level = 1 ;

};

#endif // GAMEPLAY_H
