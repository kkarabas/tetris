#include "figure.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "GlobalConst/globalconst.h"
#include "Utilities/utilities.h"


Figure::Figure(int DIM): m_figSize(DIM) {  // задаем размеры матрицы, по умолчанию 4х4

        m_figure.resize(m_figSize);
        for (int i = 0; i < m_figSize; i++){
           m_figure.at(i).resize(m_figSize);
        }
}

void Figure::clearFigure(){
        int figSize = m_figure.size();
        for (int i = 0; i < figSize; i++)
                for (int j = 0; j < figSize; j++)
                    m_figure[i][j] = emptyElement;
}

void Figure::printFigure() const{
        int figSize = m_figure.size();
        for (int i = 0; i < figSize; i++){
            for (int j = 0; j < figSize; j++)
                std::cout << m_figure[i][j];
            std::cout << std::endl;
        }
}

void Figure::findArrCenter ( int& centerRow, int& centerCol )const {   // поиск центра матрицы с фигурой
        int figSize = m_figure.size();
        for (int i = 0; i < figSize ; i++){
            centerRow += i;
            centerCol += i;
        }
        centerRow /= figSize;
        centerCol /= figSize;
}

void Figure::findFigCenter ( int& figCenterRow, int& figCenterCol ) const{   // поиск центра фигуры
        int figSize = m_figure.size();
        int rowCount = 0, colCount = 0; // Переменные для подсчета размера матрицы, нужной под фигуру (1x4, 3x2)
        for (int row = 0; row < figSize ; row++){
            for (int col = 0; col < figSize ; col++){
                if (m_figure[row][col] == filledElement){
                    figCenterRow += row;
                    figCenterCol += col;
                    if (row > rowCount) rowCount = row;
                    if (col > colCount) colCount = col;
                }
            }
        }
        figCenterRow /= rowCount+1;  // +1 потому что отсчет с нуля
        figCenterCol /= colCount+1;
}

void Figure::moveFigure(){
        int figSize = m_figure.size();
        bool toMove = false;
        do{
            for (int row = 0; row < figSize; row++){
                toMove = toMove || (m_figure[row][0] == filledElement);
                if (toMove) break;
            }
            if (!toMove){
                for (int row = 0; row < figSize; row++)
                    for(int col = 0; col < figSize-1; col++){
                       m_figure[row][col]=m_figure[row][col+1];
                       m_figure[row][col+1]= emptyElement;
                    }
            }
        } while (!toMove);
    }

void Figure::superposeCenters (){
        Figure::moveFigure();
        int centerRow = 0, centerCol = 0, figCenterRow = 0, figCenterCol = 0;
        int figSize = m_figure.size();
        findArrCenter(centerRow, centerCol);
  //std::cout << "arrCenterRow:" << centerRow << "arrCenterCol:" << centerCol << std::endl;
        findFigCenter(figCenterRow, figCenterCol);
  //std::cout << "figCenterRow:" << figCenterRow << "figCenterCol:" << figCenterCol << std::endl;
        while (centerRow != figCenterRow){
            if ((centerRow == 0 && centerCol ==0) || (figCenterRow == 0 && figCenterCol == 0 ) ) break; // если какой-то центр не посчитался
            if (centerRow > figCenterRow) {
                for (int row = figSize-1; row > 0; row--)
                    for(int col = 0; col < figSize; col++){
                      m_figure[row][col]=m_figure[row-1][col];
                      m_figure[row-1][col]= emptyElement;
                    }
                figCenterRow += 1;
            }
        }
        while (centerCol != figCenterCol){
            if (centerCol > figCenterCol) {
                for (int row = 0; row < figSize; row++)
                    for(int col = figSize - 1; col > 0; col--){
                      m_figure[row][col]=m_figure[row][col-1];
                      m_figure[row][col-1]= emptyElement;
                    }
                figCenterCol += 1;
            }
            if (centerCol < figCenterCol) {
                for (int row = 0; row < figSize; row++)
                    for(int col = 0; col < figSize-1; col++){
                        m_figure[row][col]=m_figure[row][col+1];
                        m_figure[row][col+1]= emptyElement;
                    }
                figCenterCol -= 1;
            }
        }
}

void Figure::arrCrop (){
        int arrSize = m_figure.size();
        int rowMax= 0, colMax = 0; // Переменные для подсчета max размера матрицы, нужной под фигуру
        for (int row = 0; row < arrSize ; row++){
            for (int col = 0; col < arrSize ; col++){
                if (m_figure[row][col] == filledElement){
                    if (row > rowMax) rowMax = row;
                    if (col > colMax) colMax = col;
                }
            }
        }
        int figSize = ((rowMax>colMax)?rowMax:colMax)+1;
        while (figSize < m_figure.size()){
            m_figure.resize(figSize);
            for (int i = 0; i < figSize; i++){
               m_figure.at(i).resize(figSize);
            }
        }
}

