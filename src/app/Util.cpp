
// Global config
SDL_Color button_bg = {70,70,70,255};
SDL_Color button_fg = {255,255,255,255};

const char *curr_op_fp = NULL;

// Header button functions


void* new_file_fn(void* data)
{
	extern int tab_btn_gap;
	extern SDL_Rect tabnav_rect;
	SDL_Renderer *ren = (SDL_Renderer*)data;
	TabNav *tabnav = TabNav::get(NULL);

	cout << tabnav->tabs.size() << endl; 
	

	Tab tab = {btn,select_tab};
	tabnav->tabs.push_back(tab);

	return NULL;
}

/**
 * Writes the {Editor::text} to {Tab::file_path}
 * **/
void* save_file_fn(void*)
{
	TabNav *tabnav = TabNav::get(NULL);
	int active_tab = tabnav->current_active_tab;

	string file_path = tabnav->tabs[active_tab].get_file_path();

	if (file_path.size() == 0)
	{
	}

	string text = Editor::get(NULL)->get_text();

	ofstream outFile(file_path.c_str());

	if (!outFile.is_open()) 
	{
		cerr << "Couldn't open saving file " << file_path << endl;
		return NULL;
	}

	outFile << text;
	outFile.close();
	
	tabnav->tabs[active_tab].setSavedState(true);
	//tabnav
	return NULL;
}

/**
 * Recives file path and sets up the editor for use.
 * **/
void* open_file_fn(void *data)
{
	extern int tab_btn_gap;
	extern SDL_Rect tabnav_rect;
	SDL_Renderer *ren = (SDL_Renderer*)data;
	TabNav *tabnav = TabNav::get(NULL);
	Header *header = Header::get(NULL);

	header->popInput_active = true;

	
	return NULL;
}

void* close_file_fn(void*)
{
	TabNav *tabnav = TabNav::get(NULL);

	return NULL;
}

// tab button functions

void* select_tab(void* data)
{
	Tab *curr_tab = (Tab*) data;
	TabNav *tb = TabNav::get(NULL);

	return NULL;
}