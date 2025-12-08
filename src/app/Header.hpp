
	class PopInput: public View
	{
		private:
			TextInput inp;
			Button ok;
		public:

			PopInput(SDL_Renderer *ren,SDL_Color bgColor);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};

	class Header: public View
	{
		private:
			static Header *header;

			Button newFile;
			Button saveFile;
			Button openFile;
			Button closeFile;

			PopInput popInput;

			Header(SDL_Renderer *ren);
		public:
			bool popInput_active = false;
			static Header* get(SDL_Renderer *ren);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};
