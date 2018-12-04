
#include "command.h"
#include "../core/game.h"

// MARK: - Static


// MARK: - Constructors & Destructor
Command::~Command() {}


// MARK: - Setters


// MARK: - Getters
std::string Command::getKey() { return key; }

// MARK: - Public Functions
bool Command::keyMatches(std::string &keyToCheck)
{
    if (keyToCheck.length() > key.length()) return false;
    return key.compare(0, keyToCheck.length(), keyToCheck) == 0;
}

// MARK: - Private Functions
