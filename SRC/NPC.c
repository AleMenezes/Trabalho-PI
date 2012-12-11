#include "Variaveis.h"

void CriaNPC(NPC *NPC, int Tipo, int x, int y, ALLEGRO_BITMAP *ImagemNPCs, int Estado, int QtdDialogos, ...)
{
	/* Utilizado para pegar todas as falas do personagem */
	NPC->QtdFalas = QtdDialogos;

	va_list values;
	int Pos = 0;
	va_start( values, QtdDialogos);
	while (QtdDialogos--)
	{
		NPC->FalaNPC[Pos] = va_arg ( values, char* );
		Pos++;
	}
	va_end( values);

	/* Inicia o NPC */
	NPC->x = x;
	NPC->y = y;
	NPC->LimiteX1 = 0;
	NPC->LimiteX2 = 0;
	NPC->LimiteY1 = 0;
	NPC->LimiteY2 = 0;
	NPC->Tipo = Tipo;

	NPC->Velocidade = 2;
	NPC->frameWidth = 32;
	NPC->frameHeight = 32;
	NPC->LinhaAnimacao = 1; /* padrao o personagem virado pra cima */
	NPC->animationDirection = 1;
	NPC->frameCount = 0;
	NPC->frameDelay = 1;

	if (Tipo == NPCMagia)
	{
		NPC->ColunaAnimacao = 3;
		NPC->maxFrame = 3;
		NPC->curFrame = 0;
		NPC->curFramePadrao = 0;
		NPC->LimiteX1 = 400;
		NPC->LimiteX2 = 270;
	}
	else if (Tipo == NPCArmadura)
	{
		NPC->ColunaAnimacao = 6;
		NPC->maxFrame = 6;
		NPC->curFrame = 3;
		NPC->curFramePadrao = 3;
		NPC->LimiteX1 = 592;
		NPC->LimiteX2 = 464;
	}
	else if (Tipo == NPCCurandeira)
	{
		NPC->ColunaAnimacao = 9;
		NPC->maxFrame = 9;
		NPC->curFrame = 6;
		NPC->curFramePadrao = 6;
		NPC->maxFrame = 3; //Deve Mudar, porque só tem ela no mapa
		NPC->LimiteX1 = 400;
		NPC->LimiteX2 = 270;
	}

	else if (Tipo == NPCCivil)
	{
		NPC->ColunaAnimacao = 12;
		NPC->maxFrame = 12;
		NPC->curFrame = 9;
		NPC->curFramePadrao = 9;
		NPC->LimiteX1 = 640;
		NPC->LimiteX2 = 480;
		NPC->LimiteY1 = 708;
		NPC->LimiteY2 = 772;
	}
	else if (Tipo == NPCGuarda)
	{
		NPC->ColunaAnimacao = 15;
		NPC->maxFrame = 15;
		NPC->curFrame = 12;
		NPC->curFramePadrao = 12;
		NPC->LimiteX1 = 752;
		NPC->LimiteX2 = 640;
	}
	else if (Tipo == NPCAgricultor)
	{
		NPC->ColunaAnimacao = 18;
		NPC->maxFrame = 18;
		NPC->curFrame = 15;
		NPC->curFramePadrao = 15;
	}
	else if (Tipo == NPCIdoso)
	{
		NPC->ColunaAnimacao = 21;
		NPC->maxFrame = 21;
		NPC->curFrame = 18;
		NPC->curFramePadrao = 18;
		NPC->maxFrame = 3;
	}

	else if (Tipo == Placa)
	{
		NPC->ColunaAnimacao = 24;
		NPC->maxFrame = 24;
		NPC->curFrame = 21;
		NPC->curFramePadrao = 21;
	}

	/* Cria NPC para Ficarem Parados */
	if (Estado == Parado)
	{
		NPC->LimiteX1 = 0;
		NPC->LimiteX2 = 0;
		NPC->LimiteY1 = 0;
		NPC->LimiteY2 = 0;
		NPC->maxFrame = 3;
	}

	NPC->Sentido = Right;
	NPC->Estado = Mudo;

	NPC->ImagemNPC = ImagemNPCs;
}

