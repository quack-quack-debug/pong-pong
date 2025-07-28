#include <SFML/Graphics.hpp>

sf::RectangleShape background;
sf::CircleShape ball;
sf::RectangleShape player1;
sf::RectangleShape player2;

int main() {
    background.setPosition(sf::Vector2f(0,0));
    background.setSize(sf::Vector2f(800,800));
    background.setFillColor(sf::Color::Black);

    ball.setRadius(30);
    ball.setPosition(sf::Vector2f(background.getSize().x / 2 - ball.getRadius(), background.getSize().y / 2 - ball.getRadius()));
    ball.setFillColor(sf::Color::White);

    player1.setSize(sf::Vector2f(50,100));
    player1.setPosition(sf::Vector2f(50, background.getSize().y / 2 - player1.getSize().y / 2));
    player1.setFillColor(sf::Color::Red);


    player2.setSize(sf::Vector2f(50,100));
    player2.setPosition(sf::Vector2f(700,background.getSize().y / 2 - player2.getSize().y / 2));
    player2.setFillColor(sf::Color::Cyan);


  sf::RenderWindow window(sf::VideoMode({800, 800}), "SFML", sf::Style::Close);
  while (window.isOpen()) {
    window.clear();
    if (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.draw(background);
    window.draw(ball);
    window.draw(player1);
    window.draw(player2);
    window.display();
  }
}