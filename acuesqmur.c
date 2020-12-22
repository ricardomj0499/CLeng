#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define FILASMAX 23
#define COLMAX 20
#define TAMANOX 380
#define TAMANOY 440


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
BITMAP *naranja = NULL;
BITMAP *naranjabuff = NULL;
BITMAP *pared = NULL;



pthread_t hilos[4];
int dir = 4;
int pacPosx = 20*9;
int pacPosy = 20*16;
int naranjaPosx = 20*10;
int naranjaPosy = 20*9;
int asustados = 0; 
int game = 1;
float pacvel = 100;
float fantvel = 100;
int cantSemillas = 4;
char formaSemillas[10];

//Tablero de juego actual
char tablero[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"XCCCACCXCCCXCCACCCX",
"XCXXCXCXCXCXCXCXXCX",
"XACCAXCCAXACCXACCAX",
"XCXXCXXXCXCXXXCXXCX",
"XCXCACACCXCCACACXCX",
"XCXCXXCXXXXXCXXCXCX",
" ACAACACCFCCACAACA ",
"XCXXCXCXDDDXCXCXXCX",
"XCXXCXCXFFFXCXCXXCX",
"XACCAXCXXXXXCXACCAX",
"XCXXCXACCCCCAXCXXCX",
"XCCXCXCXXXXXCXCXCCX",
"XXCXACACCXCCACAXCXX",
" ACXCXXXCXCXXXCXCA ",
"XCXXCXCCCXACCXCXXCX",
"XACACXCXACAXCXCACAX",
"XCXCXXCXCXCXCXXCXCX",
"XCXCCCAXCCCXACCCXCX",
"XCXXXXCXXXXXCXXXXCX",
"XCCCCCACCCCCACCCCCX",
"XXXXXXXXXXXXXXXXXXX"
};

//Tablero base para para reiniciar cada nivel
char tableroAux[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"XCCCACCXCCCXCCACCCX",
"XCXXCXCXCXCXCXCXXCX",
"XACCAXCCAXACCXACCAX",
"XCXXCXXXCXCXXXCXXCX",
"XCXCACACCXCCACACXCX",
"XCXCXXCXXXXXCXXCXCX",
" ACAACACCFCCACAACA ",
"XCXXCXCXDDDXCXCXXCX",
"XCXXCXCXFFFXCXCXXCX",
"XACCAXCXXXXXCXACCAX",
"XCXXCXACCCCCAXCXXCX",
"XCCXCXCXXXXXCXCXCCX",
"XXCXACACCXCCACAXCXX",
" ACXCXXXCXCXXXCXCA ",
"XCXXCXCCCXACCXCXXCX",
"XACACXCXACAXCXCACAX",
"XCXCXXCXCXCXCXXCXCX",
"XCXCCCAXCCCXACCCXCX",
"XCXXXXCXXXXXCXXXXCX",
"XCCCCCACCCCCACCCCCX",
"XXXXXXXXXXXXXXXXXXX"
};
/*
char tablero[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"X      X   X      X",
"X XX X X X X X XX X",
"X    X   X   X    X",
"X XX XXX X XXX XX X",
"X X      X      X X",
"X X XX XXXXX XX X X",
"         F         ",
"X XX X XDDDX X XX X",
"X XX X XFFFX X XX X",
"X    X XXXXX X    X",
"X XX X       X XX X",
"X  X X XXXXX X X  X",
"XX X     X     X XX",
"   X XXX X XXX X   ",
"X XX X   X   X XX X",
"X    X X   X X    X",
"X X XX X X X XX X X",
"X X    X   X    X X",
"X XXXX XXXXX XXXX X",
"XC                X",
"XXXXXXXXXXXXXXXXXXX"
};

char tableroAux[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"X      X   X      X",
"X XX X X X X X XX X",
"X    X   X   X    X",
"X XX XXX X XXX XX X",
"X X      X      X X",
"X X XX XXXXX XX X X",
"         F         ",
"X XX X XDDDX X XX X",
"X XX X XFFFX X XX X",
"X    X XXXXX X    X",
"X XX X       X XX X",
"X  X X XXXXX X X  X",
"XX X     X     X XX",
"   X XXX X XXX X   ",
"X XX X   X   X XX X",
"X    X X   X X    X",
"X X XX X X X XX X X",
"X X    X   X    X X",
"X XXXX XXXXX XXXX X",
"XC                X",
"XXXXXXXXXXXXXXXXXXX"
};*/

//tablero[pacPosy/20][(pacPosx+20)/20] == 'C'
void cooldown(float seconds)
{
    clock_t start = clock();
    clock_t period = seconds * CLOCKS_PER_SEC;
    clock_t elapsed;

    do {
        elapsed = clock() - start;
    } while(elapsed < period);
}

