#include "utilities.h"
#include "Figure/figure.h"
#include "GameField/gamefield.h"
#include <vector>
#include <iostream>
#include "GlobalConst/globalconst.h"

// для каждого элемента фигуры:
// row (в координатах поля) = figCoordRow (коорд фигуры в координатах поля) - (figSize - 1) + row (в координатах фигуры)
// col (в координатах поля) = figCoordCol (коорд фигуры в координатах поля) + col (в координатах фигуры)

// при повороте координаты меняются след. образом (в координатах фигуры):
// row -> col
// col -> figSize - 1 - row

// при повороте координаты меняются след. образом (в координатах поля):
// col(в координатах поля) = (figCoordCol + (figSize-1-row(в координатах фигуры))
// row (в координатах поля) = (figCoordRow - (figSize-1) + col(в координатах фигуры))

bool Utilities::checkLeftMovement(const Figure* fig, const GameField* gameField){
    std::vector<std::vector<char>> fig_arr = fig -> getFig();
    std::vector<std::vector<char>> gameField_arr = gameField -> getField();
    int figSize = fig_arr.size();
    int figCoordRow = fig -> getFigPositionRow();
    int figCoordCol = fig -> getFigPositionCol();

    for (int row = figSize-1; row >= 0; row--){              //начинаем с последнего ряда                
        for (int col = 0; col < figSize; col++){  
            if (fig_arr[row][col] == filledElement){                  // находим элемент фигуры
                 //std::cout << "fig_arr["<<row<<"]["<<col<<"]=filledEl"<< std::endl;
                  //std::cout << "col in field coord ="<<figCoordCol + col<< std::endl;
                  //std::cout << "col -1 in field coord ="<<gameField_arr[figCoordRow - (figSize-1) + row][figCoordCol + col - 1]<< std::endl;

                if ( figCoordCol + col == 0 ) return false;     //если слева от него находится граница, т.е. координаты в системе поля == 0
                if ( (figCoordRow - (figSize-1) + row >= 0) &&  // для элементов фигуры, кот. уже вышли на поле
                    (gameField_arr[figCoordRow - (figSize-1) + row][figCoordCol + col - 1] == filledElement) )                                          //если слева от элемента фигуры поле занято
                     return false;
            }
        }
    }
    return true;
}

bool Utilities::checkRightMovement(const Figure* fig, const GameField* gameField){
    std::vector<std::vector<char>> fig_arr = fig -> getFig();
    std::vector<std::vector<char>> gameField_arr = gameField -> getField();
    int figSize = fig_arr.size();
    int fieldSizeCol = gameField_arr[0].size();
    int figCoordRow = fig -> getFigPositionRow();
    int figCoordCol = fig -> getFigPositionCol();

    for (int row = figSize-1; row >= 0; row--){              //начинаем с последнего ряда
        for (int col = 0; col < figSize; col++){
            if (fig_arr[row][col] == filledElement){                  // находим элемент фигуры
                if ( figCoordCol + col == fieldSizeCol - 1 ) return false;      //если справа от него находится граница
                if ( (figCoordRow - (figSize-1) + row >= 0) &&
                     (gameField_arr [figCoordRow - (figSize-1) + row][figCoordCol + col + 1] == filledElement) )  //если справа от элемента фигуры поле занято
                        return false;
                }
            }
    }
    return true;
}

bool Utilities::checkDownMovement(const Figure* fig, const GameField* gameField){
    std::vector<std::vector<char>> fig_arr = fig -> getFig();
    std::vector<std::vector<char>> gameField_arr = gameField -> getField();
    int figSize = fig_arr.size();
    int fieldSizeRow = gameField_arr.size();
    int figCoordRow = fig -> getFigPositionRow();
    int figCoordCol = fig -> getFigPositionCol();

    for (int row = figSize-1; row >= 0; row--){              //начинаем с последнего ряда
        if (figCoordRow - (figSize-1) + row < 0) break;              //Если фигура не полностью на поле прерываем цикл
        for (int col = 0; col < figSize; col++){
            if (fig_arr[row][col] == filledElement){ // находим элемент фигуры
                if ( ( figCoordRow - (figSize-1) + row  == fieldSizeRow - 1 ) ||      //если снизу от него находится граница
                   (gameField_arr [figCoordRow - (figSize-1) + row + 1][figCoordCol + col] == filledElement) )  //если снизу от элемента фигуры поле занято
                      return false;
                }
            }
    }
    return true;
}

bool Utilities::checkRotate(const Figure* fig, const GameField* gameField){
    std::vector<std::vector<char>> fig_arr = fig -> getFig();
    std::vector<std::vector<char>> gameField_arr = gameField -> getField();
    int figSize = fig_arr.size();
    int fieldSizeCol = gameField_arr[0].size();
    int fieldSizeRow = gameField_arr.size();
    int figCoordRow = fig -> getFigPositionRow();
    int figCoordCol = fig -> getFigPositionCol();

    for (int col = figSize-1; col >= 0 ; col--){              //начинаем с последнего элемента последней колонки и идем вверх по колонке, чтобы прерывать цикл если фигура не свя на поле
        for (int row = figSize-1; row >= 0; row--){
            if ( fig_arr[row][col] == filledElement &&                     // если находим элемент фигуры и
                 ( figCoordCol + (figSize-1-row) < 0 ||                    //если после поворота этот элемент вылезет за поле слева
                   figCoordCol + (figSize-1-row) > fieldSizeCol - 1 ||     // или справа
                   figCoordRow - (figSize-1) + col  > fieldSizeRow - 1 ))  // или снизу
                return false;
            if ( (figCoordRow - (figSize-1) + col >= 0) &&  //если после поворота фигура элемент фигуры находится в поле, т.е. его ряд > 0 и
                 (gameField_arr [figCoordRow - (figSize-1) + col][figCoordCol + (figSize-1-row)] == filledElement) ) // этот элемент залезет на заполненную ячейку
                return false;
        }
    }
    return true;
}
