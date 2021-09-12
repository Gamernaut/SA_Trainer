#ifndef TESTOBJECT_H
#define TESTOBJECT_H


#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_TTF.h>
#include <iostream>

class TextObject
{
private:
	std::string fontName;
	int fontSize = 16;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	SDL_Renderer* myRenderer;
	TTF_Font* font = nullptr;

public:


private:


public:
	TextObject(SDL_Renderer* renderer, std::string fontname, int fontSize);
	~TextObject();
	void draw(std::string text, SDL_Color colour, int xPos, int yPos);
	void update();

};

#endif	// TESTOBJECT_H