#include "World.h"

World::World(sf::Vector2u l_windSize)
{
	m_blockSize = 16;

	m_windowSize = l_windSize;
	RespawnAShip();

	m_bgroundTexture.loadFromFile("ocean.png");
	m_bground.setTexture(m_bgroundTexture);
	sf::Vector2u l_size = m_bgroundTexture.getSize();
	m_bground.setPosition(800, 400);
	m_bground.setOrigin(l_size.x / 2, l_size.y / 2);

	m_ashipTexture.loadFromFile("Ship.jpg");
	m_aship.setTexture(m_ashipTexture);
	m_aship.rotate(90);

	for (int i = 0; i < 4; ++i)
	{
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2))
		{
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else
		{
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}
		if (i < 2)
		{
			m_bounds[i].setPosition(0, 0);
		}
		else
		{
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}

World::~World() {}

int World::GetBlockSize() { return m_blockSize; }

void World::RespawnAShip()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_pos_aship = sf::Vector2f(
		rand() % maxX + 1, rand() % maxY + 1);
	m_aship.setPosition(
		m_pos_aship.x * m_blockSize,
		m_pos_aship.y * m_blockSize);
}

void World::Update(Ship& l_player)
{
	if (l_player.GetPosition() == m_pos_aship)
	{
		l_player.IncreaseScore();
		RespawnAShip();
	}

	int gridSize_x = m_windowSize.x / m_blockSize;
	int gridSize_y = m_windowSize.y / m_blockSize;

	if (l_player.GetPosition().x <= 0 ||
		l_player.GetPosition().y <= 0 ||
		l_player.GetPosition().x >= gridSize_x - 1 ||
		l_player.GetPosition().y >= gridSize_y - 1)
	{
		l_player.Lose();
	}
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