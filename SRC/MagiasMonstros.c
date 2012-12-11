#include "Variaveis.h"

void IniciaMagiasMonstros(MagiasMonstros *MagiasMonstros, Monstros Monstros, ALLEGRO_BITMAP *ImagemMagia, int Tipo)
{
	if (!MagiasMonstros->Mostrar)
	{
		MagiasMonstros->x = Monstros.x;
		MagiasMonstros->y = Monstros.y;

		MagiasMonstros->Mostrar = false;
		MagiasMonstros->Velocidade = 18;

		MagiasMonstros->Tipo = Tipo;

		MagiasMonstros->maxFrame = 3;
		MagiasMonstros->ColunaAnimacao = 3;
		MagiasMonstros->curFrame = 0;
		MagiasMonstros->frameWidth = 16;
		MagiasMonstros->frameHeight = 16;
		MagiasMonstros->animationDirection = 1;
		MagiasMonstros->frameCount = 0;

		if (Monstros.Boss)
			MagiasMonstros->frameDelay = 6;
		else
			MagiasMonstros->frameDelay = 3;

		MagiasMonstros->Sentido = Monstros.Sentido;

		if (Tipo == Fire) //Fogo
		{
			MagiasMonstros->LinhaAnimacao = 0;
			if (Monstros.Boss)
				MagiasMonstros->Atk = rand() % 13 + 1;
			else
				MagiasMonstros->Atk = rand() % 10 + 1;
		}

		else if (Tipo == Ice) //GELO
		{
			MagiasMonstros->LinhaAnimacao = 1;
			if (Monstros.Boss)
				MagiasMonstros->Atk = rand() % 18 + 5;
			else
				MagiasMonstros->Atk = rand() % 15 + 5;
		}

		else if (Tipo == Life) // Regenera
		{
			MagiasMonstros->maxFrame = 3;
			MagiasMonstros->curFrame = 0;
			MagiasMonstros->frameWidth = 147;
			MagiasMonstros->frameHeight = 141;
			MagiasMonstros->ColunaAnimacao = 7;
			MagiasMonstros->LinhaAnimacao = 0;
			MagiasMonstros->frameDelay = 4;

			MagiasMonstros->animationDirection = 1;
			MagiasMonstros->frameCount = 0;
			MagiasMonstros->frameDelay = 3;
		}

		MagiasMonstros->ImagemMagiasMonstros = ImagemMagia;
	}
}

void AtkMagiaMonstros(MagiasMonstros *MagiasMonstros, Monstros *Monstros)
{
	if (Monstros->Vivo && MagiasMonstros->Mostrar && Estado != Parado)
	{
		if (MagiasMonstros->Tipo != Life)
		{
			redraw = true;
			if (MagiasMonstros->Sentido == Up)
				MagiasMonstros->y -= MagiasMonstros->Velocidade;

			else if (MagiasMonstros->Sentido == Down)
				MagiasMonstros->y += MagiasMonstros->Velocidade;

			else if (MagiasMonstros->Sentido == Left)
				MagiasMonstros->x -= MagiasMonstros->Velocidade;

			else if (MagiasMonstros->Sentido == Right)
				MagiasMonstros->x += MagiasMonstros->Velocidade;
		}

		/* Faz o Evento do Sprite - Efeito da Magia */
		if (++MagiasMonstros->frameCount >= MagiasMonstros->frameDelay)
		{
			MagiasMonstros->curFrame += MagiasMonstros->animationDirection;
			if (MagiasMonstros->curFrame >= MagiasMonstros->maxFrame)
			{
				MagiasMonstros->curFrame = 0;
				MagiasMonstros->Mostrar = false;
				Monstros->Andar = true;
			}
			else if (MagiasMonstros->curFrame <= 0)
				MagiasMonstros->curFrame = MagiasMonstros->maxFrame - 1;

			MagiasMonstros->frameCount = 0;
		}
	}
	else
		MagiasMonstros->Mostrar = false;
}

void DrawMagicMonster(MagiasMonstros MagiasMonstros[], int QtdMonstros)
{
	for (i = 0; i < QtdMonstros; i++)
	{
		if (MagiasMonstros[i].Mostrar)
		{
			/* Recorta a Imagem */
			int fx = (MagiasMonstros[i].curFrame % MagiasMonstros[i].ColunaAnimacao) * MagiasMonstros[i].frameWidth;
			int fy = MagiasMonstros[i].LinhaAnimacao * MagiasMonstros[i].frameHeight;

			/* Desenha na tela o personagem */
			al_draw_bitmap_region(MagiasMonstros[i].ImagemMagiasMonstros, fx, fy, MagiasMonstros[i].frameWidth, MagiasMonstros[i].frameHeight, MagiasMonstros[i].x - MagiasMonstros[i].frameWidth / 2, MagiasMonstros[i].y - MagiasMonstros[i].frameHeight / 2, 0);
		}
	}
}

void RegeneraVidaMonstros(Monstros *Monstros)
{
	if (Monstros->Life < Monstros->MaxLife)
	{
		Monstros->Life += 10;
		if (Monstros->Life > Monstros->MaxLife)
		{
			int VidaAux = 0;
			VidaAux = Monstros->Life - Monstros->MaxLife;
			Monstros->Life -= VidaAux;
		}
	}
}
