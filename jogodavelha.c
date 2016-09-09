#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

//Imprimir o estado atual do jogo
void imprimeJogo(char matriz[3][3] ){
    char barra = 179; 
    printf("\t\t\t\t%c %c %c %c %c\n", matriz[0][0], barra, matriz[0][1], barra, matriz[0][2]);
    printf("\t\t\t\t__________\n");
    printf("\t\t\t\t%c %c %c %c %c\n", matriz[1][0], barra, matriz[1][1], barra, matriz[1][2]);
    printf("\t\t\t\t__________\n");
    printf("\t\t\t\t%c %c %c %c %c\n\n", matriz[2][0], barra, matriz[2][1], barra, matriz[2][2]);    
}

//verifica se a jogada eh valida
int jogadaEhValida(char matriz[3][3], int jogada){
        if(matriz[(jogada/10) - 1][(jogada%10) -1] == ' ')
            return TRUE;
        return FALSE;  
}

//pontua o cenario final do jogo
int gameOver(char matriz[3][3]){
    if ((matriz[0][0] == 'X' && matriz[1][0] == 'X' && matriz[2][0] == 'X') ||
            (matriz[0][1] == 'X' && matriz[1][1] == 'X' && matriz[2][1] == 'X') ||
            (matriz[0][2] == 'X' && matriz[1][2] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][0] == 'X' && matriz[0][1] == 'X' && matriz[0][2] == 'X') ||
            (matriz[1][0] == 'X' && matriz[1][1] == 'X' && matriz[1][2] == 'X') ||
            (matriz[2][0] == 'X' && matriz[2][1] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][0] == 'X' && matriz[1][1] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][2] == 'X' && matriz[1][1] == 'X' && matriz[2][0] == 'X')){
                return -1;  //é ruim pra AI
            }
       else if ((matriz[0][0] == 'O' && matriz[1][0] == 'O' && matriz[2][0] == 'O') ||
            (matriz[0][1] == 'O' && matriz[1][1] == 'O' && matriz[2][1] == 'O') ||
            (matriz[0][2] == 'O' && matriz[1][2] == 'O' && matriz[2][2] == 'O') ||
            (matriz[0][0] == 'O' && matriz[0][1] == 'O' && matriz[0][2] == 'O') ||
            (matriz[1][0] == 'O' && matriz[1][1] == 'O' && matriz[1][2] == 'O') ||
            (matriz[2][0] == 'O' && matriz[2][1] == 'O' && matriz[2][2] == 'O') ||
            (matriz[0][0] == 'O' && matriz[1][1] == 'O' && matriz[2][2] == 'O') ||
            (matriz[0][2] == 'O' && matriz[1][1] == 'O' && matriz[2][0] == 'O')){
                return 1; //é bom para a AI
            }
        else return 0; //deu empate ou nao acabou ainda
}

//converte um vetor linear nas posições do tabuleiro
int converte(int posic){
    switch(posic){
        case 0:
            return 11;
            break;
        case 1:
            return 12;
            break;
        case 2:
            return 13;
            break;
        case 3:
            return 21;
            break;
        case 4:
            return 22;
            break;
        case 5:
            return 23;
            break;
        case 6:
            return 31;
            break;
        case 7:
            return 32;
            break;
        case 8:
            return 33;
            break;
    }
}

//algoritmo minmax
/*-2 -> jogada ilegal
-1 -> AI perde
0 -> empate
1 -> AI ganha*/
int minmax(char matriz[3][3], int maquinaJoga){
    char auxmatriz[3][3];
    char jogador;
    int auxpossibilidades[9];
    int i, j, min, acabou, jogada;
    acabou = TRUE;

    if(maquinaJoga)
        jogador = 'O';
    else jogador = 'X';

    for(i=0; i<3; i++)
        for(j=0; j<3; j++){
            auxmatriz[i][j] = matriz[i][j];
            if(auxmatriz[i][j] == ' ')
                acabou = FALSE; //pode ou nao ter acabado
        }

    for(i=0; i<9;i++)
        auxpossibilidades[i] = -2; //se ainda for -2, é porque não atualizou

    if(gameOver(auxmatriz) != 0) //se o jogo acabou, retorna o resultado
        return gameOver(auxmatriz);
    else if(acabou)
        return 0;
    //o jogo simulado ainda nao acabou, tem que ver os melhores caminhos (ou menos piores)
    for(i=0; i<9; i++){ //forma o vetor de todas as jogadas possiveis
        jogada = converte(i);
        if(jogadaEhValida(auxmatriz, jogada)){
            auxmatriz[(jogada/10) - 1][(jogada%10) -1] = jogador;
            auxpossibilidades[i] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[(jogada/10) - 1][(jogada%10) -1] = ' ';
        }
    }
    if(!maquinaJoga){
        min = 3;
        for(i=0; i<9; i++){
            if(auxpossibilidades[i] <= min && auxpossibilidades[i] != -2){ //queremos a pior jogada
                min = auxpossibilidades[i];
                if(jogadaEhValida(auxmatriz, converte(i))){
                    jogada = converte(i);
                }
            }
        }
    }
    else {
        min = -3; //aqui na verdade é max
        for(i=0; i<9; i++){
            if(auxpossibilidades[i] >= min){ 
                min = auxpossibilidades[i];
                if(jogadaEhValida(auxmatriz, converte(i))){
                    jogada = converte(i);
                }
            }
        }
    }
    //Aqui faz a jogada e retorna a melhor/menos pior jogada válida
    auxmatriz[(jogada/10) - 1][(jogada%10) -1] = jogador;
    return minmax(auxmatriz, !maquinaJoga);
}


