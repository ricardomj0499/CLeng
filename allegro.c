#include <allegro5/allegro.h>
int main(int argc, char** argv) {
  al_init();
  ALLEGRO_DISPLAY* pDisplay = al_create_display(400, 400);
  while(true) {
    al_flip_display();
  }    
  return 0;
}