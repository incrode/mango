

	class Tab: public View
	{
		private:
			Button btn;
			string file_path = "";
			bool temp_file = false;

		public:
			Tab(void* (*fn)(void*));
			void set_file_path(const char *file_path);
			string get_file_path(void);
			void setSavedState(bool saved);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
	};
	class TabNav: public View
	{
		private:
			static TabNav *tabnav;
			size_t current_active_tab = 0;
			vector<Tab> tabs;

			TabNav(SDL_Renderer *ren);
		public:
			static TabNav* get(SDL_Renderer *ren);
			void process_events(SDL_Event *e);
			void render(SDL_Renderer *ren);
			friend void* new_file_fn(void*);
			friend void* open_file_fn(void*);
			friend void* save_file_fn(void*);
			friend void* close_file_fn(void*);
			friend void* select_tab(void*);
	};
