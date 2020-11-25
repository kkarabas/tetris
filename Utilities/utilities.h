#ifndef UTILITIES_H
#define UTILITIES_H

class Figure;
class GameField;

namespace Utilities {

bool checkLeftMovement(const Figure*, const GameField*);

bool checkRightMovement(const Figure*, const GameField*);

bool checkDownMovement(const Figure*, const GameField*);

bool checkRotate(const Figure*, const GameField*);

}

#endif // UTILITIES_H
