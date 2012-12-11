#include "Variaveis.h"

void IniciaHeroi(Heroi *Heroi, ALLEGRO_BITMAP *ImagemHeroi)
{
	Heroi->x = 208;
	Heroi->y = 176;

	Heroi->maxFrame = 6;
	Heroi->curFrame = 0;
	Heroi->CurFramePadrao = 0;
	Heroi->frameWidth = 60;
	Heroi->frameHeight = 64;
	Heroi->ColunaAnimacao = 3;
	Heroi->LinhaAnimacao = 0;
	Heroi->animationDirection = 1;
	Heroi->frameCount = 0;
	Heroi->frameDelay = 1;

	Heroi->Life = 100;
	Heroi->MaxLife = 100;
	Heroi->Mana = 100;
	Heroi->MaxMana = 100;
	Heroi->ForcaAtk = 15;
	Heroi->Atacou = false;
	Heroi->AtkMagia = false;

	Heroi->QtdVida = 0;
	Heroi->QtdMana = 0;

	Heroi->Sentido = Parado;
	Heroi->Velocidade = 16;

	Heroi->ImagemHeroi = ImagemHeroi;
}

void DrawHeroi(Heroi Heroi)
{
	/* Recorta a Imagem e desenha na tela*/
	int fx = (Heroi.curFrame % Heroi.ColunaAnimacao) * Heroi.frameWidth;
	int fy = Heroi.LinhaAnimacao * Heroi.frameHeight;

	al_draw_bitmap_region(Heroi.ImagemHeroi, fx, fy, Heroi.frameWidth, Heroi.frameHeight, Heroi.x - Heroi.frameWidth / 2, Heroi.y - Heroi.frameHeight / 2, 0);
}

void MovimentaHeroi(Heroi *Heroi, int iSentido)
{
	if (iSentido == Up) //Up
	{
		Heroi->LinhaAnimacao = 3;
		Heroi->Sentido = Up;
		Heroi->y -= Heroi->Velocidade;
	}
	else if (iSentido == Down) // Down
	{
		Heroi->LinhaAnimacao = 0;
		Heroi->Sentido = Down;
		Heroi->y += Heroi->Velocidade;
	}
	else if (iSentido == Left) //Left
	{
		Heroi->LinhaAnimacao = 1;
		Heroi->Sentido = Left;
		Heroi->x -= Heroi->Velocidade;
	}
	else if (iSentido == Right) //Right
	{
		Heroi->LinhaAnimacao = 2;
		Heroi->Sentido = Right;
		Heroi->x += Heroi->Velocidade;
	}

	/* Faz o Evento do Sprite, Movimentação do personagem */
	if (++Heroi->frameCount >= Heroi->frameDelay)
	{
		Heroi->curFrame += Heroi->animationDirection;
		if (Heroi->curFrame >= Heroi->maxFrame)
			Heroi->curFrame = Heroi->CurFramePadrao;
		else if (Heroi->curFrame <= Heroi->CurFramePadrao)
			Heroi->curFrame = Heroi->maxFrame - 1;

		Heroi->frameCount = 0;
	}
}

void ValidaColisaoHeroi(Heroi *Heroi, MagiasHeroi *MagiasHeroi, Monstros *Monstros, int Tipo)
{
	if (Tipo == Movimentacao) //Movimento
	{
		if (Heroi->Sentido == Up)
			Heroi->y += Heroi->Velocidade;
		if (Heroi->Sentido == Down)
			Heroi->y -= Heroi->Velocidade;
		if (Heroi->Sentido == Left)
			Heroi->x += Heroi->Velocidade;
		if (Heroi->Sentido == Right)
			Heroi->x -= Heroi->Velocidade;
	}
	else if (Tipo == AtaqueFisico) // Ataque Fisico
	{
		Monstros->Life -= rand() % Heroi->ForcaAtk + 3;
	}
	else if (Tipo == AtaqueMagico && MagiasHeroi->Tipo != Life) // Ataque Fisico
	{
		srand(time(NULL ));
		Monstros->Life -= MagiasHeroi->Atk;
		if (MagiasHeroi->Tipo != Mort)
			MagiasHeroi->Mostrar = false;
		redraw = true;
	}
}

void AtkFisicoHeroi(Heroi *Heroi, Mapas Mapa, Monstros Monstros[], int Flag)
{
	if (Flag == 0)
	{
		/* inicia as Variaveis com valores padrões para fazer a animação de ataque */
		Heroi->ImagemHeroi = ImagemHeroiAtk;
		Heroi->frameCount = 0;
		Heroi->maxFrame = 3;
		Heroi->curFrame = 0;
		Heroi->animationDirection = 1;
		Heroi->frameCount = 0;
		Heroi->frameDelay = 1;

		Heroi->Atacou = true;
	}
	else
	{
		/* Faz a Animacao de Ataque */
		if (Heroi->Atacou)
		{
			if (++Heroi->frameCount >= 2)
			{
				Heroi->curFrame += Heroi->animationDirection;
				if (Heroi->curFrame >= Heroi->maxFrame)
				{
					Heroi->curFrame = 0;
					Heroi->ImagemHeroi = ImagemHeroi;
					Heroi->Atacou = false;
				}
				else if (Heroi->curFrame <= 0)
					Heroi->curFrame = Heroi->maxFrame - 1;

				Heroi->frameCount = 0;
				redraw = true;
			}
		}
	}
}

void VerificaSentidoHeroi(Heroi *Heroi)
{
	if (Heroi->LinhaAnimacao == 0)
		Heroi->Sentido = Down;
	else if (Heroi->LinhaAnimacao == 1)
		Heroi->Sentido = Left;
	else if (Heroi->LinhaAnimacao == 2)
		Heroi->Sentido = Right;
	else if (Heroi->LinhaAnimacao == 3)
		Heroi->Sentido = Up;
}
