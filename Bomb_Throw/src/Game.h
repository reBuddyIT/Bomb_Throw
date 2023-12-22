#pragma once
#include "Window.h"
#include "Ship.h"
#include "World.h"
#include "CBall.h"
#include "Textbox.h"

class Game
{
public:
	Game();
	~Game();

	// обработка команд
	void HandleInput();
	// обновление объектов
	void Update();
	// отрисовка объектов
	void Render();
	// объект класса окна
	Window* GetWindow();

	// замер пройденного времени
	sf::Time GetElapsed();
	// обновление часов
	void RestartClock();
private:
	// объект класса окна
	Window m_window;
	// часы
	sf::Clock m_clock;
	// пройденное время
	float m_elapsed;

	// объект класса окна
	World m_world;
	// объект класса мир
	Ship m_ship;
	// объект класса пушечное ядро
	CBall m_cball;
	// объекты класса тектового окна
	Textbox m_textbox1;
	Textbox m_textbox2;
};