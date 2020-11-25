#ifndef DRAWINTERFACE_H
#define DRAWINTERFACE_H

#include <vector>
#include <string>

class DrawInterface{
public:
        virtual void drawGameField( const std::vector< std::vector<char> > & ) = 0 ;
        virtual void printMsg(const std::string&) = 0 ;
        virtual void drawNextFigure( const std::vector< std::vector<char> > & ) = 0 ;
        virtual void printScore(int, int) = 0 ;
};


#endif // DRAWINTERFACE_H
