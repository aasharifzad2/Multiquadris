
#include "repeatableCommand.h"
#include "../core/game.h"


// MARK: - Static


// MARK: - Constructors & Destructor
RepeatableCommand::RepeatableCommand
(
    Game *game,
    std::string key,
    void(Game::*func)(int)
 ) :
    func(func)
{
    this->game = game;
    this->key = key;
}


// MARK: - Setters


// MARK: - Getters


// MARK: - Public Functions
void RepeatableCommand::execute(int multiplier = 1)
{
    (game->*func)(multiplier);
}

// MARK: - Private Functions