//funcion qeu se encarga de dibujar en el bufer las imagenes respectivas segun la matriz "tablero"
void dibujar_tablero(){
  int i;
  int j;
  for(i = 0; i< FILASMAX; i++){
    for(j = 0; j<COLMAX; j++){
      if (tablero[i][j] == 'X'){
        draw_sprite(buffer,muro,j*20,i*20);
      }else if(tablero[i][j] == 'C' || tablero[i][j] == 'A'){
        if(pacPosy/20 == i && pacPosx/20  == j){
          tablero[i][j] = ' ';
          asustados = 100;
        }else{
          draw_sprite(buffer,cocos,j*20,i*20);
        }  
      }else if (tablero[i][j] == 'S'){
         if(pacPosy/20 == i && pacPosx/20  == j){
          tablero[i][j] = ' ';
          asustados = 100;
        }else{
          draw_sprite(buffer,semilla,j*20,i*20);
        }  
      }else if(tablero[i][j] == 'D'){
          draw_sprite(buffer,pared,j*20,i*20);
        }else{
        draw_sprite(buffer,muroFondo,j*20,i*20);
      }
    }
  }
}

//Fucion que coloca las semillas segun lo que diga el "Config.txt"
void coloca_semillas(){
  formaSemillas[strcspn(formaSemillas, "\n")] = 0;

  if(strcmp(formaSemillas,"normal") == 0){
    int dist = (FILASMAX*COLMAX)/cantSemillas;
    for(int i = 0;i<=cantSemillas; i++){
      int a = dist/FILASMAX;
      int b = dist-(FILASMAX*a);
      if (tablero[a][b] != 'C'){
        if (tablero[a][b+1] == 'C'){
          tablero[a][b+1]='S';
        }else if(tablero[a+1][b] == 'C'){
          tablero[a+1][b]='S';
        }else if(tablero[a][b-1]=='C'){
          tablero[a][b-1]='S';
        }else if(tablero[a-1][b]=='C'){
          tablero[a-1][b]='S';
        }else if(tablero[a-2][b]=='C'){
          tablero[a-2][b]='S';
        }
      }else{
        tablero[a][b]='S';
      }
      dist+= (FILASMAX*COLMAX)/cantSemillas;
    }
  }else if (strcmp(formaSemillas,"aleatorio") == 0){
    srand(time(NULL));
    for( int i = 0 ; i <= cantSemillas ; i++ ) {
      int a = rand()%((FILASMAX)-1) + 1;
      int b = rand()%((COLMAX)-1) + 1;
      if (tablero[a][b] != 'C'){
        if (tablero[a][b+1] == 'C'){
          tablero[a][b+1]='S';
        }else if(tablero[a+1][b] == 'C'){
          tablero[a+1][b]='S';
        }else if(tablero[a][b-1]=='C'){
          tablero[a][b-1]='S';
        }else if(tablero[a-1][b]=='C'){
          tablero[a-1][b]='S';
        }
      }else{
        tablero[a][b]='S';
      }
   }

  }
}
 
//Funcion que se encarga de abrir el archivo de configuracion "Config.txt" donde ingresa la informacion 
//de la velocidad del pacman y los fantasmas, y la dispocionon de semillas en el mapa
void openFile(){

	//open and get the file handle
	FILE* fh;
	fh = fopen("config.txt", "r");

	char a[150];
	char b[150];
	char d[150]; 

	int aa;
	int bb;
	int dd;

	if (fh == NULL)
	{
		printf("El archivo Config no existe");
	}

	fgets(a,150,fh);
	fgets(b,150,fh);
	fgets(formaSemillas,150,fh);
	fgets(d,150,fh);

	fantvel = atof(a)/100;
  pacvel = atof(b)/100;
  cantSemillas = atoi(d);
  if (cantSemillas < 4){
    cantSemillas = 4;
  }else if(cantSemillas>16){
    cantSemillas = 16;
  }
  //printf("%d\n",cantSemillas);
  coloca_semillas();
/*
	printf("%d\n", aa);
	printf("%d\n", bb);
	printf("%s", formaSemillas);
	printf("%d\n", dd);*/
}

//funcion que verifica si el pacman ya se comio todos los cocos
//retorna 0 si no se los ha comido todos o 1 si ya estan todos comidos
int restart(){
	for(int i = 0; i< FILASMAX; i++){
    	for(int j = 0; j<COLMAX; j++){
     		if (tablero[i][j] == 'C') {
     			return 0;
     		}
    	}
    }
    return 1;
}

//Funcion que muestra el contenido del bufer en la pantalla
void show_pantalla(){
  blit(buffer,screen,0,0,0,0,TAMANOX,TAMANOY);
}

//Funcion que dibuja al pacman segun en la direccion en la se dirija
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
  draw_sprite(buffer,pacbuff,pacPosx,pacPosy);
}