void DrawNPC(struct NPC NPC[], int QtdNPC)
{
	for (i = 0; i < QtdNPC; i++)
	{
		/* Recorta a Imagem */
		int fx = (NPC[i].curFrame % NPC[i].ColunaAnimacao) * NPC[i].frameWidth;
		int fy = NPC[i].LinhaAnimacao * NPC[i].frameHeight;

		/* Desenha na tela o personagem */
		al_draw_bitmap_region(NPC[i].ImagemNPC, fx, fy, NPC[i].frameWidth, NPC[i].frameHeight, NPC[i].x - NPC[i].frameWidth / 2, NPC[i].y - NPC[i].frameHeight / 2, 0);
	}
}

void MovimentaNPC(NPC NPC[], int QtdNPC, Heroi Heroi)
{
	/* Deve ser criado aqui só para não dar erro, pois a função precisa desses parametros */
	MagiasHeroi MagiasHeroi;
	MagiasMonstros MagiasMonstros;
	Itens Itens;
	Monstros Monstros;

	for (i = 0; i < QtdNPC; i++)
	{
		if (NPC[i].Estado == Mudo && NPC[i].Tipo != Placa)
		{
			/* Valida se o NPC deve andar somente para os lados ou não */
			if (NPC[i].LimiteY1 != 0 && NPC[i].LimiteY2 != 0)
			{
				//Right
				if ((NPC[i].x <= NPC[i].LimiteX1) && (NPC[i].Sentido == Right))
				{
					NPC[i].x += NPC[i].Velocidade;
					NPC[i].LinhaAnimacao = 2;
				}
				else if ((NPC[i].x >= NPC[i].LimiteX1) && (NPC[i].Sentido == Right))
					NPC[i].Sentido = Up;

				//Up
				if ((NPC[i].y >= NPC[i].LimiteY1) && (NPC[i].Sentido == Up))
				{
					NPC[i].y -= NPC[i].Velocidade;
					NPC[i].LinhaAnimacao = 3;
				}
				else if ((NPC[i].y <= NPC[i].LimiteY1) && (NPC[i].Sentido == Up))
					NPC[i].Sentido = Left;

				//Left
				if ((NPC[i].x >= NPC[i].LimiteX2) && (NPC[i].Sentido == Left))
				{
					NPC[i].x -= NPC[i].Velocidade;
					NPC[i].LinhaAnimacao = 1;
				}
				else if ((NPC[i].x <= NPC[i].LimiteX2) && (NPC[i].Sentido == Left))
					NPC[i].Sentido = Down;

				//Down
				if ((NPC[i].y <= NPC[i].LimiteY2) && (NPC[i].Sentido == Down))
				{
					NPC[i].y += NPC[i].Velocidade;
					NPC[i].LinhaAnimacao = 0;
				}
				else if ((NPC[i].y >= NPC[i].LimiteY2) && (NPC[i].Sentido == Down))
					NPC[i].Sentido = Right;
			}
			else if (NPC[i].LimiteX1 != 0 && NPC[i].LimiteX2 != 0)
			{
				//Right
				if ((NPC[i].x <= NPC[i].LimiteX1) && (NPC[i].Sentido == Right))
				{
					NPC[i].x += NPC[i].Velocidade;
					NPC[i].LinhaAnimacao = 2;
				}
				else if ((NPC[i].x >= NPC[i].LimiteX1) && (NPC[i].Sentido == Right))
					NPC[i].Sentido = Left;

				//Left
				if ((NPC[i].x >= NPC[i].LimiteX2) && (NPC[i].Sentido == Left))
				{
					NPC[i].x -= NPC[i].Velocidade;
					NPC[i].LinhaAnimacao = 1;
				}
				else if ((NPC[i].x <= NPC[i].LimiteX2) && (NPC[i].Sentido == Left))
					NPC[i].Sentido = Right;
			}

			if (ColisaoTotal(Heroi, Monstros, MagiasHeroi, MagiasMonstros, Itens, NPC[i], Movimentacao, HeroiENPC))
			{
				if (NPC[i].Sentido == Right)
					NPC[i].x -= NPC[i].Velocidade;
				else if (NPC[i].Sentido == Left)
					NPC[i].x += NPC[i].Velocidade;
				else if (NPC[i].Sentido == Up)
					NPC[i].y += NPC[i].Velocidade;
				else if (NPC[i].Sentido == Down)
					NPC[i].y -= NPC[i].Velocidade;
			}
			else
			{
				if (++NPC[i].frameCount >= NPC[i].frameDelay)
				{
					NPC[i].curFrame += NPC[i].animationDirection;
					if (NPC[i].curFrame >= NPC[i].maxFrame)
						NPC[i].curFrame = NPC[i].curFramePadrao;
					else if (NPC[i].curFrame <= NPC[i].curFramePadrao)
						NPC[i].curFrame = NPC[i].maxFrame - 1;

					NPC[i].frameCount = 0;
				}
			}
		}
	}
}

