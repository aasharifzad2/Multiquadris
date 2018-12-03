#ifndef _cell_h_
#define _cell_h_


#include "colour.h"
class Block;
class BQDisplay;

class Cell
{
protected:
    Block *parent;
    bool filled;
    int row, col;
    Colour colour;
    
public:
    Cell(int row, int col, Block * = nullptr);
    
    void setRow(int);
    void setCol(int);
    void setCoords(int, int);
    
    int getRow() const;
    int getCol() const;
    bool isEmpty() const;
    bool isFilled() const;
    bool isInBlindZone() const;
    char getSymbol() const;
    Colour getColour() const;
    
    // Observer Pattern : Subject (Cell) notifying observer (Block) that one of
    //   the block's cells has been cleared
    void notifyCleared() const;
    
    // Visitor Pattern : visit(BQDisplay)
    void display(BQDisplay &);
};


#endif
