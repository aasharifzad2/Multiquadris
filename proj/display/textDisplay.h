#ifndef _text_display_h_
#define _text_display_h_


#include "display.h"
#include <iostream>

const int
    BUFFER_WIDTH = 7,
    NEXT_BLOCK_NUM_ROWS = 3;

class TextDisplay : public BQDisplay
{
protected:
    std::ostream &out;
    
public:
    TextDisplay(std::ostream & = std::cout);
    ~TextDisplay() override {}
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) const override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
    

protected:
    virtual void printPlacedCell(const Cell *) const;
    virtual void printFallingCell(const Cell *, bool curTurn = false) const;
    virtual void printBlindCell() const;
    
    
private:
    void printRow(const std::vector<Cell *>, bool, bool, const Block *) const;
    void printNextBlockRow(std::vector<Cell *>, bool) const;
    std::string getScoreText(const Player *) const;
    std::string getHighScoreText(const Player *) const;
    std::string getLevelText(const Player *) const;
    std::string getNextBlockText() const;
    void displayScores(const Game *, const std::vector<int>) const;
    void displayHighScores(const Game *, const std::vector<int>) const;
    void displayLevels(const Game *, const std::vector<int>) const;
    void displayBorder(const Game *, const std::vector<int>) const;
    void displayBoards(const Game *, const std::vector<int>) const;
    void displayNextBlock(const Game *, const std::vector<int>) const;
    std::vector<std::vector<std::vector<Cell *>>> getNextBlockCellGrids(const Game *) const;
    std::vector<std::vector<Cell *>> getNextBlockCellGrid(const Block *) const;
    std::vector<int> getWidths(const Game *) const;
    int getWidth(const Player *) const;
};


#endif

