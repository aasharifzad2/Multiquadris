#ifndef _command_h_
#define _command_h_


#include <string>
class Game;


class Command
{
protected:
    Game *game;
    std::string key;
    
public:
    // Destructor
    virtual ~Command();
    
    // Getters
    std::string getKey();
    
    // returns true if the command starts with the key
    bool keyMatches(std::string &);
    virtual void execute(int multiplier) = 0;
};


#endif
