#ifndef _game_h_
#define _game_h_


#include <string>
#include <map>
#include "player.h"
#include "../display/textDisplay.h"
#include "../display/display.h"


enum Command
{
    Left,
    Right,
    Down,
    RotateCW,
    RotateCCW,
    Drop,
    LevelUp,
    LevelDown,
    NoRandom,
    Random,
    Sequence,
    Restart,
    ForceIBlock,
    ForceJBlock,
    ForceLBlock,
    ForceOBlock,
    ForceSBlock,
    ForceZBlock,
    ForceTBlock,
    // Bonus:
    PrintCommandInput
};


class Game
{
    int playerIndex;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::string> commandsRead;
    
    
    Display &tDisplay;
    std::map<std::string, Command> commands =
        {
            {"left", Command::Left},
            {"right", Command::Right},
            {"down", Command::Down},
            {"clockwise", Command::RotateCW},
            {"counterclockwise", Command::RotateCCW},
            {"drop", Command::Drop},
            {"levelup", Command::LevelUp},
            {"leveldown", Command::LevelDown},
            {"norandom", Command::NoRandom},
            {"random", Command::Random},
            {"sequence", Command::Sequence},
            {"restart", Command::Restart},
            {"I", Command::ForceIBlock},
            {"J", Command::ForceJBlock},
            {"L", Command::ForceLBlock},
            {"O", Command::ForceOBlock},
            {"S", Command::ForceSBlock},
            {"Z", Command::ForceZBlock},
            {"T", Command::ForceTBlock},
            {"precmd", Command::PrintCommandInput}
        };
    
public:
    Game(Display &);
    
    // Setters
    
    // Getters
    std::vector<Player *> getPlayers() const;
    
    void play();
    void addPlayer(std::ifstream &);

    // Visitor Pattern : visit(Display)
    void display(Display &);
    
    
private:
    Player *curPlayer() const;
    Player *nextPlayer() const;
    void endTurn();
    
    // Command Functions
    Command getCommand(std::string);
    void printCommandInput() const;
    bool readCommand(std::istream &);
};


#endif
