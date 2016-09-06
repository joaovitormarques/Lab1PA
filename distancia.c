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
struct cidade ListaCidades[735];

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
//verifica se existe caminho entre duas cidades
int caminho(struct cidade a, struct cidade b){
	ListaDeVisitados[a.id] = TRUE;
	int i;
	for (i=0; i<10; i++){
		if(a.listAdj[i] == b.id){
			printf("chegou em %d\n", a.listAdj[i]);
			return TRUE;
		}
		if(!ListaDeVisitados[a.listAdj[i]]){ //se nao visitou ainda, visita
			printf("andou por %d\n", a.listAdj[i]);
			return caminho(ListaCidades[a.listAdj[i]], b);
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

	
	for(n=0; n<735; n++){
		for(i=0; i<10; i++)
			ListaCidades[n].listAdj[i] = 0;
		ListaCidades[n].id = n;
		ListaDeVisitados[n]= FALSE;
	}

	entrada = fopen("uruguai.txt", "r");
	if (entrada == NULL){
		printf("Arquivo não existe.\n");
		exit(0);
	}
	cont =1;
	n =0;
	//printf("oi\n");



	//Armazenamento da lista de cidades e suas características
	while(fgets(linha, 64, entrada)){
		token = strtok(linha, delimit); //pegou o ID da cidade, que é o cont
		token = strtok(NULL, delimit); //pegou posição x
      	ListaCidades[cont].x = atof(token);
      	token = strtok(NULL, delimit); //pegou posição y
      	ListaCidades[cont].y = atof(token);
      	n =0;
      	//printf("oi antes %d\n", cont);
      	token = strtok(NULL, delimit); //pega a lista de adjacencias
   		while(token != NULL){
   			//printf("entrou\n");
   			ListaCidades[cont].listAdj[n] = atoi(token);
			n++;
			token = strtok(NULL, delimit); //pega a lista de adjacencias
			
		}
   		//printf("oi depois %d \n", cont);
	//printf("%f", ListaCidades[0].y);
   		cont++;
	}

	printf("\n\nexiste caminho %d\n", caminho(ListaCidades[601], ListaCidades[202]));
}