#include "Variaveis.h"

void IniciaMagia(Heroi Heroi, MagiasHeroi *MagiasHeroi, ALLEGRO_BITMAP *ImagemMagia, int Tipo)
{
	MagiasHeroi->x = Heroi.x;
	MagiasHeroi->y = Heroi.y;

	MagiasHeroi->Mostrar = false;
	MagiasHeroi->Velocidade = 22;

	MagiasHeroi->Tipo = Tipo;
	MagiasHeroi->Colisao = true;

	MagiasHeroi->maxFrame = 3;
	MagiasHeroi->ColunaAnimacao = 3;
	MagiasHeroi->curFrame = 0;
	MagiasHeroi->frameWidth = 16;
	MagiasHeroi->frameHeight = 16;
	MagiasHeroi->animationDirection = 1;
	MagiasHeroi->frameCount = 0;
	MagiasHeroi->frameDelay = 2;
	MagiasHeroi->Sentido = Heroi.Sentido;

	if (Tipo == Fire) //Fogo
	{
		MagiasHeroi->LinhaAnimacao = 0;

		MagiasHeroi->GastoMana = 15;
		MagiasHeroi->Atk = rand() % 20 + 1;
		MagiasHeroi->Distancia = (MagiasHeroi->frameWidth + 16) / 2 - 10;
	}

	else if (Tipo == Ice) //GELO
	{
		MagiasHeroi->LinhaAnimacao = 1;

		MagiasHeroi->GastoMana = 25;
		MagiasHeroi->Atk = rand() % 35 + 15;
		MagiasHeroi->Distancia = (MagiasHeroi->frameWidth + 16) / 2 - 10;
	}
	else if (Tipo == Life) // Regenera
	{
		MagiasHeroi->maxFrame = 3;
		MagiasHeroi->curFrame = 0;
		MagiasHeroi->frameWidth = 147;
		MagiasHeroi->frameHeight = 141;
		MagiasHeroi->ColunaAnimacao = 7;
		MagiasHeroi->LinhaAnimacao = 0;

		MagiasHeroi->animationDirection = 1;
		MagiasHeroi->frameCount = 0;
		MagiasHeroi->frameDelay = 3;

		MagiasHeroi->GastoMana = 40;
	}
	else if (Tipo == Mort) // MORT
	{
		MagiasHeroi->maxFrame = 9;
		MagiasHeroi->curFrame = 0;
		MagiasHeroi->frameWidth = 160;
		MagiasHeroi->frameHeight = 160;

		MagiasHeroi->ColunaAnimacao = 9;
		MagiasHeroi->LinhaAnimacao = 0;
		MagiasHeroi->animationDirection = 1;
		MagiasHeroi->frameCount = 0;
		MagiasHeroi->frameDelay = 1;

		MagiasHeroi->Atk = rand() % 60 + 30;
		MagiasHeroi->GastoMana = 35;
	}

	MagiasHeroi->ImagemMagiasHeroi = ImagemMagia;
}

void DrawMagic(MagiasHeroi MagiasHeroi)
{
	if (MagiasHeroi.Mostrar)
	{
		/* Recorta a Imagem */
		int fx = (MagiasHeroi.curFrame % MagiasHeroi.ColunaAnimacao) * MagiasHeroi.frameWidth;
		int fy = MagiasHeroi.LinhaAnimacao * MagiasHeroi.frameHeight;

		/* Desenha na tela o personagem */
		al_draw_bitmap_region(MagiasHeroi.ImagemMagiasHeroi, fx, fy, MagiasHeroi.frameWidth, MagiasHeroi.frameHeight, MagiasHeroi.x - MagiasHeroi.frameWidth / 2, MagiasHeroi.y - MagiasHeroi.frameHeight / 2, 0);
	}
}

void AtkMagia(MagiasHeroi *MagiasHeroi, Heroi *Heroi)
{
	redraw = true;
	if (MagiasHeroi->Tipo == Fire || MagiasHeroi->Tipo == Ice) //é fogo e gelo
	{
		if (MagiasHeroi->Sentido == Up)
			MagiasHeroi->y -= MagiasHeroi->Velocidade;
		else if (MagiasHeroi->Sentido == Down)
			MagiasHeroi->y += MagiasHeroi->Velocidade;

		else if (MagiasHeroi->Sentido == Left)
			MagiasHeroi->x -= MagiasHeroi->Velocidade;

		else if (MagiasHeroi->Sentido == Right)
			MagiasHeroi->x += MagiasHeroi->Velocidade;
	}

	/* Faz o Evento do Sprite - Efeito da Magia */
	if (++MagiasHeroi->frameCount >= MagiasHeroi->frameDelay)
	{
		MagiasHeroi->curFrame += MagiasHeroi->animationDirection;
		if (MagiasHeroi->curFrame >= MagiasHeroi->maxFrame)
		{
			MagiasHeroi->curFrame = 0;
			MagiasHeroi->Mostrar = false;
		}
		else if (MagiasHeroi->curFrame <= 0)
			MagiasHeroi->curFrame = MagiasHeroi->maxFrame - 1;

		MagiasHeroi->frameCount = 0;
	}
}

void RegeneraVidaPersonagem(Heroi *Heroi)
{
	if (Heroi->Life < Heroi->MaxLife)
	{
		//CharPrincipal.life += rand() % (CharPrincipal.MaxLife - 76) + 1;
		Heroi->Life += 10;
		if (Heroi->Life > Heroi->MaxLife)
		{
			int VidaAux = 0;
			VidaAux = Heroi->Life - Heroi->MaxLife;
			Heroi->Life -= VidaAux;
		}
	}
}

void RegeneraMana(Heroi *Heroi)
{
	if (Heroi->Mana < Heroi->MaxMana)
	{
		Heroi->Mana += rand() % 35 + 1;
		if (Heroi->Mana > Heroi->MaxMana)
		{
			int ManaAux = 0;
			ManaAux = Heroi->Mana - Heroi->MaxMana;
			Heroi->Mana -= ManaAux;
		}
	}
}

