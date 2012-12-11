#include "Variaveis.h"

bool ColisaoTotal(Heroi Heroi, Monstros Monstros, MagiasHeroi MagiasHeroi, MagiasMonstros MagiasMonstros, Itens Itens, NPC NPC, int TipoColisao, int QuaisEntidades)
{
	int Bx1;
	int By1;
	int Bx2;
	int By2;
	int x1;
	int x2;
	int y1;
	int y2;

	if (QuaisEntidades == HeroiEMonstros || QuaisEntidades == MonstrosEHeroi)
		if (!Monstros.Vivo)
			return false;

	if (TipoColisao == AtaqueMagico && QuaisEntidades == HeroiEMonstros)
		if (!MagiasHeroi.Mostrar || !MagiasHeroi.Colisao)
			return false;

	if (TipoColisao == Movimentacao && QuaisEntidades == HeroiEItens)
		if (!Itens.Mostrar)
			return false;

	if (TipoColisao == Movimentacao) //Movimento
	{
		if (QuaisEntidades == HeroiEMonstros)
		{
			Bx1 = Heroi.frameWidth / 2 - 10;
			By1 = Heroi.frameHeight / 2 - 10;
			x1 = Heroi.x;
			y1 = Heroi.y;
			Bx2 = Monstros.frameWidth / 2 - 10;
			By2 = Monstros.frameHeight / 2 - 10;
			x2 = Monstros.x;
			y2 = Monstros.y;
		}
		else if (QuaisEntidades == MonstrosEHeroi)
		{
			Bx1 = Monstros.frameWidth / 2 - 10;
			By1 = Monstros.frameHeight / 2 - 10;
			x1 = Monstros.x;
			y1 = Monstros.y;
			Bx2 = Heroi.frameWidth / 2 - 10;
			By2 = Heroi.frameHeight / 2 - 10;
			x2 = Heroi.x;
			y2 = Heroi.y;
		}

		else if (QuaisEntidades == HeroiEItens)
		{
			if (sqrt(pow(Heroi.x - Itens.x, 2) + pow(Heroi.y - Itens.y, 2)) < (Heroi.frameWidth / 2 - 10) + (Itens.frameWidth / 2 - 10))
				return true;
			else
				return false;
		}

		else if (QuaisEntidades == HeroiENPC)
		{
			Bx1 = Heroi.frameWidth / 2 - 10;
			By1 = Heroi.frameHeight / 2 - 10;
			x1 = Heroi.x;
			y1 = Heroi.y;
			Bx2 = NPC.frameWidth / 2 - 10;
			By2 = NPC.frameHeight / 2 - 10;
			x2 = NPC.x;
			y2 = NPC.y;
		}

		if (x1 + Bx1 > x2 - Bx2 && x1 - Bx1 < x2 + Bx2 && y1 + Bx1 > y2 - By2 && y1 - By1 < y2 + Bx2)
			return true;
		else
			return false;
	}
	else if (TipoColisao == AtaqueFisico) //AtaqueFisico
	{
		if (QuaisEntidades == HeroiEMonstros) //Ataque do Personagem
		{
			if (Monstros.Boss)
			{
				if ((sqrt(pow(Heroi.x - Monstros.x, 2) + pow(Heroi.y - Monstros.y, 2))) <= 100 && Monstros.Vivo)
					return true;
				else
					return false;
			}
			else
			{
				if ((sqrt(pow(Heroi.x - Monstros.x, 2) + pow(Heroi.y - Monstros.y, 2))) <= 50 && Monstros.Vivo)
					return true;
				else
					return false;
			}
		}

		else if (QuaisEntidades == MonstrosEHeroi) //Ataque dos Monstros
		{
			if (Monstros.Boss)
			{
				if ((sqrt(pow(Heroi.x - Monstros.x, 2) + pow(Heroi.y - Monstros.y, 2))) <= 100)
					return true;
				else
					return false;
			}
			else
			{
				if ((sqrt(pow(Heroi.x - Monstros.x, 2) + pow(Heroi.y - Monstros.y, 2))) <= 50)
					return true;
				else
					return false;
			}
		}
	}
	else if (TipoColisao == AtaqueMagico) //Ataque Magico
	{
		if (QuaisEntidades == HeroiEMonstros)
		{
			if (MagiasHeroi.Tipo == Fire || MagiasHeroi.Tipo == Ice)
			{
				//Colisao por Area (circulo)
				if ((sqrt(pow(MagiasHeroi.x - Monstros.x, 2) + pow(MagiasHeroi.y - Monstros.y, 2))) <= MagiasHeroi.Distancia + (Monstros.frameWidth / 2 - 10))
					return true;
				else
					return false;
			}
			else if (MagiasHeroi.Tipo == Mort)
			{
				//Colisão por distancia (Retangulo)
				int Magiabx = MagiasHeroi.frameWidth / 2 - 10;
				int Monstrosbx = Monstros.frameWidth / 2 - 10;
				int Magiaby = MagiasHeroi.frameHeight / 2 - 10;
				int Monstrosby = Monstros.frameHeight / 2 - 10;

				if (MagiasHeroi.x + Magiabx > Monstros.x - Monstrosbx && MagiasHeroi.x - Magiabx < Monstros.x + Monstrosbx && MagiasHeroi.y + Magiaby > Monstros.y - Monstrosby && MagiasHeroi.y - Magiaby < Monstros.y + Monstrosby)
					return true;
				else
					return false;
			}
		}

		else if (QuaisEntidades == MonstrosEHeroi)
		{
			//Colisao por Area (circulo)
			if ((sqrt(pow(MagiasMonstros.x - Heroi.x, 2) + pow(MagiasMonstros.y - Heroi.y, 2))) <= (MagiasMonstros.frameWidth + 16) / 2 - 10 + (Heroi.frameWidth / 2 - 10))
				return true;
			else
				return false;
		}
	}
	return false;
}

