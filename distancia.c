//Exercicio 1 do lab 1 CTC-17 ->Menor distancia entre duas cidades do Uruguai

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

struct cidade{
	int id;
	float x, y;
	int listAdj[10];
};
int ListaDeVisitados[735];
int ListaDePercorridos[735]; //para auxiliar a função existe_caminho
struct cidade ListaCidades[735];
float distancia_greedy;
float distancia_aestrela;

//Calculo da distancia entre duas cidades adjacentes
float distancia(struct cidade a, struct cidade b){
	//verifica se elas são adjacentes
	int i, achou;
	achou = FALSE;
	for (i=0; i<10; i++){
		if(a.listAdj[i] == b.id){
			achou = TRUE;
			break;
		}
	}
	if (!achou)
		return 0; //retorna 0 se elas nao forem adjacentes
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y -b.y));
}

//Calculo da distancia em linha reta entre duas cidades. Para utilizar no A*
float distancia_absoluta(struct cidade a, struct cidade b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y -b.y));
}

//função para auxiliar o uso da função existe_caminho
void zerarListaDePercorridos(){
	int n;
	for(n=0; n<735; n++){
		ListaDePercorridos[n]= FALSE;
	}
}

//verifica por aquela cidade o caminho, sem voltar pra tras, se chega no destino
int existe_caminho(struct cidade a, struct cidade b){
	if(ListaDeVisitados[a.id] == TRUE)
		return FALSE;
	ListaDePercorridos[a.id] = TRUE;
	int i;
	int pode_chegar[10];
	for (i=0; i<10; i++){
		pode_chegar[i] = FALSE;
	}
	for(i=0; i<10; i++){
		if(a.listAdj[i] != 0 && !ListaDePercorridos[a.listAdj[i]]){ //é expansível
			if(a.listAdj[i] == b.id)
				return TRUE;
			pode_chegar[i] = existe_caminho(ListaCidades[a.listAdj[i]], b);
		}
	}
	for (i=0; i<10; i++){
		if(pode_chegar[i] == TRUE)
			return TRUE;
	}
	return FALSE;
}

//Implementação do algoritmo greedy
int caminho_greedy(struct cidade a, struct cidade b){
	ListaDeVisitados[a.id] = TRUE;
	int i;
	float minimo = 1000;
	for (i=0; i<10; i++){
		zerarListaDePercorridos();
		if(a.listAdj[i] != 0 && distancia(a, ListaCidades[a.listAdj[i]]) < minimo && existe_caminho(ListaCidades[a.listAdj[i]],b))
			minimo = distancia(a, ListaCidades[a.listAdj[i]]);
	}
	for (i=0; i<10; i++){
		if(a.listAdj[i] == b.id){
			distancia_greedy += distancia(a, b); //chegou na cidade desejada
			return TRUE;
		}
		if(distancia(a, ListaCidades[a.listAdj[i]]) == minimo){ //visita o mais perto
			distancia_greedy += minimo; //algoritmo greedy sempre busca o menor caminho nao visitado.
			return caminho_greedy(ListaCidades[a.listAdj[i]], b);
		}
	}
	return FALSE;

}

//Implementação do algoritmo A*
int caminho_aestrela(struct cidade a, struct cidade b){
	ListaDeVisitados[a.id] = TRUE;
	int i, destino_local;
	float minimo = 10000;
	float f_n, g_n, h_n;
	destino_local = 0;
	//Cálculo de f_n minimo
	for (i=0; i<10; i++){
		if(a.listAdj[i] != 0 && !ListaDeVisitados[a.listAdj[i]]){
			h_n = distancia_absoluta(ListaCidades[a.listAdj[i]], b);
			g_n = distancia_absoluta(a, ListaCidades[a.listAdj[i]]);
			f_n = h_n + g_n;
			if(f_n < minimo){
				//é a melhor estimativa
				minimo = f_n;
				destino_local = i; //i guarda a posição na Lista de Adj da cidade "a" com a melhor estimativa
			}
		}
	}
	for (i=0; i<10; i++){
		if(a.listAdj[i] == b.id){
			distancia_aestrela += distancia(a, b); //chegou na cidade desejada
			return TRUE;
		}
		if(!ListaDeVisitados[a.listAdj[i]]){ //se nao visitou ainda, visita o de menor f_n
			distancia_aestrela += distancia(a, ListaCidades[a.listAdj[i]]); //algoritmo greedy sempre busca o menor caminho nao visitado.
			return caminho_aestrela(ListaCidades[a.listAdj[i]], b);
		}
	}
	return FALSE;

}


void main(){
	//Declaração de variáveis
	FILE *entrada;
	char linha[60];
	const char delimit[2] = ";";
	char *token;
	int i, cont, n;


	//Inicialização de variáveis
	ListaCidades[0].x = 0;
	ListaCidades[0].y = 0;
	ListaCidades[0].id = 0;
	distancia_greedy = 0;
	distancia_aestrela = 0;
	
	for(n=0; n<735; n++){
		for(i=0; i<10; i++)
			ListaCidades[n].listAdj[i] = 0;
		ListaCidades[n].id = n;
		ListaDeVisitados[n]= FALSE;
		ListaDePercorridos[n]= FALSE;
	}

	entrada = fopen("uruguai.txt", "r");
	if (entrada == NULL){
		printf("Arquivo não existe.\n");
		exit(0);
	}
	cont =1;
	n =0;

	//Armazenamento da lista de cidades e suas características
	while(fgets(linha, 64, entrada)){
		token = strtok(linha, delimit); //pegou o ID da cidade, que é o cont
		token = strtok(NULL, delimit); //pegou posição x
      	ListaCidades[cont].x = atof(token);
      	token = strtok(NULL, delimit); //pegou posição y
      	ListaCidades[cont].y = atof(token);
      	n =0;
      	token = strtok(NULL, delimit); //pega a lista de adjacencias
   		while(token != NULL){
   			ListaCidades[cont].listAdj[n] = atoi(token);
			n++;
			token = strtok(NULL, delimit); //pega a lista de adjacencias
			
		}
   		cont++;
	}
	//zerar a lista de percorridos para rodar a função existe_caminho de novo
	for(n=0; n<735; n++){
		ListaDePercorridos[n]= FALSE;
		ListaDeVisitados[n]= FALSE;
	}
	ListaDePercorridos[202] = TRUE;
	ListaDeVisitados[202]= TRUE;
	int algoritmo_greedy = caminho_greedy(ListaCidades[202], ListaCidades[601]);
	printf("\n\n%d: a distancia greedy eh %f\n",algoritmo_greedy, distancia_greedy);

	//zerar os caminhos visitados para rodar A*
	for(n=0; n<735; n++){
		ListaDePercorridos[n]= FALSE;
		ListaDeVisitados[n]= FALSE;
	}
	ListaDePercorridos[202] = TRUE;
	ListaDeVisitados[202]= TRUE;
	int algoritmo_aestrela = caminho_aestrela(ListaCidades[601], ListaCidades[202]);
	printf("%d:a distancia A* eh %f\n", algoritmo_aestrela, distancia_aestrela);

}