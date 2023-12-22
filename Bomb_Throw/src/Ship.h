#pragma once
#include <SFML/Graphics.hpp>
#include "CBall.h"
#include "Window.h"
#include "Textbox.h"

// ��������� �����������
enum class Direction {None, Up, Down, Left, Right };

class Ship
{
public:
	Ship(Textbox* l_log);
	~Ship();

	// ��������� �����������
	void SetDirection(Direction l_dir);
	// �������� ������� �����������
	Direction GetDirection();

	// ������ ��������
	void SetFire(bool fire);
	// ���������� � ��������
	bool GetFire();

	// �������� �������� �������
	int GetSpeed();
	// �������� ���������� � ���������
	void updateAmmo();

	// �������� ������� ����
	int GetScore();
	// ��������� ����
	void IncreaseScore();
	// ��������� ����
	void DecreaseScore();

	// ������ ���������� �������
	sf::Vector2f GetPosition();
	// ���������� ����������
	void SetPosition(sf::Vector2f pos);

	// �������� ���������� � ���������
	bool HasLost();
	// ���������
	void Lose();
	// ���������� ���� ���������
	void ToggleLost();
	// �������� ��������� �������
	void Reset();

	// ����������� �������
	void moveShip();
	// ��������� �������
	void Fire(CBall& l_cball,std::shared_ptr<sf::RenderWindow>);
	// �������� ������
	void shipUpdate(CBall& l_cball, std::shared_ptr<sf::RenderWindow>);
	// ���������� ������
	void Render(sf::RenderWindow& l_window);
	// �������� ������
	sf::Sprite& GetSprite();
private:
	// ����
	int m_score;
	// ��������� ���������
	bool m_lost;
	// ���������� ��������
	bool m_toggleFire;
	// ��������
	int m_ammo;
	// �������� �������
	float m_speed;
	// ������� ���������
	Direction m_dir;
	// �������� �������
	sf::Texture m_shipTexture;
	// ������ �������
	sf::Sprite m_ship;
	// ������ ���������� ����
	Textbox* m_log;
};