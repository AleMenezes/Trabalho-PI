#include "Variaveis.h"

void IniciaMapa(Mapas *Mapa, int ID)
{
	Mapa->ID = ID;
	Mapa->QtdMonstros = 0;
	Mapa->QtdNPC = 0;
	Mapa->QtdColunaColisao = 0;
	Mapa->CaminhoMapaColisao = "";

	/* Colisao Monstros */
	Mapa->CaminhoMapaColisaoMonster = "";
	Mapa->QtdColunaColisaoMonster = 0;

	if (ID == Casa)
	{
		al_set_window_title(Display, "Home - Side Quest");
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoCasaH.txt";
		Mapa->QtdColunaColisao = 40;
	}
	else if (ID == Floresta)
	{
		Mapa->QtdNPC = 2;
		al_set_window_title(Display, "Floresta - Side Quest");
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoFlorestaH.txt";
		Mapa->QtdColunaColisao = 96;
	}
	else if (ID == Cidade)
	{
		Mapa->QtdNPC = 8;
		al_set_window_title(Display, "Draco City - Side Quest");
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoCidadeH.txt";
		Mapa->QtdColunaColisao = 72;
	}
	else if (ID == Loja)
	{
		Mapa->QtdNPC = 3;
		al_set_window_title(Display, "Loja de Magias e Armas - Side Quest");
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoLojaH.txt";
		Mapa->QtdColunaColisao = 42;
	}
	else if (ID == Curandeira)
	{
		Mapa->QtdNPC = 1;
		al_set_window_title(Display, "Curandeira - Side Quest");
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoCurandeiraH.txt";
		Mapa->QtdColunaColisao = 40;
	}
	else if (ID == Montanha)
	{
		al_set_window_title(Display, "Montanha - Side Quest");
		Mapa->QtdMonstros = 10;
		Mapa->QtdNPC = 1;
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoMontanhaH.txt";
		Mapa->QtdColunaColisao = 96;
	}
	else if (ID == Caverna)
	{
		Mapa->QtdMonstros = 2;
		Mapa->CaminhoMapaColisao = "Mapas/";
		Mapa->QtdColunaColisao = 96;
	}
	else if (ID == Castelo)
	{
		al_set_window_title(Display, "Castelo - Side Quest");
		Mapa->QtdMonstros = 0;
		Mapa->QtdNPC = 1;
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoCasteloH.txt";
		Mapa->QtdColunaColisao = 64;
	}
	else if (ID == CasteloInterior)
	{
		al_set_window_title(Display, "Boss - Side Quest");
		Mapa->QtdMonstros = 1;
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoCasteloInteirorH.txt";
		Mapa->QtdColunaColisao = 64;
	}
	else if (ID == Campo)
	{
		al_set_window_title(Display, "Boss - Side Quest");
		Mapa->QtdMonstros = 1;
		Mapa->CaminhoMapaColisao = "Mapas/MapaColisaoCampoH.txt";
		Mapa->QtdColunaColisao = 100;
	}

	if (Mapa->QtdMonstros > MAX_MONSTROS)
		Mapa->QtdMonstros = MAX_MONSTROS;
}

void DrawMapa(Mapas Mapa)
{
	//Tem que pintar a Tela de Preto Antes.
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(ImagemMapa[Mapa.ID], 0, 0, 0);
	//al_draw_filled_rectangle(0, 0, 32, 32, al_map_rgb(0, 0, 0));
}

void MovimentaTela(float *cameraPosition, float x, float y, int width, int height)
{
	cameraPosition[0] = -(LARGURA_TELA / 2) + (x + width / 2);
	cameraPosition[1] = -(ALTURA_TELA / 2) + (y + height / 2);

	if (cameraPosition[0] < 0)
		cameraPosition[0] = 0;

	if (cameraPosition[1] < 0)
		cameraPosition[1] = 0;

	al_identity_transform(&camera);
	al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	al_use_transform(&camera);
}

