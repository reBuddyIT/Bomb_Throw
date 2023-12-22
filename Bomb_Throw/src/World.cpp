#include "World.h"
#include <iostream>

World::World(std::shared_ptr<sf::RenderWindow> wnd, Ship& l_ship)
:m_wnd(wnd)
{
	// размер раниц
	m_blockSize = 8;
	// установка границ
	SetupBounds();

	// загрузка текстур заднего фона
	m_bgroundTexture.loadFromFile("assets/pics/ocean.png");
	m_bground.setTexture(m_bgroundTexture);
	sf::Vector2u l_size = m_bgroundTexture.getSize();
	m_bground.setPosition(800, 400);
	m_bground.setOrigin(l_size.x / 2, l_size.y / 2);

	// загрузка текстур корабля
	m_ashipTexture.loadFromFile("assets/pics/AShip.png");
	m_aship.setTexture(m_ashipTexture);
	// установка позиции корабля
	m_aship.setOrigin({ m_aship.getGlobalBounds().width / 2, m_aship.getGlobalBounds().height / 2 });
	m_aship.setScale(0.25, 0.25);
	m_aship.rotate(180);

	// возраждение корабля противника
	RespawnAShip(l_ship);
}

World::~World() {}

// установка границ
void World::SetupBounds()
{
	for (int i = 0; i < 4; ++i)
	{
		// установка цвета
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
		{
			// получение размеров окна
			m_bounds[i].setSize(sf::Vector2f(m_wnd->getSize().x, m_blockSize));
		}
		else
		{
			// получение размеров окна
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_wnd->getSize().y));
		}
		if (i < 2)
		{
			// установка координат
			m_bounds[i].setPosition(0, 0);
		}
		else
		{
			// установка координат
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_wnd->getSize()));
		}
	}
}
// размер раниц
int World::GetBlockSize() { return m_blockSize; }

// возраждение корабля противника
void World::RespawnAShip(Ship& l_ship)
{
	do
	{
		// вычисление потенциальных допустимых новых координат
		float new_y = rand() % int(m_wnd->getSize().y - m_aship.getGlobalBounds().height - m_blockSize)
			+ m_blockSize / 2 + m_aship.getGlobalBounds().height / 2;
		float new_x = rand() % int(m_wnd->getSize().x - m_aship.getGlobalBounds().width - m_blockSize)
			+ m_blockSize / 2 + m_aship.getGlobalBounds().width / 2;

		// установка новых координат
		m_aship.setPosition(new_x, new_y);

		// условие столкновения кораблей + смещение
	} while (IsShipColl(l_ship, 1000));
}
// обновление объектов(проверка взаимодействия)
void World::Update(Ship& l_ship, CBall& l_cball)
{
	// устнановление границ экрана
	int gridSize_x = m_wnd->getSize().x;
	int gridSize_y = m_wnd->getSize().y;

	/*if ((sqrt(pow(l_ship.GetPosition().x - m_aship.getPosition().x, 2) +
		pow(l_ship.GetPosition().y - m_aship.getPosition().y, 2)))
		<= 0.4 * (512 * 0.25 + 512 * 0.3))*/
		// при столкновении кораблей
	if(IsShipColl(l_ship))
	{
		/*l_ship.IncreaseScore();
		RespawnAShip(l_ship);*/
		// пройгрыш
		l_ship.Lose();
	}
	// при попадании
	else if (((sqrt(pow(l_cball.GetPosition().x - m_aship.getPosition().x, 2) +
		pow(l_cball.GetPosition().y - m_aship.getPosition().y, 2)))
		<= 0.6 * (512 * 0.25 + 10)) && l_cball.getVisible())
	{
		// обновление параметров
		l_cball.Reset();
		// увелеличение счёта
		l_ship.IncreaseScore();
		// обновление боезапаса
		l_ship.updateAmmo();
		// возраждение корабля противника
		RespawnAShip(l_ship);
	}
	// при промахе
	else if ((l_cball.getDist() < sqrt(pow(l_cball.GetPosition().x - l_cball.GetFpos().x, 2)
		+ pow(l_cball.GetPosition().y - l_cball.GetFpos().y, 2))) && l_cball.getVisible())
	{
		// обновление параметров
		l_cball.Reset();
		// уменьшение счёта
		l_ship.DecreaseScore();
		// обновление боезапаса
		l_ship.updateAmmo();
	}
	// выхлет за границу
	else if ((l_cball.GetPosition().x <= 0 ||
		l_cball.GetPosition().y <= 0 ||
		l_cball.GetPosition().x >= gridSize_x - 1 ||
		l_cball.GetPosition().y >= gridSize_y - 1))
	{
		// обновление параметров
		l_cball.Reset();
		// уменьшение счёта
		l_ship.DecreaseScore();
		// обновление боезапаса
		l_ship.updateAmmo();
	}	
	// выход за границу
	if (l_ship.GetPosition().x <= 0 ||
		l_ship.GetPosition().y <= 0 ||
		l_ship.GetPosition().x >= gridSize_x - 1 ||
		l_ship.GetPosition().y >= gridSize_y - 1)
	{
		// пройгрыш
		l_ship.Lose();
	}
}

// проверка столкновения кораблей
bool World::IsShipColl(Ship& l_ship, float offset)
{
	return ((sqrt(pow(l_ship.GetPosition().x - m_aship.getPosition().x, 2) +
		pow(l_ship.GetPosition().y - m_aship.getPosition().y, 2)))
		<= 0.4 * ((512 + offset) * 0.25 + (512 + offset) * 0.3));
}

// отображение объектов
void World::Render(sf::RenderWindow& l_window)
{
	// задний фон
	l_window.draw(m_bground);

	// границы
	for (int i = 0; i < 4; ++i)
	{
		l_window.draw(m_bounds[i]);
	}

	// корабля противника
	l_window.draw(m_aship);

}