//BIBLIOTECAS
#include <windows.h> //PERMITE MANIPULAR DEFINIÇÕES DO CONSOLE
#include <conio2.h>
#include <stdio.h>

//CONSTANTES TECLAS
#define ENTER 13
#define ALT 18
#define ESC 27
#define CIMA 72
#define BAIXO 80

//MENU PRINCIPAL
void MENU_PRINCIPAL()
{
    CURSOR(100,1); //TAMANHO DO CURSOR (1-100);

    int X = LARGURA_CONSOLE();
    int Y = ALTURA_CONSOLE();

    INTERFACE_MENU_PRINCIPAL(X,Y);

//NAVEGAÇÃO____________________________________________________//

    int comando = NAVEGACAO((X/2)-4,(Y/2)-3,(Y/2)-3,(Y/2)+3,2);

    //NOVO JOGO
    if(comando == (Y/2)-3)
        JOGO(X,Y);
    //REGRAS
    else if(comando == (Y/2)-1)
        REGRAS(X,Y,1);
    //CRÉDITOS
    else if(comando == (Y/2)+1)
        CREDITOS(X,Y);
    //SAIR
    else if(comando == (Y/2)+3)
        MENU_SAIR(X,Y);
    //PONTUAÇÕES
    else if(comando == ESC)
        JOGADORES(X,Y);
    else
        MENU_PRINCIPAL();
}

//REGRAS BATALHA NAVAL
void REGRAS(int X, int Y, int menu)
{
    system("cls");

    cputsxy((X/2)-26,3,  "Batalha naval é um jogo de tabuleiro no qual o jogador deve");
    cputsxy((X/2)-26,4,  "adivinhar em que quadrados estão os navios do oponente para");
    cputsxy((X/2)-26,5,  "derrubá-los. O jogador vence no momento em que todos os");
    cputsxy((X/2)-26,6,  "navios forem derrubados.");
    cputsxy((X/2)-26,8,  "No jogo há 2 tabuleiros quadrados com identificação de linhas");
    cputsxy((X/2)-26,9,  "e colunas. No primeiro tabuleiro, o jogador efetua seus tiros");
    cputsxy((X/2)-26,10,  "enquanto no segundo encontram-se os barcos do adversário.");
    cputsxy((X/2)-26,11, "Antes do início do jogo, os navios são dispostos no tabuleiro");
    cputsxy((X/2)-26,12, "alinhados horizontalmente ou verticalmente, não podendo ser");
    cputsxy((X/2)-26,13, "sobrepostos.");
    cputsxy((X/2)-26,15, "Após os navios terem sido posicionados, o jogo continua numa");
    cputsxy((X/2)-26,16, "série de turnos. A cada turno o jogador seleciona um quadrado");
    cputsxy((X/2)-26,17, "identificando pela linha e coluna no tabuleiro do oponente.");
    cputsxy((X/2)-26,19, "Os tipos de navios são:");
    cputsxy((X/2)-26,21, "PORTA-AVIÕES (5 quadrados)");
    cputsxy((X/2)-26,22, "ENCOURAÇADOS (4 quadrados)");
    cputsxy((X/2)-26,23, "HIDROAVIÕES  (3 quadrados)");
    cputsxy((X/2)-26,24, "CRUZADORES   (2 quadrados)");
    cputsxy((X/2)-26,25, "SUBMARINOS   (1 quadrado)");
    cputsxy((X/2)-26,27, "Vale notar que os quadrados que compõem parte de um navio");
    cputsxy((X/2)-26,28, "estarão conectados sequencialmente ao restante.");

    cputsxy((X/2)-3,(Y-2), "Voltar");

//NAVEGAÇÃO____________________________________________________//

    if(NAVEGACAO((X/2)-5,(Y-2),(Y-2),(Y-2),0) == Y-2 || ESC)
    {
        //VOLTA AO MENU PRINCIPAL
        if(menu == 1)
            MENU_PRINCIPAL();
        //VOLTA AO MENU DO JOGO
        else
            MENU(X,Y);
    }

    else
        REGRAS(X,Y,menu);
}

