#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>

class Figure;

class GameField
{  
public:
    const int fieldSize_row=20;
    const int fieldSize_col=10;

    GameField();

    void printField() const;

    int clearFullRows();

    const std::vector<std::vector<char>>& getField() const;

    void addFigure(Figure*);

    void removeFigure(Figure*);

    bool gameOver();

private:
    std::vector<std::vector<char>> m_field;
};

#endif // GAMEFIELD_H
