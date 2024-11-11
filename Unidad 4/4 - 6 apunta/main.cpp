#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib> // Para rand y srand
#include <ctime>   // Para inicializar srand

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAX_ENEMIES = 5;

// Clase Crosshair (Mira del jugador)
class Crosshair {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Crosshair(const std::string& texturePath) {
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setScale(0.8f, 0.8f); // Escalar la mira
        sprite.setOrigin(sprite.getScale().x * texture.getSize().x / 2.0f, sprite.getScale().y * texture.getSize().y / 2.0f); // Poner el inicio en el medio
    }

    void update(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sprite.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

// Clase Enemy (Enemigos del juego)
class Enemy {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Enemy(const std::string& texturePath) {
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setScale(0.05f, 0.05f); // Escalar el enemigo
        respawn();
    }

    void respawn() {
        float x = static_cast<float>(rand() % (WINDOW_WIDTH - static_cast<int>(sprite.getGlobalBounds().width)));
        float y = static_cast<float>(rand() % (WINDOW_HEIGHT - static_cast<int>(sprite.getGlobalBounds().height)));
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

int main() {
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Clickale");
    App.setFramerateLimit(60);

    // Inicializar random
    srand(static_cast<unsigned>(time(0)));

    // Crear mira
    Crosshair crosshair("./assets/crosshair.png");

    // Crear enemigo
    Enemy enemy("./assets/et.png");

    int defeatedEnemies = 0;
    
    //bucle de la ventana
    while (App.isOpen()) {

        sf::Event evt;
        //bucle de eventos
        while (App.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed)
                App.close();

            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                if (enemy.getBounds().contains(static_cast<float>(sf::Mouse::getPosition(App).x),
                    static_cast<float>(sf::Mouse::getPosition(App).y))) {
                    defeatedEnemies++;
                    if (defeatedEnemies >= MAX_ENEMIES) {
                        std::cout << "¡Ganaste! Derrotaste a 5 enemigos." << std::endl;
                        App.close();
                    }
                    else {
                        enemy.respawn();
                    }
                }
            }
        }

        // Actualizar la posición de la mira
        crosshair.update(App);

        // Dibujar todo
        App.clear();
        enemy.draw(App);
        crosshair.draw(App);
        App.display();
    }

    return 0;
}
