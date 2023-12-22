#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox
{
public:
	Textbox();
	Textbox(int l_visible, int l_charSize,
		int l_width, sf::Vector2f l_screenPos);
	~Textbox();

	// установка координат
	void SetPos(sf::Vector2f pos);
	// получение размеров
	sf::Vector2f GetSize();

	// установка параметров
	void Setup(int l_visible, int l_charSize,
		int l_width, sf::Vector2f l_screenPos);
	// добавление строчки
	void Add(std::string l_message, int max_size);
	// очистка текст бокса
	void Clear();

	// отображение текстового окна
	void Render(sf::RenderWindow& l_wind);
private:
	// сообхение окна
	MessageContainer m_messages;
	// количество видимых
	int m_numVisible;
	// смещение
	sf::Vector2f m_offset;
	// оболочка
	sf::RectangleShape m_backdrop;
	// шрифт
	sf::Font m_font;
	// текст
	sf::Text m_content;
};