void main (){
    //Declaração de variáveis
    int jogada, loop, i, j, jogadaLegal;
    int maquinaJoga, maximo;
    char matriz[3][3];
    int possibilidades[9];

    //Inicialização de variáveis
    loop = 1;
    jogada = 0;
    maquinaJoga = FALSE;
    maximo = -300000;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            matriz[i][j] = ' ';
        }
    }
    for(i=0; i<9;i++)
        possibilidades[i] = -2;


    //Jogo
    printf("\n\n\t\t\tTIC-TAC-TOE\n\n");
    printf("\t\tAperte enter para comecar...\n");
    getchar();
    imprimeJogo(matriz);

    //loop principal do jogo
    while(loop < 6){
        maquinaJoga = FALSE;
        for(i=0; i<9;i++)
            possibilidades[i] = -2; //Se o vetor de possibilidades tiver algum -2, nao atualizou
        printf("\t\tDigite a posicao da matriz onde se deseja jogar o X\n");
        do{
            scanf(" %d", &jogada);
            if(jogadaEhValida(matriz, jogada)){
                matriz[(jogada/10) - 1][(jogada%10) -1] = 'X';
                break;
            }
            printf("Jogada ilegal! Tente novamente.\n");
        }while(!jogadaEhValida(matriz, jogada));
        maquinaJoga = TRUE;
        maximo = -3;
        //calcula o valor para todas as possibilidades de jogadas

        for(i=0; i<9; i++){
            jogada = converte(i);
            if(jogadaEhValida(matriz, jogada)){
                matriz[(jogada/10) - 1][(jogada%10) -1] = 'O';
                possibilidades[i] = minmax(matriz, !maquinaJoga);
                matriz[(jogada/10) - 1][(jogada%10) -1] = ' ';
            }
        }

        for(i=0; i<9; i++)
            printf("%d ", possibilidades[i]);
        printf("\n");
        //Agora analisa o vetor de possibilidades e ve qual a jogada menos pior =]

        for(i=0;i<9;i++){
                if(possibilidades[i] > maximo && possibilidades[i] != -2){
                    //antes de atribuir a jogada, verificar se ela é legal
                    if(jogadaEhValida(matriz, converte(i))){
                        jogadaLegal = i;
                        maximo = possibilidades[i];
                    }
                }
            }
            jogadaLegal = converte(jogadaLegal);
            matriz[(jogadaLegal/10) - 1][(jogadaLegal%10) -1] = 'O'; //joga de fato
        
        
    
        imprimeJogo(matriz);
        loop++;    
        //poe o resultado
        if ((matriz[0][0] == 'X' && matriz[1][0] == 'X' && matriz[2][0] == 'X') ||
            (matriz[0][1] == 'X' && matriz[1][1] == 'X' && matriz[2][1] == 'X') ||
            (matriz[0][2] == 'X' && matriz[1][2] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][0] == 'X' && matriz[0][1] == 'X' && matriz[0][2] == 'X') ||
            (matriz[1][0] == 'X' && matriz[1][1] == 'X' && matriz[1][2] == 'X') ||
            (matriz[2][0] == 'X' && matriz[2][1] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][0] == 'X' && matriz[1][1] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][2] == 'X' && matriz[1][1] == 'X' && matriz[2][0] == 'X')){
                printf("\t\t\t\tVoce ganhou!   =]\n");
                break;  //é ruim pra AI
        }
        if ((matriz[0][0] == 'O' && matriz[1][0] == 'O' && matriz[2][0] == 'O') ||
        (matriz[0][1] == 'O' && matriz[1][1] == 'O' && matriz[2][1] == 'O') ||
        (matriz[0][2] == 'O' && matriz[1][2] == 'O' && matriz[2][2] == 'O') ||
        (matriz[0][0] == 'O' && matriz[0][1] == 'O' && matriz[0][2] == 'O') ||
        (matriz[1][0] == 'O' && matriz[1][1] == 'O' && matriz[1][2] == 'O') ||
        (matriz[2][0] == 'O' && matriz[2][1] == 'O' && matriz[2][2] == 'O') ||
        (matriz[0][0] == 'O' && matriz[1][1] == 'O' && matriz[2][2] == 'O') ||
        (matriz[0][2] == 'O' && matriz[1][1] == 'O' && matriz[2][0] == 'O')){
            printf("\t\t\t\tVoce perdeu!   =[\n");
            break; //é bom para a AI
        }
        if(loop == 6){
            printf("\n\n\t\t\t\t*****Empate!*******\n");
        }
        
    }
}