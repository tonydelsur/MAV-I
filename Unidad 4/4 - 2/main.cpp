#include<SFML/audio.hpp>
#include<SFML/graphics.hpp>
#include<SFML/main.hpp>
#include<SFML/network.hpp>
#include<SFML/system.hpp>
#include<SFML/window.hpp>

// Video del desarrollo y estudio de caso:
// https://drive.google.com/open?id=1-Hi54ht2FwfkxoE2S1C_pXhjUnYRh4dD&usp=drive_fs

sf::Sprite circulo;
sf::Texture t_circulo;

int main() {
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Sprites Moviendo");
    t_circulo.loadFromFile("./assets/rcircle.png");
    circulo.setTexture(t_circulo);
    circulo.setPosition(300, 200);

    bool bandera = false;
    sf::Vector2i inicialMousePos;
    sf::Vector2f distancia;

    while (App.isOpen()) {
        sf::Event evt;
        while (App.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed)
                App.close();
            // detectar si se presiona el botón izquierdo en el sprite
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                inicialMousePos = sf::Mouse::getPosition(App);
                sf::Vector2f spritePos = circulo.getPosition();

                // Verificar si el puntero toca el sprite pero ademas calcular su distancia
                if (inicialMousePos.x >= spritePos.x && inicialMousePos.x <= spritePos.x + t_circulo.getSize().x &&
                    inicialMousePos.y >= spritePos.y && inicialMousePos.y <= spritePos.y + t_circulo.getSize().y) {
                    bandera = true;
                    distancia.x = inicialMousePos.x - spritePos.x;
                    distancia.y = inicialMousePos.y - spritePos.y;
                }
               
            }

            //detectar si suelta el botón
            if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
                bandera = false;
            }
        }
        // Actualizar la posición del sprite con Bandera True
        if (bandera) {
            sf::Vector2i actualMousePos = sf::Mouse::getPosition(App);
            circulo.setPosition(actualMousePos.x - distancia.x, actualMousePos.y - distancia.y);
        }


        App.clear();
        App.draw(circulo);
        App.display();
    }

    return 0;
}