//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //PERMITE A GERAÇÃO DE NÚMEROS ALEATÓRIOS
#include <windows.h> //PERMITE MANIPULAR DEFINIÇÕES DO CONSOLE
#include <conio2.h>

//CONSTANTES
#define TAMANHO 15

//CONSTANTES TECLAS
#define ENTER 13
#define ESC 27
#define CIMA 72
#define BAIXO 80
#define TAB 9
#define ESPACO 32

//SELEÇÃO DE DIFICULDADE
int NIVEL(int X, int Y)
{
    system("cls");

    cputsxy((X/2)-2,(Y/2)-1, "Fácil");
    cputsxy((X/2)-2,(Y/2)+1, "Médio");
    cputsxy((X/2)-2,(Y/2)+3, "Difícil");

//NAVEGAÇÃO____________________________________________________//

    int comando = NAVEGACAO((X/2)-4,(Y/2)-1,(Y/2)-1,(Y/2)+3,2);

    //VOLTA AO MENU PRINCIPAL
    if(comando == ESC)
        MENU_PRINCIPAL();
    //NÍVEL FÁCIL
    else if(comando == (Y/2)-1)
        return 1;
    //NÍVEL MÉDIO
    else if(comando == (Y/2)+1)
        return 2;
    //NÍVEL DIFÍCIL
    else if(comando == (Y/2)+3)
    {
        system("cls");

        cputsxy((X/2)-26,(Y/2)-2, "Este nível de dificuldade requer habilidade especiais de um");
        cputsxy((X/2)-26,(Y/2)-1, "pirata raiz. Tem certeza disso, marujo?");
        cputsxy((X/2)-1,(Y/2)+2, "Sim");
        cputsxy((X/2)-1,(Y/2)+4, "Não");

        int sub_comando = NAVEGACAO((X/2)-3,(Y/2)+2,(Y/2)+2,(Y/2)+4,2);

        //SIM
        if(sub_comando == (Y/2)+1)
            return 3;
        //NÃO
        if(sub_comando == ESC || sub_comando == (Y/2)+3)
            NIVEL(X,Y);
    }
}

