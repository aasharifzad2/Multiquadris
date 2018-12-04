#ifndef _game_h_
#define _game_h_


#include <string>
#include <map>
#include "player.h"
#include "../display/textDisplay.h"
#include "../display/graphicDisplay.h"
#include "../cmd/commandInterpreter.h"

const int
    MIN_NUM_PLAYERS = 1,
    MAX_NUM_PLAYERS = 5;

class Game
{
    // 1 or -1 depending on the direction the game travels
    int turnDirection;
    int playerIndex;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<TextDisplay> tDisplay;
    std::unique_ptr<GraphicDisplay> gDisplay;
    std::vector<std::string> commandsRead;
    CommandInterpreter cmd;
    
public:
    Game();
    
    // Setters
    void setNumPlayers(int);
    void setSequence1(std::ifstream &);
    void setSequence2(std::ifstream &);
    void setGraphicsEnabled(bool);
    void setRichTextEnabled(bool);
    void setLevel(int);
    
    // Getters
    std::vector<Player *> getPlayers() const;
    int getPlayerIndex() const;
    
    void play();
    
    // Observer Patterns
    void triggerGameOver();
    void triggerSpecialAction();

    // Visitor Pattern : visit()
    void display();
    
    
private:
    Player *curPlayer() const;
    int nextPlayerIndex() const;
    Player *nextPlayer() const;
    void endTurn();
    void initCommands();

    // Command Functions
    void moveBlockLeft(int);
    void moveBlockRight(int);
    void moveBlockDown(int);
    void rotateBlockCW(int);
    void rotateBlockCCW(int);
    void dropBlock();
    void increaseCurPlayerLevel(int);
    void decreaseCurPlayerLevel(int);
    void randomizeCurPlayerLevel();
    void unrandomizeCurPlayerLevel();
    void readSequence();
    void restart();
    void forceIBlock();
    void forceJBlock();
    void forceLBlock();
    void forceOBlock();
    void forceSBlock();
    void forceZBlock();
    void forceTBlock();
    void printCommandInput();
    void setGraphicsEnabled();
    void setRichTextEnabled();
    void addPlayer(int);
    void removePlayer(int);
    
    // Special Commands
    void blindAction();
    void forceAction();
    void heavyAction();
    void denzelAction();
};


#endif
