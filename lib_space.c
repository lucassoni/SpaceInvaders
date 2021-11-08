#include <stdlib.h>
#include <stdio.h>
#include "lib_space.h"
#include <ncurses.h>
#include <string.h>

/* Verifica a colisao dos tiros do canhao com a nave mae */
void verificacolisaonavemae(t_lista *nave_mae, t_lista *tiros, int *pontos) {
	int i;
	if (nave_mae->quant>0) {
		inicializa_atual_inicio(nave_mae);
		inicializa_atual_inicio(tiros);
		for(i=0; i<tiros->quant; i++) {
			if (nave_mae->quant>0) {
				if (tiros->atual->pos_lin>=nave_mae->atual->pos_lin &&
					tiros->atual->pos_lin<=nave_mae->atual->pos_lin+2 && 
					tiros->atual->pos_col>=nave_mae->atual->pos_col &&
					tiros->atual->pos_col<=nave_mae->atual->pos_col+8) {
						remove_item_atual(tiros);
						remove_item_atual(nave_mae);
						*pontos=*pontos+100;
					}
				incrementa_atual(tiros);
			}
		}
	}
}
/* Imprime a nave mae na tela */
void imprimenavemae(t_lista *nave_mae) {
	int i,j;
	if (nave_mae->quant>0) {
		inicializa_atual_inicio(nave_mae);
		wattron(stdscr, COLOR_PAIR(4));
		for(i=0; i<3; i++) {
			for(j=0; j<9; j++) {
				if (nave_mae->atual->pos_col+j<99 && nave_mae->atual->pos_col+j>0) {
					move(nave_mae->atual->pos_lin+i, nave_mae->atual->pos_col+j);
					addch(nave_mae->atual->tipo[j+i*9]);
				}
			}
		}
		wattron(stdscr, COLOR_PAIR(2));
	}
}
/* Move a nave mae ate o fim da tela e remove caso ela passe da borda */
void move_nave_mae(t_lista *nave_mae) {
	if (nave_mae->quant>0) {
		inicializa_atual_inicio(nave_mae);
		if (nave_mae->atual->pos_col<99)
			nave_mae->atual->pos_col++;
		else remove_item_atual(nave_mae);
	}
}
/* Insere a nave mae na lista */
void inserenavemae(t_lista *nave_mae) {
	insere_fim_lista(2, -8, 1, vivo, NaveMae, nave_mae);
}
/* Imprime os pontos no canto superior esquerdo da tela */
void imprimepontos(int pontos) {
	int i;
	for(i=2; i<10; i++) {
		move(1,i);
		addch(placar[i-2]);
	}
	printw("%d",pontos);
}
/* Verifica a colisao dos aliens com o canhao */
int verificacolisaoaliencanhao(t_lista *aliens, t_lista *canhao) {
	int j,k,m,lin,col;
	if (aliens->quant>0) {
		inicializa_atual_inicio(aliens);
		inicializa_atual_inicio(canhao);
		for(j=0; j<aliens->quant; j++) {
			for(k=0; k<2; k++) {
				for(m=0; m<5; m++) {
					lin=canhao->atual->pos_lin+k;
					col=canhao->atual->pos_col+m;
					if (lin>=aliens->atual->pos_lin &&
						lin<=aliens->atual->pos_lin+2 &&
						col>=aliens->atual->pos_col &&
						col<=aliens->atual->pos_col+4) {

						return 1;
					}
				}
			}
		incrementa_atual(aliens);
		}
	}
	return 0;
}
/* Verifica a colisao dos aliens com as barreiras */
void verificacolisaoalienbarreira(t_lista *barreira, t_lista *aliens) {
	int i,j,k,m,lin,col;
	if (aliens->quant>0) {
		inicializa_atual_inicio(aliens);
		for(i=0; i<aliens->quant; i++) {
			inicializa_atual_inicio(barreira);
			for(j=0; j<barreira->quant; j++) {
				for(k=0; k<3; k++) {
					for(m=0; m<7; m++) {
						lin=barreira->atual->pos_lin+k;
						col=barreira->atual->pos_col+m;
						if (lin>=aliens->atual->pos_lin &&
							lin<=aliens->atual->pos_lin+2 &&
							col>=aliens->atual->pos_col &&
							col<=aliens->atual->pos_col+4)

							if (barreira->atual->tipo[k*7+m]!=' ')
								barreira->atual->tipo[k*7+m]=' ';
					}
				}
			incrementa_atual(barreira);
			}
		incrementa_atual(aliens);
		}
	}
}
/* Verifica a colisao de todos os tiros com a barreira */
void verificacolisaotirosbarreira(t_lista *barreira, t_lista *tiros) {
	int i,j,lin,col;
	inicializa_atual_inicio(barreira);
	for(i=0; i<barreira->quant; i++) {
		inicializa_atual_inicio(tiros);
		for(j=0; j<tiros->quant; j++) {
			if (tiros->atual->pos_lin>=barreira->atual->pos_lin && 	
			   	tiros->atual->pos_lin<=barreira->atual->pos_lin+2 &&
			   	tiros->atual->pos_col>=barreira->atual->pos_col &&
			   	tiros->atual->pos_col<=barreira->atual->pos_col+6) {

					lin=tiros->atual->pos_lin - barreira->atual->pos_lin;
					col=tiros->atual->pos_col - barreira->atual->pos_col;
					if (barreira->atual->tipo[col+lin*7]!=' ') {
						barreira->atual->tipo[col+lin*7]=' ';
						remove_item_atual(tiros);
				}
			}
		incrementa_atual(tiros);
		}
	incrementa_atual(barreira);
	}
}
/* Imprime a barreira na tela */
void imprimebarreira(t_lista *l) {
	int i,j,k;
	inicializa_atual_inicio(l);
	for(i=0; i<l->quant; i++) {
		for(j=0; j<3; j++)
			for(k=0; k<7; k++) {
				move(l->atual->pos_lin+j, l->atual->pos_col+k);
				addch(l->atual->tipo[k+j*7]);
			}
		incrementa_atual(l);
	}
}
/* Insere as barreiras na lista */
void inserebarreira(t_lista *l) {
	int i;
	inicializa_lista(l);
	for(i=1; i<5; i++) {
		insere_fim_lista(30, 19*i, 0, vivo, Barreira, l);
	}
}
/* Verfica a colisao dos tiros dos aliens e do canhao */
int verificacolisaocanhao(t_lista *tiros, t_lista *canhao) {
	int i;
	inicializa_atual_inicio(tiros);
	for(i=0; i<tiros->quant; i++) {
		if (tiros->atual->pos_lin>=canhao->atual->pos_lin &&
			tiros->atual->pos_lin<=canhao->atual->pos_lin+1 &&
			tiros->atual->pos_col>=canhao->atual->pos_col && 
			tiros->atual->pos_col<=canhao->atual->pos_col+4) {
			return 1;
		}
		incrementa_atual(tiros);	
	}
	return 0;
}
/* Insere os tiros dos aliens na lista */
void inseretirosaliens(t_lista *tiros, t_lista *aliens) {
	int n,i;
	if (aliens->quant>0) {
		inicializa_atual_inicio(aliens);
		if (tiros->quant<3) {
			n=rand()%aliens->quant;
			for(i=0; i<n; i++)
				incrementa_atual(aliens);
			insere_fim_lista(aliens->atual->pos_lin, aliens->atual->pos_col+2, -1, vivo, TiroAlien, tiros);
		}
	}
}
/* Remove os aliens que foram mortos pelo canhao */
void removealiensmortos(t_lista *l) {
	int i;
	if (l->quant>0) {
		inicializa_atual_inicio(l);
		for(i=0; i<l->quant; i++) {
			if (l->atual->estado==morrendo)
				remove_item_atual(l);
			else 
				incrementa_atual(l);
		}
	}
}
/* Verifica a colisao dos tiros do canhao com os aliens */
void verificacolisaoaliens(t_lista *tiros, t_lista *aliens, int *pontos) {
	int i,j;
	if (aliens->quant>0) {
		inicializa_atual_inicio(aliens);
		for(j=0; j<aliens->quant; j++)  {
			inicializa_atual_inicio(tiros);
			for(i=0; i<tiros->quant; i++) {
				if (tiros->atual->pos_lin>=aliens->atual->pos_lin &&
				tiros->atual->pos_lin<=aliens->atual->pos_lin+2 && 
				tiros->atual->pos_col>=aliens->atual->pos_col &&
				tiros->atual->pos_col<=aliens->atual->pos_col+4) {
					remove_item_atual(tiros);
					troca_corpo(aliens, AlienMorrendo);
					aliens->atual->estado=morrendo;
					*pontos=*pontos+10;
				}
				incrementa_atual(tiros);
			}
			incrementa_atual(aliens);
		}
	}
}
/* Troca o corpo dos aliens do tipo 1 pelo tipo 2 e vice-versa */
void troca_corpo(t_lista *l, char corpo[]) {
	int i,j;
		for(i=0; i<3; i++)
			for(j=0; j<5; j++) {
				l->atual->tipo[j+i*5]=corpo[j+i*5];
			}
}
/* Move os tiros */
void move_tiros(t_lista *l) {
	int j;
	inicializa_atual_inicio(l);
	for(j=0; j<l->quant; j++) {

		if (l->atual->pos_lin>1 && l->atual->pos_lin<38) {
			if (l->atual->velocidade>0)
	    		l->atual->pos_lin--;
	    	else l->atual->pos_lin++;
	    	incrementa_atual(l);
	    }
	    else remove_item_atual(l);
	}
}		
/* Imprime os tiros */
void imprimetiros(t_lista *l) {
	int j;
	inicializa_atual_inicio(l);
	for(j=0; j<l->quant; j++) {
		if (l->atual->velocidade>0)
			wattron(stdscr, COLOR_PAIR(5));
		else wattron(stdscr, COLOR_PAIR(4));
	    move(l->atual->pos_lin, l->atual->pos_col);
	    addch(l->atual->tipo[0]);
	    incrementa_atual(l);
	}
	wattron(stdscr, COLOR_PAIR(2));
}
/* Insere os tiros na lista */
void inseretiros(t_lista *l, t_lista *c) {
	if (l->quant<3)
		insere_fim_lista(c->atual->pos_lin-1, c->atual->pos_col+2, 1, vivo, TiroCanhao, l);
}
/* Imprime o canhao */
void imprimecanhao(t_lista *l) {
	int i,j;
	inicializa_atual_inicio(l);
	for(i=0; i<2; i++ ) {
		for(j=0; j<5; j++) {
			wattron(stdscr, COLOR_PAIR(3));
			move(l->atual->pos_lin+i,l->atual->pos_col+j);
			addch(l->atual->tipo[j+i*5]);
		}
	}
	wattron(stdscr, COLOR_PAIR(2));
}
/* Insere o canhao na lista */
void inserecanhao(t_lista *l) {
	inicializa_lista(l);
	insere_fim_lista(36, 49, 1, vivo, Canhao, l);
}
/* Move o canhao para os lados */
void move_canhao(t_lista *l, int lado) {
	inicializa_atual_inicio(l);
	if (lado==1) {
		if (l->atual->pos_col<94)
			l->atual->pos_col++;
	}
	else if (l->atual->pos_col>1)
			l->atual->pos_col--;
}
/* Move os aliens no jogo */
int move_aliens(t_lista *l) {
	int i,desce=0;
	if (l->quant>0) {
		inicializa_atual_inicio(l);
		for(i=0; i<l->quant; i++) {
			if ((l->atual->pos_col==94)) {
				desce=1;
			}
			if ((l->atual->pos_col==1)) {
				desce=1;
			}	
			incrementa_atual(l);
		}
		inicializa_atual_inicio(l);
		for(i=0; i<l->quant; i++) {
			if (desce) {
				if (l->atual->velocidade>2) {
					if (l->atual->velocidade>0)
						l->atual->velocidade-=2;
					if (l->atual->velocidade<0)
						l->atual->velocidade+=2;
				}
				l->atual->pos_lin++;
				if (l->atual->pos_lin==36) {
					return 1;
				}

				(l->atual->velocidade)=(l->atual->velocidade)*-1;
			}
			if (!strcmp(l->atual->tipo, AlienA1))
				troca_corpo(l, AlienA2);
			else if (!strcmp(l->atual->tipo, AlienA2))
				troca_corpo(l, AlienA1);
			if (!strcmp(l->atual->tipo, AlienB1))
				troca_corpo(l, AlienB2);
			else if (!strcmp(l->atual->tipo, AlienB2))
				troca_corpo(l, AlienB1);
			if (!strcmp(l->atual->tipo, AlienC1))
				troca_corpo(l, AlienC2);
			else if (!strcmp(l->atual->tipo, AlienC2))
				troca_corpo(l, AlienC1);
			if (l->atual->velocidade>0) {
				l->atual->pos_col++;
			}
			else if (l->atual->velocidade<0)
				l->atual->pos_col--;

			incrementa_atual(l);
		}
	}
	return 0;
}
/* Insere todos os aliens na lista */
void inserealiens(t_lista *l) {
	int i,j=1;
	inicializa_lista(l);
	for(i=1;i<12;i++) {
		insere_fim_lista(6, 7+(7*i), 10, vivo, AlienA1, l);
	}
	while(j<3) {
		for(i=1;i<12;i++) {
			insere_fim_lista(6+4*j, 7+(7*i), 10, vivo, AlienB1, l);
		}
		j++;
	}
	while(j<5) {
		for(i=1;i<12;i++) {
			insere_fim_lista(6+4*j, 7+(7*i), 10, vivo, AlienC1, l);
		}
		j++;
	}
}
/*Imprime a lista contendo todos os aliens vivos*/
void imprimealiens(t_lista *l) {
	int i,j,k;
	wattron(stdscr, COLOR_PAIR(1));
	if (l->quant>0) {
		inicializa_atual_inicio(l);
		for(i=0; i<(l->quant); i++) {
			for(j=0; j<3; j++) 
				for(k=0; k<5; k++) {
					move((l->atual->pos_lin)+j,(l->atual->pos_col)+k);
					addch(l->atual->tipo[k+5*j]);
				}
			incrementa_atual(l);
		}
	}
	wattron(stdscr, COLOR_PAIR(2));
}
/* Cria uma borda ao redor do jogo*/
void criaborda(int nlin, int ncol) {
	int i;
	for(i=1; i<38; i++) {
		move(i,0);
		addch('|');
		move(i,99);
		addch('|');
	}
	for(i=0; i<100; i++) {
		move(0,i);
		addch('-');
		move(38,i);
		addch('-');
	}
}
/* Cria uma lista vazia duplamente encadeada com sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer. */
int inicializa_lista(t_lista *l){
	l->quant=0;
	l->ini=(t_nodo *)malloc(sizeof(t_nodo));
	if (l->ini==NULL)
		return 0;
	l->fim=(t_nodo *)malloc(sizeof(t_nodo));
	if (l->fim==NULL)		
		return 0;

	l->ini->prox=l->fim;
	l->ini->prev=NULL;

	l->fim->prox=NULL;
	l->fim->prev=l->ini;

	l->atual=NULL;
	
	return 1;
}
/* Retorna 1 se a lista está vazia e zero caso contrário. */
int lista_vazia(t_lista *l){
	if (l->quant==0)
		return 1;
	return 0;
}
/* Remove todos os elementos da lista e faz com que ela aponte para NULL. */
void destroi_lista(t_lista *l){

	inicializa_atual_inicio(l);
	while(!lista_vazia(l)){
		remove_item_atual(l);
	}

	free(l->ini);
	free(l->fim);

	l->ini=NULL;
	l->fim=NULL;
	l->atual=NULL;
}
/* Retorna o tamanho da lista em *tam.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int quant_lista(int *tam, t_lista *l){
	if (lista_vazia(l))
		return 0;

	*tam = l->quant;
	return 1;
}
/* Insere o elemento item no final da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int insere_fim_lista(int lin, int col, int velocidade, int estado, char tipo[], t_lista *l) {
	t_nodo *new;
	int m;
	new=(t_nodo *)malloc(sizeof(t_nodo));
	if (new==NULL)
		return 0;

	new->pos_col=col;
	new->pos_lin=lin;
	new->velocidade=velocidade;
	new->estado=estado;
	if (!(strcmp(AlienA1,tipo) && strcmp(AlienB1,tipo) && strcmp(AlienC1,tipo)))	
		for(m=0; m<15; m++)
				new->tipo[m]=tipo[m];
	else if (!strcmp(Canhao,tipo))
			for(m=0; m<10; m++)
				new->tipo[m]=tipo[m];
			else if (!strcmp(Barreira, tipo))
				for(m=0; m<21; m++)
					new->tipo[m]=tipo[m];
				else if (!strcmp(NaveMae, tipo))
					for(m=0; m<27; m++)
						new->tipo[m]=tipo[m];
					else new->tipo[0]=tipo[0];
	new->prev=l->fim->prev;
	new->prox=l->fim;
	if (lista_vazia(l))
		l->ini->prox=new;
	l->fim->prev->prox=new;
	l->fim->prev=new;
	l->quant++;

	return 1;
}

/* Inicializa o ponteiro atual para o primeiro elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int inicializa_atual_inicio(t_lista *l){
	if (lista_vazia(l))
		return 0;
	l->atual=l->ini->prox;
	return 1;
}
/* Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL.
*/
void incrementa_atual(t_lista *l){
	if (l->atual->prox!=NULL)
		l->atual=(l->atual)->prox;
	else
		l->atual=NULL;
}
/* Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o primeiro, isto é, não 
  tem anterior, retorna NULL. */
void decrementa_atual(t_lista *l){
	if (l->atual->prev != NULL)
		l->atual=(l->atual)->prev;
	else
		l->atual=NULL;
}
/* Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário. */
int remove_item_atual(t_lista *l){
	if (lista_vazia(l))
		return 0;

	t_nodo *temp;

	temp=l->atual->prox;
	l->atual->prev->prox=l->atual->prox;
	l->atual->prox->prev=l->atual->prev;
	free(l->atual);
	l->atual=temp;
	l->quant--;
	return 1;
}
