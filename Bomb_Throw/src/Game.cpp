#include "Game.h"
#include <iostream>

Game::Game()
	: m_window("Bomb Throw", sf::Vector2u(1600, 800)), m_ship(&m_textbox1),
	m_cball(&m_textbox2), m_world(m_window.GetRenderWindow(), m_ship)
{
	// обновление часов
	RestartClock();
	srand(time(NULL));

	// установка параметров текстовых окон
	m_textbox1.Setup(3, 18, 270, sf::Vector2f(665, 8));
	m_textbox2.Setup(4, 16, 270, sf::Vector2f(8, 8));

	// пройденное время
	m_elapsed = 0.0f;
}

Game::~Game() { }

// получить пройденное время
sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
// обновить часы
void Game::RestartClock() { m_elapsed += m_clock.restart().asSeconds(); }
// получить объект окна
Window* Game::GetWindow() { return &m_window; }

// обработка команд
void Game::HandleInput()
{
	// нажатие левой кнопки мыши
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))	
	{
		// если не ядро уже было выстрелено
		if (!m_cball.getVisible())
		{
			// разрешение кораблю на выстрел
			m_ship.SetFire(true);
		}
	}
	else
	{
		// выстрел запрещён
		m_ship.SetFire(0);
	}
	// нажатие на W
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& m_ship.GetDirection() != Direction::Down)
	{
		// установка направления вверх
		m_ship.SetDirection(Direction::Up);
	}
	// нажатие на S
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& m_ship.GetDirection() != Direction::Up)
	{
		// установка направления вниз
		m_ship.SetDirection(Direction::Down);
	}
	// нажатие на A
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& m_ship.GetDirection() != Direction::Right)
	{
		// установка направления налево
		m_ship.SetDirection(Direction::Left);
	}
	// нажатие на D
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& m_ship.GetDirection() != Direction::Left)
	{
		// установка направления направо
		m_ship.SetDirection(Direction::Right);
	}
	else
	{
		// сброс направления
		m_ship.SetDirection(Direction::None);
	}
}

// обновление всех объектов
void Game::Update()
{
	// обновление окна
	m_window.Update();

	// установка частоты обновлений в секунду(60)
	float timestep = 1.0f / 60.0f;
	// если обновлений больше установленного
	if (m_elapsed >= timestep)
	{
		// обновление ядра
		m_cball.cballUpdate();
		// обновление корабля
		m_ship.shipUpdate(m_cball, m_window.GetRenderWindow());
		// обновление игрового мира
		m_world.Update(m_ship, m_cball);
		m_elapsed -= timestep;

		// обработка пройгрыша
		if (m_ship.HasLost())
		{
			// очистка 1-го текстового окна
			m_textbox1.Clear();
			// вывод текста о пройгрыше и финального количесва очков
			m_textbox1.Add("GAME OVER! Score: "
				+ std::to_string((long long)m_ship.GetScore()), 3);
			// возвращение корабля в начальное положение
			// обновление очков и снарядов
			m_ship.Reset();
		}
	}
	// если был изменён размер окна
	if (m_window.IswndResized())
	{
		// вычисление новых координат
		sf::Vector2u new_pos = m_window.GetRenderWindow()->getSize();
		new_pos.x /= 2;
		new_pos.x -= m_textbox1.GetSize().x / 2;
		new_pos.y = m_world.GetBlockSize();
		// установка новых границ
		m_world.SetupBounds();
		// узменение позиции тектового окна
		m_textbox1.SetPos(sf::Vector2f(new_pos));
	}
}

// отображение объектов
void Game::Render()
{
	// очистка окна
	m_window.BeginDraw();

	// прорисовка игрового мира
	m_world.Render(*m_window.GetRenderWindow());

	// прорисовка пушечного ядра, если был выстрел
	if (m_cball.getVisible())
	{
		m_cball.Render(*m_window.GetRenderWindow());
	}

	// прорисовка корабля
	m_ship.Render(*m_window.GetRenderWindow());
	// прорисовка текстовых окон
	m_textbox1.Render(*m_window.GetRenderWindow());
	m_textbox2.Render(*m_window.GetRenderWindow());

	// прорисовка окна
	m_window.EndDraw();
}