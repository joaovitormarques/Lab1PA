#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Exercicio 1 do lab 1 CTC-17 ->Menor distancia entre duas cidades do Uruguai

struct cidade{
	float x, y;
	int listAdj[10];
};

void main(){
	//Declaração de variáveis
	FILE *entrada;
	char linha[60];
	const char delimit[2] = ";";
	char *token;
	struct cidade ListaCidades[735];
	int i, cont, n;


	//Inicialização de variáveis
	ListaCidades[0].x = 0;
	ListaCidades[0].y = 0;
	
	for(n=0; n<735; n++){
		for(i=0; i<10; i++)
			ListaCidades[n].listAdj[i] = 0;
	}

	entrada = fopen("uruguai.txt", "r");
	if (entrada == NULL){
		printf("Arquivo não existe.\n");
		exit(0);
	}
	cont =1;
	n =0;
	printf("oi\n");



	//Armazenamento da lista de cidades e suas características
	while(fgets(linha, 64, entrada)){
		token = strtok(linha, delimit); //pegou o ID da cidade, que é o cont
		token = strtok(NULL, delimit); //pegou posição x
      	ListaCidades[cont].x = atof(token);
      	token = strtok(NULL, delimit); //pegou posição y
      	ListaCidades[cont].y = atof(token);
      	n =0;
      	printf("oi antes %d\n", cont);
      	token = strtok(NULL, delimit); //pega a lista de adjacencias
   		while(token != NULL){
   			printf("entrou\n");
   			ListaCidades[cont].listAdj[n] = atoi(token);
			n++;
			token = strtok(NULL, delimit); //pega a lista de adjacencias
			
		}
   		printf("oi depois %d \n", cont);
	//printf("%f", ListaCidades[0].y);
   		cont++;
	}

	printf("\n\nID 732, x %f, y %f, %d,%d,%d,%d,%d\n", ListaCidades[734].x, ListaCidades[734].y, ListaCidades[734].listAdj[0],ListaCidades[734].listAdj[1],ListaCidades[734].listAdj[2],ListaCidades[734].listAdj[3],ListaCidades[734].listAdj[4]);
}