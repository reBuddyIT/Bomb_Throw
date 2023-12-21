#include "CBall.h"

CBall::CBall(Textbox* l_log)
{
	m_log = l_log;

	m_IsCBallVisible = 0;
	m_cball.setRadius(10);
	m_cball.setFillColor(sf::Color::Black);
	m_cball.setPosition(800, 400);

	m_speed_cb = sf::Vector2f(100, 100);

	m_angel = 60;
	m_speed = 100;
	m_mass = 100;
	m_ffall = 10;

	m_THdis = ((2 * pow(m_speed, 2) * sin(m_angel) * cos(m_angel)) / m_ffall);
}

CBall::~CBall() {}

void CBall::setSpeed(sf::Vector2f speed)
{
	m_speed_cb = speed;
}

bool CBall::getVisible() { return m_IsCBallVisible; }
void CBall::setVisible(bool visib) { m_IsCBallVisible = visib; }

float CBall::getDis() { return m_THdis; }

sf::Vector2f CBall::GetFpos() { return m_fpos; }
void CBall::SetFpos(sf::Vector2f f_pos) { m_fpos = f_pos; }

void CBall::displayStats()
{
	m_log->Add("Throwing angel: "
		+ std::to_string((long long)m_angel));

	m_log->Add("Starting cannon ball speed: "
		+ std::to_string((long long)m_speed));

	m_log->Add("Cannon ball mass: "
		+ std::to_string((long long)m_mass));

	m_log->Add("Free fall: "
		+ std::to_string((long long)m_ffall));

	m_log->Add("Expected throwing distance: "
		+ std::to_string((long long)m_THdis));
}

//int CBall::GetSpeed() { return m_speed_cb; }
sf::Vector2f CBall::GetPosition() { return m_cball.getPosition(); }
void CBall::SetPosition(sf::Vector2f pos)
{
	m_cball.setPosition(pos);
}

void CBall::MoveCBall()
{
	if (m_IsCBallVisible)
	{
		m_cball.move(m_speed_cb * m_speed);
	}
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