#ifndef cell_h
#define cell_h


#include "colour.h"
#include "placedBlock.h"

class Xwindow;

class Cell
{
    static Xwindow *window;
    
    bool filled;
    int x, y;
    Colour colour;
    PlacedBlock *parent;
    
    public:
    Cell(int, int, PlacedBlock *);
    static void setWindow(Xwindow *);
    bool isEmpty();
    bool isFilled();
    void notifyCleared();
    void draw();
};


#endif
