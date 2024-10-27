// Utilice la imagen llamada “fondo.jpg” cree una ventana de 800x600 y dibújela en toda la
// extensión de la pantalla para que funcione como un fondo de nuestro videojuego.

//////Bibliotecas//////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
//////Variables//////
Texture textura;
Sprite fondo;
float escalaX, escalaY;


///Punto de entrada a la aplicación///
int main() {
	//Cargamos la textura del archivo 128x128
	textura.loadFromFile("./assets/fondo.jpg");
	//Cargamos el material del sprite
	fondo.setTexture(textura);
	escalaX = 800 / (float)textura.getSize().x;
	escalaY = 600 / (float)textura.getSize().y;
	fondo.setScale(escalaX, escalaY);

	//Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32),
		"Que ventana horrible");
	// Loop principal
	while (App.isOpen()) {

		// Limpiamos la ventana
		App.clear();
		// Dibujamos la escena
		App.draw(fondo);
		// Mostramos la ventana
		App.display();
	}
	return 0;
}