int Figure::getRandomNumber(int min, int max) const{
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Figure::generateFig(){
        clearFigure();

        int figSize = m_figure.size();
        int rest = figSize;                         // оставшиеся для расстановки кубики
        int j=0;                                             // количество кубиков в данной строке
        int pos_begin, pos_end;                              // позиции первого и последнего кубиков в строке
        pos_begin = pos_end = getRandomNumber(0, rest-1);    // выбираем позицию первого кубика в первой строке
        for(int row = 0; row < figSize; row++){
             if (rest == 0) break;

             if (row == 0){                                  // для первой строки такое распределение, чтобы палочки не часто выпадали
                 int k = getRandomNumber (0, 100);
                 if ( k>=0 && k< 53 ) j = 1;
                    else if ( k >= 53 && k < 82) j = 2;
                        else if ( k >= 82 && k < 94 ) j = 3;
                            else if ( k >= 94 && k <= 100 ) j = 4;
             }
             else j = getRandomNumber (1, rest);                // количество кубиков в строке
             rest -= j;                                         //уменьшаем кол-во оставшихся кубиков
             int pos = getRandomNumber(pos_begin, pos_end);     // ищем позицию куда поставить первый кубик в строке
             pos_begin = pos_end = pos;                         // сбрасываем значения pos_begin и pos_end
             m_figure[row][pos]=filledElement;                            // ставим туда кубик

                     for (int i = 1; i < j; i++){                       // ищем позицию куда поставить следующий кубик
                            int nextPos = getRandomNumber(0, 1);
                            if ( pos_begin == 0) {                      // если первый кубик на позиции ноль,
                                pos_end +=1;                            // то може добавлять только в конец
                                m_figure[row][pos_end]=filledElement;
                                continue;
                            }
                            else if ( pos_end == figSize-1){            // если кубик на позиции figSize-1,
                                pos_begin -=1;                          // то може добавлять только в начало
                                m_figure[row][pos_begin]=filledElement;
                                continue;
                            }
                             if ( nextPos == 1  ) {                       // если выпадает 1, то добавляем кубик в конец
                                 pos_end +=1;
                                 m_figure[row][pos_end]=filledElement;
                             }
                             else if ( nextPos == 0  ){                   // если выпадает 0, то добавляем кубик в начало
                                pos_begin -=1;
                                m_figure[row][pos_begin]=filledElement;
                             }
                      }
        }
        superposeCenters();
}

int Figure::getFigPositionRow() const{
    return m_figPositionRow;
}

int Figure::getFigPositionCol() const{
    return m_figPositionCol;
}

const std::vector<std::vector<char>>& Figure::getFig() const{
    return m_figure;
}

int Figure::getFigSize() const{
    return m_figure.size();
}

void Figure::resetFigPosition(){
    m_figPositionRow = 0 ;
    m_figPositionCol = 3 ;
}

void Figure::copy_cropNextFigure(const Figure* nextFigure){
    std::vector<std::vector<char>> nextFig = nextFigure -> getFig();
    if ( m_figure.size() != m_figSize ){
        m_figure.resize(m_figSize);
        for (int i = 0; i < m_figSize; i++){
            m_figure.at(i).resize(m_figSize);
        }
    }
    if (m_figure.size() != nextFig.size()){
        std::cerr << "Can not copy next figure";
        std::exit(2);
    } else for (int i = 0; i < m_figure.size(); i++)
            for (int j = 0; j < m_figure.size(); j++)
                m_figure[i][j] = nextFig[i][j];
    this -> arrCrop();
    this -> resetFigPosition();

   for (int j = m_figure.size()-1; j > 0 ; j--){
        bool movefigPosition = false ; // сдвинуть позицию фигуры вниз, если последний ряд пустой
                                       //(чтобы фигурасразу появлялась на поле)
        for (int i = 0; i < m_figure.size(); i++){
            movefigPosition = (movefigPosition || (m_figure[j][i] == filledElement)) ;
        }

        if( !movefigPosition )  m_figPositionRow++ ;
    }
}

void Figure::moveFigureLeft(){m_figPositionCol--;}
void Figure::moveFigureRight(){m_figPositionCol++;}
void Figure::moveFigureDown(){m_figPositionRow++;}
void Figure::rotateFig(){
    int figSize = m_figure.size();
    std::vector<std::vector<char>> temp_figure;
    temp_figure.resize(figSize);
    for (int i = 0; i < figSize; i++){
       temp_figure.at(i).resize(figSize);
    }
    for (int row = 0; row < figSize ; row++){
        for (int col = 0; col < figSize ; col++){
            temp_figure[row][col] = m_figure[col][figSize-1-row];
        }
    }
    for (int row = 0; row < figSize ; row++){
        for (int col = 0; col < figSize ; col++){
            m_figure[row][col] = temp_figure[row][col];
        }
    }
}


