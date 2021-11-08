/*
  Feito por Marcos Castiho para a disciplina CI1001 - Programacao I
  Em 18/10/2019.
  Define a estrutura de dados para o Tipo Abstrato de Dados Lista
  como sendo uma lista duplamente encadeada com sentinelas no inicio
  e no final. A cabeca da lista tem ponteiros para o inicio, fim e
  para um elemento qualquer da lista, alem do tamanho da lista.
  Contem os prototipos publicos das funcoes que manipulam o TAD.
*/
#define MAX 25
#define AlienA1 "  A   AMA  /X\\ "
#define	AlienB1 ".v_v.}WMW{ / \\ "
#define AlienC1 " nmn dbMdb_/-\\_"
#define AlienA2 "  A   AMA  { } "
#define AlienB2 ".v_v.{WMW}'( )'"
#define AlienC2	" nmn dbMdb <^> "
#define AlienMorrendo " \\'/ -   - /,\\ "
#define Canhao " / \\ MMMMM"
#define NaveMae " /MMMMM\\ AMoMoMoMA \\/'--\\/ "
#define TiroCanhao "|"
#define TiroAlien "V"
#define Barreira " AMMMA AMMMMMAMM   MM"
#define vivo 1
#define morrendo 0
#define placar "Pontos: "

struct t_nodo {
    int pos_col;
    int pos_lin;
    int velocidade;
    int estado;
    struct t_nodo *prox;
    struct t_nodo *prev;
    char tipo[MAX];
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int quant;
};
typedef struct t_lista t_lista;

/* Verifica a colisao dos tiros do canhao com a nave mae */
void verificacolisaonavemae(t_lista *nave_mae, t_lista *tiros, int *pontos);

/* Imprime a nave mae na tela */
void imprimenavemae(t_lista *nave_mae);

/* Move a nave mae ate o fim da tela e remove caso ela passe da borda */
void move_nave_mae(t_lista *nave_mae);

/* Insere a nave mae na lista */
void inserenavemae(t_lista *nave_mae);

/* Imprime os pontos no canto superior esquerdo da tela */
void imprimepontos(int pontos);

/* Verifica a colisao dos aliens com o canhao */
int verificacolisaoaliencanhao(t_lista *aliens, t_lista *canhao);

/* Verifica a colisao dos aliens com as barreiras */
void verificacolisaoalienbarreira(t_lista *barreira, t_lista *aliens);

/* Verifica a colisao de todos os tiros com a barreira */
void verificacolisaotirosbarreira(t_lista *barreira, t_lista *tiros);

/* Imprime a barreira na tela */
void imprimebarreira(t_lista *l);

/* Insere as barreiras na lista */
void inserebarreira(t_lista *l);

/* Verfica a colisao dos tiros dos aliens e do canhao */
int verificacolisaocanhao(t_lista *tiros, t_lista *canhao);

/* Insere os tiros dos aliens na lista */
void inseretirosaliens(t_lista *tiros, t_lista *aliens);

/* Remove os aliens que foram mortos pelo canhao */
void removealiensmortos(t_lista *l);

/* Verifica a colisao dos tiros com os aliens */
void verificacolisaoaliens(t_lista *tiros, t_lista *aliens, int *pontos);

/* Troca o corpo dos aliens do tipo 1 pelo tipo 2 e vice-versa */
void troca_corpo(t_lista *l, char corpo[]);

/* Move os tiros */
void move_tiros(t_lista *l);

/* Imprime os tiros na tela */
void imprimetiros(t_lista *l);

/* Insere tiros na lista */
void inseretiros(t_lista *l, t_lista *c);

/* Imprime o canhao na tela */
void imprimecanhao(t_lista *l); 

/* Insere o canhao na lista */
void inserecanhao(t_lista *l);

/* Move canhao */
void move_canhao(t_lista *l, int lado);

/* Move aliens */
int move_aliens(t_lista *l);

/* Insere aliens na lista */
void inserealiens(t_lista *l);

/* Imprime aliens na tela */
void imprimealiens(t_lista *l);

/* Cria uma borda ao redor do jogo*/
void criaborda(int nlin, int ncol);

/*
  Cria uma lista vazia. Ela eh duplamente encadeada e tem sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer.
*/
int inicializa_lista(t_lista *l);

/*
  Retorna 1 se a lista está vazia e zero caso contrário.
*/
int lista_vazia(t_lista *l);

/*
  Remove todos os elementos da lista e faz com que ela aponte para NULL.
*/
void destroi_lista(t_lista *l);

/*
  Retorna o tamanho da lista em *tam.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int quant_lista(int *tam, t_lista *l);

/*
  Insere o elemento item no final da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int insere_fim_lista(int lin, int col, int velocidade, int estado, char tipo[], t_lista *l);

/*
  Se o elemento chave existir na lista, o retorna em *item.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário
  (elemento não encontrado também retorna zero).
*/
int inicializa_atual_inicio(t_lista *l);

/* 
  Inicializa o ponteiro atual para o ultimo elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int inicializa_atual_fim(t_lista *l);

/*
  Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL.
*/
void incrementa_atual(t_lista *l);

/*
  Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o primeiro, isto é, não 
  tem anterior, retorna NULL.
*/
void decrementa_atual(t_lista *l);

/*
  Retorna em *item o valor contido na chave apontada pelo ponteiro atual. 
  Se atual não for válido a função retorna zero senão retorna 1.
*/
/*int consulta_item_atual(int *item, t_lista *atual);*/

/*
  Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário.
*/
int remove_item_atual(t_lista *l);
