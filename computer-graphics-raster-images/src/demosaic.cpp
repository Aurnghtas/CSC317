#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);

   /* 
   * GBGBGB G
   * RGRGRG R
   * GBGBGB G
   * RGRGRG R
   * 
   * GBGBGB G
   * 
   * coordinate for red have odd row and even column
   * coordinate for green are always divisible by 2
   * other coordinate are for blue
   */

  double red, green, blue;

  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      red = 0;
      green = 0;
      blue = 0;

      /* leave the outmost hollow rectangle for now */
      if(i!=0 && i!=height-1 && j!=0 && j!=width-1) {

        /* current pixel is red */
        if((i%2==1) && (j%2==0)) {
          red = bayer[i*width+j];
          /* average up, down, left, right */
          green = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j] + bayer[i*width+j-1] + bayer[i*width+j+1])/4;
          /* average top left/right, bottom left/right */
          blue = (bayer[(i-1)*width+j-1] + bayer[(i-1)*width+j+1] + bayer[(i+1)*width+j-1] + bayer[(i+1)*width+j+1])/4;
        }

        /* current pixel is green */
        else if((i+j)%2==0) {
          green = bayer[i*width+j];
          if(i%2==0){
            /* average up and bottom */
            red = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j])/2;
            /* average left, right */
            blue = (bayer[i*width+j-1] + bayer[i*width+j+1])/2;
          } else {
            /* average left, right */
            red = (bayer[i*width+j-1] + bayer[i*width+j+1])/2;
            /* average up and bottom */
            blue = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j])/2;
          }
        }
        
        /* current pixel is blue */
        else {
          blue = bayer[i*width+j];
          /* average top left/right, bottom left/right */
          red = (bayer[(i-1)*width+j-1] + bayer[(i-1)*width+j+1] + bayer[(i+1)*width+j-1] + bayer[(i+1)*width+j+1])/4;
          /* average up, down, left, right */
          green = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j] + bayer[i*width+j-1] + bayer[i*width+j+1])/4;
        }

      }

       /* first or last rows is GBGBGB... */
       else if (i==0 || (i==height-1&&(height%2==1))) {
         // first element in first and last row
        if(j==0){
          green = bayer[i*width+j];
           blue = bayer[i*width+j+1];
           if(i==0) {
             red = bayer[(i+1)*width+j];
           } else {
             red = bayer[(i-1)*width+j];
           }

         // last element in first and last row
         } else if (j==width-1) {
           // last element is blue
          if(width%2==0) {
            blue = bayer[i*width+j];
            if(i==0) {
              red = bayer[(i+1)*width+j-1];
              green = (bayer[i*width+j-1] + bayer[(i+1)*width+j])/2;
            } else {
              red = bayer[(i-1)*width+j-1];
              green = (bayer[i*width+j-1] + bayer[(i-1)*width+j])/2;
            }
          }
          // last element is green
          else {
            green = bayer[i*width+j];
            blue = bayer[i*width+j-1];
            if(i==0) {
              red = bayer[(i+1)*width+j];
            } else {
              red = bayer[(i-1)*width+j];
            }
          }
        } 
        // normal case
        else {
          // green
          if(j%2==0) {
            green = bayer[i*width+j];
            blue = (bayer[i*width+j-1] + bayer[i*width+j+1])/2;
            if(i==0) {
              red = bayer[(i+1)*width+j];
            } else {
              red = bayer[(i-1)*width+j];
            }
          } 
          // blue
          else {
            blue = bayer[i*width+j];
            if(i==0) { 
              green = (bayer[(i+1)*width+j] + bayer[i*width+j-1] + bayer[i*width+j+1])/3;
              red = (bayer[(i+1)*width+j-1] + bayer[(i+1)*width+j+1])/2;
            } else {
              green = (bayer[(i-1)*width+j] + bayer[i*width+j-1] + bayer[i*width+j+1])/3;
              red = (bayer[(i-1)*width+j-1] + bayer[(i-1)*width+j+1])/2;
            }
          }
        }
      }

      /* last row is RGRGRG */
      else if(i==height-1&&(height%2==0)) {
        // first element in last row
        if(j==0) {
          red = bayer[i*width+j];
          green = bayer[i*width+j+1];
          blue = bayer[(i-1)*width+j+1];
        } else if(j==width-1) {
          // last element is green;
          if(width%2==0) {
            green = bayer[i*width+j];
            red = bayer[i*width+j-1];
            blue = bayer[(i-1)*width+j];
          } 
          // last element is red
          else {
            red = bayer[i*width+j];
            green = (bayer[i*width+j-1]+bayer[(i-1)*width+j])/2;
            blue = bayer[(i-1)*width+j-1];
          }
        } else {
           // red
          if(j%2==0) {
            red = bayer[i*width+j];
            green = (bayer[(i-1)*width+j] + bayer[i*width+j-1] + bayer[i*width+j+1])/3;
            blue = (bayer[(i-1)*width+j-1] + bayer[(i-1)*width+j+1])/2;
          } 
          // green
          else {
            green = bayer[i*width+j];
            blue = bayer[(i-1)*width+j];
            red = (bayer[i*width+j-1] + bayer[i*width+j+1])/2;
          }
        }
      }

      /* first column general case */ 
      else if ((i!=0 && i!=height-1) && j==0) {
        // red
        if(i%2==1) {
          red = bayer[i*width+j];
          green = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j] + bayer[i*width+j+1])/3;
          blue = (bayer[(i-1)*width+j+1] + bayer[(i+1)*width+j+1])/2;
        } 
        // green
        else {
          green = bayer[i*width+j];
          red = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j])/2;
          blue = bayer[i*width+j+1];
        }
      }

      /* last column is GRGR general case */
      else if ( (i!=0 && i!=height-1) && j==width-1 && width%2==1) {
        // red
        if(i%2==1) {
          red = bayer[i*width+j];
          green = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j] + bayer[i*width+j-1])/3;
          blue = (bayer[(i-1)*width+j-1] + bayer[(i+1)*width+j-1])/2;
        } 
        // green
        else {
          green = bayer[i*width+j];
          red = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j])/2;
          blue = bayer[i*width+j-1];
        }
      }

      /* last column is BGBG general case */
      else if ( (i!=0 && i!=height-1) && j==width-1 && width%2==1) {
        // green
        if(i%2==1) {
          green = bayer[i*width+j];
          red = bayer[i*width+j-1];
          blue = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j])/2;
        } 
        // blue
        else {
          blue = bayer[i*width+j];
          green = (bayer[(i-1)*width+j] + bayer[(i+1)*width+j] + bayer[i*width+j-1])/3;
          red = (bayer[(i-1)*width+j-1] + bayer[(i+1)*width+j-1])/2;
        }
      }

      rgb[0+3*(i*width+j)] = red;
      rgb[1+3*(i*width+j)] = green;
      rgb[2+3*(i*width+j)] = blue;
    }
  }

}