void TrocaMapa(Heroi *Heroi, Mapas *Mapa)
{
	LastID = Mapa->ID; /* Salva o ID Antigo, para parar de tocar a musica anterior */
	switch (Mapa->ID)
	{
		case Casa: //Casa
			if (Heroi->x == 176 && Heroi->y >= 580 && Heroi->Sentido == Down)
			{	//Esta Saindo da Casa
				Heroi->x = 336;
				Heroi->y = 218;
				TrocouMapa = true;
				IDMapa = Floresta;
			}
			break;
		case Floresta: //Floresta
			if (Heroi->x == 336 && Heroi->y <= 218 && Heroi->Sentido == Up)
			{	//Esta Entrando na Casa
				Heroi->x = 176;
				Heroi->y = 548;
				TrocouMapa = true;
				IDMapa = Casa;
			}
			else if (Heroi->x == 240 && Heroi->y >= 1482 && Heroi->Sentido == Down)
			{	//Esta Indo Pra Cidade
				Heroi->x = 720;
				Heroi->y = 64;
				TrocouMapa = true;
				IDMapa = Cidade;
			}
			break;
		case Cidade: //Cidade
			if ((Heroi->x >= 668 && Heroi->x <= 752) && Heroi->y <= 36 && Heroi->Sentido == Up)
			{ //Esta Indo para a Floresta.
				Heroi->x = 240;
				Heroi->y = 1472;
				TrocouMapa = true;
				IDMapa = Floresta;
			}
			else if (Heroi->x == 816 && Heroi->y <= 756 && Heroi->Sentido == Up)
			{ //Esta indo pra Loja
				Heroi->x = 144;
				Heroi->y = 864;
				TrocouMapa = true;
				IDMapa = Loja;
			}
			else if (Heroi->x == 208 && Heroi->y <= 308 && Heroi->Sentido == Up)
			{ //Esta indo pra Curandeira
				Heroi->x = 208;
				Heroi->y = 544;
				TrocouMapa = true;
				IDMapa = Curandeira;
			}
			else if ((Heroi->x >= 436 && Heroi->x <= 560) && Heroi->y >= 1108 && Heroi->Sentido == Down)
			{	//Esta Indo para a Montanha
				Heroi->x = 256;
				Heroi->y = 32;
				TrocouMapa = true;
				IDMapa = Montanha;
			}
			break;
		case Loja: //Loja
			if (Heroi->x == 144 && Heroi->y >= 872 && Heroi->Sentido == Down)
			{	//Esta indo pra Cidade
				Heroi->x = 816;
				Heroi->y = 752;
				TrocouMapa = true;
				IDMapa = Cidade;
			}
			break;
		case Curandeira: //Curandeira
			if (Heroi->x == 208 && Heroi->y >= 552 && Heroi->Sentido == Down)
			{	//Esta indo pra Cidade
				Heroi->x = 208;
				Heroi->y = 320;
				TrocouMapa = true;
				IDMapa = Cidade;
			}
			break;
		case Montanha: //Montanha
			if ((Heroi->x >= 240 && Heroi->x <= 288) && Heroi->y <= 26 && Heroi->Sentido == Up)
			{	//Esta indo para a Cidade
				Heroi->x = 528;
				Heroi->y = 1072;
				TrocouMapa = true;
				IDMapa = Cidade;
			}
			/*else if (Heroi->x == 224 && Heroi->y <= 762 && Heroi->Sentido == Up)
			 {
			 //Esta indo pra caverna
			 Heroi->x = 1008;
			 Heroi->y = 212;
			 Heroi->LinhaAnimacao = 0;
			 TrocouMapa = true;
			 IDMapa = Caverna;
			 }*/
			else if (Heroi->x <= 32 && (Heroi->y <= 1216 && Heroi->y >= 1184) && Heroi->Sentido == Left)
			{
				//Esta indo pra o castelo
				Heroi->x = 932;
				Heroi->y = 952;
				TrocouMapa = true;
				IDMapa = Castelo;
			}
			break;
		case Caverna:
			/*if (Heroi->x == 1008 && Heroi->y <= 186 && Heroi->Sentido == Up)
			 {
			 //Esta indo para a montanha
			 Heroi->x = 224;
			 Heroi->y = 810;
			 Heroi->LinhaAnimacao = 0;
			 TrocouMapa = true;
			 IDMapa = Montanha;
			 }*/
			break;
		case Castelo:
			if (Heroi->x >= 976 && (Heroi->y >= 928 && Heroi->y <= 980) && Heroi->Sentido == Right)
			{
				/* Esta indo para a montanha */
				Heroi->x = 48;
				Heroi->y = 1216;
				TrocouMapa = true;
				IDMapa = Montanha;
			}
			else if ((Heroi->y == 584) && (Heroi->x <= 724 && Heroi->x >= 708) && Heroi->Sentido == Left)
			{
				/* Esta descendo a escada da esquerda */
				Heroi->x = 868;
				Heroi->y = 1264;
				TrocouMapa = true;
				IDMapa = CasteloInterior;
			}
			else if ((Heroi->y == 584) && (Heroi->x >= 292 && Heroi->x <= 308) && Heroi->Sentido == Right)
			{
				/* Esta descendo a escada da Direita */
				Heroi->x = 148;
				Heroi->y = 1264;
				TrocouMapa = true;
				IDMapa = CasteloInterior;
			}
			break;
		case CasteloInterior:
			if (Heroi->y == 1264 && Heroi->x < 130 && Heroi->Sentido == Left)
			{
				/* Esta subindo a escada da Direita */
				Heroi->x = 276;
				Heroi->y = 584;
				TrocouMapa = true;
				IDMapa = Castelo;
			}
			else if (Heroi->y == 1264 && (Heroi->x > 900) && Heroi->Sentido == Right)
			{
				/* Esta subindo a escada da Esquerda */
				Heroi->x = 756;
				Heroi->y = 584;
				TrocouMapa = true;
				IDMapa = Castelo;
			}
			else if (Heroi->y == 176 && (Heroi->x >= 452 && Heroi->x <= 468))
			{
				Heroi->x = 434;
				Heroi->y = 232;
				TrocouMapa = true;
				IDMapa = Campo;
			}
			break;
	}
}

