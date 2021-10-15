#include "Renderer.h"
#include "Framebuffer.h"
#include "Image.h"
#include "PostProcessing.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);

	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	std::unique_ptr<Image> image = std::make_unique<Image>();
	image->Load("../resources/cat.bmp");
	image->Flip();
	
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
		
		framebuffer->DrawRect(300, 500, 200, 50, { 255, 255, 255, 255 });
		framebuffer->DrawLine(100, 200, 300, 50, { 255, 255, 255, 255 });
		framebuffer->DrawTriangle(650, 550, 700, 500, 750, 550, { 255, 255, 255, 255 });
		framebuffer->DrawSimpleCurve(200, 500, 100, 450, 2, {255, 255, 255, 255});
		framebuffer->DrawQuadCurve(200, 200, 300, 100, 400, 200, 100, { 255, 255, 255, 255 });
		framebuffer->DrawCubeCurve(400, 400, 500, 300, 500, 450, 600, 300, 30, {255, 255, 255, 255});
		framebuffer->DrawCircle(500, 300, 50, { 255, 255, 255, 255 });

		framebuffer->DrawImage(450, 10, image.get());

		PostProcess::Invert(framebuffer->colorBuffer);
		//PostProcess::Monochrome(framebuffer->colorBuffer);
		//PostProcess::ColorBalance(framebuffer->colorBuffer, 0, 0, 100);
		//PostProcess::Brightness(framebuffer->colorBuffer, 100);
		//PostProcess::Threshold(framebuffer->colorBuffer, 200);
		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
