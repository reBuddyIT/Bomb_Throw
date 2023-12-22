#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Textbox.h"

class CBall
{
public:
	CBall(Textbox* l_log);
	~CBall();

	// установка скорости(вектор направления)
	void setSpeed(sf::Vector2f speed);
	// видимость ядра
	bool getVisible();
	// установка видимости
	void setVisible(bool visib);
	// получить дистацию полёта ядра
	float getDist();
	// отобразить физические параметры
	void displayStats();

	// получить координаты ядра
	sf::Vector2f GetPosition();
	// задать координаты ядра
	void SetPosition(sf::Vector2f pos);
	// получить координаты выстрела
	sf::Vector2f GetFpos();
	// задать координаты выстрела
	void SetFpos(sf::Vector2f f_pos);

	// смещение ядра
	void MoveCBall();
	// обнулени параметров
	void Reset();
	// обновление объекта
	void cballUpdate();
	// отображение объекта
	void Render(sf::RenderWindow& l_window);
private:
	// тектура пушечное ядро
	sf::Texture m_cballTexture;
	// спрайт пушечное ядро
	sf::Sprite m_cball;
	// направление выстрела
	sf::Vector2f m_speed_cb;
	// координаты выстрела
	sf::Vector2f m_fpos;
	// видимость объекта
	bool m_IsCBallVisible;
	// скорость ядра
	float m_speed;
	// угол выстрела
	float m_angel;
	// ускорение свободного падения
	float m_ffall;
	// дистация полёта ядра
	float m_THdis;
	// объект тектового окна
	Textbox* m_log;
};