void *pacMan (){
   while(game && !restart()){
    
    if (key[KEY_ESC]){
      game = 0;
      pthread_exit(NULL);
    }
    
    if(key[KEY_RIGHT]){
    	if(tablero[pacPosy/20][(pacPosx+20)/20] != 'X' && tablero[pacPosy/20][(pacPosx+20)/20] != 'D'){
      		dir  = 1;
      }
    }else if(key[KEY_UP]){
    	if(tablero[(pacPosy-20)/20][pacPosx/20] != 'X' && tablero[(pacPosy-20)/20][pacPosx/20] != 'D'){
    		dir = 2;}
    }else if(key[KEY_DOWN]){
    	  if(tablero[(pacPosy+20)/20][pacPosx/20] != 'X' && tablero[(pacPosy+20)/20][pacPosx/20] != 'D'){
    		  dir = 3;}
        }else if(key[KEY_LEFT]){
    	    if(tablero[pacPosy/20][(pacPosx-20)/20] != 'X' && tablero[pacPosy/20][(pacPosx-20)/20] != 'D'){
    		    dir = 0;
          }}


    if(dir == 0) {
      if(tablero[pacPosy/20][(pacPosx-20)/20] != 'X'){
        pacPosx-=20;
        }else{
          dir = 4;
        }
    }
    if(dir == 1) {
      if(tablero[pacPosy/20][(pacPosx+20)/20] != 'X'){
        pacPosx+=20;
        }else{
          dir = 4;
        }
    }
    if(dir == 2) {
      if(tablero[(pacPosy-20)/20][pacPosx/20] != 'X'){
        pacPosy-=20;
        }else{
          dir = 4;
        }    
    }
    if(dir == 3) {
      if(tablero[(pacPosy+20)/20][pacPosx/20] != 'X'){
        pacPosy+=20;
        }else{
          dir = 4;
        }
    }
/*
    for (int i=0;i<=TAMANOY/20;i++){
      for (int j=0; j<=TAMANOX/20;j++){
        printf("%c,",tablero[i][j]);
      }
      printf("\n");
    }printf("\n\n\n");*/

    if(pacPosx<=-20){
        pacPosx=TAMANOX;
    }else if(pacPosx>=TAMANOX){
        pacPosx=-20;
    }
    clear(buffer);
    dibujar_tablero();
    if(dir != 4){
    clear(buffer);
    clear(pacbuff);
    dibujar_tablero();
    move_pacman();
    show_pantalla();
    //printf("%f\n",pacvel);
    cooldown(0.15/pacvel);}

    clear(pacbuff);
    blit(pacman_stop,pacbuff,0,0,0,0,20,20);
    draw_sprite(buffer,pacbuff,pacPosx,pacPosy);
    show_pantalla();
    cooldown(0.075);
  }
}

void *fantNaranja(){
  while(game && !restart()){
    
    if (key[KEY_ESC]){
      game = 0;
      pthread_exit(NULL);
    }
  draw_sprite(buffer,naranjabuff,naranjaPosx,naranjaPosy);
  }
}
//Funcion que mantienen el ciclo de juego por cada nivel
void start_game(){
  
  pthread_create(hilos, NULL, pacMan, NULL);
  pthread_create(hilos+1, NULL, fantNaranja, NULL);
  
  
  pthread_join(hilos[0],NULL);
  pthread_join(hilos[1],NULL);
}

//Funcion que setea las variables iniciales para empezar un nivel nuevo
void rebuild_game(){
  dir = 4;
  pacPosx = 20*9;
  pacPosy = 20*16;
  asustados = 0;
  for (int i = 0;i<FILASMAX;i++){
      for(int j =0; j<COLMAX;j++){
        tablero[i][j] = tableroAux[i][j];
      }
  }
}


void *sumar(){
  for (int i=0;i<40;i++){
  printf("test\n");}
}
//Funcion principal, que mantienen el ciclo principal del juego
int main(int argc, char *argv[]) {
  
  openFile();
  allegro_init();
  install_keyboard();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,TAMANOX,TAMANOY,0,0);  
  buffer = create_bitmap(TAMANOX,TAMANOY);
  muro = load_bitmap("assets/brick.bmp",NULL);
  muroFondo = load_bitmap("assets/brick_fondo.bmp",NULL);
  pacman_izq = load_bitmap("assets/pac_izq.bmp",NULL);
  pacman_der = load_bitmap("assets/pac_der.bmp",NULL);
  pacman_up = load_bitmap("assets/pac_up.bmp",NULL);
  pacman_down = load_bitmap("assets/pac_down.bmp",NULL);
  pacman_stop = load_bitmap("assets/pac_stop.bmp",NULL);
  naranja = load_bitmap("assets/fantasma_naranja.bmp",NULL);
  pared = load_bitmap("assets/pared.bmp",NULL);
  pacbuff = create_bitmap(20,20);
  naranjabuff = create_bitmap(20,20);
  cocos = load_bitmap("assets/comida.bmp",NULL);
  semilla = load_bitmap("assets/semilla.bmp",NULL);
  blit(naranja,naranjabuff,0,0,0,0,20,20);
 
  
  while(game){
    start_game();
    rebuild_game(); 
  }
  

}
END_OF_MAIN(); 