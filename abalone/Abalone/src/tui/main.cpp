#include "../abalone/Controller.h"
#include "../abalone/Game.h"
#include "View.h"

int main()
{
    abalone::Model::Game game = abalone::Model::Game();
    tui::View::View view = tui::View::View();
    abalone::Controlleur::Controller controller = abalone::Controlleur::Controller(game,view);
    controller.start();
    return 0;
}
