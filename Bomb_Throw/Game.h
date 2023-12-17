#pragma once
#include "Window.h"
#include <iostream>

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
	void MoveShip();
	void MoveBall();
	void Fire();

	Window m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;

	bool m_IsBallVisible;
	sf::CircleShape m_ball;
	sf::Vector2f m_increment_b;
	sf::Texture m_shipTexture;
	sf::Sprite m_ship;
	sf::Vector2f m_increment_s;
};