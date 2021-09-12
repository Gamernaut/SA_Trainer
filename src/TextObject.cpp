#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "TextObject.h"

TextObject::TextObject(SDL_Renderer* renderer, std::string fontname, int fontSize) {
	// Store renderer in object
	myRenderer = renderer;
	fontSize = fontSize;

	font = TTF_OpenFont(fontName.c_str(), fontSize);
	if (!font) {
		std::cerr << "Error opening font Renderer" << std::endl;
		return;
	}

}


TextObject::~TextObject() {
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void TextObject::draw(std::string text, SDL_Color textColour, int xPosition, int yPosition) {
	textSurface = TTF_RenderText_Blended(font, text.c_str(), textColour);
	textTexture = SDL_CreateTextureFromSurface(myRenderer, textSurface);

	SDL_Rect textDestinationRectangle = {xPosition, yPosition, textSurface->w, textSurface->h};

	SDL_RenderCopy(myRenderer, textTexture, NULL, &textDestinationRectangle);
}

void TextObject::update() {

}