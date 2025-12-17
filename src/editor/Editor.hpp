#pragma once

#include <cstdio>
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "ui/TextView.hpp"
#include "ui/TextInput.hpp"
#include "ui/View.hpp"
#include "ui/Button.hpp"
#include <vector>

#define FONT_PATH "./font/FiraMonoNerdFontMono-Medium.otf"

using namespace std;

namespace mango
{	
	class Editor: public View
	{
		private:
			static Editor *editor;
			SDL_Color fgColor;
			SDL_Rect cursor_rect;
			SDL_Point cursor_pos;
			uint8_t cursor_opacity = 255;
			int prev_time = 0;
			size_t current_active_line = 0;
			size_t current_char_pos = 0;
			int scrollYVal = 0;
			int scrollXVal = 0;
			vector<TextView> line_nos;
			vector<SDL_Rect> text_rects;
			vector<string> str_chunks;
			TTF_Font *editor_font = NULL;
			string text = "Hello,World";
			uint32_t text_size = 24;
			SDL_Renderer *ren = NULL;
			const int scrollSpeed = 10;
			const int line_ht = 30;
			const int line_rects_width = 50;
			const string allowed_char = "1234567890abcdefghijklmnopqrstuvwxyz`-=[]\\;',./ ";
			const string allowed_shift_char = "!@#$%^&*()ABCDEFGHIJKLMNOPQRSTUVWXYZ~_+{}|:\"<>? ";
			bool pending_shift = false;
			Editor(SDL_Renderer *ren);
		public:

			bool keydown = false;

			int cursorA = 255;
			uint32_t lp = 0;
			uint32_t cp = 0;

			bool editing = false;

			static Editor* get(SDL_Renderer *ren);
			void start_edit();
			void stop_edit();
			void add_line(int line_before);
			void remove_line(int line_no);
			string get_text();
			void set_text(string s);
			void scrollY(int dist);
			void scrollX(int dist);
			void process_events(SDL_Event *e);
			void parse_text();
			void render_text(SDL_Renderer *ren);
			void render(SDL_Renderer*);
	};

} // namespace mango