//EXECUÇÃO DO JOGO
void JOGO(int X, int Y)
{
    int dificuldade = NIVEL(X,Y);

    //ALIMENTA RAND() COM NÚMEROS DIFERENTES
    srand((unsigned)time(NULL));

    int i, j;

//GERA OS NAVIOS___________________________________________//

    int **matriz = malloc(TAMANHO * sizeof(int *));
    for (i=0; i < TAMANHO; i++)
        matriz[i] =  malloc(TAMANHO * sizeof(int));
    for(i=0; i < TAMANHO; i++)
    {
        for(j=0; j < TAMANHO; j++)
            matriz[i][j] = 0;
    }

    //PORTA-AVIÕES
    NAVIOS(matriz,1,5,11);
    //ENCOURAÇADOS
    NAVIOS(matriz,2,4,12);
    //CRUZADORES
    NAVIOS(matriz,3,2,14);
    //SUBMARINOS
    NAVIOS(matriz,4,1,15);
    //HIDROAVIÕES
    HIDROAVIAO(matriz);
//_________________________________________________________//

    //MATRIZ DE TIROS
    int **matriz_jogador = malloc(TAMANHO * sizeof(int *));
    for (i=0; i < TAMANHO; i++)
        matriz_jogador[i] =  malloc(TAMANHO * sizeof(int));
    for(i=0; i < TAMANHO; i++)
    {
        for(j=0; j < TAMANHO; j++)
            matriz_jogador[i][j] = 0;
    }

    //CONTADORES
    int pontos = 0;
    int tiros_dados = 0;
    int erros = 0;
    int acertos = 0;

    //CONTADOR DE TIROS RESTANTES BASEADOS NA DIFICULDADE
    int tiros_restantes = 0;

    //DIFICULDADE CONFORME AS 38 PARTES DOS NAVIOS
    if(dificuldade == 1)
        tiros_restantes = (38*3);
    if(dificuldade == 2)
        tiros_restantes = (38*2);
    if(dificuldade == 3)
        tiros_restantes = 43;

    //POSIÇÃO DO TIRO
    int linha;
    int coluna;
    int aux;

    //POSSIBILITA MOSTRAR/OCULTAR NAVIOS
    int oculta = 1;

    //CHAMA A FUNÇÃO CORRETA PARA LINHA OU COLUNA
    int linha_coluna = 0;

    system("cls");


//DÁ INÍCIO AO JOGO_____________________________________________________//

    inicio_jogo:

    //TERMINA O JOGO SEM ERROS
    if(acertos == 38 && tiros_dados == 38)
    {
        FIM_DO_JOGO(X,Y,0,acertos,tiros_dados);

        goto final_jogo;
    }
    //TERMINA O JOGO
    if(acertos == 38 && tiros_dados != 38)
    {
        FIM_DO_JOGO(X,Y,1,acertos,tiros_dados);

        goto final_jogo;
    }
    //TERMINA O JOGO POR FALTA DE TIROS RESTANTES
    else if(tiros_restantes == 0)
    {
        FIM_DO_JOGO(X,Y,2,acertos,tiros_dados);

        goto final_jogo;
    }
    //DÁ SEGUIMENTO AO JOGO
    else
    {
        linha = RECEBE_TECLA(X,Y,(X/2)+2,5,dificuldade,pontos,tiros_dados,tiros_restantes,erros,acertos,matriz,matriz_jogador,oculta,0) - 1;
        coluna = RECEBE_TECLA(X,Y,(X/2)+2,7,dificuldade,pontos,tiros_dados,tiros_restantes,erros,acertos,matriz,matriz_jogador,oculta,1) - 1;

        //VERIFICA AONDE FOI DADO O TIRO
        if(matriz_jogador[coluna][linha] != 1)
        {
            matriz_jogador[coluna][linha] = 1;
            tiros_dados++;
            tiros_restantes--;

            //CASO TENHA ACERTADO UM NAVIO
            if(matriz[coluna][linha] != 0)
            {
                pontos += 10;
                acertos++;
                TIRO(X,Y,1,coluna,linha,matriz);
            }
            //CASO TENHA ACERTADO NA ÁGUA
            else
            {
                pontos -= 10;
                erros++;
                TIRO(X,Y,0);
            }
        }
        //CASO BLOCO JÁ LEVOU UM TIRO ANTERIORMENTE
        else
            TIRO(X,Y,2);
    }

    goto inicio_jogo;

//______________________________________________________________________//

    final_jogo:

    //LIBERA ESPAÇO DE MEMÓRIA RESERVADO PARA A MATRIZ DOS NAVIOS
    for (i=0; i < TAMANHO; i++)
        free(matriz[i]);

    free(matriz);
    matriz = NULL;

    //LIBERA ESPAÇO DE MEMÓRIA RESERVADO PARA A MATRIZ DO JOGADOR
    for (i=0; i < TAMANHO; i++)
        free(matriz_jogador[i]);

    free(matriz_jogador);
    matriz_jogador = NULL;

    //SALVA PONTUAÇÃO EM ARQUIVO DE TEXTO
    SALVA_PONTOS(X,Y,pontos);

    //VOLTA AO MENU PRINCIPAL
    MENU_PRINCIPAL();
}

//GERAÇÃO DOS NAVIOS
void NAVIOS(int **matriz, int quantidade, int tamanho_navio, int limite)
{
    int x, y, aux_x, aux_y, pos, i;

    do
    {
        inicio:

        //POSICÃO VERTICAL OU HORIZONTAL
        pos = rand()%2;

//LIMITA AS COORDENADAS PARA O NAVIO NÃO EXCEDER O TABULEIRO_______//

        //LIMITE HORIZONTAL
        if(pos == 1)
        {
            x = rand()%limite;
            y = rand()%TAMANHO;
        }
        //LIMITE VERTICAL
        else
        {
            x = rand()%TAMANHO;
            y = rand()%limite;
        }

        aux_x = x;
        aux_y = y;

//VERIFICA SE OS BLOCOS ESTÃO VAZIOS_______________________________//

        for(i=0; i < tamanho_navio; i++)
        {
            //CASO BLOCO ESTEJA OCUPADO, GERA NOVAS COORDENADAS
            if(matriz[aux_x][aux_y] != 0)
                goto inicio;

            //POSICIONA OUTROS BLOCOS DO NAVIO CONFORME A POSIÇÃO
            if(pos == 1)
                aux_x++;
            else
                aux_y++;
        }
//_________________________________________________________________//

        for(i=0; i < tamanho_navio; i++)
        {
            matriz[x][y] = tamanho_navio;

            //POSICIONA OUTRAS PARTES DO NAVIO CONFORME A POSIÇÃO
            if(pos == 1)
                x++;
            else
                y++;
        }

        quantidade--;

    }while(quantidade > 0);
}

