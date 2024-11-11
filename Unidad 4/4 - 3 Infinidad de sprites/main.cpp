
#include<SFML/graphics.hpp>
#include<SFML/main.hpp>
#include<SFML/network.hpp>
#include<SFML/system.hpp>
#include<SFML/window.hpp>
#include<iostream>

// Clase personalizada Sprite
class circulo {
public:
    sf::Sprite sprite;
    float x, y;

    circulo(sf::Texture& t_circle, float _x, float _y) {
        sprite.setTexture(t_circle);
        x = _x;
        y = _y;
        sprite.setPosition(_x, _y);
    }
};

// Como no puedo definir infinitos, utilizo un máximo de elementos
const int MAX_CIRCULOS = 100;

int main() {
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Invasión de Sprites");
   // App.setFramerateLimit(60);

    sf::Texture t_circuloA;
    sf::Texture t_circuloR;
    t_circuloA.loadFromFile("./assets/bcircle.png"); // Textura Azul
    t_circuloR.loadFromFile("./assets/rcircle.png"); // Textura Roja

    // Arreglo dinamico de punteros para los sprites
    circulo* circulos[MAX_CIRCULOS];
    int contador = 0;

    while (App.isOpen()) {
        sf::Event evt;
        //eventos
        while (App.pollEvent(evt)) {
            // cerrar ventana
            if (evt.type == sf::Event::Closed)
                App.close();

            // Detectar clic con el botón derecho del mouse
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Right) {
                if (contador < MAX_CIRCULOS) { // Verificar si hay espacio en el arreglo
                    float posX = static_cast<float>(evt.mouseButton.x) - (t_circuloA.getSize().x / 2); // acomodar el círculo en el puntero
                    float posY = static_cast<float>(evt.mouseButton.y) - (t_circuloA.getSize().y / 2);
                    circulos[contador] = new circulo(t_circuloA, posX, posY);
                    contador++;
                }
            }
            // Detectar clic con el botón izquierdo del mouse
            if (evt.type == sf::Event::MouseButtonPressed && evt.mouseButton.button == sf::Mouse::Left) {
                if (contador < MAX_CIRCULOS) { // Verificar si hay espacio en el arreglo
                    float posX = static_cast<float>(evt.mouseButton.x) - (t_circuloR.getSize().x / 2); // acomodar el círculo en el puntero
                    float posY = static_cast<float>(evt.mouseButton.y) - (t_circuloR.getSize().y / 2);
                    circulos[contador] = new circulo(t_circuloR, posX, posY);
                    contador++;
                }
            }

            
        }

        App.clear();

        // Dibujar todos los sprites
        for (int i = 0; i < contador; ++i) {
            App.draw(circulos[i]->sprite);
        }

        App.display();
    }

    // Liberar memoria asignada
    for(int i = 0; i < contador; ++i) {
        delete circulos[i];
    }

    return 0;
}