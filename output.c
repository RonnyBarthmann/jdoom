int initOutput(int output) {
  if(SDL_Init(SDL_INIT_VIDEO) != -1) {
    fprintf(stderr, "init SDL successful");
    fprintf(stderr, "\n");
    return 1;
  } else {
    fprintf(stderr, "Cannot init SDL > ");
    fprintf(stderr, SDL_GetError());
    fprintf(stderr, "\n");
    return 0;
  };
}

int openOutput(int output, int width, int height) {
  SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, 0);
  if(screen)
  {
    SDL_WM_SetCaption("yDOOM", "yDOOM");
    fprintf(stderr, "open SDL window successful");
    fprintf(stderr, "\n");
    return 1;
  } else {
    fprintf(stderr, "Cannot create SDL window > ");
    fprintf(stderr, SDL_GetError());
    fprintf(stderr, "\n");
    return 0;
  }
}