void EventoBoss(Heroi *Heroi, Monstros Monstros[], Mapas Mapa)
{
	bool SairEvento = false, FalandoBoss = false;
	bool RedrawEvento = true;
	bool RedrawFala = false;
	bool MoveHeroi = true;
	int PosFala = 0, QtdFalas;
	bool ChegouDireita = false, ChegouEsquerda = false;

	char *FalasBoss[3] = { "O Castigo por me desafiar e a MORTE!", "MUAHAHAHAHAHAHAHAHAHAHAH.", "Va embora Guerreiro e eu pouparei a sua vida." };
	QtdFalas = 3;

	ALLEGRO_FONT *FonteFala = al_load_font("Arial.ttf", 16, 0);
	ALLEGRO_TIMER *Evento = al_create_timer(1 / 12.0);
	al_register_event_source(Fila_Eventos, al_get_timer_event_source(Evento));

	al_start_timer(Evento);
	while (!SairEvento)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(Fila_Eventos, &events);
		al_get_keyboard_state(&keyState);

		if (events.type == ALLEGRO_EVENT_TIMER && !FalandoBoss)
		{
			if (events.timer.source == TimerFPS)
			{
				if (Heroi->x < 516 && !ChegouDireita && MoveHeroi)
				{
					ChegouEsquerda = true;
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Right);
				}
				else if (Heroi->x > 516 && !ChegouEsquerda && MoveHeroi)
				{
					ChegouDireita = true;
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Left);
				}
				else if (Heroi->y > 896 && MoveHeroi)
				{
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Up);
				}
				else if (Heroi->x <= 596 && MoveHeroi)
				{
					ChegouEsquerda = true;
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Right);
				}
				else if (Heroi->y <= 896 && MoveHeroi)
				{
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Up);
				}

				if (Heroi->y == 736 && MoveHeroi)
				{
					FalandoBoss = true;
					RedrawEvento = false;
					RedrawFala = true;
					MoveHeroi = false;
					FadeOut(5, 150);
				}
			}
		}

		/* Comeca a falar */
		if (FalandoBoss)
		{
			if (events.type == ALLEGRO_EVENT_KEY_DOWN && events.keyboard.keycode == ALLEGRO_KEY_S)
			{
				if (PosFala >= QtdFalas)
				{
					RedrawEvento = false;
					RedrawFala = false;
					///SairEvento = false;
					FalandoBoss = false;
					///break;
				}
				else
				{
					RedrawFala = true;
					FalandoBoss = true;
				}
			}
		}
		else if (PosFala >= QtdFalas && !FalandoBoss)
		{
			RedrawEvento = true;

			Monstros[0].y -= Monstros[0].Velocidade;
			Monstros[0].LinhaAnimacao = 3;

			/* Movimentacao do Sprite */
			if (++Monstros[i].frameCount >= Monstros[i].frameDelay)
			{
				Monstros[i].curFrame += Monstros[i].animationDirection;
				if (Monstros[i].curFrame >= Monstros[i].maxFrame)
					Monstros[i].curFrame = Monstros[i].curFramePadrao;
				else if (Monstros[i].curFrame <= Monstros[i].curFramePadrao)
					Monstros[i].curFrame = Monstros[i].maxFrame - 1;

				Monstros[i].frameCount = 0;
			}

			if (Monstros[0].y <= 400)
			{
				Monstros[0].Vivo = false;
				SairEvento = true;
				JaFezEvento = true;
				break;
			}
		}

		if (RedrawEvento)
		{
			RedrawEvento = false;
			MovimentaTela(cameraPosition, Heroi->x, Heroi->y, 32, 32);
			DrawMapa(Mapa);
			DrawMonstros(Monstros, Mapa.QtdMonstros);
			DrawHeroi(*Heroi);
			ColocaInformacoesHeroi(*Heroi, Mapa);
			al_flip_display();
		}
		else if (RedrawFala)
		{
			RedrawFala = false;
			/* Desenha a Borda do Retangulo */
			al_draw_rectangle(cameraPosition[0], cameraPosition[1] + (ALTURA_TELA - 80), cameraPosition[0] + LARGURA_TELA, cameraPosition[1] + ALTURA_TELA, al_map_rgb(255, 255, 255), 2);
			al_draw_filled_rectangle(cameraPosition[0], cameraPosition[1] + (ALTURA_TELA - 80), cameraPosition[0] + LARGURA_TELA, cameraPosition[1] + ALTURA_TELA, al_map_rgb(240, 255, 113));

			/* Escreve o Texto na Tela */
			al_draw_textf(FonteFala, al_map_rgb(0, 0, 0), cameraPosition[0] + 30, cameraPosition[1] + (ALTURA_TELA - 70), 0, "%s", FalasBoss[PosFala]);
			al_draw_text(Fonte12, al_map_rgb(0, 0, 0), cameraPosition[0] + (LARGURA_TELA - 80), ((cameraPosition[1] + (ALTURA_TELA - 100) + cameraPosition[1] + ALTURA_TELA) / 2) + 30, 0, "Pressione S");
			al_flip_display();
			PosFala++;
		}
	}

	al_destroy_timer(Evento);
	al_destroy_font(FonteFala);
}

