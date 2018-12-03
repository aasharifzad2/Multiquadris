
#include "graphicDisplay.h"
#include "../core/game.h"
#include "../excp/not_implemented.h"


// Mark: - Static


// MARK: - Constructors & Destructor
GraphicDisplay::GraphicDisplay(int width, int height)
{
    window = std::make_unique<Xwindow>(width, height);
}


// MARK: - Visitors
void GraphicDisplay::accept(const Game *game) const
{
    int index = 0;

    for (auto player : game->getPlayers())
    {
        displayPlayer(player, index);
        
        index++;
    }
}


void GraphicDisplay::accept(const Player *player) const
{
    accept(player->getBoard());
}

void GraphicDisplay::accept(const Board *board) const
{
    for (auto row : board->getCells())
    {
        for (auto cell : row)
        {
            accept(cell);
        }
    }
}

void GraphicDisplay::accept(const Cell *cell) const
{
    int xpos = cell->getCol() * (CELL_DIM + INTER_CELL_BUFFER_WIDTH) + PAD_LEFT_WIDTH;
    int ypos = cell->getRow() * (CELL_DIM + INTER_CELL_BUFFER_WIDTH) + PAD_TOP_WIDTH;
    
    window->fillRectangle
    (
         xpos,
         ypos,
         CELL_DIM,
         CELL_DIM,
         cell->getColour()
    );
}


// MARK: - Protected Functions


// MARK: - Private Functions
void GraphicDisplay::displayPlayer(const Player * player, int index) const
{
    int interPlayerWidth = INTER_PLAYER_BUFFER_WIDTH * index;
    int cellDim = CELL_DIM + INTER_CELL_BUFFER_WIDTH;
    
    for (auto row : player->getBoard()->getCells())
    {
        for (auto cell : row)
        {
            int xpos = cell->getCol() * cellDim + PAD_LEFT_WIDTH + interPlayerWidth;
            int ypos = cell->getRow() * cellDim + PAD_TOP_WIDTH;
            
            window->fillRectangle
            (
                xpos,
                ypos,
                CELL_DIM,
                CELL_DIM,
                cell->getColour()
            );
        }
    }
}