void ValidaNPC(NPC NPC[], Heroi *Heroi, int QtdNPC)
{
	for (i = 0; i < QtdNPC; i++)
	{
		if (sqrt(pow(Heroi->x - NPC[i].x, 2) + pow(Heroi->y - NPC[i].y, 2)) < 90)
		{
			/* Faz a Validação de qual lado deve ser mostrado o NPC */
			/* ---------------------------------------------------- */
			if (Heroi->Sentido == Up && NPC[i].y > Heroi->y)
				return;
			else if (Heroi->Sentido == Down && NPC[i].y < Heroi->y)
				return;
			else if (Heroi->Sentido == Left && NPC[i].x > Heroi->x)
				return;
			else if (Heroi->Sentido == Right && NPC[i].x < Heroi->x)
				return;

			if (Heroi->Sentido == Up)
				NPC[i].LinhaAnimacao = 0;
			else if (Heroi->Sentido == Down)
				NPC[i].LinhaAnimacao = 3;
			else if (Heroi->Sentido == Left)
				NPC[i].LinhaAnimacao = 2;
			else if (Heroi->Sentido == Right)
				NPC[i].LinhaAnimacao = 1;
			NPC[i].Estado = Falando;
			/* ---------------------------------------------------- */

			/* Valida O Que o NPC deve Fazer */
			if (NPC[i].Tipo != NPCCurandeira)
			{
				NPCFalando(&NPC[i]);
				NPC[i].Estado = Mudo;
			}
			else
			{
				NPCFalando(&NPC[i]);
				Heroi->Life = Heroi->MaxLife;
				Heroi->Mana = Heroi->MaxMana;
				Heroi->AtkMagia = true;
				NPC[i].Estado = Mudo;
			}
		}
	}
}

void NPCFalando(NPC *NPC)
{
	ALLEGRO_FONT *FonteFala = al_load_font("Arial.ttf", 16, 0);
	bool Sair;

	FadeOut(5, 150);
	Sair = true;
	int PosFala = 0;
	bool Redraw = true;

	ALLEGRO_EVENT evento;
	ALLEGRO_TIMEOUT timeout;
	al_init_timeout(&timeout, 0.05);

	while (Sair)
	{
		int tem_eventos = al_wait_for_event_until(Fila_Eventos, &evento, &timeout);
		if (tem_eventos)
		{
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_S)
			{
				if (PosFala >= NPC->QtdFalas)
				{
					Redraw = false;
					Sair = false;
					break;
				}
				else
				{
					Redraw = true;
				}
			}

		}

		if (Redraw)
		{
			Redraw = false;
			/* Desenha a Borda do Retangulo */
			al_draw_rectangle(cameraPosition[0], cameraPosition[1] + (ALTURA_TELA - 80), cameraPosition[0] + LARGURA_TELA, cameraPosition[1] + ALTURA_TELA, al_map_rgb(255, 255, 255), 2);
			al_draw_filled_rectangle(cameraPosition[0], cameraPosition[1] + (ALTURA_TELA - 80), cameraPosition[0] + LARGURA_TELA, cameraPosition[1] + ALTURA_TELA, al_map_rgb(240, 255, 113));

			/* Escreve o Texto na Tela */
			al_draw_textf(FonteFala, al_map_rgb(0, 0, 0), cameraPosition[0] + 30, cameraPosition[1] + (ALTURA_TELA - 70), 0, "%s", NPC->FalaNPC[PosFala]);
			al_draw_text(Fonte12, al_map_rgb(0, 0, 0), cameraPosition[0] + (LARGURA_TELA - 80), ((cameraPosition[1] + (ALTURA_TELA - 100) + cameraPosition[1] + ALTURA_TELA) / 2) + 30, 0, "Pressione S");
			al_flip_display();
			PosFala++;
		}
	}
	redraw = true;
	al_destroy_font(FonteFala);
}

