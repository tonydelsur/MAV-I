//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
//////Variables//////
Texture texture;
Sprite plataforma[9];
float escalaX, escalaY;

///Punto de entrada a la aplicación///
int main() {
	//Cargamos la textura del rectángulo
	texture.loadFromFile("./assets/cuad_blue.png");

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32),
		"Plataformas");
	// Loop principal
	while (App.isOpen()) {

		// Limpiamos la ventana
		App.clear();
		// Dibujamos la escena
		escalaX = (float)25 / texture.getSize().x; // escala x - ancho

		//bucle de dibujo de sprites verticales
		for (int i = 0; i < 8; i++) {
			// asignar textura a los sprites
			plataforma[i].setTexture(texture);
			// calcular escala para altura incremental
			escalaY = (float)(i * 25 + 25) / texture.getSize().y;
			// aplicar escala
			plataforma[i].setScale(escalaX, escalaY);
			// posicion x en multiplos de 50, posicion de y desde la base
			plataforma[i].setPosition(25 + i * 50, 600 - (25 + i * 25));
			// dibujar sprites
			App.draw(plataforma[i]);
		}
		// plataforma horizontal
		//asignar textura
		plataforma[8].setTexture(texture);
		// escalar a 300 x 25
		plataforma[8].setScale((float)300 / texture.getSize().x, (float)25 / texture.getSize().y);
		// colocar en posición siguiente
		plataforma[8].setPosition(425, 350);
		// dibujar
		App.draw(plataforma[8]);
		// Mostramos la ventana
		App.display();
	}
	return 0;
}
