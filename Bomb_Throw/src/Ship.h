#pragma once
#include <SFML/Graphics.hpp>
#include "CBall.h"
#include "Window.h"
#include "Textbox.h"

// возможные направления
enum class Direction {None, Up, Down, Left, Right };

class Ship
{
public:
	Ship(Textbox* l_log);
	~Ship();

	// установка направления
	void SetDirection(Direction l_dir);
	// получить текущее направление
	Direction GetDirection();

	// начать стрельбу
	void SetFire(bool fire);
	// готовность к стрельбе
	bool GetFire();

	// получить скорость корабля
	int GetSpeed();
	// обновить информацию о боезапасе
	void updateAmmo();

	// получить текущие очки
	int GetScore();
	// увеличить очки
	void IncreaseScore();
	// уменьшить очки
	void DecreaseScore();

	// узнать координаты корабля
	sf::Vector2f GetPosition();
	// установить координаты
	void SetPosition(sf::Vector2f pos);

	// получить информацию о пройгрыше
	bool HasLost();
	// проиграть
	void Lose();
	// установить флаг пройгрыша
	void ToggleLost();
	// сбросить параметры корабля
	void Reset();

	// переместить корабль
	void moveShip();
	// совершить выстрел
	void Fire(CBall& l_cball,std::shared_ptr<sf::RenderWindow>);
	// обновить объект
	void shipUpdate(CBall& l_cball, std::shared_ptr<sf::RenderWindow>);
	// отобразить объект
	void Render(sf::RenderWindow& l_window);
	// получить спрайт
	sf::Sprite& GetSprite();
private:
	// очки
	int m_score;
	// состояние пройгрыша
	bool m_lost;
	// готовность стрелять
	bool m_toggleFire;
	// боезапас
	int m_ammo;
	// скорость корабля
	float m_speed;
	// текущее положение
	Direction m_dir;
	// текстура спрайта
	sf::Texture m_shipTexture;
	// спрайт корабля
	sf::Sprite m_ship;
	// объект текстового окна
	Textbox* m_log;
};