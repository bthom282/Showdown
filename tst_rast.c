#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "BITMAPS.H"
#include "splash.h"

int main()
{
  char *base = Physbase(); 
  
  /* Test clear_screen*/
  clear_screen((UINT32 *)base);

  Cnecin();
  /* Test plot_bitmap_16 */

  plot_bitmap_16((UINT16 *)base, 10, 10, cowboy_lives, BITMAP_HEIGHT);

  Cnecin();  

  /* Test clear_bitmap_16*/
  clear_bitmap_16((UINT16 *)base, 10, 10, (UINT16 *)blank, BITMAP_HEIGHT);

  Cnecin();

  /*  Test plot_bitmap_32*/
  plot_bitmap_32((UINT32 *)base, 20, 20, cactus_bitmap, BITMAP_32_HEIGHT);

  Cnecin();

  /* Test clear_bitmap_32*/
  clear_bitmap_32((UINT32 *)base, 20, 20, blank, BITMAP_32_HEIGHT);

  Cnecin();

  /* Test plot_bitmap_8*/
  plot_bitmap_8((UINT8 *)base, 30, 30, bullet_bitmap, BITMAP_8_HEIGHT);

  Cnecin();

  /* Test clear_bitmap_8*/
  clear_bitmap_8((UINT8 *)base, 30, 30, bullet_blank, BITMAP_8_HEIGHT);

  Cnecin();

  /* Test plot_char*/
  plot_char((UINT8 *)base, 40, 40, 'a');

  Cnecin();

  /*Test fill_screen */
  fill_screen((UINT32 *)base, 0xFFFFFFFF);

  Cnecin();

  /* Test fill_rec*/
  fill_rec((UINT16 *)base, 50, 50, 10, 10);

  Cnecin();

  /* Test clear_rec*/
  clear_rec((UINT32 *)base, 50, 50, 10, 10);

  Cnecin();

  /*Test print_message*/
  print_message((UINT8 *)base, (UINT8 *)"LIVES", 60, 60);

  Cnecin();

  /* Test plot_splash*/
  plot_splash((UINT32 *)base, SCREEN_HEIGHT, splash_bitmap);

  /* Test plot_bitmap_64
  printf("Testing plot_bitmap_64...\n");
  UINT32 bitmap64[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
  plot_bitmap_64((UINT32 *)base, 70, 70, bitmap64, 4);*/

  /* Test clear_bitmap_64
  printf("Testing clear_bitmap_64...\n");
  clear_bitmap_64((UINT32 *)base, 70, 70, bitmap64, 4);*/

return 0;
}
