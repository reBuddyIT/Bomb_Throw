#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"

class World
{
public:
	World(sf::Vector2u l_windSize);
	~World();

	int GetBlockSize();

	void RespawnAShip();

	void Update(Ship& l_ship, CBall& l_cball);
	void Render(sf::RenderWindow& l_window);
private:
	sf::Vector2u m_windowSize;
	sf::Vector2f m_pos_aship;
	int m_blockSize;

	sf::Texture m_ashipTexture;
	sf::Sprite m_aship;
	sf::Texture m_bgroundTexture;
	sf::Sprite m_bground;
	sf::RectangleShape m_bounds[4];
};