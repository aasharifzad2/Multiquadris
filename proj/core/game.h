#ifndef __GAME_H__
#define __GAME_H__


#include <string>
#include <map>

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
    IBlock,
    JBlock,
    LBlock,
    OBlock,
    SBlock,
    ZBlock,
    TBlock
};


class Game {
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
            {"I", Command::IBlock},
            {"J", Command::JBlock},
            {"L", Command::LBlock},
            {"O", Command::OBlock},
            {"S", Command::SBlock},
            {"Z", Command::ZBlock},
            {"T", Command::TBlock}
        };
    void readCommand();
    Command getCommand(std::string);
    
    public:
    void play();
};


#endif
