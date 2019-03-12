#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <windows.h>
#include <wincon.h>
#include <conio2.h>

//CONSTANTES TECLAS
#define ENTER 13
#define ALT 18
#define ESC 27
#define CIMA 72
#define BAIXO 80

//DEFINIÇÕES JANELA DO CONSOLE
void CONFIG_CONSOLE()
{
    //TÍTULO
    system("TITLE BATALHA NAVAL");
    //TAMANHO
    system("MODE CON: LINES=37 COLS=174");

    //COR DE FUNDO E COR DO PRIMEIRO PLANO
    textbackground(WHITE);
    textcolor(BLACK);

    //TAMANHO E VISIBILIDADE DO CURSOR
    //TAMANHO: (1-100)
    //VISIBILIDADE: 0/NÃO 1/SIM
    CURSOR(100,1);
}

//EXECUTA CONSOLE EM TELA CHEIA
void TELA_CHEIA()
{
    //EMULA TECLAS ALT+ENTER
    keybd_event(ALT,0x36,0,0);
    keybd_event(ENTER,0x1C,0,0);
    keybd_event(ENTER,0x1C,KEYEVENTF_KEYUP,0);
    keybd_event(ALT,0x38,KEYEVENTF_KEYUP,0);
}

//RECEBE INFORMAÇÕES LARGURA JANELA
int LARGURA_CONSOLE()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int colunas = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return colunas;
}

//RECEBE INFORMAÇÕES ALTURA JANELA
int ALTURA_CONSOLE()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int linhas = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return linhas;
}

//DEFINIÇÕES CURSOR
void CURSOR(int tamanho, int visivel)
{
    HANDLE hout;

    CONSOLE_CURSOR_INFO cursor; //ESTRUTURA DO CONSOLE
    hout = GetStdHandle(STD_OUTPUT_HANDLE); //CONFIGURA O HANDLE PARA SAÍDA

     //RECEBE TAMANHO DO CURSOR
    cursor.dwSize = tamanho;
     //DEFINE VISIBILIDADE DO CURSOR
    cursor.bVisible = visivel;

    SetConsoleCursorInfo(hout,&cursor);
}

//NAVEGAÇÃO PELAS LINHAS
int NAVEGACAO(int COORD_X, int COORD_Y, int Y_MIN, int Y_MAX, int AUX)
{

/*ÍNDICE COORDENADAS_______________________________________________//

    COORD_X  // COLUNA EM QUE ESTÁ O CURSOR
    COORD_Y  // LINHA EM QUE ESTÁ O CURSOR
    Y_MIN    // PRIMEIRA LINHA DE COMANDO
    Y_MAX    // ÚLTIMA LINHA DE COMANDO
    AUX      // SOMA-SE (OU DIMINUI-SE) O VALOR DO AUXILIAR CASO
                UMA LINHA NÃO ESTEJA LOGO ACIMA OU ABAIXO DA OUTRA
//_________________________________________________________________*/

    int linha;

    gotoxy(COORD_X,COORD_Y);

    linha = getch();

    switch(linha)
    {
        case CIMA:
                   if(COORD_Y > Y_MIN)
                        return NAVEGACAO(COORD_X, COORD_Y-AUX, Y_MIN, Y_MAX, AUX);

                   return NAVEGACAO(COORD_X, COORD_Y=Y_MAX, Y_MIN, Y_MAX, AUX);

                   break;

        case BAIXO:
                   if(COORD_Y < Y_MAX)
                        return NAVEGACAO(COORD_X, COORD_Y+AUX, Y_MIN, Y_MAX, AUX);

                   return NAVEGACAO(COORD_X, COORD_Y=Y_MIN, Y_MIN, Y_MAX, AUX);

                   break;

        case ENTER:
                   return COORD_Y;

                   break;

        case ESC:
                   return ESC;

                   break;

        default:
                   return NAVEGACAO(COORD_X, COORD_Y, Y_MIN, Y_MAX, AUX);
    }
}

#endif // CONFIG_H_INCLUDED
