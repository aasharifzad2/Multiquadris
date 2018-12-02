#ifndef _text_display_h_
#define _text_display_h_


#include "display.h"
#include <iostream>

const int
    bufferWidth = 4;

class TextDisplay : public Display
{
protected:
    std::ostream &out;
    
public:
    TextDisplay(std::ostream & = std::cout);
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) const override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
    

protected:
    virtual void printPlacedCell(const Cell *) const;
    virtual void printFallingCell(const Cell *) const;
    virtual void printBlindCell() const;
    
    
private:
    void printRow(std::vector<Cell *>, bool, Block *) const;
    std::string getScoreText(const Player *) const;
    std::string getHighScoreText(const Player *) const;
    std::string getLevelText(const Player *) const;
    void displayScores(const Game *, const std::vector<int>) const;
    void displayHighScores(const Game *, const std::vector<int>) const;
    void displayLevels(const Game *, const std::vector<int>) const;
    void displayBorder(const Game *, const std::vector<int>) const;
    void displayBoards(const Game *, const std::vector<int>) const;
    std::vector<int> getWidths(const Game *) const;
    int getWidth(const Player *) const;
};


#endif

