#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#define FILASMAX 23
#define COLMAX 20
#define TAMANOX 380
#define TAMANOY 440
#define PACVEL 20

BITMAP *buffer = NULL;
BITMAP *muro = NULL;
BITMAP *muroFondo = NULL;
BITMAP *pacman_izq= NULL;
BITMAP *pacman_der= NULL;
BITMAP *pacman_up= NULL;
BITMAP *pacman_down= NULL;
BITMAP *pacman_stop= NULL;
BITMAP *temp = NULL;
BITMAP *pacbuff = NULL;
BITMAP *cocos = NULL;
BITMAP *semilla = NULL;

int dir = 4;
int posx = 20*9;
int posy = 20*16;
int asustados = 0; 

char tablero[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"XCSCCCCXCCCXCCSCCCX",
"XCXXCXCXCXCXCXCXXCX",
"XCCCCXCCCXCCCXCCSCX",
"XCXXCXXXCXCXXXCXXCX",
"XCXCCCCCSXCCCCCCXCX",
"XCXCXXCXXXXXCXXSXCX",
"ACCCCCCCCCCCCCCCCCA",
"XSXXCXCXXXXXCXCXXCX",
"XCXXCXSXAAAXCXCXXSX",
"XCCSCXCXXXXXCXCCCCX",
"XCXXCXCCCCCCCXCXXCX",
"XCCXCXCXXXXXCXSXCCX",
"XXSXCCCCCXCCCCCXCXX",
"ACCXCXXXCXSXXXCXCCA",
"XCXXCXCCCXCCCXCXXCX",
"XCCCCXCXCCCXCXCCCCX",
"XCXCXXCXCXCXCXXCXCX",
"XCXSCCCXCCSXCCCSXCX",
"XCXXXXCXXXXXCXXXXCX",
"XCCCCCCSCCCCCCCCCCX",
"XXXXXXXXXXXXXXXXXXX"
};


void cooldown(float seconds)
{
    clock_t start = clock();
    clock_t period = seconds * CLOCKS_PER_SEC;
    clock_t elapsed;

    do {
        elapsed = clock() - start;
    } while(elapsed < period);
}

void dibujar_tablero(){
  int i;
  int j;
  for(i = 0; i< FILASMAX; i++){
    for(j = 0; j<COLMAX; j++){
      if (tablero[i][j] == 'X'){
        draw_sprite(buffer,muro,j*20,i*20);
      }else if(tablero[i][j] == 'C'){
        if(posy/20 == i && posx/20  == j){
          tablero[i][j] = ' ';
          asustados = 100;
        }else{
          draw_sprite(buffer,cocos,j*20,i*20);
        }  
      }else if (tablero[i][j] == 'S'){
         if(posy/20 == i && posx/20  == j){
          tablero[i][j] = ' ';
          asustados = 100;
        }else{
          draw_sprite(buffer,semilla,j*20,i*20);
        }  
      }else {
        draw_sprite(buffer,muroFondo,j*20,i*20);
      }
    }
  }
}


int restar(){
	for(int i = 0; i< FILASMAX; i++){
    	for(int j = 0; j<COLMAX; j++){
     		if (tablero[i][j] == 'C') {
     			return 0;
     		}
    	}
    }
    return 1;
}



void show_pantalla(){
  blit(buffer,screen,0,0,0,0,TAMANOX,TAMANOY);
}

void move_pacman(){
  if(dir == 0){
    blit(pacman_izq,pacbuff,0,0,0,0,20,20);
  }else if(dir == 1){
    blit(pacman_der,pacbuff,0,0,0,0,20,20);
  }else if(dir == 2){
    blit(pacman_up,pacbuff,0,0,0,0,20,20);  
  }else if(dir == 3){
    blit(pacman_down,pacbuff,0,0,0,0,20,20);
  }  
  draw_sprite(buffer,pacbuff,posx,posy);
}


int main(int argc, char *argv[]) {
  allegro_init();
  install_keyboard();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,TAMANOX,TAMANOY,0,0);  
  buffer = create_bitmap(TAMANOX,TAMANOY);
  muro = load_bitmap("brick.bmp",NULL);
  muroFondo = load_bitmap("brick_fondo.bmp",NULL);
  pacman_izq = load_bitmap("pac_izq.bmp",NULL);
  pacman_der = load_bitmap("pac_der.bmp",NULL);
  pacman_up = load_bitmap("pac_up.bmp",NULL);
  pacman_down = load_bitmap("pac_down.bmp",NULL);
  pacman_stop = load_bitmap("pac_stop.bmp",NULL);
  pacbuff = create_bitmap(20,20);
  cocos = load_bitmap("comida.bmp",NULL);
  semilla = load_bitmap("semilla.bmp",NULL);

  while(!key[KEY_ESC] && !restar()){
    if(key[KEY_RIGHT]){
      dir  = 1;
    }else if(key[KEY_UP]){
      dir = 2;
    }else if(key[KEY_DOWN]){
      dir = 3;
    }else if(key[KEY_LEFT]){
      dir = 0;
    }

    if(dir == 0) {
      if(tablero[posy/20][(posx-20)/20] != 'X'){
        posx-=PACVEL;}
    }
    if(dir == 1) {
      if(tablero[posy/20][(posx+20)/20] != 'X'){
        posx+=PACVEL;}
    }
    if(dir == 2) {
      if(tablero[(posy-20)/20][posx/20] != 'X'){
        posy-=PACVEL;}    
    }
    if(dir == 3) {
      if(tablero[(posy+20)/20][posx/20] != 'X'){
        posy+=PACVEL;}
    }

    if(posx<=-20){
        posx=TAMANOX;
    }else if(posx>=TAMANOX){
        posx=-20;
    }
    clear(buffer);
    clear(pacbuff);
    dibujar_tablero();
    move_pacman();
    show_pantalla();
    cooldown(0.15);

  }

}
END_OF_MAIN(); 