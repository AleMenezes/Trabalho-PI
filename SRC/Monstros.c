#include "Variaveis.h"

enum ESTADO
{
	normal, perseguindo, fugindo
};

enum Andando
{
	up, down, left, right, parado
};

void IniciaMonstros(Monstros Monstros[], ALLEGRO_BITMAP *ImagemMonstro, int QtdMonstros, bool Boss)
{
	EhBoss = Boss;

	int VetorPosy[MAX_MONSTROS];
	bool Sorteia;
	int j;

	/* Obs: Para Mudar a Imagem do Monstro deve Mudar o MaxFrame, curFrame e ColunaAnimacao */
	srand(time(NULL ));
	for (i = 0; i < QtdMonstros; i++)
	{
		//Gera numeros aleatorios para posicionar os monstros
		Monstros[i].x = rand() % 1200 + 200;
		Monstros[i].y = rand() % 1328 + 336;
		VetorPosy[i] = Monstros[i].y;

		while (Monstros[i].x > 1200)
			Monstros[i].x = rand() % 1200 + 1;

		/* Verifica se já nao foi sorteado esse y */
		for (j = 0; j < MAX_MONSTROS; j++)
		{
			if (Monstros[i].y == VetorPosy[j])
				Sorteia = true;
		}

		while (Monstros[i].y > 1312 || Sorteia)
		{
			Sorteia = false;
			Monstros[i].y = rand() % 1328 + 336;
			VetorPosy[i] = Monstros[i].y;
		}


		Monstros[i].maxFrame = 3;
		Monstros[i].curFrame = 0;
		Monstros[i].curFramePadrao = 0;
		Monstros[i].frameWidth = 64;
		Monstros[i].frameHeight = 64;
		Monstros[i].ColunaAnimacao = 3;
		Monstros[i].LinhaAnimacao = 0;
		Monstros[i].animationDirection = 1;
		Monstros[i].frameCount = 0;
		Monstros[i].frameDelay = 1;

		Monstros[i].Life = 100;
		Monstros[i].MaxLife = 100;
		Monstros[i].Velocidade = 4;
		Monstros[i].ForcaAtk = 10;

		Monstros[i].Vivo = true;
		Monstros[i].DropItens = rand() % 2;
		Monstros[i].Sentido = parado;
		Monstros[i].Andar = true;
		Monstros[i].AndandoCima = false;
		Monstros[i].AndandoBaixo = false;
		Monstros[i].Foge = false;

		Monstros[i].Boss = Boss;

		if (Boss)
		{
			Monstros[i].x = 516;
			Monstros[i].y = 656;
			Monstros[i].frameWidth = 32;
			Monstros[i].frameHeight = 32;
			Monstros[i].Vivo = true;
			Monstros[i].DropItens = false;
			Monstros[i].Life = 350;
			Monstros[i].MaxLife = 350;
			Monstros[i].ForcaAtk = 20;
			Monstros[i].Velocidade = 8;
			Monstros[i].Andar = false;
		}
		Monstros[i].ImagemMonstros = ImagemMonstro;
	}
}

void DrawMonstros(Monstros Monstros[], int QtdMonstros)
{
	for (i = 0; i < QtdMonstros; i++)
	{
		if (Monstros[i].Vivo)
		{
			/* Recorta a Imagem e desenha na tela*/
			int fx = (Monstros[i].curFrame % Monstros[i].ColunaAnimacao) * Monstros[i].frameWidth;
			int fy = Monstros[i].LinhaAnimacao * Monstros[i].frameHeight;

			al_draw_bitmap_region(Monstros[i].ImagemMonstros, fx, fy, Monstros[i].frameWidth, Monstros[i].frameHeight, Monstros[i].x - Monstros[i].frameWidth / 2, Monstros[i].y - Monstros[i].frameHeight / 2, 0);
			al_draw_textf(Fonte12, al_map_rgb(255, 255, 255), Monstros[i].x - 10, Monstros[i].y - 35, 0, "%d", Monstros[i].Life);
		}
	}
}

