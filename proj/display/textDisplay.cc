
#include "textDisplay.h"
#include <iomanip>
#include <algorithm>
#include "../core/game.h"


// Mark: - Static


// Mark: - Constructors & Destructor
TextDisplay::TextDisplay(std::ostream &out) :
    out(out)
{}


// Mark: - Visitors
void TextDisplay::accept(const Game *game)
{
    std::vector<int> widths = getWidths(game);
    
    displayLevels(game, widths);
    displayHighScores(game, widths);
    displayScores(game, widths);
    displayBorder(game, widths);
    displayBoards(game, widths);
    displayBorder(game, widths);
    displayNextBlock(game, widths);
}

void TextDisplay::accept(const Player *player) const
{
    std::string horizontalBorder;
    for (int i = 0; i < player->getBoard()->getNumCols(); i++)
    {
        horizontalBorder += '-';
    }
    
    out << "Score: " << player->getScore() << std::endl;
    out << "High Score: " << player->getHighScore() << std::endl;
    out << "Level:  " << player->getLevelIndex() << std::endl;
    
    out << horizontalBorder << std::endl;
    
    for (auto row : player->getBoard()->getCells())
    {
        printRow
        (
            row,
            player->hasEffect(Effect::Blind),
            true,
            player->getFallingBlock()
        );
        
        out << std::endl;
    }
    out << horizontalBorder << std::endl;
}

void TextDisplay::accept(const Board *board) const
{
    for (auto row : board->getCells())
    {
        for (auto cell : row)
        {
            printPlacedCell(cell);
        }
        out << std::endl;
    }
}

void TextDisplay::accept(const Cell *cell) const
{
    printPlacedCell(cell);
}


// MARK: - Protected Functions
void TextDisplay::printPlacedCell(const Cell *cell) const
{
    out << cell->getSymbol();
}

void TextDisplay::printFallingCell(const Cell *cell, bool curTurn) const
{
    out << cell->getSymbol();
}

void TextDisplay::printBlindCell() const
{
    out << '?';
}


// MARK: - Private Functions
void TextDisplay::printRow
(
    const std::vector<Cell *> row,
    bool playerIsBlind,
    bool isTurn,
    const Block *fallingBlock
)
const
{
    for (auto cell : row)
    {
        Cell *fallingCell = fallingBlock->getMatchingCell(cell);
        if (playerIsBlind && cell->isInBlindZone())
        {
            printBlindCell();
        }
        else if (fallingCell)
        {
            printFallingCell(fallingCell, isTurn);
        }
        else
        {
            printPlacedCell(cell);
        }
    }
}

// Print rows for displaying the next Block
void TextDisplay::printNextBlockRow(std::vector<Cell *> row, bool isTurn) const
{
    for (auto cell : row)
    {
        if (cell && isTurn)
        {
            printPlacedCell(cell);
        }
        else
        {
            out << ' ';
        }
    }
}

std::string TextDisplay::getScoreText(const Player *player) const
{
    return "Score: " + std::to_string(player->getScore());
}

std::string TextDisplay::getHighScoreText(const Player *player) const
{
    return "High Score: " + std::to_string(player->getHighScore());
}

std::string TextDisplay::getLevelText(const Player *player) const
{
    return "Level: " + std::to_string(player->getLevelIndex());
}

std::string TextDisplay::getNextBlockText() const
{
    return "Next: ";
}

void TextDisplay::displayScores
(
    const Game *game,
    const std::vector<int> widths
)
const
{
    int index = 0;
    for (auto player : game->getPlayers())
    {
        std::string scoreText = getScoreText(player);
        
        out << scoreText
            << std::setw(widths.at(index) - (int)scoreText.length())
            << std::setfill(' ')
            << "";
        
        index++;
    }
    
    out << std::endl;
}

void TextDisplay::displayHighScores
(
    const Game *game,
    const std::vector<int> widths
)
const
{
    int index = 0;
    for (auto player : game->getPlayers())
    {
        std::string hScoreText = getHighScoreText(player);
        
        out << hScoreText
            << std::setw(widths.at(index) - (int)hScoreText.length())
            << std::setfill(' ')
            << "";
        
        index++;
    }
    
    out << std::endl;
}

void TextDisplay::displayLevels
(
    const Game * game,
    const std::vector<int> widths
)
const
{
    int index = 0;
    
    for (auto player : game->getPlayers())
    {
        std::string levelText = getLevelText(player);
        
        out << levelText
            << std::setw(widths.at(index) - (int)levelText.length())
            << std::setfill(' ')
            << "";
        
        index++;
    }
    
    out << std::endl;
}

void TextDisplay::displayBorder
(
    const Game * game,
    const std::vector<int> widths
)
const
{
    int index = 0;
    
    for (auto player : game->getPlayers())
    {
        int numCols = player->getBoard()->getNumCols();
        
        out << std::setw(numCols) << std::setfill('-') << "";
        out << std::setw(widths.at(index) - numCols)
            << std::setfill(' ')
            << "";
    }
    
    out << std::endl;
}

