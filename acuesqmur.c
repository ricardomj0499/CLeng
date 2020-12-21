#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int dir = 4;
int posx = 20*9;
int posy = 20*16;
int asustados = 0; 
int game = 1;
float pacvel = 100;
float fantvel = 100;
int cantSemillas = 4;
char formaSemillas[10];

//Tablero de juego actual
char tablero[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"XCCCCCCXCCCXCCCCCCX",
"XCXXCXCXCXCXCXCXXCX",
"XCCCCXCCCXCCCXCCCCX",
"XCXXCXXXCXCXXXCXXCX",
"XCXCCCCCCXCCCCCCXCX",
"XCXCXXCXXXXXCXXCXCX",
"ACCCCCCCCCCCCCCCCCA",
"XCXXCXCXXXXXCXCXXCX",
"XCXXCXCXAAAXCXCXXCX",
"XCCCCXCXXXXXCXCCCCX",
"XCXXCXCCCCCCCXCXXCX",
"XCCXCXCXXXXXCXCXCCX",
"XXCXCCCCCXCCCCCXCXX",
"ACCXCXXXCXCXXXCXCCA",
"XCXXCXCCCXCCCXCXXCX",
"XCCCCXCXCCCXCXCCCCX",
"XCXCXXCXCXCXCXXCXCX",
"XCXCCCCXCCCXCCCCXCX",
"XCXXXXCXXXXXCXXXXCX",
"XCCCCCCCCCCCCCCCCCX",
"XXXXXXXXXXXXXXXXXXX"
};

//Tablero base para para reiniciar cada nivel
char tableroAux[FILASMAX][COLMAX] = {
"XXXXXXXXXXXXXXXXXXX",
"XCCCCCCXCCCXCCCCCCX",
"XCXXCXCXCXCXCXCXXCX",
"XCCCCXCCCXCCCXCCCCX",
"XCXXCXXXCXCXXXCXXCX",
"XCXCCCCCCXCCCCCCXCX",
"XCXCXXCXXXXXCXXCXCX",
"ACCCCCCCCCCCCCCCCCA",
"XCXXCXCXXXXXCXCXXCX",
"XCXXCXCXAAAXCXCXXCX",
"XCCCCXCXXXXXCXCCCCX",
"XCXXCXCCCCCCCXCXXCX",
"XCCXCXCXXXXXCXCXCCX",
"XXCXCCCCCXCCCCCXCXX",
"ACCXCXXXCXCXXXCXCCA",
"XCXXCXCCCXCCCXCXXCX",
"XCCCCXCXCCCXCXCCCCX",
"XCXCXXCXCXCXCXXCXCX",
"XCXCCCCXCCCXCCCCXCX",
"XCXXXXCXXXXXCXXXXCX",
"XCCCCCCCCCCCCCCCCCX",
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
"A                 A",
"X XX X XXXXX X XX X",
"X XX X XAAAX X XX X",
"X    X XXXXX X    X",
"X XX X       X XX X",
"X  X X XXXXX X X  X",
"XX X     X     X XX",
"A  X XXX X XXX X  A",
"X XX X   X   X XX X",
"X    X X   X X    X",
"X X XX X X X XX X X",
"X X    X   X    X X",
"X XXXX XXXXX XXXX X",
"X        C        X",
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
"A                 A",
"X XX X XXXXX X XX X",
"X XX X XAAAX X XX X",
"X    X XXXXX X    X",
"X XX X       X XX X",
"X  X X XXXXX X X  X",
"XX X     X     X XX",
"A  X XXX X XXX X  A",
"X XX X   X   X XX X",
"X    X X   X X    X",
"X X XX X X X XX X X",
"X X    X   X    X X",
"X XXXX XXXXX XXXX X",
"X        C        X",
"XXXXXXXXXXXXXXXXXXX"
};*/

//
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

	pacvel = atof(a)/100;
  fantvel = atof(b)/100;
  cantSemillas = atoi(d);
  if (cantSemillas < 4){
    cantSemillas = 4;
  }else if(cantSemillas>16){
    cantSemillas = 16;
  }
  printf("%d\n",cantSemillas);
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
  draw_sprite(buffer,pacbuff,posx,posy);
}

//Funcion que mantienen el ciclo de juego por cada nivel
void start_game(){
  openFile();
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
  pacbuff = create_bitmap(20,20);
  cocos = load_bitmap("assets/comida.bmp",NULL);
  semilla = load_bitmap("assets/semilla.bmp",NULL);
  

  while(game && !restart()){
    
    if (key[KEY_ESC]){
      game = 0;
    }
    
    if(key[KEY_RIGHT]){
    	if(tablero[posy/20][(posx+20)/20] != 'X'){
      		dir  = 1;
      }
    }else if(key[KEY_UP]){
    	if(tablero[(posy-20)/20][posx/20] != 'X'){
    		dir = 2;}
    }else if(key[KEY_DOWN]){
    	  if(tablero[(posy+20)/20][posx/20] != 'X'){
    		  dir = 3;}
        }else if(key[KEY_LEFT]){
    	    if(tablero[posy/20][(posx-20)/20] != 'X'){
    		    dir = 0;
          }}


    if(dir == 0) {
      if(tablero[posy/20][(posx-20)/20] != 'X'){
        posx-=20;
        }else{
          dir = 4;
        }
    }
    if(dir == 1) {
      if(tablero[posy/20][(posx+20)/20] != 'X'){
        posx+=20;
        }else{
          dir = 4;
        }
    }
    if(dir == 2) {
      if(tablero[(posy-20)/20][posx/20] != 'X'){
        posy-=20;
        }else{
          dir = 4;
        }    
    }
    if(dir == 3) {
      if(tablero[(posy+20)/20][posx/20] != 'X'){
        posy+=20;
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
    }printf("\n\n\n");
*/
    if(posx<=-20){
        posx=TAMANOX;
    }else if(posx>=TAMANOX){
        posx=-20;
    }
    clear(buffer);
    dibujar_tablero();
    if(dir != 4){
    clear(buffer);
    clear(pacbuff);
    dibujar_tablero();
    move_pacman();
    show_pantalla();
    cooldown(0.15/pacvel);}

    clear(pacbuff);
    blit(pacman_stop,pacbuff,0,0,0,0,20,20);
    draw_sprite(buffer,pacbuff,posx,posy);
    show_pantalla();
    cooldown(0.075);
  }
}

//Funcion que setea las variables iniciales para empezar un nivel nuevo
void rebuild_game(){
  dir = 4;
  posx = 20*9;
  posy = 20*16;
  asustados = 0;
  for (int i = 0;i<FILASMAX;i++){
      for(int j =0; j<COLMAX;j++){
        tablero[i][j] = tableroAux[i][j];
      }
  }
}



//Funcion principal, que mantienen el ciclo principal del juego
int main(int argc, char *argv[]) {
  	
  allegro_init();
  while(game){
    start_game();
    rebuild_game(); 
  }
  

}
END_OF_MAIN(); 