void MovimentaMonstros(Monstros Monstros[], Heroi Heroi, int QtdMonstros)
{
	//Cria os objetos só para passar para a funcao. Não faz nada com eles.
	MagiasHeroi MagiasHeroi;
	MagiasMonstros MagiasMonstros;
	NPC NPC;
	Itens Itens;

	int i;
	int AuxPosy;
	Estado = normal; //Inicia o Estado NORMAL da IA (Não faz nada).

	for (i = 0; i < QtdMonstros; i++) //Roda o array monstros
	{
		if (Monstros[i].Vivo && Monstros[i].Andar) //Verifica se o monstro esta vivo
		{
			IA(Monstros[i], Heroi);

			switch (Estado)
			{
				case perseguindo: // Perseguindo

					/* Correção do Bug da Movimentação do Monstro */
					/* ------------------------------------------------- */
					if (Heroi.y - Monstros[i].y < Monstros[i].Velocidade && Heroi.y - Monstros[i].y > (Monstros[i].Velocidade) * -1)
					{
						AuxPosy = Heroi.y - Monstros[i].y;
						if (AuxPosy < 0)
							Monstros[i].y += AuxPosy;
						else
							Monstros[i].y -= AuxPosy;
					}
					/* ------------------------------------------------- */

					if (Monstros[i].y > Heroi.y)
						Monstros[i].Sentido = up;
					else if (Monstros[i].y < Heroi.y)
						Monstros[i].Sentido = down;
					else if (Monstros[i].x > Heroi.x)
						Monstros[i].Sentido = left;
					else if (Monstros[i].x < Heroi.x)
						Monstros[i].Sentido = right;

					if (Monstros[i].Sentido == up)
					{
						Monstros[i].y -= Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 3;
						break;
					}

					else if (Monstros[i].Sentido == Down)
					{
						Monstros[i].y += Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 0;
						break;
					}
					else if (Monstros[i].Sentido == left)
					{
						Monstros[i].x -= Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 1;
						break;
					}
					else if (Monstros[i].Sentido == right)
					{
						Monstros[i].x += Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 2;
						break;
					}
					break;
				case fugindo: // Fugindo
					Monstros[i].Sentido = -1;

					if (Monstros[i].y < Heroi.y)
					{
						//UP
						Monstros[i].y -= Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 3;
						break;
					}

					if (Monstros[i].x < Heroi.x)
					{
						//Esquerda
						Monstros[i].x -= Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 1;
						break;
					}

					if (Monstros[i].x > Heroi.x)
					{
						//Direita
						Monstros[i].x += Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 2;
						break;
					}

					if (Monstros[i].y > Heroi.y)
					{
						//Down
						Monstros[i].y += Monstros[i].Velocidade;
						Monstros[i].LinhaAnimacao = 0;
						break;
					}
					break;
			}

			/* Colisão do Monstro com o Personagem */
			if (Estado != normal)
			{
				if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros, Itens, NPC, Movimentacao, MonstrosEHeroi)) //|| ColisaoMonstroMonstro(Monstros, QtdMonstros))
				{
					if (Monstros[i].Sentido == up)
						Monstros[i].y += Monstros[i].Velocidade;
					if (Monstros[i].Sentido == down)
						Monstros[i].y -= Monstros[i].Velocidade;
					if (Monstros[i].Sentido == left)
						Monstros[i].x += Monstros[i].Velocidade;
					if (Monstros[i].Sentido == right)
						Monstros[i].x -= Monstros[i].Velocidade;
				}
			}
			if (++Monstros[i].frameCount >= Monstros[i].frameDelay)
			{
				Monstros[i].curFrame += Monstros[i].animationDirection;
				if (Monstros[i].curFrame >= Monstros[i].maxFrame)
					Monstros[i].curFrame = Monstros[i].curFramePadrao;
				else if (Monstros[i].curFrame <= Monstros[i].curFramePadrao)
					Monstros[i].curFrame = Monstros[i].maxFrame - 1;

				Monstros[i].frameCount = 0;
			}
			redraw = true;
		}
	}
}

void IA(Monstros Monstros, Heroi Heroi)
{
	int LifeAux;

	/* Calcula a distancia dos monstros até o Personagem  - Verifica se pode Seguir */
	if ((sqrt(pow(Heroi.x - Monstros.x, 2) + pow(Heroi.y - Monstros.y, 2))) < 240)
	{
		LifeAux = Monstros.MaxLife * 0.40; //Calcula 40% da vida do monstro;

		/* Se a vida do monstro for menor que 40%, o monstro foge */
		if (Monstros.Life < LifeAux)
		{
			if (Monstros.Foge)
				Estado = fugindo;
			else
				Estado = perseguindo;
		}
		else
			Estado = perseguindo;
	}

	if (Monstros.Boss)
		Estado = perseguindo;
}
