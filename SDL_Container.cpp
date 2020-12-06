class SDL_Container
{
    private:
        static SDL_Window* window;
        static SDL_Renderer* renderer;
        static SDL_Texture* texture;
        static short width;
        static short height;


    public:
        static bool quit_event;
        
        static void init(int W, int H);
        static void updateFrame( unsigned char *pixels);
        static void quit();
};

bool SDL_Container::quit_event = false;
SDL_Window* SDL_Container::window;
SDL_Renderer* SDL_Container::renderer;
SDL_Texture* SDL_Container::texture;
short SDL_Container::width;
short SDL_Container::height;

void SDL_Container::init(int W, int H, std::string window_name)
{
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Container::width = W; SDL_Container::height = H;
    SDL_Container::window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
    SDL_Container::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Container::texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W, H);
}

void SDL_Container::updateFrame( unsigned char  *pixels)
{
    SDL_SetRenderDrawColor( SDL_Container::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
    SDL_RenderClear( SDL_Container::renderer );

    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        if( SDL_QUIT == event.type )
        {
            SDL_Container::quit_event = true;
            break;
        }
    }

    SDL_UpdateTexture(SDL_Container::texture, NULL, pixels, SDL_Container::width * 4);
    SDL_RenderCopy( SDL_Container::renderer, SDL_Container::texture, NULL, NULL );
    SDL_RenderPresent( SDL_Container::renderer );
}


void SDL_Container::quit()
{
    SDL_DestroyRenderer( SDL_Container::renderer );
    SDL_DestroyWindow( SDL_Container::window );
    SDL_Quit();
}
