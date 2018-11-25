#ifndef cell_h
#define cell_h


#include "colour.h"
#include "block/placedBlock.h"

class Xwindow;

class Cell
{
    static Xwindow *window;
    
    bool filled;
    int row, col;
    Colour colour;
    PlacedBlock *parent;
    
    public:
    static void setWindow(Xwindow *);
    
    Cell(int row, int col, PlacedBlock *);
    
    int getRow() const;
    int getCol() const;
    bool isEmpty() const;
    bool isFilled() const;
    
    void setRow(int);
    void setCol(int);
    void setCoords(int, int);
    
    void notifyCleared() const;
    void draw();
};


#endif
