
#include "textDisplay.h"
#include <iomanip>
#include "../core/game.h"
#include "../excp/not_implemented.h"

// Mark: - Static


// Mark: - Constructors & Destructor
TextDisplay::TextDisplay(std::ostream &out) :
    out(out)
{}


// Mark: - Visitors
void TextDisplay::accept(const Game *game) const
{
    std::vector<int> widths = getWidths(game);
    
    displayScores(game, widths);
    displayHighScores(game, widths);
    displayLevels(game, widths);
    displayBorder(game, widths);
    displayBoards(game, widths);
    displayBorder(game, widths);
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
    out << "Level:  " << player->getCurLevel() << std::endl;
    
    out << horizontalBorder << std::endl;
    
    for (auto row : player->getBoard()->getCells())
    {
        printRow
        (
            row,
            player->hasEffect(Effect::Blind),
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


// MARK: - Protected Function
void TextDisplay::printPlacedCell(const Cell *cell) const
{
    out << cell->getSymbol();
}

void TextDisplay::printFallingCell(const Cell *cell) const
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
    std::vector<Cell *> row,
    bool playerIsBlind,
    Block *fallingBlock
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
            printFallingCell(fallingCell);
        }
        else
        {
            printPlacedCell(cell);
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
    return "Level: " + std::to_string(player->getCurLevel());
}

void TextDisplay::displayScores(const Game * game, const std::vector<int> widths) const
{
    int index = 0;
    for (auto player : game->getPlayers())
    {
        std::string scoreText = getScoreText(player);
        
        out << scoreText
            << std::setw(widths.at(index) - (int) scoreText.length())
            << std::setfill(' ')
            << "";
        
        index++;
    }
    
    out << std::endl;
}

void TextDisplay::displayHighScores(const Game * game, const std::vector<int> widths) const
{
    int index = 0;
    for (auto player : game->getPlayers())
    {
        std::string hScoreText = getHighScoreText(player);
        
        out << hScoreText
            << std::setw(widths.at(index) - (int) hScoreText.length())
            << std::setfill(' ')
            << "";
        
        index++;
    }
    
    out << std::endl;
}

void TextDisplay::displayLevels(const Game * game, const std::vector<int> widths) const
{
    int index = 0;
    
    for (auto player : game->getPlayers())
    {
        std::string levelText = getLevelText(player);
        
        out << levelText
            << std::setw(widths.at(index) - (int) levelText.length())
            << std::setfill(' ')
            << "";
        
        index++;
    }
    
    out << std::endl;
}

void TextDisplay::displayBorder(const Game * game, const std::vector<int> widths) const
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

void TextDisplay::displayBoards(const Game * game, const std::vector<int> widths) const
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
                 player->getFallingBlock()
            );
            
            out << std::setw(widths.at(index) - numCols) << std::setfill(' ') << "";
        }
        
        out << std::endl;
    }
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
    int scoreLen = (int) (getScoreText(player)).length();
    int highScoreLen = (int) (getHighScoreText(player)).length();
    int numCols = player->getBoard()->getNumCols();
    
    return std::max({scoreLen, highScoreLen, numCols}) + bufferWidth;
}
