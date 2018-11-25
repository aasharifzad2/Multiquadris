
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#ifdef DEBUG
#include "core/board.h"
#include "core/level.h"
#include "core/block/stream/blockStream.h"
#include "core/block/stream/randomBlockStream.h"
#endif


const std::string
    DEFAULT_SCRIPTFILE1 = "sequence1.txt",
    DEFAULT_SCRIPTFILE2 = "sequence2.txt";

const int
    DEFAULT_STARTLEVEL  = 1,
    DEFAULT_SEED        = 19990113;



int main(int argc, char* argv[])
{
    
#ifdef DEBUG
    std::cout << "This is a debug run.." << std::endl;
    srand(DEFAULT_SEED);
    Board b = Board(8, 4);
    RandomBlockStream blockstream = RandomBlockStream({{IShape, 3}, {JShape, 4}, {OShape, 3}});
    
    Level l = Level(1, &blockstream);
    std::cout << b.blockFits(l.getBlock().get()) << std::endl;
    
#endif
    
    std::string execName = argv[0];
    bool textOnly = false;
    int seed = DEFAULT_SEED;
    std::ifstream scriptFile1 = std::ifstream(DEFAULT_SCRIPTFILE1);
    std::ifstream scriptFile2 = std::ifstream(DEFAULT_SCRIPTFILE2);
    int startLevel = DEFAULT_STARTLEVEL;
    
    std::string usageMessage = "Usage: " + execName + " [-text] [-seed xxx] [-scriptfile1 xxx] [-scriptfile2 xxx] [-startlevel n]";
    
    for (int i = 1; i < argc; ++i)
    {
        std::string option = argv[i];
        if (option == "-text")
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
        if (option == "-seed")
        {
            seed = std::stoi(value);
        }
        else if (option == "-scriptfile1")
        {
            scriptFile1 = std::ifstream(value);
        }
        else if (option == "-scriptfile2")
        {
            scriptFile2 = std::ifstream(value);
        }
        else if (option == "-startlevel")
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
