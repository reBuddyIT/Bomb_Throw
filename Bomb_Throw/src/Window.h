#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Window
{
public:
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	std::shared_ptr<sf::RenderWindow> GetRenderWindow() const;

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IswndResized();
	bool IsDone();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

	void Draw(sf::Drawable& l_drawable);
private:
	void Setup(const std::string title, const sf::Vector2u& size);
	void Create();
	void Destroy();

	std::shared_ptr<sf::RenderWindow> m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	bool m_IsResized;
};
