#ifndef NCURS_H
#define NCURS_H

#include "GamePlay/drawinterface.h"
#include <ncurses.h>

class GamePlay;

class NCurs: public DrawInterface
{
public:
    NCurs();
    ~NCurs();
    void drawGameField( const std::vector< std::vector<char> > & );
    void printMsg(const std::string&);
    void printScore(int, int);
    void drawNextFigure( const std::vector< std::vector<char> > & );
    void play();

private:
    WINDOW *win_field;
    WINDOW *win_info;
    WINDOW *win_nextFig;
    WINDOW *win_score;
    int m_i = 1;
    GamePlay* m_game;

};

#endif // NCURS_H
