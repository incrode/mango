

// Tab starts here


Tab::Tab(void* (*fn)(void*), const char *file_path): View({0},{0}),
	btn()
{
	this->btn.attach_click_listener(fn);
	this->btn.click_param_data = this;

	this->setSavedState(false);
}

/**
 * Sets opened file path for the tab, pass NULL for "Unnamed" file
 * **/
void Tab::set_file_path(const char *file_path)
{
	this->temp_file = true;
	this->file_path = file_path;
}

string Tab::get_file_path()
{
	return file_path;
}

void Tab::setSavedState(bool saved)
{
	if (!saved) 
	{
		btn.set_border({255,255,0,255});
		return;
	}

	btn.set_border({0});
}

void Tab::process_events(SDL_Event *e)
{
	this->btn.process_events(e);
}

void Tab::render(SDL_Renderer *ren)
{
	this->btn.render(ren);
}

// Tab ends here

// TabNav starts here

SDL_Color tabnav_bg = {60,60,60,255};

SDL_Rect tabnav_rect = {
	0,
	header_rect.y + header_rect.h + (header_padding),
	WINDOW_WIDTH,
	20
};

int tab_btn_gap = 20;

TabNav* TabNav::tabnav = NULL;

TabNav::TabNav(SDL_Renderer *ren):View(tabnav_bg,tabnav_rect)
{
	Button untitled_tab{
		"Unnamed",
			ren,
			{tab_btn_gap,tabnav_rect.y,100,20},
			FONT_PATH,
			button_bg,
			button_fg,
			0
	};
	this->tabs.push_back(Tab{untitled_tab,select_tab});
}

void TabNav::process_events(SDL_Event *e)
{
	for (Tab tab: tabs)
		tab.process_events(e);
}

void TabNav::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);

	for (Tab tab: tabs)
	{
		tab.render(ren);
	}
}

TabNav* TabNav::get(SDL_Renderer *ren)
{
	if (TabNav::tabnav == NULL && ren != NULL)
		tabnav = new TabNav(ren);

	if (TabNav::tabnav == NULL) cerr << "Unconstructed TabNav!" << endl;
	return tabnav;
}

// TabNav ends here
