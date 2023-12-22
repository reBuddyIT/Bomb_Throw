#include "Ship.h"
#include <iostream>

Ship::Ship(Textbox* l_log)
{
	m_log = l_log;

	// загрузка спрайта
	m_shipTexture.loadFromFile("assets/pics/Ship.png");
	m_ship.setTexture(m_shipTexture);
	// установка размеров
	m_ship.setScale(0.3, 0.3);
	sf::Vector2u l_size = m_shipTexture.getSize();
	// установка координат
	m_ship.setPosition(800, 400);
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.setRotation(270);

	// скорость
	m_speed = 3.f;
	// направление
	m_dir = Direction::None;
	// боезапас
	m_ammo = 20;
	// очки
	m_score = 0;
	// готовность к стрельбе
	m_toggleFire = 0;
	// состояние пройгрыша
	m_lost = false;
}

Ship::~Ship() {}

// установка направления
void Ship::SetDirection(Direction l_dir) { m_dir = l_dir; }
// получение направления
Direction Ship::GetDirection() { return m_dir; }

// установка готовности к стрельбе
void Ship::SetFire(bool fire) { m_toggleFire = fire; }
// состояние готовности
bool Ship::GetFire() { return m_toggleFire; }
// текущая скорость
int Ship::GetSpeed() { return m_speed; }
// текущие очки
int Ship::GetScore() { return m_score; }

// получение координат
sf::Vector2f Ship::GetPosition() { return m_ship.getPosition(); }
// установка координат
void Ship::SetPosition(sf::Vector2f pos) { m_ship.setPosition(pos); }

// увеличение очков
void Ship::IncreaseScore()
{
	m_score += 1;
	m_log->Add("You destroyed a ship! Score: "
		+ std::to_string((long long)m_score), 3);
}
// уменьшение очков
void Ship::DecreaseScore()
{
	m_score -= 1;
	m_log->Add("You missed! Score: "
		+ std::to_string((long long)m_score), 3);
}
// информация о боезапасе
void Ship::updateAmmo()
{
	m_ammo -= 1;
	m_log->Add("You have: "
		+ std::to_string((long long)m_ammo)
	+ " cannon balls left!", 3);

	if (m_ammo == 0)
	{
		// пройгрыш, если закончились снаряды
		ToggleLost();
	}
}

// сбрасывание значений
void Ship::Reset()
{
	// установка начальных положений
	m_ship.setPosition(800, 400);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.setRotation(270);

	// установка начальных значений
	m_dir = Direction::None;
	m_ammo = 20;
	m_toggleFire = 0;
	m_score = 0;
	m_lost = false;
}

// состоянее пройгрыша
bool Ship::HasLost() { return m_lost; }
// проиграть
void Ship::Lose() { m_lost = true; }
// установить значение пройгрыша
void Ship::ToggleLost() { m_lost = !m_lost; }

// получить спрайт
sf::Sprite& Ship::GetSprite()
{
	return m_ship;
}

// сдвинуть корабль
void Ship::moveShip()
{
	// если направление налево
	if (m_dir == Direction::Left)
	{
		// повернуть на 180 градусов
		m_ship.setRotation(180);
		// сдвинуть в направлении
		m_ship.move(sf::Vector2f{ -(m_speed),  0.f });
	}
	// если направление вправо
	else if (m_dir == Direction::Right)
	{
		// повернуть на 0 градусов
		m_ship.setRotation(0);
		// сдвинуть в направлении
		m_ship.move(sf::Vector2f{ (m_speed),  0.f });
	}
	// если направление вверх
	else if (m_dir == Direction::Up)
	{
		// повернуть на -90 градусов
		m_ship.setRotation(-90);
		// сдвинуть в направлении
		m_ship.move(sf::Vector2f{ 0.f,  -(m_speed) });
	}
	// если направление вниз
	else if (m_dir == Direction::Down)
	{
		// повернуть на 90 градусов
		m_ship.setRotation(90);
		// сдвинуть в направлении
		m_ship.move(sf::Vector2f{ 0.f,  (m_speed) });
	}
}

// выстрелить
void Ship::Fire(CBall& l_cball, std::shared_ptr<sf::RenderWindow> m_window)
{
	// если корабль готов к стрельбе 
	if (GetFire())
	{
		// установка видимости ядру
		l_cball.setVisible(1);
		// установка позиции к кораблю
		l_cball.SetPosition(GetPosition());

		// вычисление вектора траектории от точки координат ядра
		// до выбранной точки на экране
		sf::Vector2f ball_vec =
			sf::Vector2f(sf::Mouse::getPosition(*m_window)) -
			l_cball.GetPosition();

		// запоминание координат выстрела
		l_cball.SetFpos(GetPosition());

		// вычисление длины вектора
		float vec_len = sqrt(pow(ball_vec.x, 2) + pow(ball_vec.y, 2));
		// нахождение единичного вектора траектории
		ball_vec /= vec_len;
		// установка траектории полёта ядра
		l_cball.setSpeed(ball_vec);

		// если ядро отображается
		if (l_cball.getVisible() == 1)
		{
			// смещение ядрп по траектории
			l_cball.MoveCBall();
		}
	}
}

// обновление корабля
void Ship::shipUpdate(CBall& l_cball, std::shared_ptr<sf::RenderWindow> m_window)
{
	// выстрел
	Fire(l_cball, m_window);
	// смещение
	moveShip();	
}

// отрисовка корабля
void Ship::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_ship);
}