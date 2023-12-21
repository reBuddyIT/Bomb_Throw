#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
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
	float getDis();
	void displayStats();
	sf::Vector2f GetPosition();
	sf::Vector2f GetFpos();
	void SetFpos(sf::Vector2f f_pos);
	void SetPosition(sf::Vector2f pos);

	//void Reset(); // Reset to starting position.

	void MoveCBall();
	void Reset(); // Reset to starting position.
	void cballUpdate(); // Update method.
	void Render(sf::RenderWindow& l_window);
private:
	bool m_IsCBallVisible;

	//sf::CircleShape m_cball;
	sf::Texture m_cballTexture; // Shape used in rendering.
	sf::Sprite m_cball;
	sf::Vector2f m_speed_cb;
	sf::Vector2f m_fpos;
	float m_speed;
	float m_angel;
	float m_mass;
	float m_ffall;
	float m_THdis;
	Textbox* m_log;
};