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
    char symbol;
    Colour colour;
    std::vector<std::shared_ptr<Cell>> cells;
    
    public:
    virtual ~Block() = 0;
    Block(char, Colour);

    void setLevelGenerated(int);
    
    int getNumCells() const;
    int getLevelGenerated() const;
    char getSymbol() const;
    Colour getColour() const;
    std::shared_ptr<Cell> getCell(int) const;
    std::vector<std::shared_ptr<Cell>> getCells() const;
    
    // Observer Pattern : Called by subject (Cell) to notify cell being cleared
    void cellCleared(const Cell *);
    // Movement methods
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void rotateCW();
    void rotateCCW();
    
    private:
    void getBounds(int &, int &, int &, int &);
};


#endif
