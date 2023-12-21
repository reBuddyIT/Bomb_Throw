#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"

class World
{
public:
	World(std::shared_ptr<sf::RenderWindow>, Ship& l_ship);
	~World();

	void SetupBounds();
	int GetBlockSize();

	void RespawnAShip(Ship& l_ship);

	bool IsShipColl(Ship& l_ship, float offset = 0);

	void Update(Ship& l_ship, CBall& l_cball);
	void Render(sf::RenderWindow& l_window);
private:
	std::shared_ptr<sf::RenderWindow> m_wnd;
	sf::Vector2f m_pos_aship;
	int m_blockSize;

	sf::Texture m_ashipTexture;
	sf::Sprite m_aship;
	sf::Texture m_bgroundTexture;
	sf::Sprite m_bground;
	sf::RectangleShape m_bounds[4];
};