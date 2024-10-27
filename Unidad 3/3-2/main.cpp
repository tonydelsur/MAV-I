#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

using namespace sf;
//////Variables//////
Texture texturaN;
Texture texturaB;
// 64 posiciones 32 blancos y 32 negros
Sprite spriteN[32];
Sprite spriteB[32];
float escalaX;
float escalaY;

///Punto de entrada a la aplicación///
int main() {
	//Cargamos la textura del archivo
	texturaB.loadFromFile("./assets/chessw.png"); // 128 x 128
	texturaN.loadFromFile("./assets/chessb.png"); // 128 x 128
	//cargamos el material en todas los sprites
	for (int i = 0; i < 32; i++) {
		spriteB[i].setTexture(texturaB);
		spriteN[i].setTexture(texturaN);
	}

	//calcular la proporción x e y de cada sprite
	// pantalla 800x800, esto incluye 8 fichas por 8 línea
	escalaX = 100 / 128; //128 es el tamaño de la imagen
	escalaY = 100 / 128;
	// escalamos...
	for (int i = 0; i < 32; i++) {
		spriteB[i].setScale(0.78125, 0.78125);
		spriteN[i].setScale(0.78125, 0.78125);
	}

	//fijo posiciíon para cada sprite de cada color comenzando por blanco
	for (int i = 0; i < 4; i++) {
		for (int g = 0; g < 8; g++) {
			if (g % 2 == 0) {
				spriteN[i + g * 4].setPosition(i * 200, g * 100);
				spriteB[i + g * 4].setPosition(100 + i * 200, g * 100);
			}
			else {
				spriteB[i + g * 4].setPosition(i * 200, g * 100);
				spriteN[i + g * 4].setPosition(100 + i * 200, g * 100);
			}
		}
	}
	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 800, 32),
		"Jugando ajedrez");
	// Loop principal
	while (App.isOpen())
	{
		// Limpiamos la ventana
		App.clear();
		// Dibujamos los sprites
		for (int i = 0; i < 32; i++) {
			App.draw(spriteB[i]);
			App.draw(spriteN[i]);
		}
		// Mostramos la ventana
		App.display();
	}
	return 0;
}
