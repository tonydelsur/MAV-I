#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

sf::Texture t_circulo;
sf::Sprite sprites[5]; // Arreglo estático para los 5 sprites

int main() {
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Crazy Sprites");

    // Cargar la textura para todos los sprites
    t_circulo.loadFromFile("./assets/rcircle.png");

    // Asignar la textura a cada sprite
    for (int i = 0; i < 5; i++) {
        sprites[i].setTexture(t_circulo);
    }

    // Colocamos los sprites
    sprites[0].setPosition(0, 0);                         // Esquina superior izquierda
    sprites[1].setPosition(800 - t_circulo.getSize().x, 0); // Esquina superior derecha
    sprites[2].setPosition(0, 600 - t_circulo.getSize().y); // Esquina inferior izquierda
    sprites[3].setPosition(800 - t_circulo.getSize().x, 600 - t_circulo.getSize().y); // Esquina inferior derecha
    sprites[4].setPosition(400 - t_circulo.getSize().x / 2, 300 - t_circulo.getSize().y / 2); // Centro

    bool bandera = false;
    sf::Sprite* spriteSeleccionado = nullptr;
    sf::Vector2i inicialMousePos;
    sf::Vector2f distancia;

    // bucle de ventana
    while (App.isOpen()) {
        sf::Event evt;
        // bucle de eventos
        while (App.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed)
                App.close();

            // Detectar si se presiona el botón izquierdo sobre algún sprite
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                inicialMousePos = sf::Mouse::getPosition(App);

                for (int i = 0; i < 5; i++) {
                    sf::Vector2f spritePos = sprites[i].getPosition();

                    // Calcular el centro del sprite
                    sf::Vector2f spriteCentro;
                    float radio = t_circulo.getSize().x / 2.0f;
                    spriteCentro.x = spritePos.x + radio;
                    spriteCentro.y = spritePos.y + radio;

                    float disX = inicialMousePos.x - spriteCentro.x;
                    float disY = inicialMousePos.y - spriteCentro.y;

                    // Hipotenusa = raiz cuadrada (a2 + b2)
                    float hipotenusa = std::sqrt(std::pow(disX, 2) + std::pow(disY, 2));

                    // Verificar si el mouse está dentro del radio del sprite
                    if (hipotenusa <= radio) {
                        bandera = true;
                        spriteSeleccionado = &sprites[i];
                        distancia.x = inicialMousePos.x - spritePos.x;
                        distancia.y = inicialMousePos.y - spritePos.y;
                        break;
                    }
                }
            }

            // Detectar si se suelta el botón izquierdo
            if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
                bandera = false;
                spriteSeleccionado = nullptr;
            }
        }

        // Actualizar la posición del sprite seleccionado
        if (bandera && spriteSeleccionado) {
            sf::Vector2i actualMousePos = sf::Mouse::getPosition(App);
            spriteSeleccionado->setPosition(actualMousePos.x - distancia.x, actualMousePos.y - distancia.y);
        }

        // Dibujar los sprites
        App.clear();
        for (int i = 0; i < 5; i++) {
            App.draw(sprites[i]);
        }
        App.display();
    }

    return 0;
}