/* Verifica se tem colisao*/
int TemColisao(Heroi Heroi)
{
	int x_aux = Heroi.x / Heroi.Velocidade;
	int y_aux = Heroi.y / Heroi.Velocidade;

	if (Heroi.Sentido == Down) //Baixo
		y_aux += 1;
	else if (Heroi.Sentido == Right) //Direita
		x_aux += 1;
	else if (Heroi.Sentido == Left) //Esquerda
		x_aux -= 1;
	else if (Heroi.Sentido == Up) //Cima
		y_aux -= 1;

	if (MatrizMapaColisao[y_aux][x_aux] != 0)
		return 1;

	/* Nao existe colisao*/
	else
		return 0;
}

int TemColisaoMonster(Monstros Monstros, int Sentido)
{
	int x_aux = Monstros.x / Monstros.Velocidade;
	int y_aux = Monstros.y / Monstros.Velocidade;

	if (Sentido == Down) //Baixo
		y_aux += 1;
	else if (Sentido == Right) //Direita
		x_aux += 1;
	else if (Sentido == Left) //Esquerda
		x_aux -= 1;
	else if (Sentido == Up) //Cima
		y_aux -= 1;

	if (MatrizMapaColisaoMonster[y_aux][x_aux] != 0)
		return 1;

	/* Nao existe colisao*/
	else
		return 0;
}

void CarregaMapaColisao(Mapas Mapa)
{
	// Função utilizada para carregar os mapas de colisão
	char vLe_Char;
	int x = 0;
	int y = 0;

	FILE *fMapa;
	fMapa = fopen(Mapa.CaminhoMapaColisao, "r"); // Carrega o arquivo de texto da fase em questão

	while ((vLe_Char = getc(fMapa)) != EOF) // Grava Caracter enquanto não chegar ao final do arquivo;
	{
		if (x < Mapa.QtdColunaColisao) // Enquanto estivar na linha;
		{
			MatrizMapaColisao[y][x] = atoi(&vLe_Char); // Carrega a matriz com os caracteres que representam as imagens;
			x++;
		}
		else // senao passa para a proxima linha;
		{
			y++;
			x = 0;
		}
	}
	fclose(fMapa);
}

void CarregaMapaColisaoMonster(Mapas Mapa)
{
	// Função utilizada para carregar os mapas de colisão
	char vLe_Char;
	int x = 0;
	int y = 0;

	FILE *fMapa;
	fMapa = fopen(Mapa.CaminhoMapaColisaoMonster, "r"); // Carrega o arquivo de texto da fase em questão

	while ((vLe_Char = getc(fMapa)) != EOF) // Grava Caracter enquanto não chegar ao final do arquivo;
	{
		if (x < Mapa.QtdColunaColisaoMonster) // Enquanto estivar na linha;
		{
			MatrizMapaColisaoMonster[y][x] = atoi(&vLe_Char); // Carrega a matriz com os caracteres que representam as imagens;
			x++;
		}
		else // senao passa para a proxima linha;
		{
			y++;
			x = 0;
		}
	}
	fclose(fMapa);
}
