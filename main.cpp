#include <iostream>
#include <sfml/Graphics.hpp>
#include <random>

/*On my own computer, when I gave the path to the photos etc., it's giving an error,
 * but whenever I entered the "absolute path" it worked. */

auto main() -> int {
    auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Dino");
    auto event = sf::Event();

    // On your computer please take the absolute path to work properly
    auto cactusPicPath = R"(C:\Users\lordo\OneDrive\Masaüstü\C++\Projects\SFML dinosaur\pics\cactus.png)";
    auto dinoPicPath = R"(C:\Users\lordo\OneDrive\Masaüstü\C++\Projects\SFML dinosaur\pics\dino.png)";
    auto fontPath = R"(C:\Users\lordo\OneDrive\Masaüstü\C++\Projects\SFML dinosaur\fonts\slkscr.ttf)";

    auto dead = false;
    std::random_device randomDevice;
    std::mt19937 mt19937(randomDevice());
    std::uniform_int_distribution<> distribution(3, 9);

    // Score font
    auto clock1 = sf::Clock();
    auto font = sf::Font();
    auto score = 0;
    if (!font.loadFromFile(fontPath)) {
        std::cout << "Cant load font";
    }

    // Restart game text
    sf::Text restartText("G A M E   O V E R", font, 30);
    restartText.setFillColor(sf::Color::Black);
    restartText.setPosition(250, 150);
    sf::Text restartInfo("Play Again: Space Button", font, 15);
    restartInfo.setFillColor(sf::Color::Black);
    restartInfo.setPosition(10, 10);

    // Dino pic
    auto dinoTexture = sf::Texture();
    auto dino = sf::Sprite();
    if (!dinoTexture.loadFromFile(dinoPicPath))
        std::cout << "Cant load dino image";
    dino.setTexture(dinoTexture);
    dino.setPosition(100, 300);
    dino.setScale(.1f, .1f);

    // Cactus pic
    auto cactusTexture = sf::Texture();
    auto cactus = sf::Sprite();
    if (!cactusTexture.loadFromFile(cactusPicPath))
        std::cout << "Cant load cactus image";
    cactus.setTexture(cactusTexture);
    cactus.setPosition(800, 290);
    cactus.setScale(.1f, .1f);

    // Cactus1 pic
    auto cactus1Texture = sf::Texture();
    auto cactus1 = sf::Sprite();
    if (!cactus1Texture.loadFromFile(cactusPicPath))
        std::cout << "Cant load cactus1 image";
    cactus1.setTexture(cactus1Texture);
    cactus1.setPosition(1000, 290);
    cactus1.setScale(.1f, .1f);

    // Line path
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(0, window.getSize().y / 2 + dino.getGlobalBounds().height);
    line[1].position = sf::Vector2f(window.getSize().x, window.getSize().y / 2 + dino.getGlobalBounds().height);
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    // Dino movement
    auto jumpHigh = .5f;
    auto gravity = 0.0005f;
    bool isJumping = false;

    // Cactus movement
    auto cactusSpeed = -.1f;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Keyboard Check
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (dead) {
                    // Restart game
                    dead = false;
                    score = 0;
                    clock1.restart();
                    dino.setPosition(100, 300);
                    cactus.setPosition(800, 290);
                    cactus1.setPosition(1000, 290);
                } else {
                    isJumping = true;
                }
            }
        }
        auto randomNumber = distribution(mt19937) * 50.0f; // Generate a new random number

        // Dino jump move
        if (isJumping) {
            dino.move(0, jumpHigh);
            jumpHigh += gravity; // Gravity

            // reset gravity
            if (dino.getPosition().y >= 300) {
                dino.setPosition(dino.getPosition().x, 300);
                jumpHigh = -jumpHigh;
                isJumping = false;
            }
        }

        // Cactus move
        cactus.move(cactusSpeed, 0);
        if (cactus.getPosition().x < -50) { // remove cactus and spawn
            cactus.setPosition(650 + randomNumber, 290);
        }
        cactus1.move(cactusSpeed, 0);
        if (cactus1.getPosition().x < -50) {    // remove cactus and spawn
            cactus1.setPosition(650 + randomNumber, 290);
        }

        // if dino touch any cactus game over
        if (dino.getGlobalBounds().intersects(cactus.getGlobalBounds()) ||
            dino.getGlobalBounds().intersects(cactus1.getGlobalBounds())) {
            dead = true;
        }

        // Score counting
        if (clock1.getElapsedTime().asMilliseconds() >= 250) { // Count every 1/4 second (1 second = 1000 milliseconds)
            score++;
            clock1.restart();
        }
        sf::Text scoreText("Score: " + std::to_string(score), font, 30);
        scoreText.setFillColor(sf::Color::Black);
        scoreText.setPosition(600, 25);

        if (!dead) {
            window.clear(sf::Color(169, 169, 169));
            window.draw(scoreText);
            window.draw(dino);
            window.draw(cactus);
            window.draw(cactus1);
            window.draw(line);
            window.display();
        } else {
            window.draw(restartText);
            window.draw(restartInfo);
            window.display();
        }
    }
}