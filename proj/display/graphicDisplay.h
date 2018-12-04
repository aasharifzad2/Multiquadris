#ifndef _graphic_display_h_
#define _graphic_display_h_


#include "display.h"

#ifdef GRAPHICS
#include "window.h"
#else
#include "windowTemp.h"
#endif

const int
    NUM_ROWS = 18,
    NUM_COLS = 11,
    CELL_DIM = 15,
    PAD_TOP_WIDTH = 200,
    PAD_LEFT_WIDTH = 60,
    INTER_CELL_BUFFER_WIDTH= 2,
    INTER_PLAYER_BUFFER_WIDTH = 390,
    WINDOW_WIDTH = 700,
    WINDOW_HEIGHT = 700,
    HIGH_SCORE_Y = 100,
    LEVEL_Y = 125,
    SCORE_Y = 150,
    NEXT_BLOCK_Y = 550,
    ERASER_RECT_WIDTH = 187,
    ERASER_RECT_HEIGHT = 15,
    PAD_BELOW_PLAYER = 350;

class GraphicDisplay : public BQDisplay
{
    std::unique_ptr<Xwindow> window;
    std::vector<std::vector<std::vector<Cell *>>> prevState;
    std::vector<std::vector<Cell *>> prevFallingBlocks;
    
public:
    GraphicDisplay(int = 700, int = 700);
    ~GraphicDisplay() override {};
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
    
    void gameIsOver(const Game *);
    
private:
    void displayPlayer(const Player *, int);
    void displayHighScore(const Player *, int) const;
    void displayLevel(const Player *, int) const;
    void displayScore(const Player *, int) const;
    void updateState(const Game *);
    bool cellChanged(const Cell *, int);
    void displayNextBlock(const Player *, int) const;
    void displayFallingBlock(const Player *, int) ;
    void erasePrevFallingBlocks(const Player *, int);
    void updatePrevFallingBlocks(const Game *);
    void fillBlindCell(int, int, int, int);
    void fillCell(int, int, int, int, Colour);
};


#endif
