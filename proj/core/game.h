#ifndef _game_h_
#define _game_h_


#include <string>
#include <map>
#include "player.h"
#include "../display/textDisplay.h"
#include "../display/graphicDisplay.h"

const int
    MIN_NUM_PLAYERS = 1,
    MAX_NUM_PLAYERS = 5;

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
    PrintCommandInput,
    EnableGraphics,
    DisableGraphics,
    EnableRichText,
    DisableRichText,
    AddPlayer,
    RemovePlayer
};

class Game
{
    int playerIndex;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<TextDisplay> tDisplay;
    std::unique_ptr<GraphicDisplay> gDisplay;
    std::vector<std::string> commandsRead;
    
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
            {"precmd", Command::PrintCommandInput},
            {"engraphics", Command::EnableGraphics},
            {"disgraphics", Command::DisableGraphics},
            {"enrichtext", Command::EnableRichText},
            {"disrichtext", Command::DisableRichText},
            {"addplayer", Command::AddPlayer},
            {"removeplayer", Command::RemovePlayer}
        };
    
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
    void addPlayer(std::ifstream &);

    // Visitor Pattern : visit()
    void display();
    
    
private:
    void restart();
    Player *curPlayer() const;
    Player *nextPlayer() const;
    void endTurn();
    
    // Command Functions
    Command getCommand(std::string);
    void printCommandInput() const;
    bool readCommand(std::istream &);
};


#endif
