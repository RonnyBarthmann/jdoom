struct tex {
  int used;
  int width;
  int height;
  int *mem;
  int x;
  int y;
};
struct tex ImageMemory[255];

int DummyTex(int tex, int size, int c1, int c2) {
  fprintf(stderr, "Create Texture ... ");
  ImageMemory[tex].used = 0;
  ImageMemory[tex].mem = malloc(size * size * sizeof(int));
  if ( ImageMemory[tex].mem == NULL ) {
    fprintf(stderr, "failed\n");
    return 0;
  } else {
    ImageMemory[tex].used = 1;
    ImageMemory[tex].width = size;
    ImageMemory[tex].height = size;
    for ( int y = 0; y < size/2; y++) {
      for ( int x = 0; x < size/2 ; x++) {
        int *address = ImageMemory[tex].mem;
        address + ( ImageMemory[tex].width * y * 4 );
        address + ( x * 4 );
        *address = c1;
      }
    }
    for ( int y = size/2; y < size; y++) {
      for ( int x = size/2; x < size ; x++) {
        int *address = ImageMemory[tex].mem;
        address + ( ImageMemory[tex].width * y * 4 );
        address + ( x * 4 );
        *address = c1;
      }
    }
    for ( int y = 0; y < size/2; y++) {
      for ( int x = size/2; x < size ; x++) {
        int *address = ImageMemory[tex].mem;
        address + ( ImageMemory[tex].width * y * 4 );
        address + ( x * 4 );
        *address = c2;
      }
    }
    for ( int y = size/2; y < size; y++) {
      for ( int x = 0; x < size/2 ; x++) {
        int *address = ImageMemory[tex].mem;
        address + ( ImageMemory[tex].width * y * 4 );
        address + ( x * 4 );
        *address = c2;
      }
    }
    ImageMemory[tex].x = size/2;
    ImageMemory[tex].y = size;
    fprintf(stderr, "done\n");
    return 1;
  }
};