//GERAÇÃO HIDROAVIÃO
void HIDROAVIAO(int **matriz)
{
    int x, y, aux_x, aux_y, pos, bloco_2, i;
    int quantidade = 5;

    do
    {
        sorteio:

        //POSICÃO VERTICAL OU HORIZONTAL
        pos = rand()%2;

        //INVERTE O LADO DO NAVIO
        bloco_2 = rand()%2;

//LIMITA AS COORDENADAS PARA O NAVIO NÃO EXCEDER O TABULEIRO_______//

        //LIMITE HORIZONTAL
        if(pos == 1)
        {
            x = rand()%13;
            y = 1+(rand()%13);
        }
        //LIMITE VERTICAL
        else
        {
            x = 1+(rand()%13);
            y = rand()%13;
        }

        aux_x = x;
        aux_y = y;

    //VERIFICA SE OS BLOCOS ESTÃO VAZIOS__________________________//

        for(i=0; i < 4; i++)
        {
            //CASO BLOCO ESTEJA OCUPADO, GERA NOVAS COORDENADAS
            if(matriz[aux_x][aux_y] != 0)
                goto sorteio;

            //VERIFICA OS BLOCOS SEGUINTES PARA COLOCAR O NAVIO

            //HORIZONTAL
            if(pos == 1)
            {
                aux_x++;

                //VERIFICA POSIÇÃO PARA O BLOCO DO MEIO
                if(i == 0)
                {
                    if(bloco_2 == 1)
                        aux_y++;
                    else
                        aux_y--;
                }
                else if(i == 1)
                {
                    if(bloco_2 == 1)
                        aux_y--;
                    else
                        aux_y++;
                }
                //VERIFICA ESPAÇO LIVRE PARA O MEIO DO NAVIO
                else if(i == 2)
                    aux_x -= 2;
            }
            //VERTICAL
            else
            {
                aux_y++;

                //VERIFICA POSIÇÃO PARA O BLOCO DO MEIO
                if(i == 0)
                {
                    if(bloco_2 == 1)
                        aux_x++;
                    else
                        aux_x--;
                }
                else if(i == 1)
                {
                    if(bloco_2 == 1)
                        aux_x--;
                    else
                        aux_x++;
                }
                //VERIFICA ESPAÇO LIVRE PARA O MEIO DO NAVIO
                else if(i == 2)
                    aux_y -= 2;
            }
        }
    //____________________________________________________________//

        for(i=0; i < 3; i++)
        {
            matriz[x][y] = 3;

            //POSICIONA OUTROS BLOCOS DO NAVIO CONFORME A POSIÇÃO
            //HORIZONTAL
            if(pos == 1)
            {
                x++;

                //ADICIONA BLOCO DO MEIO UMA POSIÇÃO ACIMA/ABAIXO
                if(i == 0)
                {
                    //INVERTE POSIÇÃO BLOCO DO MEIO
                    if(bloco_2 == 1)
                        y++;
                    else
                        y--;
                }
                else if(i == 1)
                {
                    //INVERTE POSIÇÃO BLOCO DO MEIO
                    if(bloco_2 == 1)
                        y--;
                    else
                        y++;
                }
            }
            //VERTICAL
            else
            {
                y++;

                //ADICIONA BLOCO DO MEIO UMA POSIÇÃO ACIMA/ABAIXO
                if(i == 0)
                {
                    //INVERTE POSIÇÃO BLOCO DO MEIO
                    if(bloco_2 == 1)
                        x++;
                    else
                        x--;
                }
                else if(i == 1)
                {
                    //INVERTE POSIÇÃO BLOCO DO MEIO
                    if(bloco_2 == 1)
                        x--;
                    else
                        x++;
                }
            }
        }

        quantidade--;

    }while(quantidade > 0);
}

