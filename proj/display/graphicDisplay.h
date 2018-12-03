#ifndef _graphic_display_h_
#define _graphic_display_h_


#include "display.h"

#ifdef GRAPHICS
#include "window.h"
#else
#include "windowTemp.h"
#endif

const int
    CELL_DIM = 15,
    PAD_TOP_WIDTH = 300,
    PAD_LEFT_WIDTH = 60,
    INTER_CELL_BUFFER_WIDTH= 2,
    INTER_PLAYER_BUFFER_WIDTH = 390,
    WINDOW_WIDTH = 700,
    WINDOW_HEIGHT = 700;

class GraphicDisplay : public BQDisplay
{
    std::unique_ptr<Xwindow> window;
    
public:
    GraphicDisplay(int = 700, int = 700);
    ~GraphicDisplay() override {};
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) const override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
    
private:
    void displayPlayer(const Player *, int) const;
};


#endif
