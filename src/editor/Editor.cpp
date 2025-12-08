
#include "Editor.hpp"
#include "render/Render.hpp"
#include "render/Window.hpp"
#include "ui/TextView.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <ostream>
#include <stdio.h>
#include <string>
#include <fstream>

namespace mango
{

// Editor starts here
SDL_Color editor_bg = {120,30,30,255};
SDL_Rect editor_rect = {
	20,
	tabnav_rect.y + tabnav_rect.h + 20,
	WINDOW_WIDTH,
	WINDOW_HEIGHT - (tabnav_rect.y + tabnav_rect.h)
};

Editor* Editor::editor = NULL;

Editor::Editor(SDL_Renderer *ren):View(editor_bg,editor_rect)
{
	this->ren = ren;
	this->editor_font = LoadFont(FONT_PATH, 30.0*0.75);
	this->fgColor = {255,255,255,255};
	this->cursor_pos = {0,0};
	this->cursor_rect = {
		line_rects_width + 10,
		editor_rect.y,
		5,
		line_ht
	};
	this->set_border({200,200,100,255});
	this->padding(20);
	this->start_edit();
	this->add_line(current_active_line);
}

void Editor::start_edit()
{
	SDL_StartTextInput();
}

void Editor::stop_edit()
{
	SDL_StopTextInput();
}

void Editor::add_line(int line_before) // 0-indexed line before
{
	SDL_Rect line_rect = {
		10,
		editor_rect.y + (line_before)*line_ht,
		line_rects_width,
		line_ht
	};

	line_nos.insert(line_nos.begin() + line_before,TextView{
			to_string(line_before+1).c_str(),
			FONT_PATH,
			ren,
			editor_bg,
			{255,255,255,255},
			line_rect,
			TEXT_ALIGN_CENTER
	});

	for (int i = line_before+1; i < line_nos.size(); i++)
	{
		line_nos[i] = TextView {
			to_string(i+1).c_str(),
				FONT_PATH,
				ren,
				editor_bg,
				{255,255,255,255},
				line_rect,
				TEXT_ALIGN_CENTER
		};
	}

	for (int i = 0; i < line_nos.size(); i++)
		line_nos[i].set_y(editor_rect.y + i*line_ht + scrollYVal);

	this->current_active_line = line_before;
}

void Editor::remove_line(int line_no) // 0-indexed line no.
{
	line_nos.erase(line_nos.begin() + line_no);
}

string Editor::get_text()
{
	return this->text;
}

void Editor::set_text(string s)
{
	this->text = s;
}

void Editor::scrollY(int dist)
{
	if (line_nos.size() == 0) return;
	if (line_nos[0].get_rect().y >= editor_rect.y && dist > 0) 
		return;
	if (line_nos[line_nos.size()-1].get_rect().y +  line_nos[line_nos.size()-1].get_rect().h <= editor_rect.y + editor_rect.h - 40 && dist < 0) 
		return;
	
	dist *= scrollSpeed;

	for (TextView &tv: line_nos)
	{
		tv.set_y(tv.get_rect().y + dist);
	}
	cursor_rect.y += dist;

	scrollYVal += dist;
}

void Editor::scrollX(int dist)
{
	dist *= scrollSpeed;
	for (TextView &tv: line_nos)
	{
		tv.set_x(tv.get_text_rect().x + dist);
	}

}

void Editor::process_events(SDL_Event *e)
{
    // TODO: Header association !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Header *header = Header::get(NULL);
	// if (header->popInput_active) return;

	if (e->type == SDL_KEYDOWN)
	{
		int ch = e->key.keysym.sym;
		size_t ch_pos = string::npos;

		if (ch == SDLK_KP_ENTER || ch == SDLK_RETURN)
		{
			this->add_line(this->current_active_line);
		} else if ((ch_pos = allowed_char.find(ch)) != string::npos)
		{
			if (pending_shift)
			{
				ch = allowed_shift_char[ch_pos];
			}
			text.push_back(ch);
			cursor_pos.x++;
		} else if (ch == SDLK_UP)
		{
			if (this->current_active_line > 0) current_active_line--;
			this->scrollY(line_ht/scrollSpeed);
		} else if (ch == SDLK_DOWN)
		{
			if (this->current_active_line < line_nos.size()-1) current_active_line++;
			this->scrollY(-line_ht/scrollSpeed);
		}else if(ch == SDLK_LSHIFT || ch == SDLK_RSHIFT)
		{
			pending_shift = true;
		}else if (ch == SDLK_LEFT)
		{
		} else if (ch == SDLK_RIGHT)
		{
		} else if (ch == SDLK_HOME)
		{
		} else if (ch == SDLK_END)
		{
		}
	}else if (e->type == SDL_KEYUP) {
		if (e->key.keysym.sym == SDLK_LSHIFT || e->key.keysym.sym == SDLK_RSHIFT)
		{
			pending_shift = false;
		}
	}else if (e->type == SDL_MOUSEWHEEL) {
		scrollY(e->wheel.y);
		scrollX(e->wheel.x);
	}
}

/**
 * Combine lines and stores them in {text}.
 * */
void Editor::parse_text()
{
	
}

/**
 * Splits lines and renders them.
 * */
void Editor::render_text(SDL_Renderer *ren)
{
	SDL_Texture *t = TextView::LoadText(text.c_str(), editor_font, ren,fgColor);
	SDL_Rect r = {30,editor_rect.y,WINDOW_WIDTH,30};

	SDL_RenderCopy(ren,t, NULL, &r);
}

/**
 * Renders {Editor} object.
 * **/
void Editor::render(SDL_Renderer *ren)
{
	this->cursor_rect.y = editor_rect.y + line_ht*(this->current_active_line) + this->scrollYVal;
	((View*)this)->render(ren);
	// this->render_text(ren);
	for(int i = 0; i < line_nos.size(); i++)
	{
		line_nos[i].render(ren);
	}

	int time = SDL_GetTicks();

	if (time - prev_time > 600)
	{
		if (cursor_opacity == 255)
			cursor_opacity = 0;
		else 
			cursor_opacity = 255;

		prev_time = time;
	}

	//SDL_SetRenderDrawColor(ren, fgColor.r, fgColor.g, fgColor.b, cursor_opacity);
	SDL_SetRenderDrawColor(ren, fgColor.r, fgColor.g, fgColor.b, 255);
	SDL_RenderFillRect(ren,&cursor_rect);
}

/**
 * Singleton getter {Editor} class.
 * **/
Editor* Editor::get(SDL_Renderer *ren)
{
	if (editor == NULL && ren != NULL)
		editor = new Editor(ren);

	return editor;
}
// Editor ends here

} // namespace mango