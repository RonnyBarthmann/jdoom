int ImageMemory[255][6]; // 0 = used
                        // 1 = width
                        // 2 = height
                        // 3 = memory-address
                        // 4 = x-pos of center
                        // 5 = y-pos of center

int DummyTex(int tex, int size, int c1, int c2) {
  fprintf(stderr, "Create Texture ... ");
  ImageMemory[tex][0] = 0;
  ImageMemory[tex][3] = malloc(size * size * sizeof(int));
  if ( ImageMemory[tex][3] == 0 ) {
    fprintf(stderr, "failed\n");
    return 0;
  } else {
    ImageMemory[tex][0] = 1;
    ImageMemory[tex][1] = size;
    ImageMemory[tex][2] = size;
    for ( int y = 0; y < size/2; y++) {
      for ( int x = 0; x < size/2 ; x++) {
        int address = ImageMemory[tex][3] + ( ImageMemory[tex][1] * y * 4 ) + ( x * 4 )
        *address = c1;
      }
    }
    ImageMemory[tex][4] = size/2;
    ImageMemory[tex][5] = size;
  return 1;
}
