
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#ifdef DEBUG
#include <ctime>
#include "display/richTextDisplay.h"
#include "display/textDisplay.h"
#include "core/board.h"
#include "core/player.h"
#include "core/level.h"
#include "core/game.h"
#include "core/block/stream/blockStream.h"
#include "core/block/stream/randomBlockStream.h"
#endif


const std::string
    DEFAULT_SCRIPTFILE1 = "blocksq/sequence1.txt",
    DEFAULT_SCRIPTFILE2 = "blocksq/sequence2.txt",
    OPTION_TEXT = "-text",
    OPTION_SEED = "-seed",
    OPTION_SCRIPTFILE1 = "-scriptfile1",
    OPTION_SCRIPTFILE2 = "-scriptfile2",
    OPTION_LEVEL = "-startlevel";


const int
    DEFAULT_STARTLEVEL  = 1,
    DEFAULT_SEED        = 19990113;

void parseArgs
(
    bool &textOnly,
    int &seed,
    std::ifstream &scriptFile1,
    std::ifstream &scriptFile2,
    int &startLevel,
    int argc,
    char *argv[]
)
{
    std::string execName = argv[0];
    std::string usageMessage =
        "Usage: "
        + execName
        + " [-text] [-seed xxx] [-scriptfile1 xxx] "
        + "[-scriptfile2 xxx] [-startlevel n]";
    
    for (int i = 1; i < argc; ++i)
    {
        std::string option = argv[i];
        if (option == OPTION_TEXT)
        {
            textOnly = true;
            continue;
        }
        
        // Rest of the options need additional values
        ++i;
        if (i >= argc)
        {
            std::cerr << usageMessage << std::endl;
            break;
        }
        std::string value = argv[i];
        
        // All these need a value
        if (option == OPTION_SEED)
        {
            seed = std::stoi(value);
        }
        else if (option == OPTION_SCRIPTFILE1)
        {
            scriptFile1 = std::ifstream(value);
        }
        else if (option == OPTION_SCRIPTFILE2)
        {
            scriptFile2 = std::ifstream(value);
        }
        else if (option == OPTION_LEVEL)
        {
            try
            {
                startLevel = std::stoi(value);
            }
            catch (std::invalid_argument)
            {
                std::cerr << "'-startLevel' must be followed by an integer" << std::endl;
            }
            
            // TO DO: Have a constant for the number of levels
            if (startLevel < 0 || startLevel > 4)
            {
                std::cerr << "'-startLevel' must be followed by an integer between " << 0 << " and " << 4 << std::endl;
                startLevel = 0;
            }
        }
    }
}
 

int main(int argc, char* argv[])
{
    
    bool textOnly = false;
    int seed = DEFAULT_SEED;
    std::ifstream scriptFile1 = std::ifstream(DEFAULT_SCRIPTFILE1);
    std::ifstream scriptFile2 = std::ifstream(DEFAULT_SCRIPTFILE2);
    int startLevel = DEFAULT_STARTLEVEL;
    
    parseArgs
    (
        textOnly,
        seed,
        scriptFile1,
        scriptFile2,
        startLevel,
        argc,
        argv
    );
    
    Game g;
    g.setNumPlayers(2);
    g.setLevel(startLevel);
    g.setSequence1(scriptFile1);
    g.setSequence1(scriptFile2);
    g.setGraphicsEnabled(!textOnly);
    
    g.play();
}
