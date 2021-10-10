#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
#include "Main.h"
#include "TextObject.h"

using namespace cpv;

TextObject::TextObject(SDL_Renderer* renderer, std::string font_name, int font_size = 16) {
	// Store renderer in object
	myRenderer_ = renderer;

	font_ = TTF_OpenFont(font_name.c_str(), font_size);
	if (!font_) {
		std::cout << "Error opening font " << font_name << SDL_GetError() << " in TextObject::TextObject()" << std::endl;
		return;
	}
}

TextObject::~TextObject() {
	SDL_FreeSurface(text_surface_);
	SDL_DestroyTexture(text_texture_);
}

void TextObject::Draw(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int x_position, int y_position) {
	text_surface_ = TTF_RenderText_Blended(font_, text.c_str(), text_colour);
	text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

	SDL_Rect textDestinationRectangle = { x_position, y_position, text_surface_->w, text_surface_->h };

	SDL_RenderCopy(renderer, text_texture_, NULL, &textDestinationRectangle);
}

void TextObject::DrawCenteredText(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int y_position) {
	text_surface_ = TTF_RenderText_Blended(font_, text.c_str(), text_colour);
	text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

	SDL_Rect textDestinationRectangle = { (kWindowWidth / 2) - (text_surface_->w / 2) , y_position, text_surface_->w , text_surface_->h };

	SDL_RenderCopy(renderer, text_texture_, NULL, &textDestinationRectangle);
}