//CRÉDITOS DE DESENVOLVIMENTO
void CREDITOS(int X, int Y)
{
    system("cls");

    cputsxy((X/2)-29,3,  "Jogo desenvolvido na Universidade do Vale do Itajaí (UNIVALI)");
    cputsxy((X/2)-29,4,  "no segundo semestre do curso de Engenharia da Computação,");
    cputsxy((X/2)-29,5,  "tendo como objetivo colocar em prática os conhecimentos");
    cputsxy((X/2)-29,6,  "até então adquiridos no curso, tendo em foco o uso de alocação");
    cputsxy((X/2)-29,7,  "dinâmica de memória, ponteiros e manipulação de arquivos em");
    cputsxy((X/2)-29,8,  "seu desenvolvimento.");
    cputsxy((X/2)-18,(Y-17),  "IDE de desenvolvimento: Code::Blocks");
    cputsxy((X/2)-21,(Y-16),  "Sistema operacional utilizado:  Windows 10");
    cputsxy((X/2)-7,(Y-12),  "DESENVOLVEDOR:");
    cputsxy((X/2)-6,(Y-11),  "Arthur Boss");
    cputsxy((X/2)-9,(Y-6), "2017/1 - Itajaí(SC)");

    cputsxy((X/2)-3,(Y-2), "Voltar");

//NAVEGAÇÃO____________________________________________________//

    //VOLTA AO MENU PRINCIPAL
    if(NAVEGACAO((X/2)-5,(Y-2),(Y-2),(Y-2),0) == Y-2 || ESC)
        MENU_PRINCIPAL();
    else
        CREDITOS(X,Y);
}

//MOSTRA PONTUAÇÃO DOS JOGADORES
void JOGADORES(int X, int Y)
{
	//ABERTURA DO ARQUIVO DE TEXTO COM AS PONTUAÇÕES
	FILE *leitura_arquivo = fopen ("pontos_jogadores.txt", "rt");
    char pontos_jogadores;

    system("cls");

    cputsxy((X/2)-9,5, "Pontuações");
    gotoxy((X/2)-9,7);

    if(leitura_arquivo == NULL)
        cputsxy((X/2)-9,(Y/2), "Nada encontrado");

    while((pontos_jogadores = fgetc(leitura_arquivo)) != EOF)
       putchar(pontos_jogadores);

	//FECHA O ARQUIVO
	fclose(leitura_arquivo);

	if(getch() == ESC)
        MENU_PRINCIPAL();
}

//SAIR DO APLICATIVO
void MENU_SAIR(int X, int Y)
{
    system("cls");

    cputsxy((X/2)-5,(Y/2)-1, "Sair do jogo?");
    cputsxy((X/2)-1,(Y/2)+1, "Sim");
    cputsxy((X/2)-1,(Y/2)+3, "Não");

//NAVEGAÇÃO____________________________________________________//

    int comando = NAVEGACAO((X/2)-3,(Y/2)+1,(Y/2)+1,(Y/2)+3,2);

    //SAI DO JOGO
    if(comando == (Y/2)+1)
    {
        system("cls");
        exit(0);
    }
    //VOLTA AO MENU PRINCIPAL
    else if(comando == (Y/2)+3 || ESC)
        MENU_PRINCIPAL();
    else
        MENU_SAIR(X,Y);
}

