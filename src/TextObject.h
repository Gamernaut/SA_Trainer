#ifndef TESTOBJECT_H
#define TESTOBJECT_H

//#include <SDL.h>
//#include <SDL_Image.h>
//#include <SDL_TTF.h>
//#include <iostream>

class TextObject {
	// Attributes
protected:
	SDL_Surface* text_surface_;
	SDL_Texture* text_texture_;
	SDL_Renderer* myRenderer_;
	TTF_Font* font_ = nullptr;

public:

	// Methods
private:

public:
	TextObject(SDL_Renderer* renderer, std::string fontname, int fontSize);
	~TextObject();
	void Draw(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int x_position, int y_position);
	void DrawCenteredText(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int y_position);
};

#endif	// TESTOBJECT_H