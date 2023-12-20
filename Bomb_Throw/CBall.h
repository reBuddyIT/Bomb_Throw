#pragma once
#include <SFML/Graphics.hpp>
#include "Textbox.h"

class CBall
{
public:
	CBall(Textbox* l_log);
	~CBall();

	// Helper methods.
	//int GetSpeed();
	void setSpeed(sf::Vector2f speed);
	bool getVisible();
	void setVisible(bool visib);
	void displayStats();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f pos_x);

	//void Reset(); // Reset to starting position.

	void MoveCBall();

	void cballUpdate(); // Update method.
	void Render(sf::RenderWindow& l_window);
private:
	bool m_IsCBallVisible;

	bool m_miss;
	sf::CircleShape m_cball;
	sf::Vector2f m_speed_cb;
	float m_speed;
	float m_angel;
	float m_mass;
	Textbox* m_log;
};