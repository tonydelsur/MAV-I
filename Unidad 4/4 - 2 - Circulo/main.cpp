#include<SFML/audio.hpp>
#include<SFML/graphics.hpp>
#include<SFML/main.hpp>
#include<SFML/network.hpp>
#include<SFML/system.hpp>
#include<SFML/window.hpp>
#include<math.h>

//video del desarrollo y estudio de caso:
// https://drive.google.com/open?id=1-UcaDzmX5UnMJNM371QaRmCRieyIuUH_&usp=drive_fs

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
                
                //capturar el centro del sprite
                sf::Vector2f SpriteCentro;
                float radio = t_circulo.getSize().x / 2.0f;
                
                SpriteCentro.x = circulo.getPosition().x + radio;
                SpriteCentro.y = circulo.getPosition().y + radio;
                float disX = inicialMousePos.x - SpriteCentro.x;
                float disY = inicialMousePos.y - SpriteCentro.y;

                // hipotenusa 2 = lado a 2 + lado b 2 -> hipotenusa = raiz(a2 +b2)
                float hipotenusa = std::sqrt(std::pow(disX,2) + std::pow(disY,2));

                // Verificar si el puntero toca el sprite pero ademas calcular su distancia
                if (hipotenusa <= radio) {
                    bandera = true;
                    distancia.x = inicialMousePos.x - circulo.getPosition().x;
                    distancia.y = inicialMousePos.y - circulo.getPosition().y;
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