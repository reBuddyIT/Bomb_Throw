#pragma once
#include "Window.h"
#include "Ship.h"
#include "World.h"
#include "CBall.h"
#include "Textbox.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();
private:
	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;

	World m_world;
	Ship m_ship;
	CBall m_cball;
	Textbox m_textbox1;
	Textbox m_textbox2;
};