#include "Variaveis.h"

void CriaItem(Itens *Item, Monstros Monstro, int Tipo, ALLEGRO_BITMAP *ImagemItem)
{
	/* Adicionar código para fazer o drop de itens Raros */
	/* Logica do drop de itens raros ou semi raros
	  A cada 13 itens dropados, 1 será semi raro;
	  A cada 25 itens dropados, 1 será Semi Raro;
	 */

	AuxItemRaro += 1;
	if (AuxItemRaro == 25) //Item Raro
	{
		Tipo = 4;
		AuxItemRaro = 0;
	}

	else if (AuxItemRaro == 13) //Item Semi-Raro
		Tipo = 5;

	Item->x = Monstro.x;
	Item->y = Monstro.y;

	Item->frameWidth = 24;
	Item->frameHeight = 24;
	Item->maxFrame = 5;
	Item->curFrame = 0;
	Item->Tipo = Tipo;
	Item->ColunaAnimacao = 1;

	if (Tipo == PotionVida) //Vida
		Item->LinhaAnimacao = 3;

	else if (Tipo == PotionMana) //Mana
		Item->LinhaAnimacao = 4;

	Item->Mostrar = true;
	Item->ImagemItem = ImagemItem;
}

void DrawItem(Itens Item[])
{
	/* Recorta a Imagem */
	for (i = 0; i < MAX_MONSTROS; i++)
	{
		if (Item[i].Mostrar)
		{
			int fx = (Item[i].curFrame % Item[i].ColunaAnimacao) * Item[i].frameWidth;
			int fy = Item[i].LinhaAnimacao * Item[i].frameHeight;

			/* Desenha na tela o personagem */
			al_draw_bitmap_region(Item[i].ImagemItem, fx, fy, Item[i].frameWidth, Item[i].frameHeight, Item[i].x - Item[i].frameWidth / 2, Item[i].y - Item[i].frameHeight / 2, 0);
		}
	}
}

void ValidaColisaoItem(Heroi *Heroi, Itens *Item)
{
	//Se for Tipo 1, Reala a Vida
	if (Item->Tipo == PotionVida)
		Heroi->QtdVida++;

	// Se for Tipo 2, Reala a Mana
	else if (Item->Tipo == PotionMana)
		Heroi->QtdMana++;

	Item->Mostrar = false;
}
