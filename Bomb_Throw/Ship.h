#pragma once
#include <SFML/Graphics.hpp>

enum class Direction {None, Up, Down, Left, Right };

class Ship
{
public:
	Ship();
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
	//void Rotate();
	//void MoveCBall();
	//void Fire();
	void shipUpdate(); // Update method.
	void Render(sf::RenderWindow& l_window);
private:

	int m_score; // Score.
	bool m_lost; // Losing state.
	Direction m_dir; // Current direction.

	bool m_IsCBallVisible;
	sf::CircleShape m_ball;
	sf::Vector2f m_speed_cb;

	int m_speed; // Speed of the ship.
	sf::Texture m_shipTexture; // Shape used in rendering.
	sf::Sprite m_ship; 
};