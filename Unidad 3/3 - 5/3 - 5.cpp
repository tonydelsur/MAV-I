//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;
//////Variables//////
Texture crazyTextura, plataformaTextura;
Sprite crazy, plataforma;
int posY, alturaMaxima;
bool saltando;
float rotacion;


///Punto de entrada a la aplicación///
int main() {
	//Cargamos las texturas
	plataformaTextura.loadFromFile("./assets/plataforma.jpg");
	crazyTextura.loadFromFile("./assets/cuad_blue.png");
	//Cargamos los materiales a los sprites
	crazy.setTexture(crazyTextura);
	plataforma.setTexture(plataformaTextura);
	plataforma.setScale((float)400 / plataformaTextura.getSize().x, (float)25 / plataformaTextura.getSize().y);
	plataforma.setPosition(200, 525);
	crazy.setScale((float)50 / crazyTextura.getSize().x, (float)50 / crazyTextura.getSize().x);
	//calcular el centro de crazy para la rotacion
	crazy.setOrigin(crazy.getLocalBounds().width / 2, crazy.getLocalBounds().height / 2);

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32),
		"Crazy");

	alturaMaxima = 80;
	rotacion = 90 / 80;
	saltando = true;
	crazy.setPosition(400, 500);

	// Loop principal
	while (App.isOpen()) {
		//calculamos nuevas posiciones
		if (saltando) {
			posY--;
			if (posY < 500 - alturaMaxima) {
				posY++;
				saltando = false;
			}
		}
		else {
			posY++;
			if (posY == 500) {
				posY--;
				saltando = true;
			}

		}
		crazy.rotate(rotacion);
		// Limpiamos la ventana
		App.clear();
		// Dibujamos la escena
		crazy.setPosition(400, posY); 
		App.draw(plataforma);
		App.draw(crazy);
		
		// Mostramos la ventana
		App.display();
		sleep(milliseconds(10));
	}
	return 0;
}
