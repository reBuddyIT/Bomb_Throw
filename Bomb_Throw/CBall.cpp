#include "CBall.h"

CBall::CBall(Textbox* l_log)
{
	m_log = l_log;

	m_IsCBallVisible = 0;
	m_cball.setRadius(10);
	m_cball.setFillColor(sf::Color::Black);
	m_cball.setPosition(800, 400);

	m_speed_cb = sf::Vector2f(0, 0);
	m_miss = 0;

	//m_log->Setup(5, 24, 350, sf::Vector2f(400, 200));

	m_angel = 45;
	m_speed = 100;
	m_mass = 100;
}

CBall::~CBall() {}

void CBall::setSpeed(sf::Vector2f speed)
{
	m_speed_cb = speed;
}

bool CBall::getVisible() { return m_IsCBallVisible; }
void CBall::setVisible(bool visib) { m_IsCBallVisible = visib; }

void CBall::displayStats()
{
	m_log->Add("Throwing angel: "
		+ std::to_string((long long)m_angel));

	m_log->Add("Cannon ball speed: "
		+ std::to_string((long long)m_speed));

	m_log->Add("Cannon ball mass: "
		+ std::to_string((long long)m_mass));
}

//int CBall::GetSpeed() { return m_speed_cb; }
sf::Vector2f CBall::GetPosition() { return m_cball.getPosition(); }
void CBall::SetPosition(sf::Vector2f pos_x)
{
	m_cball.setPosition(pos_x);
}

void CBall::MoveCBall()
{
	m_cball.move(m_speed_cb * m_speed);
}

void CBall::cballUpdate()
{
	MoveCBall();
	displayStats();
}

void CBall::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_cball);
}