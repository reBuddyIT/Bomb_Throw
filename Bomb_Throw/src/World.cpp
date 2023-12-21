#include "World.h"
#include <iostream>

World::World(std::shared_ptr<sf::RenderWindow> wnd, Ship& l_ship)
:m_wnd(wnd)
{
	m_blockSize = 8;
	SetupBounds();

	m_bgroundTexture.loadFromFile("assets/pics/ocean.png");
	m_bground.setTexture(m_bgroundTexture);
	sf::Vector2u l_size = m_bgroundTexture.getSize();
	m_bground.setPosition(800, 400);
	m_bground.setOrigin(l_size.x / 2, l_size.y / 2);

	m_ashipTexture.loadFromFile("assets/pics/AShip.png");
	m_aship.setTexture(m_ashipTexture);
	m_aship.setOrigin({ m_aship.getGlobalBounds().width / 2, m_aship.getGlobalBounds().height / 2 });
	m_aship.setScale(0.25, 0.25);
	m_aship.rotate(180);

	RespawnAShip(l_ship);
}

World::~World() {}

void World::SetupBounds()
{
	for (int i = 0; i < 4; ++i)
	{
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
		{
			m_bounds[i].setSize(sf::Vector2f(m_wnd->getSize().x, m_blockSize));
		}
		else
		{
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_wnd->getSize().y));
		}
		if (i < 2)
		{
			m_bounds[i].setPosition(0, 0);
		}
		else
		{
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_wnd->getSize()));
		}
	}
}

int World::GetBlockSize() { return m_blockSize; }

void World::RespawnAShip(Ship& l_ship)
{
	do
	{
		float new_y = rand() % int(m_wnd->getSize().y - m_aship.getGlobalBounds().height - m_blockSize)
			+ m_blockSize / 2 + m_aship.getGlobalBounds().height / 2;
		float new_x = rand() % int(m_wnd->getSize().x - m_aship.getGlobalBounds().width - m_blockSize)
			+ m_blockSize / 2 + m_aship.getGlobalBounds().width / 2;

		m_aship.setPosition(new_x, new_y);

		std::cout << "Collided\n";
	} while (IsShipColl(l_ship, 1000));
	std::cout << std::endl;
}

void World::Update(Ship& l_ship, CBall& l_cball)
{
	int gridSize_x = m_wnd->getSize().x;
	int gridSize_y = m_wnd->getSize().y;

	/*if ((sqrt(pow(l_ship.GetPosition().x - m_aship.getPosition().x, 2) +
		pow(l_ship.GetPosition().y - m_aship.getPosition().y, 2)))
		<= 0.4 * (512 * 0.25 + 512 * 0.3))*/
	if(IsShipColl(l_ship))
	{
		/*l_ship.IncreaseScore();
		RespawnAShip(l_ship);*/

		l_ship.Lose();
	}
	else if (((sqrt(pow(l_cball.GetPosition().x - m_aship.getPosition().x, 2) +
		pow(l_cball.GetPosition().y - m_aship.getPosition().y, 2)))
		<= 0.8 * (512 * 0.25 + 10)) && l_cball.getVisible())
	{
		l_cball.Reset();
		l_ship.IncreaseScore();
		l_ship.updateAmmo();
		RespawnAShip(l_ship);
	}
	else if ((l_cball.getDis() < sqrt(pow(l_cball.GetPosition().x - l_cball.GetFpos().x, 2)
		+ pow(l_cball.GetPosition().y - l_cball.GetFpos().y, 2))) && l_cball.getVisible())
	{
		l_cball.Reset();
		l_ship.DecreaseScore();
		l_ship.updateAmmo();
	}
	else if ((l_cball.GetPosition().x <= 0 ||
		l_cball.GetPosition().y <= 0 ||
		l_cball.GetPosition().x >= gridSize_x - 1 ||
		l_cball.GetPosition().y >= gridSize_y - 1))
	{
		l_cball.Reset();
		l_ship.DecreaseScore();
		l_ship.updateAmmo();
	}	

	if (l_ship.GetPosition().x <= 0 ||
		l_ship.GetPosition().y <= 0 ||
		l_ship.GetPosition().x >= gridSize_x - 1 ||
		l_ship.GetPosition().y >= gridSize_y - 1)
	{
		l_ship.Lose();
	}
}

bool World::IsShipColl(Ship& l_ship, float offset)
{
	return ((sqrt(pow(l_ship.GetPosition().x - m_aship.getPosition().x, 2) +
		pow(l_ship.GetPosition().y - m_aship.getPosition().y, 2)))
		<= 0.4 * ((512 + offset) * 0.25 + (512 + offset) * 0.3));
}

void World::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_bground);

	for (int i = 0; i < 4; ++i)
	{
		l_window.draw(m_bounds[i]);
	}

	l_window.draw(m_aship);

}