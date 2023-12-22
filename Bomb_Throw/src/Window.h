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

	// возвращение объекта класса
	std::shared_ptr<sf::RenderWindow> GetRenderWindow() const;

	// очистка окна
	void BeginDraw();
	// отображение объектов
	void EndDraw();
	// обработка ивентов
	void Update();

	// завершена работа
	bool IsDone();
	// полный экран
	bool IsFullscreen();
	// изменён размер окна
	bool IswndResized();
	// получить размер экрана
	sf::Vector2u GetWindowSize();
	// полноэкранный режим
	void ToggleFullscreen();
	// нарисовать объект
	void Draw(sf::Drawable& l_drawable);
private:
	// установка параметров
	void Setup(const std::string title, const sf::Vector2u& size);
	// создание окна
	void Create();
	// закрытие окна
	void Destroy();
	
	// указатель на объект класса окна
	std::shared_ptr<sf::RenderWindow> m_window;
	// размер окна
	sf::Vector2u m_windowSize;
	// название окна
	std::string m_windowTitle;
	// завершена работа
	bool m_isDone;
	// полный экран
	bool m_isFullscreen;
	// изменён размер окна
	bool m_IsResized;
};
