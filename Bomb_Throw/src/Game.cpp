#include "Game.h"
#include <iostream>

Game::Game()
	: m_window("Bomb Throw", sf::Vector2u(1600, 800)), m_ship(&m_textbox1), m_cball(&m_textbox2), m_world(sf::Vector2u(1600, 800))
{
	RestartClock();
	srand(time(NULL));

	m_textbox1.Setup(3, 18, 270, sf::Vector2f(665, 8));
	m_textbox2.Setup(5, 16, 270, sf::Vector2f(8, 8));
	m_elapsed = 0.0f;
}

Game::~Game() { }

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow() { return &m_window; }

void Game::HandleInput()
{
	// Input handling.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
		&& !m_cball.getVisible())
	{
		m_ship.SetFire(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& m_ship.GetDirection() != Direction::Down)
	{
		m_ship.SetDirection(Direction::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& m_ship.GetDirection() != Direction::Up)
	{
		m_ship.SetDirection(Direction::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& m_ship.GetDirection() != Direction::Right)
	{
		m_ship.SetDirection(Direction::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& m_ship.GetDirection() != Direction::Left)
	{
		m_ship.SetDirection(Direction::Right);
	}
}

void Game::Update()
{
	m_window.Update();

	float timestep = 1.0f / 60.0f;
	if (m_elapsed >= timestep)
	{
		m_cball.cballUpdate();
		m_ship.shipUpdate(m_cball, m_window.GetRenderWindow());
		m_world.Update(m_ship, m_cball);
		m_elapsed -= timestep;
		if (m_ship.HasLost())
		{
			m_textbox1.Clear();
			m_textbox1.Add("GAME OVER! Score: "
				+ std::to_string((long long)m_ship.GetScore()), 3);

			m_ship.Reset();
		}
	}
}

void Game::Render()
{
	m_window.BeginDraw();

	m_world.Render(*m_window.GetRenderWindow());

	if (m_cball.getVisible())
	{
		m_cball.Render(*m_window.GetRenderWindow());
	}

	m_ship.Render(*m_window.GetRenderWindow());
	m_textbox1.Render(*m_window.GetRenderWindow());
	m_textbox2.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();
}