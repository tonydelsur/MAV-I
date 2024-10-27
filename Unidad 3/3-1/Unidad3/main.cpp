//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
//////Variables//////
Texture texture;
Sprite sprite1, sprite2, sprite3, sprite4;


///Punto de entrada a la aplicación///
int main() {
	//Cargamos la textura del archivo 128x128
	texture.loadFromFile("./assets/rcircle.png");
	//Cargamos el material del sprite
	sprite1.setTexture(texture);
	sprite2.setTexture(texture);
	sprite3.setTexture(texture);
	sprite4.setTexture(texture);

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32),
		"Que ventana horrible");
	// Loop principal
	while (App.isOpen()){
	
			// Limpiamos la ventana
			App.clear();
			// Dibujamos la escena
			sprite1.setPosition(20, 20);
			sprite2.setPosition(652, 20); // X = 800 - 20 - 128
			sprite3.setPosition(652, 452); // Y = 600 - 20 - 128
			sprite4.setPosition(20, 452);
			App.draw(sprite1);
			App.draw(sprite2);
			App.draw(sprite3);
			App.draw(sprite4);
			// Mostramos la ventana
			App.display();
	}
	return 0;
}
