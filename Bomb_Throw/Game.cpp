#include "Game.h"

Game::Game() : m_window("Bomb Throw", sf::Vector2u(1600, 800))
{
	RestartClock();
	srand(time(NULL));

	// объекты класса game
	m_shipTexture.loadFromFile("Ship.jpg");
	m_ship.setTexture(m_shipTexture);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setPosition(800, 400);
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_increment_s = sf::Vector2i(500, 500);
	
	m_ball.setRadius(50);
	m_ball.setFillColor(sf::Color::Black);
	m_increment_b = sf::Vector2i(200, 200);
}

Game::~Game() { }

sf::Time Game::GetElapsed() { return m_elapsed; }
void Game::RestartClock() { m_elapsed = m_clock.restart(); }
Window* Game::GetWindow() { return &m_window; }

void Game::HandleInput()
{
	// Input handling.
}

void Game::Update()
{
	m_window.Update();
	MoveShip();
	Fire();
}

void Game::Fire()
{
	float fElapsed = m_elapsed.asSeconds();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		m_ball.setPosition(m_ship.getPosition().x, m_ship.getPosition().y);

		m_ball.setPosition(
			m_ball.getPosition().x,
			m_ball.getPosition().y - (m_increment_b.y * fElapsed));
	}
}

void Game::MoveShip()
{	
	/*sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_shipTexture.getSize();*/

	float fElapsed = m_elapsed.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_ship.setPosition(
			m_ship.getPosition().x,
			m_ship.getPosition().y - (m_increment_s.y * fElapsed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_ship.setPosition(
			m_ship.getPosition().x,
			m_ship.getPosition().y + (m_increment_s.y * fElapsed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_ship.setPosition(
			m_ship.getPosition().x - (m_increment_s.x * fElapsed),
			m_ship.getPosition().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_ship.setPosition(
			m_ship.getPosition().x + (m_increment_s.x * fElapsed),
			m_ship.getPosition().y);
	}

}

void Game::Render()
{
	m_window.BeginDraw();
	
	m_window.Draw(m_ball);
	m_window.Draw(m_ship);
	m_window.EndDraw(); 
}