#include "CBall.h"

CBall::CBall(Textbox* l_log)
{
	m_log = l_log;

	// установка видимости
	m_IsCBallVisible = 0;

	// закруска спрайта ядра
	m_cballTexture.loadFromFile("assets/pics/CBall.png");
	m_cball.setTexture(m_cballTexture);
	// установление позиции
	m_cball.setOrigin({ m_cball.getGlobalBounds().width / 2, m_cball.getGlobalBounds().height / 2 });
	m_cball.setScale(0.06, 0.06);
	m_cball.setPosition(800, 400);

	// физические параметры
	m_angel = 45;
	m_speed = 10;
	m_ffall = 0.12;

	// расчёт дальности полёта
	m_THdis = ((2 * pow((m_speed), 2) * sin(m_angel) * cos(m_angel)) / m_ffall);
}

CBall::~CBall() {}

// установка скорости(вектор направления)
void CBall::setSpeed(sf::Vector2f speed) { m_speed_cb = speed; }
// видимость ядра
bool CBall::getVisible() { return m_IsCBallVisible; }
// установка видимости
void CBall::setVisible(bool visib) { m_IsCBallVisible = visib; }
// получить дистацию полёта ядра
float CBall::getDist() { return m_THdis; }
// отобразить физические параметры
void CBall::displayStats()
{
	m_log->Add("Throwing angel: "
		+ std::to_string((long long)m_angel), 5);

	m_log->Add("Starting cannon ball speed: "
		+ std::to_string((long long)m_speed), 5);

	m_log->Add("Free fall: "
		+ std::to_string(m_ffall), 5);

	m_log->Add("Expected throwing distance: "
		+ std::to_string((long long)m_THdis), 5);
}

// получить координаты выстрела
sf::Vector2f CBall::GetFpos() { return m_fpos; }
// задать координаты выстрела
void CBall::SetFpos(sf::Vector2f f_pos) { m_fpos = f_pos; }
// получить координаты ядра
sf::Vector2f CBall::GetPosition() { return m_cball.getPosition(); }
// задать координаты ядра
void CBall::SetPosition(sf::Vector2f pos) { m_cball.setPosition(pos); }

// смещение ядра
void CBall::MoveCBall()
{
	// если видим
	if (m_IsCBallVisible)
	{
		m_cball.move(m_speed_cb * m_speed);
	}
}
// обнулени параметров
void CBall::Reset()
{
	m_IsCBallVisible = 0;
	m_cball.setPosition(800, 400);
}
// обновление объекта
void CBall::cballUpdate()
{
	// смещение
	MoveCBall();
	// отображение физических параметров
	displayStats();
}
// отображение объекта
void CBall::Render(sf::RenderWindow& l_window)
{
	l_window.draw(m_cball);
}