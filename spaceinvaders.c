#include <unistd.h>
#include <ncurses.h>
#include "lib_space.h"
#include <stdlib.h>
#include <string.h>

int main() {
	int key;
	int nlin;
	int ncol;
	int pontos=0;
	int cont=0;
	t_lista lista_aliens;
	t_lista lista_canhao;
	t_lista lista_tiros_canhao;
	t_lista lista_tiros_aliens;
	t_lista lista_barreira;
	t_lista lista_nave_mae;
	initscr();             /* inicia a tela */
	cbreak();               /* desabilita o buffer de entrada */
	noecho();               /* não mostra os caracteres digitados */
	nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
	keypad(stdscr, TRUE);   /* permite a leitura das setas */
	curs_set(FALSE);        /* não mostra o cursor na tela */
	getmaxyx(stdscr, nlin, ncol);
	start_color();
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_CYAN, 700, 700, 700);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
	
	inicializa_lista(&lista_tiros_canhao);
	inicializa_lista(&lista_tiros_aliens);
	inicializa_lista(&lista_nave_mae);
	inserealiens(&lista_aliens);
	inserecanhao(&lista_canhao);
	inserebarreira(&lista_barreira);

	if (nlin>=38 && ncol>=100) {
		while (1) {
			erase();
			criaborda(nlin,ncol);
			if (cont%300==0) 
				inserenavemae(&lista_nave_mae);
			imprimenavemae(&lista_nave_mae);
			imprimepontos(pontos);
			imprimebarreira(&lista_barreira);
			imprimealiens(&lista_aliens);
			imprimecanhao(&lista_canhao);	
			imprimetiros(&lista_tiros_canhao);
			removealiensmortos(&lista_aliens);
			if (cont%2==0)
					move_nave_mae(&lista_nave_mae);
			if (cont%20==0)
				inseretirosaliens(&lista_tiros_aliens, &lista_aliens);
			imprimetiros(&lista_tiros_aliens);
			if (lista_aliens.quant>0) {
				if (cont%(abs(lista_aliens.ini->prox->velocidade))==0) {
					if (move_aliens(&lista_aliens)) {
						endwin();
						destroi_lista(&lista_nave_mae);
			    		destroi_lista(&lista_canhao);
						destroi_lista(&lista_aliens);
						destroi_lista(&lista_barreira);
						destroi_lista(&lista_tiros_canhao);
						destroi_lista(&lista_tiros_aliens);
						printf("Os aliens chegaram a terra!\n");
				    	exit(0);
					}
					verificacolisaoalienbarreira(&lista_barreira, &lista_aliens);
				}
			}
			if(cont % 2 == 0){
				move_tiros(&lista_tiros_canhao);
				move_tiros(&lista_tiros_aliens);
			  	if (verificacolisaocanhao(&lista_tiros_aliens, &lista_canhao)) {
				  	endwin();
				  	destroi_lista(&lista_nave_mae);
			    	destroi_lista(&lista_canhao);
					destroi_lista(&lista_aliens);
					destroi_lista(&lista_barreira);
					destroi_lista(&lista_tiros_canhao);
					destroi_lista(&lista_tiros_aliens);
					printf("Voce morreu!\n");
			    	exit(0);
			  	}
			  	verificacolisaonavemae(&lista_nave_mae, &lista_tiros_canhao, &pontos);

			  	verificacolisaotirosbarreira(&lista_barreira, &lista_tiros_canhao);
			  	verificacolisaotirosbarreira(&lista_barreira, &lista_tiros_aliens);
			}
			verificacolisaoaliens(&lista_tiros_canhao, &lista_aliens, &pontos);
		  	key = getch();
		  
			if(key == ' ') {
				inseretiros(&lista_tiros_canhao, &lista_canhao);
			}
			else
			if(key == KEY_LEFT) {
				move_canhao(&lista_canhao, -1);
		  	}
		  	else if (key == KEY_RIGHT) {
		  		move_canhao(&lista_canhao, 1);
		  	}
		  	else if (key == 'q') {
		    	endwin();
		    	destroi_lista(&lista_nave_mae);
		    	destroi_lista(&lista_canhao);
				destroi_lista(&lista_aliens);
				destroi_lista(&lista_barreira);
				destroi_lista(&lista_tiros_canhao);
				destroi_lista(&lista_tiros_aliens);
		    	exit(0);
		  	}
		  	if (verificacolisaoaliencanhao(&lista_aliens, &lista_canhao)) {
		  		endwin();
		  		destroi_lista(&lista_nave_mae);
		    	destroi_lista(&lista_canhao);
				destroi_lista(&lista_aliens);
				destroi_lista(&lista_barreira);
				destroi_lista(&lista_tiros_canhao);
				destroi_lista(&lista_tiros_aliens);
				printf("Voce morreu!\n");
		    	exit(0);
		  	}
		  	flushinp();
		  	usleep(30000);
		  	if (lista_aliens.quant==0) {
		  		endwin();
		  		destroi_lista(&lista_nave_mae);
		  		destroi_lista(&lista_canhao);
				destroi_lista(&lista_aliens);
				destroi_lista(&lista_barreira);
				destroi_lista(&lista_tiros_canhao);
				destroi_lista(&lista_tiros_aliens);
		  		printf("Voce ganhou!\n");
		  		exit(0);
		  	}
		  	refresh();
		  	cont++;
	  	}	
	  	return 0;
	}
	endwin();
	printf("Tamanho do terminal menor que 38x100\n");
	exit(0);
	return 0;
}
