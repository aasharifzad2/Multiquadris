#ifndef _falling_block_h_
#define _falling_block_h_


#include "block.h"
#include "placedBlock.h"

class FallingBlock : public Block
{
    protected:
    static int initialX, initialY;

    public:
    virtual ~FallingBlock() = 0;
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void rotateCW();
    void rotateCCW();
    PlacedBlock *toPlacedBlock() const;
};


#endif