void EventoBossTwo(Heroi *Heroi, Monstros Monstros[], Mapas Mapa)
{
	bool SairEvento = false, FalandoBoss = false;
	bool RedrawEvento = true;
	bool RedrawFala = false;
	int PosFala = 0, QtdFalas;

	char *FalasBoss[4] = { "Eu dei a chance de voce fugir, agora tera que lutar ate o fim.", "MUAHAHAHAHAHAHAHHAHAHA.", "Preapare-se ser derrotado guerreiro", "Sinta a Furia do Drigon Lord." };
	QtdFalas = 4;

	ALLEGRO_FONT *FonteFala = al_load_font("Arial.ttf", 16, 0);
	ALLEGRO_TIMER *Evento = al_create_timer(1 / 12.0);
	al_register_event_source(Fila_Eventos, al_get_timer_event_source(Evento));

	al_start_timer(Evento);
	while (!SairEvento)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(Fila_Eventos, &events);
		al_get_keyboard_state(&keyState);

		if (events.type == ALLEGRO_EVENT_TIMER && !FalandoBoss)
		{
			if (events.timer.source == TimerFPS)
			{
				if (Heroi->y < 504)
				{
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Down);
				}
				else if (Heroi->x <= 530)
				{
					RedrawEvento = true;
					MovimentaHeroi(Heroi, Right);
				}

				if (Heroi->x == 546)
				{
					FalandoBoss = true;
					RedrawEvento = false;
					RedrawFala = true;
					FadeOut(5, 150);
				}
			}
		}

		/* Comeca a falar */
		if (FalandoBoss)
		{
			if (events.type == ALLEGRO_EVENT_KEY_DOWN && events.keyboard.keycode == ALLEGRO_KEY_S)
			{
				if (PosFala >= QtdFalas)
				{
					RedrawEvento = false;
					RedrawFala = false;
					SairEvento = false;
					FalandoBoss = false;
					break;
				}
				else
				{
					RedrawFala = true;
					FalandoBoss = true;
				}
			}
		}

		if (RedrawEvento)
		{
			RedrawEvento = false;
			MovimentaTela(cameraPosition, Heroi->x, Heroi->y, 32, 32);
			DrawMapa(Mapa);
			DrawMonstros(Monstros, Mapa.QtdMonstros);
			DrawHeroi(*Heroi);
			ColocaInformacoesHeroi(*Heroi, Mapa);
			//al_flip_display();
		}
		else if (RedrawFala)
		{
			RedrawFala = false;
			/* Desenha a Borda do Retangulo */
			al_draw_rectangle(cameraPosition[0], cameraPosition[1] + (ALTURA_TELA - 80), cameraPosition[0] + LARGURA_TELA, cameraPosition[1] + ALTURA_TELA, al_map_rgb(255, 255, 255), 2);
			al_draw_filled_rectangle(cameraPosition[0], cameraPosition[1] + (ALTURA_TELA - 80), cameraPosition[0] + LARGURA_TELA, cameraPosition[1] + ALTURA_TELA, al_map_rgb(240, 255, 113));

			/* Escreve o Texto na Tela */
			al_draw_textf(FonteFala, al_map_rgb(0, 0, 0), cameraPosition[0] + 30, cameraPosition[1] + (ALTURA_TELA - 70), 0, "%s", FalasBoss[PosFala]);
			al_draw_text(Fonte12, al_map_rgb(0, 0, 0), cameraPosition[0] + (LARGURA_TELA - 80), ((cameraPosition[1] + (ALTURA_TELA - 100) + cameraPosition[1] + ALTURA_TELA) / 2) + 30, 0, "Pressione S");
			PosFala++;
		}
		al_flip_display();
	}

	al_destroy_timer(Evento);
	al_destroy_font(FonteFala);
}
