// Utilizando las imágenes de colores proporcionadas reproduzca la siguiente imagen. Note que
// no todas están a la misma escala en los archivos originales.
// Rojo 256x256
// Amarillo 512x512
// Azul 128x128
// Negro 128x128

//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
//////Variables//////
Texture boxT[4];
Sprite box[4];


///Punto de entrada a la aplicación///
int main() {
	//Cargamos las texturas
	boxT[0].loadFromFile("./assets/cuad_red.png");
	boxT[1].loadFromFile("./assets/cuad_yellow.png");
	boxT[2].loadFromFile("./assets/cuad_blue.png");
	boxT[3].loadFromFile("./assets/chessb.png");
	
	//Cargamos los materiales a los sprites
	// establezco como dedidas 100x100 para todos
	for (int i = 0; i < 4; i++) {
		box[i].setTexture(boxT[i]); //asigno textura
		box[i].setScale((float)100 / boxT[i].getSize().x, (float)100 / boxT[i].getSize().y); // escalar a 100x100
		boxT[i].setSmooth(true); //suavisamos texturas

	}
	box[0].setPosition(300, 200);
	box[1].setPosition(400, 200);
	box[2].setPosition(300, 300);
	box[3].setPosition(400, 300);

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32),
			"Box Party");

	// Loop principal
	while (App.isOpen()) {
		
		// Limpiamos la ventana
		App.clear();
		// Dibujamos la escena
		for (int i = 0; i < 4; i++) {
			App.draw(box[i]);
		}
		// Mostramos la ventana
		App.display();
	}
	return 0;
}