void InsereNPCMapa(NPC NPC[], Mapas Mapa)
{
	if (Mapa.ID == Floresta)
	{
		CriaNPC(&NPC[0], NPCGuarda, 656, 970, ImagemNPC, Andando, 2, "Desculpe meu jovem, voce nao podera estar passando por esta ponte", "Se voce esta procurando a os Drigons, va para a Cidade...");
		CriaNPC(&NPC[1], Placa, 304, 234, ImagemNPC, Parado, 1, "Lar, Doce Lar...");
	}

	else if (Mapa.ID == Loja)
	{
		CriaNPC(&NPC[0], NPCMagia, 336, 682, ImagemNPC, Andando, 6, "Voce pode estar soltando as Magias Utilizando as Teclas X, C, V, B", "'X' eh a Magia de Fogo", "'C' eh a Magia de Gelo", "'V' eh a magia de Life", "'B' eh a magia de Mort", "Voce pode utilizar potions de vida com 'F1' e 'F2' para Mana");
		CriaNPC(&NPC[1], NPCArmadura, 528, 682, ImagemNPC, Andando, 2, "Voce Podera Atacar utilizando a Tecla 'Z' do Teclado", "Lembre-se, voce nao pode se movimentar enquanto estiver atacando!");
		CriaNPC(&NPC[2], NPCIdoso, 560, 384, ImagemNPC, Parado, 1, "Voce eh um Guerreiro Certo?! Entao va atraz do Lord Dragao e salve a todos logo!...");
		NPC[2].LinhaAnimacao = 1;
	}

	else if (Mapa.ID == Curandeira)
		CriaNPC(&NPC[0], NPCCurandeira, 336, 392, ImagemNPC, Andando, 1, "Voce me parece Cansado, deixe me te curar!");

	else if (Mapa.ID == Cidade)
	{
		CriaNPC(&NPC[0], NPCCivil, 512, 772, ImagemNPC, Andando, 3, "Desde que os Drigons chegaram, muitos morreram.", "Existe Rumores que o Lord Dragao encontra-se na parte inferior do castelo.", "Dizem que apenas um guerreiro com grandes habilidades pode derrota-lo.");
		CriaNPC(&NPC[1], NPCGuarda, 560, 1076, ImagemNPC, Parado, 2, "Se voce estiver indo para a Floresta, tome cuidado Guerreiro.", "Os Dragoes se esconde nas sombras das arvores.");
		CriaNPC(&NPC[2], NPCGuarda, 656, 100, ImagemNPC, Parado, 2, "Bem Vindo a Cidade de Draco.", "Va a loja de magias e armaduras para aprender a atacar e soltar magias.");
		NPC[2].LinhaAnimacao = 0;
		CriaNPC(&NPC[3], NPCGuarda, 784, 100, ImagemNPC, Parado, 2, "Bem Vindo a Cidade de Draco.", "Va a loja de magias e armaduras para aprender a atacar e soltar magias.");
		NPC[3].LinhaAnimacao = 0;
		CriaNPC(&NPC[4], NPCAgricultor, 144, 964, ImagemNPC, Parado, 4, "Esta maldita raca, acabaram com as minhas plantacoes.", "Eles se alimentam dos frutos que caem das arvores.", "Jovem Guerreiro, salve o que sobrou de nosso terra...", "Encontre e mate o Lord Dragao no Castelo!!");
		NPC[4].LinhaAnimacao = 0;

		CriaNPC(&NPC[5], Placa, 896, 772, ImagemNPC, Parado, 1, "Loja de Magias e Armas.");
		CriaNPC(&NPC[6], Placa, 240, 324, ImagemNPC, Parado, 1, "Curandeira.");
		CriaNPC(&NPC[7], Placa, 896, 388, ImagemNPC, Parado, 1, "Loja de Magias e Armas, logo abaixo.");
	}
	else if (Mapa.ID == Montanha)
		CriaNPC(&NPC[0], Placa, 304, 32, ImagemNPC, Parado, 1, "Cidade de Draco.");

	else if (Mapa.ID == Castelo)
		CriaNPC(&NPC[0], Placa, 512, 580, ImagemNPC, Parado, 1, "Drigon Lord House, cuidado!");
}
