#include <SFML/Graphics.hpp>

sf::RectangleShape background;
sf::CircleShape ball;
sf::RectangleShape player1;
sf::RectangleShape player2;
sf::RectangleShape borders1;
sf::RectangleShape borders2;

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

    borders1.setSize(sf::Vector2f(800,40));
    borders1.setPosition(sf::Vector2f(0,0));
    borders1.setFillColor(sf::Color::White);

    borders2.setSize(sf::Vector2f(800,40));
    borders2.setPosition(sf::Vector2f(0,background.getSize().y - borders2.getSize().y));
    borders2.setFillColor(sf::Color::White);


  sf::RenderWindow window(sf::VideoMode({800, 800}), "Atari Pong", sf::Style::Close);
  while (window.isOpen()) {
    window.clear();
    if (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    sf::Vector2 player1_position = player1.getPosition(); //узнать позицию 1
    float p1h = player1.getSize().y; // узнаем высоту 1

    sf::Vector2 player2_position = player2.getPosition(); // узнать позицию 2
    float p2h = player2.getSize().y; // высота 2

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player1_position.y > borders1.getSize().y){player1.move({0.f,-1.f});};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player1_position.y + p1h < borders2.getPosition().y) {player1.move({0.f,1.f});};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && player2_position.y > borders1.getSize().y) {player2.move({0.f,-1.f});};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && player2_position.y + p2h < borders2.getPosition().y){player2.move({0.f,1.f});};
    


    /* Еще не проверено (протестировано)
    if (sf::Joystick::isConnected(0)){
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
        float deadzone = 15.f; // 

        if (y < deadzone) {
            player1.move ({0.f,-1.f}); // стик вверх
        }
        if (y > deadzone){
            player1.move ({0.f,1.f}); // стик вниз
        }
    }
    */

    window.draw(background);
    window.draw(ball);
    window.draw(player1);
    window.draw(player2);
    window.draw(borders1);
    window.draw(borders2);
    window.display();
  }
}