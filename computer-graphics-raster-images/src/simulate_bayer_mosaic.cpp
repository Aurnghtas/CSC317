#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);

  /* GBRG bayer pattern 
   * treat GBRG as one group - 4 pixels
   * GBGBGB
   * RGRGRG
   * GBGBGB 
   * RGRGRG
   * finish one group, skips two columns until reach the end, and then jumps to +2 rows */

  int i, j;
  for (i=0; i<height; i+=2) {
    for (j=0; j<width; j+=2) {
      bayer[i*width+j] = rgb[1+3*(i*width+j)];  // green

      /* if j is the last column, we cannot access the +1 column */
      if(j+1 < width) {
        bayer[i*width+j+1] = rgb[2+3*(i*width+j+1)];  // blue
      }

      /* if i is the last row, then we cannot access the following +1 row */
      if(i+1 < height) {
        bayer[(i+1)*width+j] = rgb[0+3*((i+1)*width+j)];  // red

        /* if j is the last column, we cannot access the +1 column */
        if(j+1 < width) {
          bayer[(i+1)*width+j+1] = rgb[1+3*((i+1)*width+j+1)];  // green
        }
      }
    }
  }

}
