#include <SFML/Graphics.hpp>
#include <random>
#include <SFML/Window/Event.hpp>

sf::RectangleShape background;
sf::CircleShape ball;
sf::RectangleShape player1;
sf::RectangleShape player2;
sf::RectangleShape borders1;
sf::RectangleShape borders2;

sf::Vector2f ballVelocity(0, 0);
bool ballMoving = false;

int main() {
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(800, 800));
    background.setFillColor(sf::Color::Black);

    ball.setRadius(30);
    ball.setPosition(sf::Vector2f(background.getSize().x / 2 - ball.getRadius(), background.getSize().y / 2 - ball.getRadius()));
    ball.setFillColor(sf::Color::White);

    player1.setSize(sf::Vector2f(50, 100));
    player1.setPosition(sf::Vector2f(50, background.getSize().y / 2 - player1.getSize().y / 2));
    player1.setFillColor(sf::Color::Red);

    player2.setSize(sf::Vector2f(50, 100));
    player2.setPosition(sf::Vector2f(700, background.getSize().y / 2 - player2.getSize().y / 2));
    player2.setFillColor(sf::Color::Cyan);

    borders1.setSize(sf::Vector2f(800, 40));
    borders1.setPosition(sf::Vector2f(0, 0));
    borders1.setFillColor(sf::Color::White);

    borders2.setSize(sf::Vector2f(800, 40));
    borders2.setPosition(sf::Vector2f(0, background.getSize().y - borders2.getSize().y));
    borders2.setFillColor(sf::Color::White);

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Atari Pong", sf::Style::Close);

    // Генератор случайного направления мяча
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(-0.5f, 0.5f); // ~±30°

    sf::Clock clock; // Для учета времени
    float deltaTime = 0.f;

    while (window.isOpen()) {
        window.clear();
        deltaTime = clock.restart().asSeconds(); // Обновляем время с последнего кадра

        if (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // ЛКМ — старт мяча
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == sf::Mouse::Button::Left && !ballMoving) {
                        float angle = angleDist(gen);
                        float speed = 150.f;
                        int direction = (std::uniform_int_distribution<>(0, 1)(gen) == 0) ? -1 : 1;
                        ballVelocity.x = std::cos(angle) * speed * direction;
                        ballVelocity.y = std::sin(angle) * speed;
                        ballMoving = true;
                    }
                }
            }
        }

        if (ballMoving) {
            sf::Vector2f ballPosition = ball.getPosition();
            ballPosition += ballVelocity * deltaTime; // Движение с учетом времени
            ball.setPosition(ballPosition);

            // Проверка столкновения с вертикальными границами
            if (ballPosition.x < 0 || ballPosition.x + ball.getRadius() * 2 > 800) {
                ballMoving = false;
                ball.setPosition(sf::Vector2f(background.getSize().x / 2 - ball.getRadius(), background.getSize().y / 2 - ball.getRadius()));
                ballVelocity = sf::Vector2f(0.f, 0.f);
            }

            // Проверка столкновения с горизонтальными границами
            if (ballPosition.y < 0 || ballPosition.y + ball.getRadius() * 2 > 800) {
                ballVelocity.y = -ballVelocity.y; // Отражение от верхней/нижней границы
            }

            // Проверка столкновения с ракетками
            if (ball.getGlobalBounds().findIntersection(player1.getGlobalBounds())) {
                ballVelocity.x = -ballVelocity.x; // Отражение от левой ракетки
            }
            else if (ball.getGlobalBounds().findIntersection(player2.getGlobalBounds())) {
                ballVelocity.x = -ballVelocity.x; // Отражение от правой ракетки
            }
        }

        sf::Vector2 player1_position = player1.getPosition(); // Узнать позицию 1
        float p1h = player1.getSize().y; // Узнать высоту 1

        sf::Vector2 player2_position = player2.getPosition(); // Узнать позицию 2
        float p2h = player2.getSize().y; // Высота 2

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player1_position.y > borders1.getSize().y) { player1.move({0.f, -1.f}); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player1_position.y + p1h < borders2.getPosition().y) { player1.move({0.f, 1.f}); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && player2_position.y > borders1.getSize().y) { player2.move({0.f, -1.f}); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && player2_position.y + p2h < borders2.getPosition().y) { player2.move({0.f, 1.f}); }

        window.draw(background);
        window.draw(ball);
        window.draw(player1);
        window.draw(player2);
        window.draw(borders1);
        window.draw(borders2);
        window.display();
    }
    return 0; // Корректное завершение main
}