//TABULEIRO DE NAVIOS
void TABULEIRO_NAVIOS(int X, int Y, int **matriz, int **matriz_jogador, int oculta)
{
    int i, j;
    int aux_y = 5;

    //FUNDO TABULEIRO
    for(i=0; i <= 30; i++)
    {
        gotoxy((X-67),4+i);
        textbackground(CYAN);
        cprintf("                                                               ");
    }

    textbackground(WHITE);

    //ÍNDICE DAS COLUNAS
    cputsxy(X-64,3, "1   2   3   4   5   6   7   8   9   10  11  12  13  14  15");
    cputsxy(X-64,35, "1   2   3   4   5   6   7   8   9   10  11  12  13  14  15");

    //ÍNDICE DAS LINHAS
    for(i=0; i < TAMANHO; i++)
    {
        //ÍNDICE DAS LINHAS
        gotoxy(X-3,aux_y);
        cprintf("%c", i+65);
        gotoxy(X-69,aux_y);
        cprintf("%c", i+65);

        aux_y += 2;
    }

    if(oculta != 1)
    {
        aux_y = 5;

        //NAVIOS
        for(i=0; i < TAMANHO; i++)
        {
            for(j=0; j < TAMANHO; j++)
            {
                gotoxy((i*4)+(X-65),5+(j*2));

                if(matriz[i][j] != 0)
                {
                    //ATRIBUI DIFERENTES CORES AOS NAVIOS
                    switch(matriz[i][j])
                    {
                        //SUBMARINO
                        case 1:
                                textbackground(BLACK);
                                printf("   ");

                                break;
                        //CRUZADOR
                        case 2:
                                textbackground(LIGHTGREEN);
                                printf("   ");

                                break;
                        //HIDROAVIÃO
                        case 3:
                                textbackground(MAGENTA);
                                printf("   ");

                                break;
                        //ENCOURAÇADO
                        case 4:
                                textbackground(LIGHTGRAY);
                                printf("   ");

                                break;
                        //PORTA AVIÃO
                        case 5:
                                textbackground(LIGHTRED);
                                printf("   ");

                                break;
                    }
                }
                //ÁGUA
                else
                {
                    textbackground(LIGHTCYAN);
                    printf("   ");
                }
            }
        }

        textbackground(WHITE);
    }

//OCULTA OS NAVIOS_____________________________________________________________________//

    else
    {
        aux_y = 5;

        //BLOCOS VAZIOS
        for(i=0; i < TAMANHO; i++)
        {
            for(j=0; j < TAMANHO; j++)
            {
                gotoxy((i*4)+(X-65),5+(j*2));

                //DESTACA NAVIOS AFUNDADOS NO TABULEIRO
                if(matriz_jogador[i][j] != 0 && matriz[i][j] != 0)
                {
                    textbackground(LIGHTRED);
                    printf("   ");
                }
                else
                {
                    textbackground(LIGHTCYAN);
                    printf("   ");
                }
            }
        }

        textbackground(WHITE);
    }
}

//TABULEIRO DE TIROS
void TABULEIRO_TIROS(int X, int Y, int **matriz_jogador)
{
    int i, j;
    int aux_y = 5;

    //FUNDO TABULEIRO
    for(i=0; i <= 30; i++)
    {
        gotoxy(6,4+i);
        textbackground(CYAN);
        cprintf("                                                               ");
    }

    textbackground(WHITE);

    //ÍNDICE DAS COLUNAS
    cputsxy(8,3,  "1   2   3   4   5   6   7   8   9   10  11  12  13  14  15");
    cputsxy(8,35, "1   2   3   4   5   6   7   8   9   10  11  12  13  14  15");

    //ÍNDICE DAS LINHAS
    for(i=0; i < TAMANHO; i++)
    {
        gotoxy(4,aux_y);
        cprintf("%c", i+65);
        gotoxy(70,aux_y);
        cprintf("%c", i+65);

        aux_y += 2;
    }

    //NAVIOS
    for(i=0; i < TAMANHO; i++)
    {
        for(j=0; j < TAMANHO; j++)
        {
            gotoxy((i*4)+8,5+(j*2));

            //DESTACA COORDENADA SELECIONADA NA MATRIZ
            if(matriz_jogador[i][j] == 1)
            {
                textbackground(BLUE);
                printf("   ");
            }
            else
            {
                textbackground(LIGHTCYAN);
                printf("   ");
            }
        }
    }

    textbackground(WHITE);
}

//ANALISA TECLA DIGITADA
int RECEBE_TECLA(int X, int Y, int COORD_X, int COORD_Y, int dificuldade, int pontos, int tiros_dados, int tiros_restantes,
                 int erros, int acertos, int **matriz, int **matriz_jogador, int oculta, int linha_coluna)
{
    //CHAMADA DAS FUNÇÕES
    TABULEIRO_TIROS(X,Y,matriz_jogador);
    TABULEIRO_NAVIOS(X,Y,matriz,matriz_jogador,oculta);
    STATUS(X,Y,dificuldade,pontos,tiros_dados,tiros_restantes,erros,acertos);

    //FUNDO DO QUADRO DE MENSAGEM DE INFORMAÇÕES DO TIRO
    textbackground(BLACK);
    cputsxy(72,11, "                                ");
    cputsxy(72,12, "                                ");
    cputsxy(72,13, "                                ");
    textbackground(WHITE);

    //PEDE LINHA E COLUNA PARA TIRO
    cputsxy((X/2)-7,5, "LINHA ");
    cputsxy((X/2)-7,7, "COLUNA ");

    //OCULTA O CURSOR
    CURSOR(1,0);

    char tecla;

    inicio_recebe_tecla:

    if(linha_coluna != 1)
        tecla = COORDENADAS_LINHAS(X,Y,COORD_X,COORD_Y,1,TAMANHO);
    else
        tecla = COORDENADAS_COLUNAS(X,Y,COORD_X,COORD_Y,1,TAMANHO);

    if(tecla == ESC)
    {
        if(MENU() == 1)
        {
            system("cls");
            return RECEBE_TECLA(X,Y,COORD_X,COORD_Y,dificuldade,pontos,tiros_dados,tiros_restantes,erros,acertos,matriz,matriz_jogador,oculta,linha_coluna);
        }
    }
    //MOSTRA OS NAVIOS TEMPORARIAMENTE
    if(tecla == ESPACO)
    {
        oculta = 0;
        TABULEIRO_NAVIOS(X,Y,matriz,matriz_jogador,oculta);
        //while(getch() != TAB){}
        goto inicio_recebe_tecla;
        //return RECEBE_TECLA(X,Y,COORD_X,COORD_Y,dificuldade,pontos,tiros_dados,tiros_restantes,erros,acertos,matriz,matriz_jogador,1,linha_coluna);
    }

    return tecla;
}

