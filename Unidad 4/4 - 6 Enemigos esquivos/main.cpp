#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib> // Para rand y srand
#include <ctime>   // Para inicializar srand
#include <cmath>   // Para funciones trigonométricas

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAX_ENEMIES = 5;
const float PI = 3.14159f;

// Clase Crosshair (Mira del jugador)
class Crosshair {
private:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Crosshair(const std::string& texturePath) { //el símbolo & en el tipo de dato es un puntero al real, no crea uno nuevo en memoria
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setScale(0.8f, 0.8f); // Escalar la mira
        sprite.setOrigin(sprite.getScale().x * texture.getSize().x / 2.0f, sprite.getScale().y * texture.getSize().y / 2.0f); // Poner el inicio en el medio
    }
    //actualizar posicion
    void update(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sprite.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

    //cargar el sprite en el buffer de video
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    //devolver el área global
    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

// Clase Enemy (Enemigos del juego)
class Enemy {
    // los enemigos deben moverse en círculos a velocidad y radio al azar
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f center; // Centro del movimiento circular
    float radius;        // Radio del movimiento circular
    float angle;         // Ángulo actual para calcular la posición
    float speed;         // Velocidad del movimiento circular

public:
    Enemy(const std::string& texturePath) {
        texture.loadFromFile(texturePath);
        sprite.setTexture(texture);
        sprite.setScale(0.05f, 0.05f); // Escalar el enemigo
        respawn();
    }

    // aparecer nuevamente
    void respawn() {
        center.x = static_cast<float>(rand() % (WINDOW_WIDTH - 100) + 50); // posicion x al azar descontando el borde derecho y 50 izquierdo
        center.y = static_cast<float>(rand() % (WINDOW_HEIGHT - 100) + 50); // posicion y al azar descontando el borde inferior y 50 superior
        radius = static_cast<float>(rand() % 100 + 50); // Radio aleatorio entre 50 y 150
        angle = static_cast<float>(rand() % 360);       // Ángulo inicial aleatorio
        speed = 0.05f;                                  // Velocidad del movimiento circular
    }

    //actualizar posición
    void update() {
        angle += speed; // Incrementar el ángulo para el movimiento
        if (angle > 2 * PI) {
            angle -= 2 * PI; // Mantener el ángulo dentro de un rango
        }
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        sprite.setPosition(x, y);
    }

    //cargar sprite en el buffer de video
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    // devolver área y coordenadas
    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};


// PRINCIPAL -----------------------------------------------------------------------------------------------
int main() {
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Clickale con Movimiento Circular");
    App.setFramerateLimit(60);

    // Inicializar random
    srand(static_cast<unsigned>(time(0)));

    // Crear mira
    Crosshair crosshair("./assets/crosshair.png");

    // Crear enemigo
    Enemy enemy("./assets/et.png");

    int defeatedEnemies = 0;

    // bucle de la ventana
    while (App.isOpen()) {
        sf::Event evt;
        // bucle de eventos
        while (App.pollEvent(evt)) {
            // cerrar ventana
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

        // Actualizar el enemigo
        enemy.update();

        // Dibujar todo
        App.clear();
        enemy.draw(App);
        crosshair.draw(App);
        App.display();
    }

    return 0;
}
