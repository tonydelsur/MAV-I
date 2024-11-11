#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow App(sf::VideoMode(800, 600), "Atrapado");
    App.setFramerateLimit(60);

    // Variable bool para cambio de textura
    bool cuadrado = true;

    // Cargar texturas
    sf::Texture squareTexture;
    sf::Texture circleTexture;
    squareTexture.loadFromFile("./assets/cuad_yellow.png"); // 512x512
    circleTexture.loadFromFile("./assets/rcircle.png"); // 128x128

    // Crear sprite inicial con textura de cuadrado
    sf::Sprite sprite(squareTexture); 
    sprite.setScale(0.25f, 0.25f); // escalar al cuadrado similar al círculo
    sprite.setPosition(400, 300); // Posición inicial en el centro
    const float speed = 5.0f; // Velocidad de movimiento

    // Evitar el terrible efecto rebote colocando una espera
    sf::Clock clock;                  // Reloj para controlar el tiempo entre pulsaciones
    const sf::Time ESPERA = sf::milliseconds(200); // Tiempo mínimo entre detecciones

    while (App.isOpen()) {
        sf::Event evt;
        while (App.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed)
                App.close();
        }

        // Verificar si ha pasado el tiempo mínimo para procesar otra pulsación
        if (clock.getElapsedTime() > ESPERA) {
            // Obtener los límites actuales del sprite
           //  sf::FloatRect bounds = sprite.getGlobalBounds(); ---------------------

            // Manejo del teclado para mover el sprite
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (sprite.getPosition().x - speed > 0)
                    sprite.move(-speed, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (sprite.getPosition().x + 128  + speed < App.getSize().x)
                    sprite.move(speed, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (sprite.getPosition().y - speed > 0)
                    sprite.move(0, -speed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (sprite.getPosition().y + 128 + speed < App.getSize().y)
                    sprite.move(0, speed);
            }

            // Cambiar de cuadrado a círculo con la barra espaciadora
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (cuadrado) {
                    sprite.setTexture(circleTexture); // Cambiar a textura de círculo
                    cuadrado = false;
                    sprite.setScale(1.0f, 1.0f); // escalar la textura circulo nuevamente a 1
                }
                else {
                    sprite.setTexture(squareTexture); // Cambiar a textura de cuadrado
                    cuadrado = true;
                    sprite.setScale(0.25f, 0.25f); // escalar al cuadrado similar al círculo
                }
                clock.restart();  // Reiniciar el reloj después del cambio
            }
        }

        // Renderizado
        App.clear();
        App.draw(sprite);
        App.display();
    }

    return 0;
}