//NAVEGAÇÃO COORDENADAS DAS LINHAS
int COORDENADAS_LINHAS(int X, int Y, int COORD_X, int COORD_Y, int VALOR, int VALOR_MAX)
{
    //IMPRIME TEXTO DAS COORDENADAS NA TELA
    gotoxy(COORD_X,COORD_Y);
    textcolor(LIGHTRED);
    cprintf("%c", VALOR+64);
    textcolor(BLACK);

    int linha = getch();

    switch(linha)
    {
        case CIMA:
                   if((VALOR >= 1) && (VALOR < VALOR_MAX))
                        return COORDENADAS_LINHAS(X,Y,COORD_X, COORD_Y, VALOR+1, VALOR_MAX);
                   else
                        return COORDENADAS_LINHAS(X,Y,COORD_X, COORD_Y, VALOR=1, VALOR_MAX);

                   break;

        case BAIXO:
                   if((VALOR > 1) && (VALOR <= VALOR_MAX))
                        return COORDENADAS_LINHAS(X,Y,COORD_X, COORD_Y, VALOR-1, VALOR_MAX);
                   else
                        return COORDENADAS_LINHAS(X,Y,COORD_X, COORD_Y, VALOR=VALOR_MAX, VALOR_MAX);

                   break;

        case ENTER:
                   return VALOR;

                   break;

        case ESC:
                   gotoxy((X/2)-3,(Y-1));

                   return ESC;

                   break;

        case ESPACO:
                   return ESPACO;

                   break;

        default:
                   return COORDENADAS_LINHAS(X,Y,COORD_X, COORD_Y, VALOR, VALOR_MAX);
    }
}

//NAVEGAÇÃO COORDENADAS DAS COLUNAS
int COORDENADAS_COLUNAS(int X, int Y, int COORD_X, int COORD_Y, int VALOR, int VALOR_MAX)
{
    //IMPRIME TEXTO DAS COORDENADAS NA TELA
    gotoxy(COORD_X,COORD_Y);
    textcolor(LIGHTRED);
    cprintf("%02d", VALOR);
    textcolor(BLACK);

    int linha = getch();

    switch(linha)
    {
        case CIMA:
                   if((VALOR >= 1) && (VALOR < VALOR_MAX))
                        return COORDENADAS_COLUNAS(X,Y,COORD_X, COORD_Y, VALOR+1, VALOR_MAX);
                   else
                        return COORDENADAS_COLUNAS(X,Y,COORD_X, COORD_Y, VALOR=1, VALOR_MAX);

                   break;

        case BAIXO:
                   if((VALOR > 1) && (VALOR <= VALOR_MAX))
                        return COORDENADAS_COLUNAS(X,Y,COORD_X, COORD_Y, VALOR-1, VALOR_MAX);
                   else
                        return COORDENADAS_COLUNAS(X,Y,COORD_X, COORD_Y, VALOR=VALOR_MAX, VALOR_MAX);

                   break;

        case ENTER:
                   return VALOR;

                   break;

        case ESC:
                   gotoxy((X/2)-3,(Y-1));

                   return ESC;

                   break;

        case ESPACO:
                   return ESPACO;

                   break;

        default:
                   return COORDENADAS_COLUNAS(X,Y,COORD_X, COORD_Y, VALOR, VALOR_MAX);
    }
}

