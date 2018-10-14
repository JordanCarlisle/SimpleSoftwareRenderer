#include "SDLRenderer.h"
#include "v2.h"

int main(int argc, char* argv[])
{
	SDLWindow window(1024, 768);
	window.init();

	SDLRenderer renderer(window);

	float x = .0f;

	while (window.running())
	{
		x += 1;
		renderer.clear();

		renderer.drawFillTriangle(v2(500.0f, 200.0f), v2(700.0f, 500.0f), v2(300.0f, 500.0f), v4(0.0f, 1.0f, 0.0f, 1.0f));
		renderer.drawFillCircle(v2(500.0f, 200.0f), 5.0f, v4(1.0f, 0.0f, 0.0f, 1.0f));
		renderer.drawFillCircle(v2(700.0f, 500.0f), 5.0f, v4(1.0f, 0.0f, 0.0f, 1.0f));
		renderer.drawFillCircle(v2(300.0f, 500.0f), 5.0f, v4(1.0f, 0.0f, 0.0f, 1.0f));
		renderer.present();

		window.update();
	}

	return 0;
}