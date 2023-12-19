#include "CBall.h"

CBall::CBall(Textbox* l_log)
{
	m_log = l_log;

	m_IsCBallVisible = 0;
	m_cball.setRadius(10);
	m_cball.setFillColor(sf::Color::Black);

	m_speed_cb = sf::Vector2f(800, 800);

	//m_log->Setup(5, 24, 350, sf::Vector2f(400, 200));

	m_angel = 45;
	m_log->Add("Throwing angel: "
		+ std::to_string((long long)m_angel));

	m_mass = 100;
	m_log->Add("Cannon ball mass: "
		+ std::to_string((long long)m_mass));

	m_IsCBallVisible = 0;
}

CBall::~CBall() {}

bool CBall::getVisible() { return m_IsCBallVisible; }
void CBall::setVisible(bool visib) { m_IsCBallVisible = visib; }

//int CBall::GetSpeed() { return m_speed_cb; }
sf::Vector2f CBall::GetPosition() { return m_cball.getPosition(); }
void CBall::SetPosition(sf::Vector2f pos_x)
{
	m_cball.setPosition(pos_x);
}


void CBall::MoveCBall()
{
	if (m_IsCBallVisible)
	{
		m_cball.move(m_speed_cb * 1000.f);
	}
}

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

void CBall::cballUpdate()
{
	void MoveCBall();
}

void CBall::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_cball);
}