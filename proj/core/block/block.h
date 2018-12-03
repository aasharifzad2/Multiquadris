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
    Block(char, Colour);
    virtual ~Block() = 0;

    // Setters
    void setLevelGenerated(int);
    
    // Getters
    int getLevelGenerated() const;
    char getSymbol() const;
    Colour getColour() const;
    int getNumCells() const;
    std::shared_ptr<Cell> getCell(int) const;
    std::vector<std::shared_ptr<Cell>> getCells() const;
    Cell *getMatchingCell(const Cell *) const;
    // Calculates the extreme row and col values of the block
    void getBounds(int &, int &, int &, int &) const;
    
    // Observer Pattern : cell notifies block that the cell has been cleared
    void cellCleared(const Cell *);
    
    // Movement methods
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void rotateCW();
    void rotateCCW();
    
private:
    void checkHeavyLevel();
    void checkHeavySpecial();
};


#endif