//MENSAGEM DE ACERTO OU ERRO DO TIRO
void TIRO(int X, int Y, int info, int coluna, int linha, int **matriz)
{
    textbackground(BLACK);
    textcolor(YELLOW);

    //CASO TENHA ERRADO O TIRO
    if(info == 0)
    {
        cputsxy((X/2)-2,12, "ÁGUA");
        Sleep(1000);
        cputsxy(72,11, "                                ");
        cputsxy(72,12, "                                ");
        cputsxy(72,13, "                                ");
    }
    //CASO TENHA ACERTADO O TIRO
    else if(info == 1)
    {
        //SUBMARINO
        if(matriz[coluna][linha] == 1)
        {
            cputsxy((X/2)-8,12, "SUBMARINO AFUNDOU");
            Sleep(1000);
        }
        //CRUZADOR
        else if(matriz[coluna][linha] == 2)
        {
            cputsxy((X/2)-7,12, "ACERTOU CRUZADOR");
            Sleep(1000);
        }
        //HIDROAVIÃO
        else if(matriz[coluna][linha] == 3)
        {
            cputsxy((X/2)-8,12, "ACERTOU HIDROAVIÃO");
            Sleep(1000);
        }
        //ENCOURAÇADO
        else if(matriz[coluna][linha] == 4)
        {
            cputsxy((X/2)-8,12, "ACERTOU ENCOURAÇADO");
            Sleep(1000);
        }
        //PORTA AVIÃO
        else if(matriz[coluna][linha] == 5)
        {
            cputsxy((X/2)-9,12, "ACERTOU PORTA AVIÃO");
            Sleep(1000);
        }

        cputsxy(72,11, "                                ");
        cputsxy(72,12, "                                ");
        cputsxy(72,13, "                                ");
    }
    //CASO BLOCO JÁ TENHA LEVADO TIRO ANTERIORMENTE
    else
    {
        cputsxy((X/2)-8,11, "ALVO REPETIDO     ");
        cputsxy((X/2)-8,13, "ESCOLHA OUTRO ALVO");
        Sleep(1000);
        cputsxy(72,11, "                                ");
        cputsxy(72,12, "                                ");
        cputsxy(72,13, "                                ");
    }

    textbackground(WHITE);
    textcolor(BLACK);

    //ESCONDE COORDENADA
    cputsxy((X/2)+2,7, "    ");
}

//ESTATÍSTICAS DO JOGO
void STATUS(int X, int Y, int dificuldade, int pontos,
            int tiros_dados, int tiros_restantes, int erros, int acertos)
{

//NÍVEL DE DIFICULDADE SELECIONADO_________________________//

    cputsxy((X/2)-7,Y-20, "DIFICULDADE ");
    gotoxy((X/2)-7,Y-19);

    if(dificuldade == 1)
    {
        textcolor(LIGHTCYAN);
        cprintf("FÁCIL", dificuldade);
    }
    else if(dificuldade == 2)
    {
        textcolor(LIGHTGRAY);
        cprintf("MÉDIO", dificuldade);
    }
    else
    {
        textcolor(LIGHTRED);
        cprintf("DIFÍCIL", dificuldade);
    }

    textcolor(BLACK);

//CONTADOR DE PONTOS_______________________________________//

    cputsxy((X/2)-7,Y-17, "PONTOS ");
    gotoxy((X/2)-7,Y-16);

    if(pontos == 0)
    {
        textcolor(LIGHTGRAY);
        cprintf("%04d", pontos);
    }
    else if(pontos < 60)
    {
        textcolor(LIGHTRED);
        cprintf("%04d", pontos);
    }
    else if(pontos >= 60 && pontos < 220)
    {
        textcolor(LIGHTGREEN);
        cprintf("%04d", pontos);
    }
    else
    {
        textcolor(LIGHTCYAN);
        cprintf("%04d", pontos);
    }

    textcolor(BLACK);

//CONTADOR DE TIROS DADOS__________________________________//

    cputsxy((X/2)-7,Y-14, "TIROS DADOS");
    gotoxy((X/2)-7,Y-13);

    if(tiros_dados < 10)
    {
        textcolor(LIGHTCYAN);
        cprintf("%04d", tiros_dados);
    }
    else if(tiros_dados >= 10 && tiros_dados < 100)
    {
        textcolor(LIGHTGREEN);
        cprintf("%04d", tiros_dados);
    }
    else
    {
        textcolor(LIGHTRED);
        cprintf("%04d", tiros_dados);
    }

    textcolor(BLACK);

//CONTADOR DE TIROS RESTANTES______________________________//

    cputsxy((X/2)-7,Y-11, "TIROS RESTANTES");
    gotoxy((X/2)-7,Y-10);

    if(tiros_restantes < 10)
    {
        textcolor(LIGHTRED);
        cprintf("%04d", tiros_restantes);
    }
    else if(tiros_restantes >= 10 && tiros_restantes < 100)
    {
        textcolor(LIGHTGREEN);
        cprintf("%04d", tiros_restantes);
    }
    else
    {
        textcolor(LIGHTCYAN);
        cprintf("%04d", tiros_restantes);
    }

    textcolor(BLACK);

//CONTADOR DE ACERTOS______________________________________//

    cputsxy((X/2)-7,Y-8, "ACERTOS");
    gotoxy((X/2)-7,Y-7);

    if(acertos == 0)
    {
        textcolor(LIGHTGRAY);
        cprintf("%04d", acertos);
    }
    else if(acertos < 14)
    {
        textcolor(LIGHTRED);
        cprintf("%04d", acertos);
    }
    else if(acertos >= 14 && acertos < 30)
    {
        textcolor(LIGHTGREEN);
        cprintf("%04d", acertos);
    }
    else
    {
        textcolor(LIGHTCYAN);
        cprintf("%04d", acertos);
    }

    textcolor(BLACK);

//CONTADOR DE ERROS________________________________________//

    cputsxy((X/2)-7,Y-5, "ERROS");
    gotoxy((X/2)-7,Y-4);

    if(erros < 8)
    {
        textcolor(LIGHTCYAN);
        cprintf("%04d", erros);
    }
    else if(erros >= 8 && erros < 25)
    {
        textcolor(LIGHTGREEN);
        cprintf("%04d", erros);
    }
    else
    {
        textcolor(LIGHTRED);
        cprintf("%04d", erros);
    }

    textcolor(BLACK);
}

