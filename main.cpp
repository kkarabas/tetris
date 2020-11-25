#include "Figure/figure.h"
#include "GameField/gamefield.h"
#include "Utilities/utilities.h"
#include "Action/action.h"
#include <iostream>
#include "GamePlay/gameplay.h"
#include "GamePlay/ncurs.h"


int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();
    NCurs* ncurs = new NCurs();
    ncurs -> play() ;
    delete ncurs;

    return 1;
    //delete field;

   // GnamePlay* game = new GamePlay();
    //game->run();
    //std::cout << "Goodbye";
   /* Figure* nextfig = new Figure();
    nextfig ->generateFig();
    Figure* fig = new Figure();
    fig -> copy_cropNextFigure(nextfig);

    GameField* fiel = new GameField();
    fiel ->addFigure(fig);
    fiel -> printField();
    fiel ->removeFigure(fig);
    fiel -> printField();
    std::cout << Utilities::checkRotate(fig, fiel)<< std::endl;
    std::cout << Utilities::checkDownMovement(fig, fiel)<< std::endl;
    std::cout << Utilities::checkLeftMovement(fig, fiel)<< std::endl;
    std::cout << Utilities::checkRightMovement(fig, fiel)<< std::endl;
    std::cout << "Goodbye" << std::endl;
    delete fig;
    delete fiel;
  */
}
