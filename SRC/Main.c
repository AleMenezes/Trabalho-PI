#include "Variaveis.h"
#include <stdbool.h>

int main(int argc, char *argv[])
{
	IniciarVariaveis();

	if (!IniciarJogo())
	{
		fprintf(stderr, "Falha ao Iniciar o Jogo");
		FinalizarJogo();
		return 1;
	}

	CarregaSistema(false); //False Mostra a Barra de Loading

	// Chama Funcao	do Menu
	if (!Menu())
	{
		fprintf(stderr, "Não foi possivel Iniciar o Jogo.\n");
		FinalizarJogo();
		return -1;
	}

		/* Verifica qual opcao foi apertada no Menu */
	if (!SairJogo && (NovoJogo || CarregarJogo))
	{
		/* Looping principal do Jogo */
		GameLooping();
	}

	FinalizarJogo();

	return 0;
}
