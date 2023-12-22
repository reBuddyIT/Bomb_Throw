#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"

class World
{
public:
	World(std::shared_ptr<sf::RenderWindow>, Ship& l_ship);
	~World();

	// установка границ
	void SetupBounds();
	// размер раниц
	int GetBlockSize();

	// возраждение корабля противника
	void RespawnAShip(Ship& l_ship);

	// проверка столкновения кораблей
	bool IsShipColl(Ship& l_ship, float offset = 0);

	// обновление объектов(проверка взаимодействия)
	void Update(Ship& l_ship, CBall& l_cball);
	// отображение объектов
	void Render(sf::RenderWindow& l_window);
private:
	std::shared_ptr<sf::RenderWindow> m_wnd;
	// координаты корабля противника
	sf::Vector2f m_pos_aship;
	// размер границы
	int m_blockSize;

	// тектура корабля противника
	sf::Texture m_ashipTexture;
	// спрайт корабля противника
	sf::Sprite m_aship;
	// тектура заднего фона
	sf::Texture m_bgroundTexture;
	// спрайт заднего фона
	sf::Sprite m_bground;
	// объект границ
	sf::RectangleShape m_bounds[4];
};