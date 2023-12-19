#include "Ship.h"

Ship::Ship()
{
	m_shipTexture.loadFromFile("Ship.jpg");
	m_ship.setTexture(m_shipTexture);
	sf::Vector2u l_size = m_shipTexture.getSize();
	m_ship.setPosition(800, 400);
	m_ship.setOrigin(l_size.x / 2, l_size.y / 2);
	m_ship.rotate(-90);
	m_speed = 20;

	m_IsCBallVisible = 0;
	m_ball.setRadius(10);
	m_ball.setFillColor(sf::Color::Black);
	m_ball.setPosition(m_ship.getPosition());
	m_speed_cb = sf::Vector2f(800, 800);

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
void Ship::IncreaseScore() { m_score += 1; }

void Ship::Reset()
{
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

	//float fElapsed = 1; //m_elapsed.asSeconds();

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//{
	//	m_ship.move({ 0,  -(m_speed.y * fElapsed) });
	//	m_ship.setPosition(
	//		m_ship.getPosition().x,
	//		m_ship.getPosition().y - (m_speed.y * fElapsed));
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	m_ship.setPosition(
	//		m_ship.getPosition().x,
	//		m_ship.getPosition().y + (m_speed.y * fElapsed));
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//{
	//	m_ship.setPosition(
	//		m_ship.getPosition().x - (m_speed.x * fElapsed),
	//		m_ship.getPosition().y);
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	m_ship.setPosition(
	//		m_ship.getPosition().x + (m_speed.x * fElapsed),
	//		m_ship.getPosition().y);
	//}
}
//
//void Rotate()
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//	{
//		m_ship.rotate(10);
//	}
//
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
//	{
//		m_ship.rotate(-10);
//	}
//}
//
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
//
//void Fire()
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		m_IsCBallVisible = true;
//
//		m_ball.setPosition(m_ship.getPosition());
//
//		sf::Vector2f ball_trac =
//			sf::Vector2f(sf::Mouse::getPosition(m_window.GetRenderWindow())) -
//			m_ball.getPosition();
//
//		float vec_len = sqrt(pow(ball_trac.x, 2) + pow(ball_trac.y, 2));
//		ball_trac /= vec_len;
//
//		m_increment_b = ball_trac;
//	}
//}

void Ship::shipUpdate()
{
	moveShip();
}

void Ship::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_ship);
}