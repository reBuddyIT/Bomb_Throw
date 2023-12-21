#include "Game.h"

int main(int argc, void** argv[])
{
	Game game;
	while (!game.GetWindow()->IsDone())
	{
		// основной цикл игры
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
}