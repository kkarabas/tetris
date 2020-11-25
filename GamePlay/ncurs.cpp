#include "GamePlay/ncurs.h"
#include <ncurses.h>
#include "GlobalConst/globalconst.h"
#include "GameField/gamefield.h"
#include "GamePlay/gameplay.h"

NCurs::NCurs(){
    WINDOW *win = initscr( ) ;
    cbreak( ) ;
    curs_set( 0 ) ;
    noecho( ) ;
    start_color( ) ;
    box( stdscr, 0, 0 ) ;
    wrefresh(win) ;

    win_field = newwin( 20+2, 2*10+2 , 1, 1 ) ; // высота 20 + 2 на границы бокса, ширина 20 + 2 на границы бокса
    win_info = newwin( 20-6+2, COLS - 2*(1 + 10) - 2 , 7 ,  2*(10+1)+1 );// высота 20 -6 на след фигуру +2 на границы бокса, ширина размер терминала - размер поля -2на границы бокса
    win_nextFig = newwin( 4+2, 2*4+2 , 1 , 2*(10+1)+1 ) ; // высота 4 + 2 на границы бокса, ширина 8 + 2 на границы бокса
    win_score = newwin( 4+2, 20+2 , 1 , 2*(10+1)+1+10+1 );
    box( win_field, 0, 0 ) ;
    box ( win_info, 0, 0 );
    box ( win_nextFig, 0, 0 );
    box ( win_score, 0, 0 );
    wrefresh( win_field ) ;
    wrefresh( win_info ) ;
    wrefresh( win_nextFig ) ;
    mvwprintw(win_score, 1, 1,"Lines destroyed:");
    wrefresh( win_score ) ;

    m_game = new GamePlay(this);
}

NCurs::~NCurs(){
    delete m_game;
    delwin( win_field ) ;
    delwin( win_info ) ;
    delwin( win_nextFig ) ;
    wclear(stdscr);
    wrefresh(stdscr);
    mvwprintw(stdscr, LINES/2, COLS/2-11,"Thank you! Good bye!!!");
    wrefresh (stdscr);
    getch();

    endwin( ) ;
}

void NCurs::drawGameField(const std::vector<std::vector<char>>& field ){
   init_pair( 1, COLOR_CYAN, COLOR_CYAN );
   init_pair( 2, COLOR_BLACK, COLOR_BLACK );
   for (int i = 0; i < field.size(); i++){
       for (int j = 0; j < field[0].size(); j++){
           if ( field[i][j] == filledElement ){
               wattron(win_field,COLOR_PAIR(1)) ;
               mvwaddch( win_field, i + 1, 2*j + 1, filledElement ) ;
               mvwaddch( win_field, i + 1, 2*j + 2, filledElement ) ;
               wattroff(win_field, COLOR_PAIR(1)) ;
           } else {
               wattron(win_field, COLOR_PAIR(2)) ;
               mvwaddch( win_field, i + 1, 2*j + 1, emptyElement ) ;
               mvwaddch( win_field, i + 1, 2*j + 2, emptyElement ) ;
               wattroff(win_field, COLOR_PAIR(2)) ;
           }
       }
   }
  // wrefresh(win_info) ;
   wrefresh(win_field);
}

void NCurs::drawNextFigure(const std::vector<std::vector<char>>& nextFig ){
   init_pair( 3, COLOR_CYAN, COLOR_CYAN );
   init_pair( 4, COLOR_BLACK, COLOR_BLACK );
   for (int i = 0; i < nextFig.size(); i++){
       for (int j = 0; j < nextFig[0].size(); j++){
           if ( nextFig[i][j] == filledElement ){
               wattron(win_nextFig,COLOR_PAIR(3)) ;
               mvwaddch( win_nextFig, i + 1, 2*j + 1, filledElement ) ;
               mvwaddch( win_nextFig, i + 1, 2*j + 2, filledElement ) ;
               wattroff(win_nextFig, COLOR_PAIR(3)) ;
           } else {
               wattron(win_nextFig, COLOR_PAIR(4)) ;
               mvwaddch( win_nextFig, i + 1, 2*j + 1, emptyElement ) ;
               mvwaddch( win_nextFig, i + 1, 2*j + 2, emptyElement ) ;
               wattroff(win_nextFig, COLOR_PAIR(4)) ;
           }
       }
   }
   wrefresh(win_nextFig);
}


void NCurs::printMsg(const std::string& str){
    mvwprintw(win_info, m_i , 1, str.c_str());
    m_i++;
    wrefresh(win_info);
}

void NCurs::printScore(int score, int level){
    mvwprintw(win_score, 2 , 1, "%i" , score);
    mvwprintw(win_score, 3 , 1, "LEVEL:%i" , level);
    wrefresh(win_score);
}

void NCurs::play(){
    m_game -> run() ;

    mvwprintw(win_info, m_i, 2,"Game over!");
    m_i++;
    wrefresh (win_info) ;
    getch();

}
