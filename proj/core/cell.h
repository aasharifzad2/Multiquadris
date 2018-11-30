#ifndef _cell_h_
#define _cell_h_


#include "colour.h"
class Block;
class Display;

class Cell
{
    protected:
    Block *parent;
    bool filled;
    int row, col;
    Colour colour;
    
    public:
    Cell(int row, int col, Block * = nullptr);
    
    int getRow() const;
    int getCol() const;
    bool isEmpty() const;
    bool isFilled() const;
    bool isInBlindZone() const;
    char getSymbol() const;
    Colour getColour() const;

    void setRow(int);
    void setCol(int);
    void setCoords(int, int);
    
    void notifyCleared() const;
    
    // Visitor Pattern : visit(Display)
    void display(Display &);
};


#endif