void INTERFACE_MENU_PRINCIPAL(int X, int Y)
{
    system("cls");

    //FUNDO AZUL
    textbackground(CYAN);
    cputsxy(6,1,"                                                                                                                                                                    ");
    cputsxy(4,2,"                                                                                                                                                                        ");
    cputsxy(4,3,"                                                                                                                                                                        ");
    cputsxy(4,4,"                                                                                                                                                                        ");
    cputsxy(4,5,"                                                                                                                                                                        ");
    cputsxy(4,6,"                                                                                                                                                                        ");
    cputsxy(4,7,"                                                                                                                                                                        ");
    cputsxy(4,8,"                                                                                                                                                                        ");
    cputsxy(4,9,"                                                                                                                                                                        ");
    cputsxy(4,10,"                                                                                                                                                                        ");
    cputsxy(4,11,"                                                                                                                                                                        ");
    cputsxy(4,12,"                                                                                                                                                                        ");
    cputsxy(4,13,"                                                                                                                                                                        ");
    cputsxy(4,14,"                                                                                                                                                                        ");
    cputsxy(4,15,"                                                                                                                                                                        ");
    cputsxy(4,16,"                                                                                                                                                                        ");
    cputsxy(4,17,"                                                                                                                                                                        ");
    cputsxy(4,18,"                                                                                                                                                                        ");
    cputsxy(4,19,"                                                                                                                                                                        ");
    cputsxy(4,20,"                                                                                                                                                                        ");
    cputsxy(4,21,"                                                                                                                                                                        ");
    cputsxy(4,22,"                                                                                                                                                                        ");
    cputsxy(4,23,"                                                                                                                                                                        ");
    cputsxy(4,24,"                                                                                                                                                                        ");
    cputsxy(4,25,"                                                                                                                                                                        ");
    cputsxy(4,26,"                                                                                                                                                                        ");
    cputsxy(4,27,"                                                                                                                                                                        ");
    cputsxy(4,28,"                                                                                                                                                                        ");
    cputsxy(4,29,"                                                                                                                                                                        ");
    cputsxy(4,30,"                                                                                                                                                                        ");
    cputsxy(4,31,"                                                                                                                                                                        ");
    cputsxy(4,32,"                                                                                                                                                                        ");
    cputsxy(4,33,"                                                                                                                                                                        ");
    cputsxy(4,34,"                                                                                                                                                                        ");
    cputsxy(6,35,"                                                                                                                                                                    ");

    //TÍTULO
    textcolor(WHITE);
    cputsxy(41,4,  "XXXXXXXXXX          XX      XXXXXXXXXXXX      XX        XX          XX       XX        XX      ");
    cputsxy(41,5,  " XX       XX       XXXX         XXXX         XXXX       XX          XX       XX       XXXX     ");
    cputsxy(41,6,  " XX       XX      XX  XX         XX         XX  XX      XX          XXX     XXX      XX  XX    ");
    cputsxy(41,7,  " XXXXXXXXXX      XXXXXXXX        XX        XXXXXXXX     XX          XXXXXXXXXXX     XXXXXXXX   ");
    cputsxy(41,8,  " XX       XX    XXX    XXX       XX       XXX    XXX    XX          XXX     XXX    XXX    XXX  ");
    cputsxy(41,9,  " XX       XX   XX        XX      XX      XX        XX   XXX         XX       XX   XX        XX ");
    cputsxy(41,10, "XXXXXXXXXX    XX          XX     XX     XX          XX  XXXXXXXXXX  XX       XX  XX          XX");

    cputsxy(58,26, "XXX     XX        XX    XX           XX    XX        XX        ");
    cputsxy(58,27, "XXXX    XX       XXXX    XX         XX    XXXX       XX        ");
    cputsxy(58,28, "XX XX   XX      XX  XX    XX       XX    XX  XX      XX        ");
    cputsxy(58,29, "XX  XX  XX     XXXXXXXX    XX     XX    XXXXXXXX     XX        ");
    cputsxy(58,30, "XX   XX XX    XXX    XXX    XX   XX    XXX    XXX    XX        ");
    cputsxy(58,31, "XX    XXXX   XX        XX    XX XX    XX        XX   XXX       ");
    cputsxy(58,32, "XX     XXX  XX          XX    XXX    XX          XX  XXXXXXXXXX");

//NAVIO________________________________________________________________________________________//

    //RASTRO NAVIO
    textbackground(LIGHTCYAN);
    cputsxy(50,12, "   ");
    cputsxy(40,13, "   ");
    cputsxy(37,14, "   ");
    cputsxy(39,15, "     ");
    cputsxy(41,16, "   ");
    cputsxy(41,17, "   ");
    cputsxy(41,18, "   ");
    cputsxy(41,19, "   ");
    cputsxy(41,20, "   ");
    cputsxy(39,21, "     ");
    cputsxy(37,22, "   ");
    cputsxy(40,23, "   ");
    cputsxy(50,24, "   ");
    //RASTRO 2
    cputsxy(34,15, "     ");
    cputsxy(36,16, "   ");
    cputsxy(36,17, "   ");
    cputsxy(36,18, "   ");
    cputsxy(36,19, "   ");
    cputsxy(36,20, "   ");
    cputsxy(34,21, "     ");
    //RASTRO 3
    cputsxy(25,14, "        ");
    cputsxy(18,16, "     ");
    cputsxy(31,17, "   ");
    cputsxy(20,18, "          ");
    cputsxy(31,19, "   ");
    cputsxy(18,20, "     ");
    cputsxy(25,22, "        ");

    textbackground(WHITE);
    //BORDA SUPERIOR
    cputsxy(54,12, "                                                                       ");
    //PONTA DIREITA
    cputsxy(134,13, "   ");
    cputsxy(138,15, "      ");
    cputsxy(142,16, "      ");
    cputsxy(146,17, "    ");
    cputsxy(149,18, "   ");
    cputsxy(146,19, "    ");
    cputsxy(142,20, "      ");
    cputsxy(138,21, "      ");
    cputsxy(134,23, "   ");
    //DECK SUPERIOR DIREITO
    cputsxy(140,16, "   ");
    cputsxy(140,17, "   ");
    cputsxy(140,18, "   ");
    cputsxy(140,19, "   ");
    cputsxy(140,20, "   ");
    //DECK INFERIOR DIREITO
    cputsxy(122,13, "             ");
    cputsxy(130,14, "          ");
    cputsxy(130,15, "    ");
    cputsxy(133,16, "   ");
    cputsxy(133,17, "   ");
    cputsxy(133,18, "   ");
    cputsxy(133,19, "   ");
    cputsxy(133,20, "   ");
    cputsxy(130,21, "    ");
    cputsxy(130,22, "          ");
    cputsxy(122,23, "             ");
    //PONTA ESQUERDA
    cputsxy(44,13, "             ");
    cputsxy(41,14, "          ");
    cputsxy(45,15, "      ");
    cputsxy(45,16, "      ");
    cputsxy(45,17, "    ");
    cputsxy(45,18, "   ");
    cputsxy(45,19, "    ");
    cputsxy(45,20, "      ");
    cputsxy(45,21, "      ");
    cputsxy(41,22, "          ");
    cputsxy(44,23, "             ");
    //BORDA INFERIOR
    cputsxy(54,24,  "                                                                       ");

//MENU_________________________________________________________________________________________//

    //CONTORNO AZUL
    textbackground(LIGHTCYAN);
    cputsxy((X/2)-9,(Y/2)-5, "     ");
    cputsxy((X/2)+9,(Y/2)-5, "     ");
    cputsxy((X/2)-8,(Y/2)-4, "                     ");
    cputsxy((X/2)-7,(Y/2)-3, "                   ");
    cputsxy((X/2)-6,(Y/2)-2, "                 ");
    cputsxy((X/2)-6,(Y/2)-1, "                 ");
    cputsxy((X/2)-6,(Y/2),   "                 ");
    cputsxy((X/2)-6,(Y/2)+1, "                 ");
    cputsxy((X/2)-6,(Y/2)+2, "                 ");
    cputsxy((X/2)-7,(Y/2)+3, "                   ");
    cputsxy((X/2)-8,(Y/2)+4, "                     ");
    cputsxy((X/2)-9,(Y/2)+5, "     ");
    cputsxy((X/2)+9,(Y/2)+5, "     ");

    //FUNDO BRANCO E TEXTO
    textbackground(WHITE);
    textcolor(BLACK);
    cputsxy((X/2)+10,(Y/2)-5, "   ");
    cputsxy((X/2)-8,(Y/2)-5, "   ");
    cputsxy((X/2)-7,(Y/2)-4, "                   ");
    cputsxy((X/2)-6,(Y/2)-3, "    Novo Jogo    ");
    cputsxy((X/2)-5,(Y/2)-2, "               ");
    cputsxy((X/2)-5,(Y/2)-1, "   Regras      ");
    cputsxy((X/2)-5,(Y/2),   "               ");
    cputsxy((X/2)-5,(Y/2)+1, "   Créditos    ");
    cputsxy((X/2)-5,(Y/2)+2, "               ");
    cputsxy((X/2)-6,(Y/2)+3, "    Sair         ");
    cputsxy((X/2)-7,(Y/2)+4, "                   ");
    cputsxy((X/2)-8,(Y/2)+5, "   ");
    cputsxy((X/2)+10,(Y/2)+5, "   ");
    cputsxy((X/2)-9,(Y/2)+6, "                       ");

}