//MENSAGEM DE FINAL DE JOGO
void FIM_DO_JOGO(int X, int Y, int caso, int acertos, int tiros_dados)
{
    //CASO VITÓRIA SEM ERROS
    if(caso == 0)
    {
        system("cls");

        textcolor(LIGHTRED);
        cputsxy((X/2)-6,(Y/2)-3, "PERFEITO!!!!");
        textcolor(BLACK);
        cputsxy((X/2)-26,(Y/2)-1, "O verdadeiro pirata que procurávamos.");
        cputsxy((X/2)-26,(Y/2), "Você derrubou todos os navios com uma precisão impecável!");
        cputsxy((X/2)-26,(Y/2)+2, "Agora, vamos rumo a conquista dos 7 mares?");

        getch();
    }
    //CASO VITÓRIA
    else if(caso == 1)
    {
        system("cls");

        textcolor(LIGHTRED);
        cputsxy((X/2)-6,(Y/2)-1, "VOCÊ GANHOU!");
        textcolor(BLACK);
        cputsxy((X/2)-26,(Y/2)+1, "Quem sabe com um pouco mais de prática você conquiste algum");
        cputsxy((X/2)-26,(Y/2)+2, "tesouro perdido nos mares?!");

        getch();
    }
    //CASO NÃO HAJA TIROS RESTANTES
    else
    {
        system("cls");

        textcolor(LIGHTRED);
        cputsxy((X/2)-6,(Y/2)-1, "VOCÊ PERDEU!");
        textcolor(BLACK);
        cputsxy((X/2)-26,(Y/2)+1, "Praticar um pouco de tiro ao alvo talvez seja uma solução viável.");
        cputsxy((X/2)-26,(Y/2)+2, "Quem sabe na próxima, marujo...");

        getch();
    }
}