void TextDisplay::displayBoards
(
    const Game * game,
    const std::vector<int> widths
)
const
{
    int firstIndex = 0;
    int numRows = game->getPlayers().at(firstIndex)->getBoard()->getNumRows();
    int numCols = game->getPlayers().at(firstIndex)->getBoard()->getNumCols();
    
    for (int i = 0; i < numRows; i++)
    {
        int index = 0;
        
        for (auto player : game->getPlayers())
        {
            printRow
            (
                player->getBoard()->getCells().at(i),
                player->hasEffect(Effect::Blind),
                (game->getPlayerIndex() == index),
                player->getFallingBlock()
            );
            
            out << std::setw(widths.at(index) - numCols) << std::setfill(' ') << "";
            
            index++;
        }
        
        out << std::endl;
    }
}

void TextDisplay::displayNextBlock(const Game *game, const std::vector<int> widths) const
{
    for (auto width : widths)
    {
        std::string nextBlockText = getNextBlockText();
        
        out << nextBlockText
            << std::setw(width - (int)nextBlockText.length())
            << std::setfill(' ')
            << "";
    }
    
    out << std::endl;
    
    std::vector<std::vector<std::vector<Cell *>>> blockBoards = getNextBlockCellGrids(game);
    
    for (int i = 0; i < NEXT_BLOCK_NUM_ROWS; i++)
    {
        int playerIndex = 0;

        for (auto &board : blockBoards)
        {
            int numCols = (int)blockBoards.at(playerIndex).at(0).size();

            printNextBlockRow(board.at(i), (game->getPlayerIndex() == playerIndex));

            out << std::setw(widths.at(playerIndex) - numCols)
                << std::setfill(' ')
                << "";

            playerIndex++;
        }

        out << std::endl;
    }
}

std::vector<std::vector<std::vector<Cell *>>> TextDisplay::getNextBlockCellGrids(const Game *game) const
{
    std::vector<std::vector<std::vector<Cell *>>> blockBoards;
    
    for (auto player : game->getPlayers())
    {
        blockBoards.emplace_back(getNextBlockCellGrid(player->getNextBlock()));
    }
    
    return blockBoards;
}

std::vector<std::vector<Cell *>> TextDisplay::getNextBlockCellGrid
(
    const Block *block
)
const
{
    int leftest, rightest, highest, lowest;
    block->getBounds(leftest, rightest, highest, lowest);
    
    int numCols = rightest - leftest + 1;
    
    // Create 2D vector of nullptrs
    std::vector<std::vector<Cell *>> blockBoard
    (
        NEXT_BLOCK_NUM_ROWS,
        std::vector<Cell *>(numCols)
    );

    for (auto cell : block->getCells())
    {
        int x = cell->getRow() - highest;
        int y = cell->getCol() - leftest;
        blockBoard[x][y] = cell.get();
    }
    
    return blockBoard;
}


std::vector<int> TextDisplay::getWidths(const Game *game) const
{
    std::vector<int> widths;
    
    for (auto player : game->getPlayers())
    {
        widths.emplace_back(getWidth(player));
    }
    return widths;
}

int TextDisplay::getWidth(const Player *player) const
{
    int scoreLen = (int)(getScoreText(player)).length();
    int highScoreLen = (int)(getHighScoreText(player)).length();
    int numCols = player->getBoard()->getNumCols();
    
    return std::max({scoreLen, highScoreLen, numCols}) + BUFFER_WIDTH;
}

void TextDisplay::gameIsOver(const Game *game)
{
    out
    << "%%%%%%%%%%%%%%%%%%%" << std::endl
    << "%%%  GAME OVER  %%%" << std::endl
    << "%%%%%%%%%%%%%%%%%%%" << std::endl
    << std::endl;
    
    std::vector<Player *> players = game->getPlayers();
    int playerIndex = game->getPlayerIndex();
    
    if (players.size() == 1)
    {
        out
        << "You ended with a highscore of: "
        << players[playerIndex]->getHighScore()
        << std::endl
        << std::endl;
    }
    else if (players.size() == 2)
    {
        out
        << "Player " << (2-playerIndex) << " won!" << std::endl
        << "Player 1 highscore: "
        << players[0]->getHighScore() << std::endl
        << "Player 2 highscore: "
        << players[1]->getHighScore() << std::endl
        << std::endl;
    }
    else
    {
        // map for score and vectors of player numbers with that score
        std::map<int, std::vector<int>> scores;
        for (int i = 0; i < players.size(); i++)
        {
            // Add all the non-losing scorers to the score board
            if (i != playerIndex)
            {
                scores[players[i]->getHighScore()].emplace_back(i+1);
            }
        }
        
        int place = 1;
        for (auto itr = scores.rbegin(); itr != scores.rend(); ++itr)
        {
            for (auto playerNum : itr->second)
            {
                out
                << place
                << ". Player "
                << playerNum
                << "    "
                << itr->first
                << std::endl;
            }
            
            place++;
        }
        
        // Print Loser's Score
        out
        << place
        << ". Player "
        << playerIndex + 1
        << "    "
        << game->getPlayers()[game->getPlayerIndex()]->getHighScore()
        << std::endl
        << std::endl;
        
    }
}
