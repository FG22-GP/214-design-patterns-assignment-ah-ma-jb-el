#include "PacmanCore.h"
#include "IGhost.h"

IGhost::IGhost(const std::shared_ptr<Actor>& pacman)
{
    PacMan = pacman;
}
