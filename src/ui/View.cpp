#include "View.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <cassert>

namespace mango
{

View::View(SDL_Color bgColor, SDL_Rect rect)
{
	this->bgColor = bgColor;
	this->rect = rect;
	this->renderRect = rect;
}

SDL_Rect View::get_rect()
{
	return rect;
}

SDL_Rect View::get_render_rect()
{
	return renderRect;
}

void View::set_x(uint32_t x)
{
	this->rect.x = x;
}

void View::set_y(uint32_t y)
{
	this->rect.y = y;
}

void View::set_border(SDL_Color borderColor)
{
	bordered = true;
	this->borderColor = borderColor;
}

void View::remove_border()
{
	bordered = false;
}

void View::set_parent(View *view)
{
	this->parent = view;
}

View* View::get_parent()
{
	return parent;
}

void View::add_child(View *view)
{
	children.push_back(view);
}

int32_t View::get_child_index(View *view)
{
	for (int32_t i = 0; i < children.size(); i++)
	{
		if (children[i] == view) return i;
	}

	return -1;
}

void View::remove_child(uint32_t index)
{
	assert(index < children.size());
	View *view = children[index];
	view->set_parent(nullptr);
	children.erase(children.begin() + index);
}

void View::padding(uint32_t p)
{
	padding_block(p);
	padding_inline(p);
}

void View::padding_block(uint32_t p)
{
	paddingT = p;
	paddingB = p;
}

void View::padding_inline(uint32_t p)
{
	paddingL = p;
	paddingR = p;
}

void View::render(SDL_Renderer *ren)
{
	renderRect = {
		.x = rect.x - paddingL,
		.y = rect.y - paddingT,
		.w = rect.w + 2*paddingR,
		.h = rect.h + 2*paddingB
	};


	SDL_SetRenderDrawColor(ren, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	SDL_RenderFillRect(ren,&renderRect);

	if (bordered)
	{
		SDL_SetRenderDrawColor(ren,borderColor.r,borderColor.g,borderColor.b,borderColor.a);
		SDL_RenderDrawRect(ren, &renderRect);
	}
}

} // namespace mango
