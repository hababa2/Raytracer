#include "Renderer.h"
#include "Framebuffer.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);
	
	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({ 0, 0, 0, 0 });

		//framebuffer->DrawRect(rand() % framebuffer->width - 100, rand() % framebuffer->height - 100, 
		//	rand() % framebuffer->width, rand() % framebuffer->height, {0, 255, 0, 255});
		//
		//for (int i = 0; i < 50; ++i)
		//{
		//	framebuffer->DrawLine(framebuffer->width >> 1, framebuffer->height >> 1, 
		//		rand() % framebuffer->width, rand() % framebuffer->height, { 0, 0, 255, 255 });
		//}

		framebuffer->DrawSimpleCurve(200, 200, 300, 100, 2, {255, 255, 255, 255});
		framebuffer->DrawQuadCurve(200, 200, 300, 100, 400, 200, 50, {255, 255, 255, 255});

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
