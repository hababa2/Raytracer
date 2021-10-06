#include "Framebuffer.h"

Framebuffer::Framebuffer(Renderer* renderer, int width, int height)
{
    this->width = width;
    this->height = height;

    texture = SDL_CreateTexture(renderer->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    pitch = width * sizeof(color_t);
    buffer = new uint8_t[pitch * height];
}

Framebuffer::~Framebuffer()
{
    SDL_DestroyTexture(texture);
    delete[] buffer;
}

void Framebuffer::Update()
{
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
}

void Framebuffer::Clear(const color_t& color)
{
    for (int i = 0; i < pitch * height;)
    {
        buffer[i++] = color.r;
        buffer[i++] = color.g;
        buffer[i++] = color.b;
        buffer[i++] = color.a;
    }
}

void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
    int index = x * sizeof(color_t) + y * pitch;

    if ((Uint32)index < pitch * height)
    {
        buffer[index++] = color.r;
        buffer[index++] = color.g;
        buffer[index++] = color.b;
        buffer[index++] = color.a;
    }
}

void Framebuffer::DrawRect(int x, int y, int rect_width, int rect_height, const color_t& color)
{
    if (x < 0) { x = 0; }
    if (y < 0) { y = 0; }

    for (int sy = y * pitch; sy < (y + rect_height) * pitch && sy < height * pitch; sy += pitch)
    {
        for (int sx = x * sizeof(color_t); sx < (x + rect_width) * sizeof(color_t) && sx < width * sizeof(color_t);)
        {
            buffer[sx++ + sy] = color.r;
            buffer[sx++ + sy] = color.g;
            buffer[sx++ + sy] = color.b;
            buffer[sx++ + sy] = color.a;
        }
    }
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{

}

void Framebuffer::DrawCircle(int x, int y, int radius, const color_t& color)
{

}
