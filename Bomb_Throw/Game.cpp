#include "Game.h"

Game::Game()
	: m_window("Bomb Throw", sf::Vector2u(1600, 800)), m_IsBallVisible(0)
{
	RestartClock();
	srand(time(NULL));

	// объекты класса game
	m_shipTexture.loadFromFile("Ship.jpg");
	m_ship.setTexture(m_shipTexture);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setPosition(800, 400);
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_increment_s = sf::Vector2f(300, 300);

	m_ball.setRadius(10);
	m_ball.setFillColor(sf::Color::Black);
	m_ball.setPosition(m_ship.getPosition());
	m_increment_b = sf::Vector2f(0, 800);
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
	Fire();
	MoveBall();
	MoveShip();
}

void Game::Fire()
{
	float fElapsed = m_elapsed.asSeconds();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_IsBallVisible = true;

		m_ball.setPosition(m_ship.getPosition());

		sf::Vector2f ball_trac =
			sf::Vector2f(sf::Mouse::getPosition(m_window.GetRenderWindow())) -
			m_ball.getPosition();

		float vec_len = sqrt(pow(ball_trac.x, 2) + pow(ball_trac.y, 2));
		ball_trac /= vec_len;

		m_increment_b = ball_trac;

		

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

void Game::MoveBall()
{
	float fElapsed = m_elapsed.asSeconds();

	if (m_IsBallVisible)
	{
		m_ball.move(m_increment_b * fElapsed * 1000.f);
	}

	if (m_ball.getPosition().y < 0)
	{
		m_IsBallVisible = 0;
	}
}

void Game::Render()
{
	m_window.BeginDraw();



	if (m_IsBallVisible)
		m_window.Draw(m_ball);

	m_window.Draw(m_ship);

	m_window.EndDraw();
}