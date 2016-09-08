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

//algoritmo minmax
/*-3 -> jogada ilegal
-2 -> AI perde
0 -> empate
3 -> AI ganha*/
int minmax(char matriz[3][3], int maquinaJoga){
    char auxmatriz[3][3];
    int auxpossibilidades[9];
    int i, j, min;
    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            auxmatriz[i][j] = matriz[i][j];
    for(i=0; i<9;i++)
        auxpossibilidades[i] = -3;
    min = 5;
    if(!maquinaJoga){
        //verifica se X ganha
        if ((matriz[0][0] == 'X' && matriz[1][0] == 'X' && matriz[2][0] == 'X') ||
            (matriz[0][1] == 'X' && matriz[1][1] == 'X' && matriz[2][1] == 'X') ||
            (matriz[0][2] == 'X' && matriz[1][2] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][0] == 'X' && matriz[0][1] == 'X' && matriz[0][2] == 'X') ||
            (matriz[1][0] == 'X' && matriz[1][1] == 'X' && matriz[1][2] == 'X') ||
            (matriz[2][0] == 'X' && matriz[2][1] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][0] == 'X' && matriz[1][1] == 'X' && matriz[2][2] == 'X') ||
            (matriz[0][2] == 'X' && matriz[1][1] == 'X' && matriz[2][0] == 'X')){
                return -2;  //é ruim pra AI
            }
        /*if(matriz[0][0] == 'O' && matriz[0][1] == 'O'){
            if(jogadaEhValida(matriz, 13)){
                return 0;
            }
        }
        if(matriz[0][0] == 'O' && matriz[0][2] == 'O'){
            if(jogadaEhValida(matriz, 12)){
                return 0;
            }
        }
        if(matriz[0][1] == 'O' && matriz[0][2] == 'O'){
            if(jogadaEhValida(matriz, 11)){
                return 0;
            }
        }
        if(matriz[1][0] == 'O' && matriz[1][1] == 'O'){
            if(jogadaEhValida(matriz, 23)){
                return 0;
            }
        }
        if(matriz[1][0] == 'O' && matriz[1][2] == 'O'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'O' && matriz[1][2] == 'O'){
            if(jogadaEhValida(matriz, 21)){
                return 0;
            }
        }
        if(matriz[2][0] == 'O' && matriz[2][1] == 'O'){
            if(jogadaEhValida(matriz, 33)){
                return 0;
            }
        }

        if(matriz[2][0] == 'O' && matriz[2][2] == 'O'){
            if(jogadaEhValida(matriz, 32)){
                return 0;
            }
        }
        if(matriz[2][1] == 'O' && matriz[2][2] == 'O'){
            if(jogadaEhValida(matriz, 31)){
                return 0;
            }
        }

        if(matriz[0][0] == 'O' && matriz[1][0] == 'O'){
            if(jogadaEhValida(matriz, 31)){
                return 0;
            }
        }
        if(matriz[0][0] == 'O' && matriz[2][0] == 'O'){
            if(jogadaEhValida(matriz, 21)){
                return 0;
            }
        }
        if(matriz[1][0] == 'O' && matriz[2][0] == 'O'){
            if(jogadaEhValida(matriz, 11)){
                return 0;
            }
        }
        if(matriz[0][1] == 'O' && matriz[1][1] == 'O'){
            if(jogadaEhValida(matriz, 32)){
                return 0;
            }
        }
        if(matriz[0][1] == 'O' && matriz[2][1] == 'O'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'O' && matriz[2][1] == 'O'){
            if(jogadaEhValida(matriz, 12)){
                return 0;
            }
        }
        if(matriz[0][2] == 'O' && matriz[1][2] == 'O'){
            if(jogadaEhValida(matriz, 33)){
                return 0;
            }
        }
        if(matriz[0][2] == 'O' && matriz[2][2] == 'O'){
            if(jogadaEhValida(matriz, 23)){
                return 0;
            }
        }
        if(matriz[1][2] == 'O' && matriz[2][2] == 'O'){
            if(jogadaEhValida(matriz, 13)){
                return 0;
            }
        }
        if(matriz[0][0] == 'O' && matriz[1][1] == 'O'){
            if(jogadaEhValida(matriz, 33)){
                return 0;
            }
        }
        if(matriz[0][0] == 'O' && matriz[2][2] == 'O'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'O' && matriz[2][2] == 'O'){
            if(jogadaEhValida(matriz, 11)){
                return 0;
            }
        }
        if(matriz[2][0] == 'O' && matriz[1][1] == 'O'){
            if(jogadaEhValida(matriz, 13)){
                return 0;
            }
        }
        if(matriz[2][0] == 'O' && matriz[0][2] == 'O'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'O' && matriz[0][2] == 'O'){
            if(jogadaEhValida(matriz, 31)){
                return 0;
            }
        }*/
        
        //para cada jogada possivel, poe x la e chama o algoritmo de novo
        //Aqui tem que olhar a jogada menos pior
        if(jogadaEhValida(matriz, 11)){
            auxmatriz[0][0] = 'X';
            auxpossibilidades[0] =  minmax(auxmatriz, !maquinaJoga);
            auxmatriz[0][0] = ' ';
        }
        if(jogadaEhValida(matriz, 12)){
            auxmatriz[0][1] = 'X';
            auxpossibilidades[1] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[0][1] = ' ';
        }
        if(jogadaEhValida(matriz, 13)){
            auxmatriz[0][2] = 'X';
            auxpossibilidades[2] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[0][2] = ' ';
        }
        if(jogadaEhValida(matriz, 21)){
            auxmatriz[1][0] = 'X';
            auxpossibilidades[3] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[1][0] = ' ';
        }
        if(jogadaEhValida(matriz, 22)){
            auxmatriz[1][1] = 'X';
            auxpossibilidades[4] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[1][1] = ' ';
        }
        if(jogadaEhValida(matriz, 23)){
            auxmatriz[1][2] = 'X';
            auxpossibilidades[5] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[1][2] = ' ';
        }
        if(jogadaEhValida(matriz, 31)){
            auxmatriz[2][0] = 'X';
            auxpossibilidades[6] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[2][0] = ' ';
        }
        if(jogadaEhValida(matriz, 32)){
            auxmatriz[2][1] = 'X';
            auxpossibilidades[7] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[2][1] = ' ';
        }
        if(jogadaEhValida(matriz, 33)){
            auxmatriz[2][2] = 'X';
            auxpossibilidades[7] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[2][2] = ' ';
            //Verifica se o jogador humano ganhou
        
        }
    }
    else{
        //aqui a maquina joga, poe a O e ve se ela ganha
        //verifica se O ganha
        if ((matriz[0][0] == 'O' && matriz[1][0] == 'O' && matriz[2][0] == 'O') ||
            (matriz[0][1] == 'O' && matriz[1][1] == 'O' && matriz[2][1] == 'O') ||
            (matriz[0][2] == 'O' && matriz[1][2] == 'O' && matriz[2][2] == 'O') ||
            (matriz[0][0] == 'O' && matriz[0][1] == 'O' && matriz[0][2] == 'O') ||
            (matriz[1][0] == 'O' && matriz[1][1] == 'O' && matriz[1][2] == 'O') ||
            (matriz[2][0] == 'O' && matriz[2][1] == 'O' && matriz[2][2] == 'O') ||
            (matriz[0][0] == 'O' && matriz[1][1] == 'O' && matriz[2][2] == 'O') ||
            (matriz[0][2] == 'O' && matriz[1][1] == 'O' && matriz[2][0] == 'O')){
                return 2; //é bom para a AI
            }
        //fecha as possibilidades de X ganhar
        /*if(matriz[0][0] == 'X' && matriz[0][1] == 'X'){
            if(jogadaEhValida(matriz, 13)){
                return 0;
            }
        }
        if(matriz[0][0] == 'X' && matriz[0][2] == 'X'){
            if(jogadaEhValida(matriz, 12)){
                return 0;
            }
        }
        if(matriz[0][1] == 'X' && matriz[0][2] == 'X'){
            if(jogadaEhValida(matriz, 11)){
                return 0;
            }
        }
        if(matriz[1][0] == 'X' && matriz[1][1] == 'X'){
            if(jogadaEhValida(matriz, 23)){
                return 0;
            }
        }
        if(matriz[1][0] == 'X' && matriz[1][2] == 'X'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'X' && matriz[1][2] == 'X'){
            if(jogadaEhValida(matriz, 21)){
                return 0;
            }
        }
        if(matriz[2][0] == 'X' && matriz[2][1] == 'X'){
            if(jogadaEhValida(matriz, 33)){
                return 0;
            }
        }

        if(matriz[2][0] == 'X' && matriz[2][2] == 'X'){
            if(jogadaEhValida(matriz, 32)){
                return 0;
            }
        }
        if(matriz[2][1] == 'X' && matriz[2][2] == 'X'){
            if(jogadaEhValida(matriz, 31)){
                return 0;
            }
        }

        if(matriz[0][0] == 'X' && matriz[1][0] == 'X'){
            if(jogadaEhValida(matriz, 31)){
                return 0;
            }
        }
        if(matriz[0][0] == 'X' && matriz[2][0] == 'X'){
            if(jogadaEhValida(matriz, 21)){
                return 0;
            }
        }
        if(matriz[1][0] == 'X' && matriz[2][0] == 'X'){
            if(jogadaEhValida(matriz, 11)){
                return 0;
            }
        }
        if(matriz[0][1] == 'X' && matriz[1][1] == 'X'){
            if(jogadaEhValida(matriz, 32)){
                return 0;
            }
        }
        if(matriz[0][1] == 'X' && matriz[2][1] == 'X'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'X' && matriz[2][1] == 'X'){
            if(jogadaEhValida(matriz, 12)){
                return 0;
            }
        }
        if(matriz[0][2] == 'X' && matriz[1][2] == 'X'){
            if(jogadaEhValida(matriz, 33)){
                return 0;
            }
        }
        if(matriz[0][2] == 'X' && matriz[2][2] == 'X'){
            if(jogadaEhValida(matriz, 23)){
                return 0;
            }
        }
        if(matriz[1][2] == 'X' && matriz[2][2] == 'X'){
            if(jogadaEhValida(matriz, 13)){
                return 0;
            }
        }
        if(matriz[0][0] == 'X' && matriz[1][1] == 'X'){
            if(jogadaEhValida(matriz, 33)){
                return 0;
            }
        }
        if(matriz[0][0] == 'X' && matriz[2][2] == 'X'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'X' && matriz[2][2] == 'X'){
            if(jogadaEhValida(matriz, 11)){
                return 0;
            }
        }
        if(matriz[2][0] == 'X' && matriz[1][1] == 'X'){
            if(jogadaEhValida(matriz, 13)){
                return 0;
            }
        }
        if(matriz[2][0] == 'X' && matriz[0][2] == 'X'){
            if(jogadaEhValida(matriz, 22)){
                return 0;
            }
        }
        if(matriz[1][1] == 'X' && matriz[0][2] == 'X'){
            if(jogadaEhValida(matriz, 31)){
                return 0;
            }
        }*/
        
        if(jogadaEhValida(matriz, 11)){
            auxmatriz[0][0] = 'O';
            auxpossibilidades[0] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[0][0] = ' ';
        }
        if(jogadaEhValida(matriz, 12)){
            auxmatriz[0][1] = 'O';
            auxpossibilidades[1] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[0][1] = ' ';
        }
        if(jogadaEhValida(matriz, 13)){
            auxmatriz[0][2] = 'O';
            auxpossibilidades[2] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[0][2] = ' ';
        }
        if(jogadaEhValida(matriz, 21)){
            auxmatriz[1][0] = 'O';
            auxpossibilidades[3] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[1][0] = ' ';
        }
        if(jogadaEhValida(matriz, 22)){
            auxmatriz[1][1] = 'O';
            auxpossibilidades[4] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[1][1] = ' ';
        }
        if(jogadaEhValida(matriz, 23)){
            auxmatriz[1][2] = 'O';
            auxpossibilidades[5] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[1][2] = ' ';
        }
        if(jogadaEhValida(matriz, 31)){
            auxmatriz[2][0] = 'O';
            auxpossibilidades[6] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[2][0] = ' ';
        }
        if(jogadaEhValida(matriz, 32)){
            auxmatriz[2][1] = 'O';
            auxpossibilidades[7] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[2][1] = ' ';
        }
        if(jogadaEhValida(matriz, 33)){
            auxmatriz[2][2] = 'O';
            auxpossibilidades[8] = minmax(auxmatriz, !maquinaJoga);
            auxmatriz[2][2] = ' ';
        }
    }
    for(i=0; i<9; i++){
        if(auxpossibilidades[i] <= min) //queremos a pior jogada
            min = auxpossibilidades[i];
    }
    return min;
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
    maximo = -5;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            matriz[i][j] = ' ';
        }
    }
    for(i=0; i<9;i++)
        possibilidades[i] = -2;


    //Jogo
    printf("\t\tTIC-TAC-TOE\n\n");
    printf("\t\tAperte enter para comecar...\n");
    getchar();
    imprimeJogo(matriz);
    while(loop < 8){
        for(i=0; i<9;i++)
            possibilidades[i] = -3;
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
        maximo = -5;
        for(i=0; i<9;i++){
            possibilidades[i] = minmax(matriz, maquinaJoga);
            printf("%d ", possibilidades[i]);
        }
        printf("\n");
        //Agora analisa o vetor de possibilidades e ve qual a jogada menos pior =]
        for(i=0;i<9;i++){
            if(possibilidades[i] >= maximo){
                maximo = possibilidades[i];
                //antes de atribuir a jogada, verificar se ela é legal
                switch(i){
            case 0:
                if(jogadaEhValida(matriz, 11)){
                    jogadaLegal = i;
                    printf("ninja\n");
                }
                break;
            case 1:
                if(jogadaEhValida(matriz, 12))
                    jogadaLegal = i;
                break;
            case 2:
                if(jogadaEhValida(matriz, 13))
                    jogadaLegal = i;
                break;
            case 3:
                if(jogadaEhValida(matriz, 21))
                    jogadaLegal = i;
                break;
            case 4:
                if(jogadaEhValida(matriz, 22))
                    jogadaLegal = i;
                break;
            case 5:
                if(jogadaEhValida(matriz, 23))
                    jogadaLegal = i;
                break;
            case 6:
                if(jogadaEhValida(matriz, 31))
                    jogadaLegal = i;
                break;
            case 7:
                if(jogadaEhValida(matriz, 32))
                    jogadaLegal = i;
                break;
            case 8:
                if(jogadaEhValida(matriz, 33))
                    jogadaLegal = i;
                break;
                
                }
            }
        }
        switch(jogadaLegal){
            case 0:
                matriz[0][0] = 'O';
                break;
            case 1:
                matriz[0][1] = 'O';
                break;
            case 2:
                matriz[0][2] = 'O';
                break;
            case 3:
                matriz[1][0] = 'O';
                break;
            case 4:
                matriz[1][1] = 'O';
                break;
            case 5:
                matriz[1][2] = 'O';
                break;
            case 6:
                matriz[2][0] = 'O';
                break;
            case 7:
                matriz[2][1] = 'O';
                break;
            case 8:
                matriz[2][2] = 'O';
                break;
        }
    
    
    
    
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
        if(loop == 8){
            printf("\n\n\t\t\t\t*****Empate!*******\n");
        }
        
    }
}