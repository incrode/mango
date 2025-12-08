#ifndef __MANGO_VIEW_HPP__
#define __MANGO_VIEW_HPP__

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

namespace mango
{

	class View
	{
		protected:
			SDL_Rect rect;
			SDL_Rect renderRect;
			SDL_Color bgColor;
			SDL_Color borderColor;
			bool bordered = false;

			View *parent;
			std::vector<View*> children;

		public:
			int paddingL = 0;
			int paddingT = 0;
			int paddingR = 0;
			int paddingB = 0;
			
			View(SDL_Color bgColor,SDL_Rect rect);
			SDL_Rect get_rect();
			SDL_Rect get_render_rect();
			void set_x(uint32_t x);
			void set_y(uint32_t y);
			void set_border(SDL_Color borderColor);
			void remove_border();
			void set_parent(View *view);
			View* get_parent();
			void add_child(View *view);
			int32_t get_child_index(View *view);
			void remove_child(uint32_t index);
			void padding(uint32_t p);
			void padding_block(uint32_t p);
			void padding_inline(uint32_t p);
			void render(SDL_Renderer *ren);
	};


} // namespace mango

#endif
