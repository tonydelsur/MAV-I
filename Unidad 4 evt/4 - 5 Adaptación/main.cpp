#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear la ventana inicial
    sf::RenderWindow App(sf::VideoMode(400, 400), "Redimensionar Ventana con Flechas");

    // Definir límites de tamaño
    const unsigned int MIN_SIZE = 100;
    const unsigned int MAX_SIZE = 1000;
    const unsigned int STEP_SIZE = 10;

    //bucle de la ventana
    while (App.isOpen()) {
        sf::Event evt;
        // buble de eventos
        while (App.pollEvent(evt)) {
            // cerrar ventana
            if (evt.type == sf::Event::Closed) {
                App.close();
            }
        }

        // ver que teclas se presionan para redimensionar la ventana
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // agrandar
            sf::Vector2u currentSize = App.getSize();
            unsigned int newWidth = currentSize.x + STEP_SIZE; //tamaño actual mas el paso
            unsigned int newHeight = currentSize.y + STEP_SIZE;

            // Restringir el tamaño máximo
            if (newWidth <= MAX_SIZE && newHeight <= MAX_SIZE) { // verificar que no se exeda del maximo
                App.setSize(sf::Vector2u(newWidth, newHeight)); // setear el nuevo tamaño
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // Achicar
            sf::Vector2u currentSize = App.getSize();
            unsigned int newWidth = currentSize.x;
            unsigned int newHeight = currentSize.y;

            // Verificar y reducir el ancho
            if (currentSize.x > MIN_SIZE) {
                newWidth = currentSize.x - STEP_SIZE;
            }
            else {
                newWidth = MIN_SIZE; // Mantener el mínimo
            }

            // Verificar y reducir la altura
            if (currentSize.y > MIN_SIZE) {
                newHeight = currentSize.y - STEP_SIZE;
            }
            else {
                newHeight = MIN_SIZE; // Mantener el mínimo
            }

            // Restringir el tamaño mínimo
            if (newWidth >= MIN_SIZE && newHeight >= MIN_SIZE) {
                App.setSize(sf::Vector2u(newWidth, newHeight));
            }
        }

        // Renderizado
        App.clear(sf::Color::Black);
        App.display();
    }

    return 0;
}
