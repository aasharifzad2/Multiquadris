
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string
    DEFAULT_SEED        = "Sir Mix-a-Lot",
    DEFAULT_SCRIPTFILE1 = "sequence1.txt",
    DEFAULT_SCRIPTFILE2 = "sequence2.txt";

const int
    DEFAULT_STARTLEVEL  = 1;


int main(int argc, char* argv[])
{
    string execName = argv[0];
    bool textOnly = false;
    string seed = DEFAULT_SEED;
    ifstream scriptFile1 = ifstream(DEFAULT_SCRIPTFILE1);
    ifstream scriptFile2 = ifstream(DEFAULT_SCRIPTFILE2);
    int startLevel = DEFAULT_STARTLEVEL;
    
    string usageMessage = "Usage: " + execName + " [-text] [-seed xxx] [-scriptfile1 xxx] [-scriptfile2 xxx] [-startlevel n]";
    
    for (int i = 1; i < argc; ++i)
    {
        string option = argv[i];
        if (option == "-text")
        {
            textOnly = true;
            continue;
        }
        
        // Rest of the options need additional values
        ++i;
        if (i >= argc)
        {
            cerr << usageMessage << endl;
            break;
        }
        string value = argv[i];
        
        // All these need a value
        if (option == "-seed")
        {
            seed = value;
        }
        else if (option == "-scriptfile1")
        {
            scriptFile1 = ifstream(value);
        }
        else if (option == "-scriptfile2")
        {
            scriptFile2 = ifstream(value);
        }
        else if (option == "-startlevel")
        {
            try
            {
                startLevel = stoi(value);
            }
            catch (invalid_argument)
            {
                cerr << "'-startLevel' must be followed by an integer" << endl;
            }
            
            // TO DO: Have a constant for the number of levels
            if (startLevel < 0 || startLevel > 4)
            {
                cerr << "'-startLevel' must be followed by an integer between " << 0 << " and " << 4 << endl;
                startLevel = 0;
            }
        }
    }
}
