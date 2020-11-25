#include "gameplay.h"

#include <string>
#include "Utilities/utilities.h"
#include "Action/action.h"
#include <iostream>
#include "GamePlay/drawinterface.h"

GamePlay::GamePlay(DrawInterface* drawInterface): m_linesDestroyed(0){
    m_drawInt = drawInterface;
        m_drawInt -> printMsg("drawInterface created");
    m_nextFigure = new Figure() ;
        m_drawInt -> printMsg("next figure constr");
    m_field = new GameField() ;
        m_drawInt -> printMsg("field constr");
    m_action = new Action() ;
        m_drawInt -> printMsg("action constr");
}

GamePlay::~GamePlay(){
        m_drawInt -> printMsg("deleting next figure");
    delete m_nextFigure;
         m_drawInt -> printMsg("deleting field");
    delete m_field;
         m_drawInt -> printMsg("deleting action");
    delete m_action;
}


void GamePlay::run(){
    m_drawInt ->printMsg("starting game");
    m_nextFigure -> generateFig() ;
    Figure* current_fig = new Figure() ;
    current_fig -> copy_cropNextFigure(m_nextFigure) ;
    m_nextFigure -> generateFig() ;
    m_drawInt -> drawNextFigure( m_nextFigure -> getFig() ) ;
    m_drawInt -> printScore(m_linesDestroyed, m_level) ;
    m_field -> addFigure(current_fig) ;
    Action::Action_en key ;
    bool cantMoveDown = false ;
    bool keyEsc = false ;

    while (true){

        m_drawInt -> drawGameField(m_field -> getField()) ;

            key = m_action -> getKey() ;

            switch (key) {

            case  Action::Action_en::Action_KEY_UP:
                m_field -> removeFigure(current_fig) ;
                if (Utilities::checkRotate(current_fig, m_field))
                    current_fig -> rotateFig() ;
                break ;

            case Action::Action_en::Action_KEY_DOWN:
                m_field -> removeFigure(current_fig) ;
                if (Utilities::checkDownMovement(current_fig, m_field))
                    current_fig -> moveFigureDown() ;
                break ;

            case Action::Action_en::Action_KEY_LEFT:
                m_field -> removeFigure(current_fig) ;
                if (Utilities::checkLeftMovement(current_fig, m_field))
                    current_fig -> moveFigureLeft() ;              
                break ;

            case Action::Action_en::Action_KEY_RIGHT:
                m_field -> removeFigure(current_fig) ;
                if (Utilities::checkRightMovement(current_fig, m_field))
                    current_fig -> moveFigureRight() ;
                break ;

            case Action::Action_en::Action_TIMEOUT:
                m_field -> removeFigure(current_fig) ;
                if (Utilities::checkDownMovement(current_fig, m_field))
                    current_fig -> moveFigureDown() ;
               break;

            case Action::Action_en::Action_KEY_ESC:
                keyEsc = true ;
                break ;

            default: break ;

            }

            if (keyEsc) break ;

            if ( Utilities::checkDownMovement(current_fig, m_field) )
                cantMoveDown = false ;

            if ( (key == Action::Action_en::Action_TIMEOUT) && cantMoveDown ) {
                m_field -> addFigure(current_fig) ;
                m_drawInt -> drawGameField(m_field -> getField()) ;
                if (m_field -> gameOver()) break ;

                int fullLines = m_field -> clearFullRows( ) ;
                if (fullLines > 0){
                    m_linesDestroyed += fullLines ;

                    if (  (m_linesDestroyed > 5) && (m_level == 1) ){
                       m_action -> setTimeout();
                       m_level ++;
                    } else if (  (m_linesDestroyed > 10) && (m_level == 2) ){
                        m_action -> setTimeout();
                        m_level ++;
                    } else if (  (m_linesDestroyed > 15) && (m_level == 3) ){
                        m_action -> setTimeout();
                        m_level ++;
                    } else if (  (m_linesDestroyed > 20) && (m_level == 4) ){
                        m_action -> setTimeout();
                        m_level ++;
                    } else if (  (m_linesDestroyed > 25) && (m_level == 5) ){
                        m_action -> setTimeout();
                        m_level ++;
                    }
                }

                m_drawInt -> printScore(m_linesDestroyed, m_level) ;
                cantMoveDown = false ;
                current_fig -> copy_cropNextFigure(m_nextFigure) ;
                m_nextFigure -> generateFig() ;
                m_drawInt -> drawNextFigure( m_nextFigure -> getFig() ) ;
                m_field -> addFigure(current_fig) ;
            }

            if ( !Utilities::checkDownMovement(current_fig, m_field) ) {
                cantMoveDown = true ;
                m_field -> addFigure(current_fig) ;
                m_drawInt -> drawGameField(m_field -> getField()) ;

            } else {
                m_field -> addFigure(current_fig) ;
                m_drawInt -> drawGameField(m_field -> getField()) ;
            }


    }
    delete current_fig;

    m_drawInt -> printMsg("End of game cycle") ;
}
