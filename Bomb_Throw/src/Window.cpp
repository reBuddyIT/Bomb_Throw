#include "Window.h"

Window::Window(const std::string& title, const sf::Vector2u& size) 
	:m_IsResized(0)
{
	Setup(title, size);
}
Window::~Window() { Destroy(); }


std::shared_ptr<sf::RenderWindow> Window::GetRenderWindow() const
{
	return m_window;
}

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

void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen
		: sf::Style::Default);

	m_window->create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, style);
}

void Window::Destroy() { m_window->close(); }

void Window::BeginDraw() { m_window->clear(sf::Color::Blue); }
void Window::EndDraw() { m_window->display(); }

bool Window::IswndResized()
{
	return m_IsResized;
}

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullscreen() { return m_isFullscreen; }

void Window::Draw(sf::Drawable& l_drawable) { m_window->draw(l_drawable); }

sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void Window::Update()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) { ToggleFullscreen(); }
		else if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visArea(0, 0, m_window->getSize().x, m_window->getSize().y);
			m_window->setView(sf::View(visArea));
			m_IsResized = 1;

		}
		else
		{
			m_IsResized = 0;
		}
	}
}