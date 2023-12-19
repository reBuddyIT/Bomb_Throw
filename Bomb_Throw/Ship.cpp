#include "Ship.h"

Ship::Ship(Textbox* l_log)
{
	m_log = l_log;

	m_shipTexture.loadFromFile("Ship.png");
	m_ship.setTexture(m_shipTexture);
	m_ship.setScale(0.3, 0.3);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setPosition(800, 400);
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.setRotation(270);
	m_speed = 10;

	m_dir = Direction::None;
	m_lost = false;
	m_score = 0;
}

Ship::~Ship() {}

void Ship::SetDirection(Direction l_dir) { m_dir = l_dir; }
Direction Ship::GetDirection() { return m_dir; }
int Ship::GetSpeed() { return m_speed; }
int Ship::GetScore() { return m_score; }
sf::Vector2f Ship::GetPosition() { return m_ship.getPosition(); }
void Ship::SetPosition(sf::Vector2f pos_x)
{
	m_ship.setPosition(pos_x);
}
void Ship::IncreaseScore()
{
	m_score += 1;
	m_log->Add("You destroyed a ship! Score: "
		+ std::to_string((long long)m_score));
}

void Ship::Reset()
{
	m_ship.setPosition(800, 400);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.setRotation(270);
	

	SetDirection(Direction::None); // Start off still.
	m_score = 0;
	m_lost = false;
}

bool Ship::HasLost() { return m_lost; }
void Ship::Lose() { m_lost = true; }
void Ship::ToggleLost() { m_lost = !m_lost; }

void Ship::moveShip()
{
	float fElapsed = 1; //m_elapsed.asSeconds();

	if (m_dir == Direction::Left)
	{
		m_ship.setRotation(180);
		m_ship.move({ -(m_speed * fElapsed),  0 });
	}
	else if (m_dir == Direction::Right)
	{
		m_ship.setRotation(0);
		m_ship.move({ (m_speed * fElapsed),  0 });
	}
	else if (m_dir == Direction::Up)
	{
		m_ship.setRotation(-90);
		m_ship.move({ 0,  -(m_speed * fElapsed) });
	}
	else if (m_dir == Direction::Down)
	{
		m_ship.setRotation(90);
		m_ship.move({ 0,  (m_speed * fElapsed) });
	}
}

//void MoveCBall()
//{
//	float fElapsed = 1; //m_elapsed.asSeconds();
//	
//		if (m_IsCBallVisible)
//		{
//			m_ball.move(m_speed_cb * fElapsed * 1000.f);
//		}
//	
//		if (m_ball.getPosition().y < 0)
//		{
//			m_IsCBallVisible = 0;
//		}
//}

//void Fire(CBall& l_cball, Ship& l_ship)
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		l_cball.setVisible(1);
//
//		l_cball.SetPosition(l_ship.GetPosition());
//
//		sf::Vector2f ball_trac =
//			sf::Vector2f(sf::Mouse::getPosition(m_window.GetRenderWindow())) -
//			l_cball.GetPosition();
//
//		float vec_len = sqrt(pow(ball_trac.x, 2) + pow(ball_trac.y, 2));
//		ball_trac /= vec_len;
//
//		if (l_cball.getVisible() == 1)
//		{
//			l_cball.MoveCBall();
//		}
//	}
//}

void Ship::shipUpdate()
{
	moveShip();
	//Fire();
}

void Ship::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_ship);
}