//MENU DO JOGO
int MENU(int X, int Y)
{
    system("cls");
    //CURSOR TIPO BARRA
    _setcursortype(_SOLIDCURSOR);

    cputsxy((X/2)-7,(Y/2)-4, "Voltar ao jogo");
    cputsxy((X/2)-7,(Y/2)-2, "Índice / Comandos ");
    cputsxy((X/2)-7,(Y/2), "Regras");
    cputsxy((X/2)-7,(Y/2)+2, "Reiniciar jogo");
    cputsxy((X/2)-7,(Y/2)+4, "Sair ao Menu Principal");

//NAVEGAÇÃO______________________________________________________________//

    int comando = NAVEGACAO((X/2)-9,(Y/2)-4,(Y/2)-4,(Y/2)+4,2);

    //VOLTA AO JOGO
    if(comando == (Y/2)-4 || comando == ESC)
    {
        system("cls");

        return 1;
    }
    //MENU ÍNDICE / COMANDOS
    else if(comando == (Y/2)-2)
        INDICE(X,Y);
    //MENU REGRAS DO JOGO
    else if(comando == (Y/2))
        REGRAS(X,Y,2);
    //CONFIRMA A OPÇÃO DE REINICIAR O JOGO
    else if(comando == (Y/2)+2)
    {
        system("cls");

        cputsxy((X/2)-7,(Y/2)-1, "Reiniciar o jogo?");
        cputsxy((X/2)-1,(Y/2)+1, "Sim");
        cputsxy((X/2)-1,(Y/2)+3, "Não");

    //NAVEGAÇÃO____________________________________________________//

        int comando = NAVEGACAO((X/2)-3,(Y/2)+1,(Y/2)+1,(Y/2)+3,2);

        //REINICIA O JOGO
        if(comando == (Y/2)+1)
            JOGO(X,Y);
        //VOLTA AO MENU
        else
            MENU(X,Y);
    }
    //CONFIRMA O RETORNO AO MENU PRINCIPAL
    else if(comando == (Y/2)+4)
    {
        system("cls");

        cputsxy((X/2)-10,(Y/2)-1, "Voltar ao Menu Principal?");
        cputsxy((X/2)-1,(Y/2)+1, "Sim");
        cputsxy((X/2)-1,(Y/2)+3, "Não");

    //NAVEGAÇÃO____________________________________________________//

        int comando = NAVEGACAO((X/2)-3,(Y/2)+1,(Y/2)+1,(Y/2)+3,2);

        //VAI AO MENU PRINCIPAL
        if(comando == (Y/2)+1)
            MENU_PRINCIPAL();
        //VOLTA AO MENU
        else
            MENU(X,Y);
    }
    else
        MENU(X,Y);
}

//TABELA LISTA DE COMANDOS
void INDICE(int X, int Y)
{
    system("cls");

    cputsxy((X/2)-3,3, "ÍNDICE");
    cputsxy((X/2)-3,8, "NAVIOS");
    cputsxy((X/2)-18,10, "VERMELHO: Porta-Aviões (5 quadrados)");
    cputsxy((X/2)-18,11, "CINZA:    Encouraçados (4 quadrados)");
    cputsxy((X/2)-18,12, "MAGENTA:  Hidroavião   (3 quadrados)");
    cputsxy((X/2)-18,13, "VERDE:    Cruzador     (2 quadrados)");
    cputsxy((X/2)-18,14, "PRETO:    Submarino    (1 quadrado)");
    cputsxy((X/2)-8,19, "LISTA DE COMANDOS");
    cputsxy((X/2)-22,21, "SETA ACIMA: Acrescenta o valor da coordenada");
    cputsxy((X/2)-21,22, "SETA ABAIXO: Diminui o valor da coordenada");
    cputsxy((X/2)-17,23, "ESPAÇO: Revela a posição dos navios");
    cputsxy((X/2)-8,24, "ESC: Menu do jogo");
    cputsxy((X/2)-3,(Y-1), "Voltar");

//NAVEGAÇÃO____________________________________________________//

    int comando = NAVEGACAO((X/2)-5,(Y-1),(Y-1),(Y-1),0);

    //VOLTA AO MENU DO JOGO
    if(comando == Y-1 || ESC)
        MENU(X,Y);
    else
        INDICE(X,Y);
}

//SALVA PONTOS EM UM ARQUIVO DE TEXTO
void SALVA_PONTOS(int X, int Y, int pontos)
{
    //ABERTURA DO ARQUIVO DE TEXTO COM AS PONTUAÇÕES
	FILE *arquivo = fopen ("pontos_jogadores.txt", "at");

	int i = 0;
	char pontos_jogadores[3] = {'\0'};
	char jogador;

    itoa(pontos, pontos_jogadores, 10);

    char escreve_nome[6] = {'N','o','m','e',':','\0'};

    //ESCREVE NO ARQUIVO
    for(i=0; i < 6; i++)
        putc(escreve_nome[i], arquivo);

    system("cls");

    cputsxy((X/2)-9,(Y/2)-1, "Digite o seu nome:");
    gotoxy((X/2)-9,(Y/2)+1);

    do
    {
        jogador = getch();
        putc(jogador, stdout);
        fputc(jogador, arquivo);

    }while(jogador != ENTER);

    char escreve_pontos[8] = {'P','o','n','t','o','s',':','\0'};

    //ESCREVE NO ARQUIVO
    for(i=0; i < 8; i++)
        putc(escreve_pontos[i], arquivo);

    //ESCREVE NO ARQUIVO
    for(i=0; i < 3; i++)
        putc(pontos_jogadores[i], arquivo);

    char pula_linha[2] = {'\n','\n'};

    //ESCREVE NO ARQUIVO
    for(i=0; i < 2; i++)
        putc(pula_linha[i], arquivo);

	//FECHA O ARQUIVO
	fclose(arquivo);
}

