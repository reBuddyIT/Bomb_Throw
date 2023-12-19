#pragma once
#include <SFML/Graphics.hpp>
#include "CBall.h"
#include "Window.h"
#include "Textbox.h"

enum class Direction {None, Up, Down, Left, Right };

class Ship
{
public:
	Ship(Textbox* l_log);
	~Ship();

	// Helper methods.
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	int GetScore();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f pos_x);
	void IncreaseScore();
	bool HasLost();

	void Lose(); // Handle losing here.
	void ToggleLost();

	void Reset(); // Reset to starting position.

	void moveShip(); // Movement method.
	//void MoveCBall();
	void Fire(CBall& l_cball,std::shared_ptr<sf::RenderWindow>);
	void shipUpdate(); // Update method.
	void Render(sf::RenderWindow& l_window);
private:

	int m_score; // Score.
	bool m_lost; // Losing state.
	Direction m_dir; // Current direction.

	
	float m_speed; // Speed of the ship.
	sf::Image m_shipImage;
	sf::Texture m_shipTexture; // Shape used in rendering.
	sf::Sprite m_ship;
	Textbox* m_log;
};