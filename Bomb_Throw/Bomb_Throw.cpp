#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bomb Throw");

    sf::Texture shipTexture;
    shipTexture.loadFromFile("ship.jpg");
    sf::Sprite ship(shipTexture);
    //ship.setScale(0.5f, 0.5f);
    sf::Vector2u size = shipTexture.getSize();
    ship.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f increment(0.2f, 0.2f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if ((ship.getPosition().x + (size.x / 2) >
            window.getSize().x && increment.x > 0) ||
            (ship.getPosition().x - (size.x / 2) < 0 &&
            increment.x < 0))
        {
           increment.x = -increment.x;
        }

        if ((ship.getPosition().y + (size.y / 2) >
            window.getSize().y && increment.y > 0) ||
            (ship.getPosition().y - (size.y / 2) < 0 &&
            increment.y < 0))
        {
            increment.y = -increment.y;
        }
        
        ship.setPosition(ship.getPosition() + increment);

        window.clear(sf::Color(40,40,40,255));
        window.draw(ship);
        window.display();
    }
}