#ifndef _block_h_
#define _block_h_


#include <vector>
#include <memory>
#include "../colour.h"
class Cell;

class Block
{
    protected:
    static int initialX, initialY;
    int levelGenerated;
    Colour colour;
    std::vector<std::shared_ptr<Cell>> cells;
    
    public:
    virtual ~Block() = 0;
    Block(Colour);

    void setLevelGenerated(int);
    
    int numCells() const;
    Colour getColour() const;
    Cell *getCell(int) const;
    std::vector<Cell *> getCells() const;
    
    // Observer Pattern : Called by subject (Cell) to notify cell being cleared
    void cellCleared(Cell const * const);
    // Movement methods
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void rotateCW();
    void rotateCCW();
};


#endif
