#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Textbox.h"

class CBall
{
public:
	CBall(Textbox* l_log);
	~CBall();

	// ��������� ��������(������ �����������)
	void setSpeed(sf::Vector2f speed);
	// ��������� ����
	bool getVisible();
	// ��������� ���������
	void setVisible(bool visib);
	// �������� �������� ����� ����
	float getDist();
	// ���������� ���������� ���������
	void displayStats();

	// �������� ���������� ����
	sf::Vector2f GetPosition();
	// ������ ���������� ����
	void SetPosition(sf::Vector2f pos);
	// �������� ���������� ��������
	sf::Vector2f GetFpos();
	// ������ ���������� ��������
	void SetFpos(sf::Vector2f f_pos);

	// �������� ����
	void MoveCBall();
	// �������� ����������
	void Reset();
	// ���������� �������
	void cballUpdate();
	// ����������� �������
	void Render(sf::RenderWindow& l_window);
private:
	// ������� �������� ����
	sf::Texture m_cballTexture;
	// ������ �������� ����
	sf::Sprite m_cball;
	// ����������� ��������
	sf::Vector2f m_speed_cb;
	// ���������� ��������
	sf::Vector2f m_fpos;
	// ��������� �������
	bool m_IsCBallVisible;
	// �������� ����
	float m_speed;
	// ���� ��������
	float m_angel;
	// ��������� ���������� �������
	float m_ffall;
	// �������� ����� ����
	float m_THdis;
	// ������ ��������� ����
	Textbox* m_log;
};