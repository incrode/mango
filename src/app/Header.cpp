
// PopInput starts here

SDL_Rect popup_rect = {
	(WINDOW_WIDTH/2) - (250/2),
	(WINDOW_HEIGHT/2) - (100/2),
	250,
	100
};
SDL_Rect popup_inp_rect = {
	popup_rect.x+popup_rect.w/2-(200/2),
	popup_rect.y+20,
	200,
	25
};
SDL_Rect popup_btn_rect = {
	popup_rect.x+popup_rect.w/2-(30/2),
	popup_inp_rect.y + popup_inp_rect.h + 25,
	30,
	15
};

void* popup_btn_click(void* data)
{
	Header *header = Header::get(NULL);
	header->popInput_active = false;

	return NULL;
}

PopInput::PopInput(SDL_Renderer *ren,SDL_Color bgColor = {50,50,50,255}):
	View(bgColor,popup_rect),
	inp(FONT_PATH,popup_inp_rect,{255,255,255,255},{0,0,0,255},10),
	ok("OK",ren, popup_btn_rect,FONT_PATH,{30,30,30,255}, {255,255,255,255}, 10)
{
	this->ok.attach_click_listener(popup_btn_click);
}

void PopInput::process_events(SDL_Event *e)
{
	inp.process_events(e);
	ok.process_events(e);
}

void PopInput::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	this->inp.render(ren);
	this->ok.render(ren);
}


// PopInput ends here

// Header starts here
SDL_Color header_bg = {45,45,45,255};
int header_padding = 20;
SDL_Rect header_rect = { header_padding,header_padding,WINDOW_WIDTH,20 };

Header* Header::header = NULL;


Header::Header(SDL_Renderer *ren):
	View(header_bg,header_rect),
	popInput(ren),
	newFile("New", ren,{header_padding+0, header_rect.y, 60, 20},FONT_PATH,button_bg,button_fg, 5),
	saveFile("Save", ren, {header_padding+90,header_rect.y,60,20},FONT_PATH,button_bg,button_fg,5),
	openFile("Open",ren,{header_padding+180,header_rect.y,60,20},FONT_PATH,button_bg,button_fg,5),
	closeFile("Close",ren,{header_padding+270,header_rect.y,60,20},FONT_PATH,button_bg,button_fg,5)
{
	this->padding_block(header_padding);
	this->padding_inline(header_padding);
	this->paddingR = 0;

	this->newFile.attach_click_listener(new_file_fn);
	this->newFile.click_param_data = ren;

	this->saveFile.attach_click_listener(save_file_fn);

	this->openFile.attach_click_listener(open_file_fn);
	this->openFile.click_param_data = ren;

	this->closeFile.attach_click_listener(close_file_fn);
}

void Header::process_events(SDL_Event *e)
{
	newFile.process_events(e);
	saveFile.process_events(e);
	openFile.process_events(e);
	closeFile.process_events(e);

	if (popInput_active)
		popInput.process_events(e);
}

void Header::render(SDL_Renderer *ren)
{
	((View*)this)->render(ren);
	newFile.render(ren);
	saveFile.render(ren);
	openFile.render(ren);
	closeFile.render(ren);

	if (popInput_active)
		popInput.render(ren);
}

Header* Header::get(SDL_Renderer *ren)
{
	if (header == NULL && ren != NULL)
		header = new Header(ren);

	return header;
}
// Header ends here