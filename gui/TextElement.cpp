#include "MainDisplay.hpp"

TextElement::TextElement(const char* text, int size, SDL_Color* color)
{
	this->text = new std::string(text);
	this->size = size;
	
	if (color == NULL)
		this->color = {0xff, 0xff, 0xff};
	else
		this->color = *color;
	
	this->textSurface = this->renderText(*(this->text), size);
}

void TextElement::render(Element* parent)
{
	if (this->hidden)
		return;
	
	SDL_Rect textLocation;
	textLocation.x = this->x + parent->x;
	textLocation.y = this->y + parent->y;
	
	SDL_BlitSurface(this->textSurface, NULL, parent->window_surface, &textLocation);
}

SDL_Surface* TextElement::renderText(std::string& message, int size)
{
	std::string key = message + std::to_string(size);
	
	// try to find it in the cache first
	if (ImageCache::cache.count(key))
		return &ImageCache::cache[key];
	
	// not found, make/render it
	
	TTF_Font *font = TTF_OpenFont("./res/productsans.ttf", size);
	
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), this->color);
	
	//	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	
	// save it to the cache for later
	ImageCache::cache[key] = *surf;
	
	return surf;
}
