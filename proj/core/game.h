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
    void setSequences();
    void setGraphicsEnabled(bool = true);
    void setRichTextEnabled(bool = true);
    
    // Getters
    std::vector<Player *> getPlayers() const;
    int getPlayerIndex() const;
    
    void play();
    void over();

    // Visitor Pattern : visit()
    void display();
    
    
private:
    Player *curPlayer() const;
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
    void enableGraphics();
    void disableGraphics();
    void enableRichText();
    void disableRichText();
    void addPlayer(int);
    void removePlayer(int);
};


#endif
