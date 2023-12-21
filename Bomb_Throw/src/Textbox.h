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

	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetSize();

	void Setup(int l_visible, int l_charSize,
		int l_width, sf::Vector2f l_screenPos);
	void Add(std::string l_message, int max_size);
	void Clear();

	void Render(sf::RenderWindow& l_wind);
private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::Vector2f m_offset;
	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};