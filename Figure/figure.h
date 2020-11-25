#ifndef FIGURE_H
#define FIGURE_H


#include <vector>

class Figure
{

private:
    std::vector<std::vector<char>> m_figure ;
    int m_figPositionRow = 0 ;
    int m_figPositionCol = 3 ;
    int m_figSize ;

    void findArrCenter(int&, int&) const ;
    void findFigCenter(int&, int&) const ;
    void moveFigure() ;
    void superposeCenters() ;
    void arrCrop() ;
    int getRandomNumber(int, int) const ;
    void clearFigure() ;
    void resetFigPosition() ;

public:
    Figure(int DIM=4) ;

    void printFigure() const ;
    void generateFig() ;

    void moveFigureLeft() ;
    void moveFigureRight() ;
    void moveFigureDown() ;
    void rotateFig() ;

    int getFigPositionRow() const ;
    int getFigPositionCol() const ;
    int getFigSize() const ;

    const std::vector<std::vector<char>>& getFig() const ;
    void copy_cropNextFigure(const Figure*) ; //копирует следующюю фигуру в текущую и обрезает массив
};

#endif // FIGURE_H
