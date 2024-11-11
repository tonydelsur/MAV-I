#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow App(sf::VideoMode(800, 600), "Atrapado");
    

    // Variable bool para cambio de textura
    bool cuadrado = true;

    // Cargar texturas
    sf::Texture squareTexture;
    sf::Texture circleTexture;

    squareTexture.loadFromFile("./assets/cuad_yellowE.png"); // pare evitar errores de escala con los l�mites de ventana, se escalo a 128x128

    circleTexture.loadFromFile("./assets/rcircle.png");

    // Crear sprite inicial con textura de cuadrado
    sf::Sprite sprite(squareTexture);
    sprite.setPosition(400, 300); // Posici�n inicial en el centro

    const float speed = 5.0f; // Velocidad de movimiento

    // Evitar el terrible efecto rebote colocando una espera
    sf::Clock clock;                  // Reloj para controlar el tiempo entre pulsaciones
    const sf::Time ESPERA = sf::milliseconds(200); // Tiempo m�nimo entre detecciones

    while (App.isOpen()) {
        sf::Event evt;
        while (App.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed)
                App.close();
        }

        // Verificar si ha pasado el tiempo m�nimo para procesar otra pulsaci�n
        if (clock.getElapsedTime() > ESPERA) {
            // Obtener los l�mites actuales del sprite
            sf::FloatRect bounds = sprite.getGlobalBounds();

            // Manejo del teclado para mover el sprite
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (bounds.left > 0)
                    sprite.move(-speed, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (bounds.left + bounds.width < App.getSize().x)
                    sprite.move(speed, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (bounds.top > 0)
                    sprite.move(0, -speed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (bounds.top + bounds.height < App.getSize().y)
                    sprite.move(0, speed);
            }

            // Cambiar de cuadrado a c�rculo con la barra espaciadora
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (cuadrado) {
                    sprite.setTexture(circleTexture); // Cambiar a textura de c�rculo
                    cuadrado = false;
                }
                else {
                    sprite.setTexture(squareTexture); // Cambiar a textura de cuadrado
                    cuadrado = true;
                }
                clock.restart();  // Reiniciar el reloj despu�s del cambio
            }
        }

        // Renderizado
        App.clear();
        App.draw(sprite);
        App.display();
    }

    return 0;
}
