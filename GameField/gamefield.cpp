#include "gamefield.h"
#include "GlobalConst/globalconst.h"
#include "Figure/figure.h"
#include <iostream>
#include "Utilities/utilities.h"
#include "GamePlay/drawinterface.h"


GameField::GameField() {  // задаем размеры поля, 20*10
    m_field.resize(fieldSize_row);
    for (int i = 0; i < fieldSize_row; i++){
       m_field.at(i).resize(fieldSize_col);
    }

    for (int i = 0; i < fieldSize_row; i++){
       for (int j = 0; j < fieldSize_col; j++){
            m_field[i][j] = emptyElement;
       }
    }
//    for (int j = 0; j < fieldSize_col; j++){
//         m_field[10][j] = filledElement;
//         m_field[19][j] = filledElement;
//    }
}

void GameField::printField() const {
    for (int i = 0; i < fieldSize_row; i++){
        std::cout << '|';
        for (int j = 0; j < fieldSize_col; j++){
            std::cout << m_field[i][j];
       }
        std::cout << '|' << std::endl;
    }
    std::cout <<" ----------" << std::endl;
}


int GameField::clearFullRows(){
    int row = fieldSize_row-1;
    int fullRowsAmount = 0 ;
    while (row > 0){
        bool fullRow = true;
        for (int col = 0; col < fieldSize_col; col++){
            if (m_field[row][col] == emptyElement){
                fullRow = false;
                row--;
                break;
            }
        }
        if (fullRow == true) {
            fullRowsAmount++ ;
            for (int row_i = row-1; row_i > 0; row_i--)
                for (int col = 0; col < fieldSize_col; col++){
                    m_field[row_i+1][col] =  m_field[row_i][col];
                }
        }
    }
    //for (int col = 0; col < fieldSize_col; col++) // очищаем нулевой ряд
    //    m_field[0][col] = emptyElement;

    return fullRowsAmount;
}

const std::vector<std::vector<char>>& GameField::getField() const{
    return m_field;
}

void GameField::addFigure(Figure *fig){
    std::vector<std::vector<char>> fig_arr = fig -> getFig();
    int figCoordRow = fig -> getFigPositionRow();
    int figCoordCol = fig -> getFigPositionCol();
    int figSize = fig -> getFigSize();

    for (int row = figSize-1; row >= 0; row--){              //начинаем с последнего ряда
        if (figCoordRow - (figSize-1) + row < 0) break;              //Если фигура не полностью на поле прерываем цикл
        for (int col = 0; col < figSize; col++){
            if (fig_arr[row][col] == filledElement){                  // находим элемент фигуры
                m_field[figCoordRow - (figSize-1) + row][figCoordCol + col] = filledElement;                                            //если слева от элемента фигуры поле занято
            }
        }
    }
}

void GameField::removeFigure(Figure *fig){
    std::vector<std::vector<char>> fig_arr = fig -> getFig();
    int figCoordRow = fig -> getFigPositionRow();
    int figCoordCol = fig -> getFigPositionCol();
    int figSize = fig -> getFigSize();

    for (int row = figSize-1; row >= 0; row--){              //начинаем с последнего ряда
        if (figCoordRow - (figSize-1) + row < 0) break;              //Если фигура не полностью на поле прерываем цикл
        for (int col = 0; col < figSize; col++){
            if (fig_arr[row][col] == filledElement){                  // находим элемент фигуры
                m_field[figCoordRow - (figSize-1) + row][figCoordCol + col] = emptyElement;                                            //если слева от элемента фигуры поле занято
            }
        }
    }
}

bool GameField::gameOver(){
    for (int j = 0; j < fieldSize_col; j++){
             if ( m_field[0][j] == filledElement)
                 return true;
    }
    return false;
}
