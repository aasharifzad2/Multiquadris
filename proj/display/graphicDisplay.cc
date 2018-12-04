
#include "graphicDisplay.h"
#include "../core/game.h"
#include "../excp/not_implemented.h"


// Mark: - Static


// MARK: - Constructors & Destructor
GraphicDisplay::GraphicDisplay(int width, int height)
{
    window = std::make_unique<Xwindow>(width, height);
    
    std::vector<std::vector<Cell *>> board
    (
         NUM_ROWS,
         std::vector<Cell *>(NUM_COLS)
    );
    std::vector<std::vector<Cell *>> board_2
    (
        NUM_ROWS,
        std::vector<Cell *>(NUM_COLS)
    );
    prevState.emplace_back(board);
    prevState.emplace_back(board_2);
    
    prevFallingBlocks = std::vector<std::vector<Cell *>>
    (
        2,
        std::vector<Cell *>(4)
    );
}


// MARK: - Visitors
void GraphicDisplay::accept(const Game *game)
{
    
    int index = 0;

    for (auto player : game->getPlayers())
    {
        
        displayScore(player, index);
        displayHighScore(player, index);
        displayLevel(player, index);
        displayPlayer(player, index);
        
        erasePrevFallingBlocks(player, index);
        displayFallingBlock(player, index);
        displayNextBlock(player, index);
        
        index++;
    }
    updateState(game);
    updatePrevFallingBlocks(game);
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
void GraphicDisplay::displayPlayer(const Player * player, int index)
{
    int interPlayerWidth = INTER_PLAYER_BUFFER_WIDTH * index;
    int cellDim = CELL_DIM + INTER_CELL_BUFFER_WIDTH;
    
    for (auto row : player->getBoard()->getCells())
    {
        for (auto cell : row)
        {
            int xpos = cell->getCol() * cellDim + PAD_LEFT_WIDTH + interPlayerWidth;
            int ypos = cell->getRow() * cellDim + PAD_TOP_WIDTH;
            
            if (cellChanged(cell, index) && cell->isInBlindZone() && player->hasEffect(Blind))
            {
                fillBlindCell(xpos, ypos, CELL_DIM, CELL_DIM);
            }
            else if (cellChanged(cell, index))
            {
                
                fillCell(xpos, ypos, CELL_DIM, CELL_DIM, cell->getColour());
            }
        }
    }
}

void GraphicDisplay::displayHighScore(const Player *player, int index) const
{
    int xpos = PAD_LEFT_WIDTH + (index * INTER_PLAYER_BUFFER_WIDTH);
    int ypos = HIGH_SCORE_Y;
    int ypos_eraser = ypos - ERASER_RECT_HEIGHT + 3;
    std::string text = "High Score: " + std::to_string(player->getHighScore());
    
    window->fillRectangle(xpos, ypos_eraser, ERASER_RECT_WIDTH, CELL_DIM, White);
    window->drawString(xpos, ypos, text);
}

void GraphicDisplay::displayLevel(const Player *player, int index) const
{
    int xpos = PAD_LEFT_WIDTH + (index * INTER_PLAYER_BUFFER_WIDTH);
    int ypos = LEVEL_Y;
    int ypos_eraser = ypos - ERASER_RECT_HEIGHT + 3;
    
    std::string text = "Level: " + std::to_string(player->getLevelIndex());
    
    window->fillRectangle(xpos, ypos_eraser, ERASER_RECT_WIDTH, CELL_DIM, White);
    window->drawString(xpos, ypos, text);
}

void GraphicDisplay::displayScore(const Player *player, int index) const
{
    int xpos = PAD_LEFT_WIDTH + (index * INTER_PLAYER_BUFFER_WIDTH);
    int ypos = SCORE_Y;
    int ypos_eraser = ypos - ERASER_RECT_HEIGHT + 3;
    std::string text = "Score: " + std::to_string(player->getScore());
    
    window->fillRectangle(xpos, ypos_eraser, ERASER_RECT_WIDTH, CELL_DIM, White);
    window->drawString(xpos, ypos, text);
}

void GraphicDisplay::updateState(const Game *game)
{
    int playerIndex = 0;
    
    for (auto player : game->getPlayers())
    {
        if (playerIndex == game->getPlayerIndex())
        {
            int rowIndex = 0;
            for (auto row : player->getBoard()->getCells())
            {
                int colIndex = 0;
                for (auto cellptr : row)
                {
                    prevState[playerIndex][rowIndex][colIndex] = cellptr;
                    colIndex++;
                }
                rowIndex++;
            }
        }
        playerIndex++;
    }
}

bool GraphicDisplay::cellChanged(const Cell *cell, int playerIndex)
{
    int row = cell->getRow();
    int col = cell->getCol();
    
    return (prevState[playerIndex][row][col] != cell);
}


void GraphicDisplay::displayNextBlock(const Player *player, int index) const
{
    int xpos = PAD_LEFT_WIDTH + (index * INTER_PLAYER_BUFFER_WIDTH);
    int ypos = NEXT_BLOCK_Y;
    std::string text = "Next Block: ";
    
    window->drawString(xpos, ypos, text);
    
    int interPlayerWidth = INTER_PLAYER_BUFFER_WIDTH * index;
    int cellDim = CELL_DIM + INTER_CELL_BUFFER_WIDTH;
    int xpos_eraser = PAD_LEFT_WIDTH + interPlayerWidth + 40;
    int ypos_eraser = PAD_TOP_WIDTH + PAD_BELOW_PLAYER + 20;
    int dim_eraser = CELL_DIM * 5;
    
    window->fillRectangle(xpos_eraser, ypos_eraser, dim_eraser, dim_eraser, White);
    
    for (auto cell : player->getNextBlock()->getCells())
    {
        int xpos = cell->getCol() * cellDim + PAD_LEFT_WIDTH + interPlayerWidth + 40;
        int ypos = cell->getRow() * cellDim + PAD_TOP_WIDTH + PAD_BELOW_PLAYER;
        
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


void GraphicDisplay::displayFallingBlock(const Player *player, int index)
{
    int interPlayerWidth = INTER_PLAYER_BUFFER_WIDTH * index;
    int cellDim = CELL_DIM + INTER_CELL_BUFFER_WIDTH;

    for (auto cell : player->getFallingBlock()->getCells())
    {
        int xpos = cell->getCol() * cellDim + PAD_LEFT_WIDTH + interPlayerWidth;
        int ypos = cell->getRow() * cellDim + PAD_TOP_WIDTH;

        if (cell->isInBlindZone() && player->hasEffect(Blind))
        {
            fillBlindCell(xpos, ypos, CELL_DIM, CELL_DIM);
        }
        else
        {
            fillCell(xpos, ypos, CELL_DIM, CELL_DIM, cell->getColour());
        }
    }
}

void GraphicDisplay::erasePrevFallingBlocks(const Player *player, int index)
{

    int interPlayerWidth = INTER_PLAYER_BUFFER_WIDTH * index;
    int cellDim = CELL_DIM + INTER_CELL_BUFFER_WIDTH;
    for (auto cell : prevFallingBlocks.at(index))
    {
        if (cell) {
            int xpos = cell->getCol() * cellDim + PAD_LEFT_WIDTH + interPlayerWidth;
            int ypos = cell->getRow() * cellDim + PAD_TOP_WIDTH;

            if (cell->isInBlindZone() && player->hasEffect(Blind))
            {
                fillBlindCell(xpos, ypos, CELL_DIM, CELL_DIM);
            }
            else
            {
                fillCell(xpos, ypos, CELL_DIM, CELL_DIM, Black);
            }
            
        }
    }
}


void GraphicDisplay::updatePrevFallingBlocks(const Game *game)
{
    int playerIndex = 0;
    
    for (auto player : game->getPlayers())
    {
        if (playerIndex == game->getPlayerIndex())
        {
            int index = 0;
            for (auto cell : player->getFallingBlock()->getCells())
            {
                Cell *newCell = new Cell();
                newCell->setCoords(cell->getRow(), cell->getCol());
                prevFallingBlocks[playerIndex][index] = newCell;
                index++;
            }
        }
        playerIndex++;
    }
}

void GraphicDisplay::fillBlindCell(int x, int y, int width, int height)
{
    window->fillRectangle
    (
     x,
     y,
     width,
     height,
     DarkGreen
     );
}

void GraphicDisplay::fillCell(int x, int y, int width, int height, Colour colour)
{
    window->fillRectangle
    (
     x,
     y,
     width,
     height,
     colour
     );
}

void GraphicDisplay::gameIsOver(const Game *game)
{
    window->fillRectangle(0, 0, 700, 700, White);
    int col = White;
    for (int i = 0; i <= 700; i+=50)
    {
        window->drawBigString(200, i, "GAME OVER", col);
        col++;
    }
    
    std::vector<Player *> players = game->getPlayers();
    int playerIndex = game->getPlayerIndex();
    
    
    if (players.size() == 1)
    {
        std::string msg = std::to_string(players[playerIndex]->getHighScore());
        for (int i = 0; i <= 11; i++)
        {
            window->fillRectangle(150, 150, 400, 400, i);
        }
        window->drawBigString(200, 200, "YOU ENDED", Red);
        window->drawBigString(200, 250, "WITH A", DarkGreen);
        window->drawBigString(200, 300, "HIGHSCORE", Blue);
        window->drawBigString(200, 350, "OF :");
        window->drawBigString(200, 400, msg, Red);
    }
    else if (players.size() == 2)
    {
        for (int i = 0; i <= 11; i++)
        {
            window->fillRectangle(150, 100, 400, 500, i);
        }
        std::string msg = std::to_string(2-playerIndex);
        std::string msg2 = std::to_string(players[0]->getHighScore());
        std::string msg3 = std::to_string(players[1]->getHighScore());
        
        window->drawBigString(200, 200, "PLAYER", Red);
        window->drawBigString(200, 250, msg, Green);
        window->drawBigString(200, 300, "WON!", Black);
        window->drawBigString(200, 350, "PLAYER 1:", DarkGreen);
        window->drawBigString(200, 400, msg2, Blue);
        window->drawBigString(200, 450, "PLAYER 2:", Yellow);
        window->drawBigString(200, 500, msg3, Red);
    }
}
