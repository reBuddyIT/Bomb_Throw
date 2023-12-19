#include "Game.h"
#include <iostream>

Game::Game()
	: m_window("Bomb Throw", sf::Vector2u(1600, 800)), m_ship(&m_textbox1), m_cball(&m_textbox2), m_world(sf::Vector2u(1600, 800))
{
	RestartClock();
	srand(time(NULL));

	//m_textbox1.Setup(5, 14, 350, sf::Vector2f(225, 0));
	m_textbox2.Setup(5, 14, 350, sf::Vector2f(800, 800));
	m_elapsed = 0.0f;
}

Game::~Game() { }

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow() { return &m_window; }

void Game::HandleInput()
{
	// Input handling.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& m_ship.GetDirection() != Direction::Down)
	{
		m_ship.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& m_ship.GetDirection() != Direction::Up)
		 {
			m_ship.SetDirection(Direction::Down);
		 }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& m_ship.GetDirection() != Direction::Right)
		 {
			m_ship.SetDirection(Direction::Left);
		 }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& m_ship.GetDirection() != Direction::Left)
		 {
			m_ship.SetDirection(Direction::Right);
		 }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& m_ship.GetDirection() != Direction::Left)
	{
		m_ship.SetDirection(Direction::Right);
	}
}

void Game::Update()
{
	m_window.Update();

	float timestep = 1.0f / m_ship.GetSpeed();
	if (m_elapsed >= timestep)
	{
		m_cball.cballUpdate();
		m_ship.shipUpdate();
		m_world.Update(m_ship, m_cball);
		m_elapsed -= timestep;
		if (m_ship.HasLost())
		{
			m_textbox1.Add("GAME OVER! Score: "
				+ std::to_string((long long)m_ship.GetScore()));

			m_ship.Reset();
		}
	}

	/*MoveShip();
	Fire();
	MoveBall();*/
}

//void Game::Fire()
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		m_IsBallVisible = true;
//
//		m_ball.setPosition(m_ship.getPosition());
//
//		sf::Vector2f ball_trac =
//			sf::Vector2f(sf::Mouse::getPosition(*m_window.GetRenderWindow())) -
//			m_ball.getPosition();
//
//		float vec_len = sqrt(pow(ball_trac.x, 2) + pow(ball_trac.y, 2));
//		ball_trac /= vec_len;
//
//		m_increment_b = ball_trac;
//	}
//}

//void Game::MoveBall()
//{
//	float fElapsed = m_elapsed.asSeconds();
//
//	if (m_IsBallVisible)
//	{
//		m_ball.move(m_increment_b * fElapsed * 1000.f);
//	}
//
//	if (m_ball.getPosition().y < 0)
//	{
//		m_IsBallVisible = 0;
//	}
//}


void Game::Render()
{
	m_window.BeginDraw();

	m_world.Render(*m_window.GetRenderWindow());

	/*if (m_IsBallVisible)
		m_window.Draw(m_ball);*/

	m_cball.Render(*m_window.GetRenderWindow());
	m_ship.Render(*m_window.GetRenderWindow());
	m_textbox1.Render(*m_window.GetRenderWindow());
	m_textbox2.Render(*m_window.GetRenderWindow());

	m_window.EndDraw();
}