#include "Ship.h"
#include <iostream>

Ship::Ship(Textbox* l_log)
{
	m_log = l_log;

	// �������� �������
	m_shipTexture.loadFromFile("assets/pics/Ship.png");
	m_ship.setTexture(m_shipTexture);
	// ��������� ��������
	m_ship.setScale(0.3, 0.3);
	sf::Vector2u l_size = m_shipTexture.getSize();
	// ��������� ���������
	m_ship.setPosition(800, 400);
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.setRotation(270);

	// ��������
	m_speed = 3.f;
	// �����������
	m_dir = Direction::None;
	// ��������
	m_ammo = 20;
	// ����
	m_score = 0;
	// ���������� � ��������
	m_toggleFire = 0;
	// ��������� ���������
	m_lost = false;
}

Ship::~Ship() {}

// ��������� �����������
void Ship::SetDirection(Direction l_dir) { m_dir = l_dir; }
// ��������� �����������
Direction Ship::GetDirection() { return m_dir; }

// ��������� ���������� � ��������
void Ship::SetFire(bool fire) { m_toggleFire = fire; }
// ��������� ����������
bool Ship::GetFire() { return m_toggleFire; }
// ������� ��������
int Ship::GetSpeed() { return m_speed; }
// ������� ����
int Ship::GetScore() { return m_score; }

// ��������� ���������
sf::Vector2f Ship::GetPosition() { return m_ship.getPosition(); }
// ��������� ���������
void Ship::SetPosition(sf::Vector2f pos) { m_ship.setPosition(pos); }

// ���������� �����
void Ship::IncreaseScore()
{
	m_score += 1;
	m_log->Add("You destroyed a ship! Score: "
		+ std::to_string((long long)m_score), 3);
}
// ���������� �����
void Ship::DecreaseScore()
{
	m_score -= 1;
	m_log->Add("You missed! Score: "
		+ std::to_string((long long)m_score), 3);
}
// ���������� � ���������
void Ship::updateAmmo()
{
	m_ammo -= 1;
	m_log->Add("You have: "
		+ std::to_string((long long)m_ammo)
	+ " cannon balls left!", 3);

	if (m_ammo == 0)
	{
		// ��������, ���� ����������� �������
		ToggleLost();
	}
}

// ����������� ��������
void Ship::Reset()
{
	// ��������� ��������� ���������
	m_ship.setPosition(800, 400);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.setRotation(270);

	// ��������� ��������� ��������
	m_dir = Direction::None;
	m_ammo = 20;
	m_toggleFire = 0;
	m_score = 0;
	m_lost = false;
}

// ��������� ���������
bool Ship::HasLost() { return m_lost; }
// ���������
void Ship::Lose() { m_lost = true; }
// ���������� �������� ���������
void Ship::ToggleLost() { m_lost = !m_lost; }

// �������� ������
sf::Sprite& Ship::GetSprite()
{
	return m_ship;
}

// �������� �������
void Ship::moveShip()
{
	// ���� ����������� ������
	if (m_dir == Direction::Left)
	{
		// ��������� �� 180 ��������
		m_ship.setRotation(180);
		// �������� � �����������
		m_ship.move(sf::Vector2f{ -(m_speed),  0.f });
	}
	// ���� ����������� ������
	else if (m_dir == Direction::Right)
	{
		// ��������� �� 0 ��������
		m_ship.setRotation(0);
		// �������� � �����������
		m_ship.move(sf::Vector2f{ (m_speed),  0.f });
	}
	// ���� ����������� �����
	else if (m_dir == Direction::Up)
	{
		// ��������� �� -90 ��������
		m_ship.setRotation(-90);
		// �������� � �����������
		m_ship.move(sf::Vector2f{ 0.f,  -(m_speed) });
	}
	// ���� ����������� ����
	else if (m_dir == Direction::Down)
	{
		// ��������� �� 90 ��������
		m_ship.setRotation(90);
		// �������� � �����������
		m_ship.move(sf::Vector2f{ 0.f,  (m_speed) });
	}
}

// ����������
void Ship::Fire(CBall& l_cball, std::shared_ptr<sf::RenderWindow> m_window)
{
	// ���� ������� ����� � �������� 
	if (GetFire())
	{
		// ��������� ��������� ����
		l_cball.setVisible(1);
		// ��������� ������� � �������
		l_cball.SetPosition(GetPosition());

		// ���������� ������� ���������� �� ����� ��������� ����
		// �� ��������� ����� �� ������
		sf::Vector2f ball_vec =
			sf::Vector2f(sf::Mouse::getPosition(*m_window)) -
			l_cball.GetPosition();

		// ����������� ��������� ��������
		l_cball.SetFpos(GetPosition());

		// ���������� ����� �������
		float vec_len = sqrt(pow(ball_vec.x, 2) + pow(ball_vec.y, 2));
		// ���������� ���������� ������� ����������
		ball_vec /= vec_len;
		// ��������� ���������� ����� ����
		l_cball.setSpeed(ball_vec);

		// ���� ���� ������������
		if (l_cball.getVisible() == 1)
		{
			// �������� ���� �� ����������
			l_cball.MoveCBall();
		}
	}
}

// ���������� �������
void Ship::shipUpdate(CBall& l_cball, std::shared_ptr<sf::RenderWindow> m_window)
{
	// �������
	Fire(l_cball, m_window);
	// ��������
	moveShip();	
}

// ��������� �������
void Ship::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_ship);
}