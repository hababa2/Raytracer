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
	image->Load("../resources/flower.bmp");
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
		
		//framebuffer->DrawRect(300, 500, 200, 50, { 255, 255, 255, 255 });
		//framebuffer->DrawLine(100, 200, 300, 50, { 255, 255, 255, 255 });
		//framebuffer->DrawTriangle(650, 550, 700, 500, 750, 550, { 255, 255, 255, 255 });
		//framebuffer->DrawSimpleCurve(200, 500, 100, 450, 2, {255, 255, 255, 255});
		//framebuffer->DrawQuadCurve(200, 200, 300, 100, 400, 200, 100, { 255, 255, 255, 255 });
		//framebuffer->DrawCubeCurve(400, 400, 500, 300, 500, 450, 600, 300, 30, {255, 255, 255, 255});
		//framebuffer->DrawCircle(690, 390, 100, { 255, 255, 255, 255 });

		framebuffer->DrawImage(300, 50, image.get());

		std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
		PostProcess::BoxBlur(image1->colorBuffer);
		framebuffer->DrawImage(0, 300, image1.get());

		std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
		PostProcess::GaussianBlur(image2->colorBuffer);
		framebuffer->DrawImage(200, 300, image2.get());

		std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
		PostProcess::Sharpen(image3->colorBuffer);
		framebuffer->DrawImage(400, 300, image3.get());

		std::unique_ptr<Image> image4 = std::make_unique<Image>(*image.get());
		PostProcess::Monochrome(image4->colorBuffer);
		PostProcess::Edge(image4->colorBuffer, 0);
		framebuffer->DrawImage(600, 300, image4.get());

		//PostProcess::Invert(framebuffer->colorBuffer);
		//PostProcess::Monochrome(framebuffer->colorBuffer);
		//PostProcess::ColorBalance(framebuffer->colorBuffer, 0, 0, 100);
		//PostProcess::Brightness(framebuffer->colorBuffer, -100);
		//PostProcess::Noise(framebuffer->colorBuffer, 100);
		//PostProcess::Threshold(framebuffer->colorBuffer, 200);
		//PostProcess::BGR(framebuffer->colorBuffer);

		framebuffer->Update();

		renderer->CopyBuffer(framebuffer.get());
		renderer->Present();
	}

	SDL_Quit();

	return 0;
}
