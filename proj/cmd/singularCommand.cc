
#include "singularCommand.h"
#include "../core/game.h"


// MARK: - Static


// MARK: - Constructors & Destructor
SingularCommand::SingularCommand
(
    Game *game,
    std::string key,
    void(Game::*func)()
) :
    func(func)
{
    this->game = game;
    this->key = key;
}


// MARK: - Setters


// MARK: - Getters


// MARK: - Public Functions
void SingularCommand::execute(int multiplier)
{
    (game->*func)();
}

// MARK: - Private Functions
