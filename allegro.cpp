#include <string>
#include <allegro5/allegro.h>
int main(int argc, char** argv) {
  al_init();
  al_install_keyboard();
  al_install_mouse();
    
  ALLEGRO_DISPLAY* pDisplay = al_create_display(400, 400);
  ALLEGRO_EVENT_QUEUE* oQueue;
  
  oQueue = al_create_event_queue();
  al_register_event_source(oQueue, al_get_keyboard_event_source());
  al_register_event_source(oQueue, al_get_display_event_source(pDisplay));
  
  std::string sWindowTitle = "Nuestra primera aplicación Allegro 5";
  al_set_window_title(pDisplay, sWindowTitle.c_str());  
  while(true) {
    ALLEGRO_EVENT oEvent;
    al_wait_for_event(oQueue, &oEvent);
    switch(oEvent.type) {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        al_destroy_display(pDisplay);
        return 0;
      break;
      
      case ALLEGRO_EVENT_KEY_DOWN:
        al_destroy_display(pDisplay);
        return 0;
      break;
      
      default:
      
      break;      
    }
    al_flip_display();
  }    
  return 0;
}