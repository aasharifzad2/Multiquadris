#ifndef _cell_h_
#define _cell_h_


#include "colour.h"

class Xwindow;
class Block;

class Cell
{
    protected:
    static Xwindow *window;
    
    Block *parent;
    bool filled;
    int row, col;
    Colour colour;
    
    public:
    static void setWindow(Xwindow *);
    
    Cell(int row, int col, Block * = nullptr);
    
    int getRow() const;
    int getCol() const;
    bool isEmpty() const;
    bool isFilled() const;
    
    void setRow(int);
    void setCol(int);
    void setCoords(int, int);
    
    void notifyCleared() const;
};


#endif
