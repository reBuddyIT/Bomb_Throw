#include "Window.h"

Window::Window(const std::string& title, const sf::Vector2u& size) 
	:m_IsResized(0)
{
	Setup(title, size);
}
Window::~Window() { Destroy(); }

// возвращение объекта класса
std::shared_ptr<sf::RenderWindow> Window::GetRenderWindow() const
{
	return m_window;
}

// установка парамметров
void Window::Setup(const std::string title, const sf::Vector2u& size)
{
	m_window = std::make_shared<sf::RenderWindow>();
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	m_window->setFramerateLimit(60);
	Create();
}

// создание окна
void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen
		: sf::Style::Default);

	m_window->create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, style);
}
// закрытие окна
void Window::Destroy() { m_window->close(); }

// очистка окна
void Window::BeginDraw() { m_window->clear(sf::Color::Blue); }
// отображение объектов
void Window::EndDraw() { m_window->display(); }

// изменён ли размер окна
bool Window::IswndResized()
{
	return m_IsResized;
}

// завершена работа
bool Window::IsDone() { return m_isDone; }
// полный экран
bool Window::IsFullscreen() { return m_isFullscreen; }

// нарисовать объект
void Window::Draw(sf::Drawable& l_drawable) { m_window->draw(l_drawable); }

// получить размер окна
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

// полноэкранный режим
void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

// обработка ивентов
void Window::Update()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		// закрытие окна
		if (event.type == sf::Event::Closed) { m_isDone = true; }
		// изменение размеров объектов
		else if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visArea(0, 0, m_window->getSize().x, m_window->getSize().y);
			m_window->setView(sf::View(visArea));
			m_IsResized = 1;

		}
		// если размер окна не менялся
		else
		{
			m_IsResized = 0;
		}
	}
}