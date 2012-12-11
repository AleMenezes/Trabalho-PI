#include "Variaveis.h"
void VerificaFullScreen();

bool IniciarJogo()
{
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_primitives_addon();

	/* Audio */
	al_install_audio(); //Inicia o Audio
	al_init_acodec_addon(); //Inicia o add-on que suporta diversos formatos
	al_reserve_samples(10); // Aloca 10 canais para tocar a musica

	/*VerificaFullScreen();
	 if (FULLSCREEN)
	 {
	 ALLEGRO_MONITOR_INFO info;
	 al_get_monitor_info(0, &info);
	 LARGURA_TELA = info.x2 - info.x1;
	 ALTURA_TELA = info.y2 - info.y1;
	 }*/

	Display = al_create_display(LARGURA_TELA, ALTURA_TELA);
	if (!Display)
	{
		fprintf(stderr, "Falha ao criar display");
		return false;
	}

		/* Cria uma fila de Eventos */
	Fila_Eventos = al_create_event_queue();
	if (!Fila_Eventos)
	{
		fprintf(stderr, "Falha ao criar fila de eventos.\n");;
		return false;
	}

	TimerFPS = al_create_timer(1.0 / FPS);
	MagiaPersonagem = al_create_timer(2.0);
	Regenera = al_create_timer(3.5);

	for (i = 0; i < MAX_MONSTROS; i++)
	{
		TimerRespawMonster[i] = al_create_timer(5.0);
		AtkMonstros[i] = al_create_timer(2.5);
		TimerDropItens[i] = al_create_timer(5.0);
	}

	/* Informa qual tipo de evento para a fila de eventos */
	al_register_event_source(Fila_Eventos, al_get_keyboard_event_source());
	al_register_event_source(Fila_Eventos, al_get_display_event_source(Display));
	al_register_event_source(Fila_Eventos, al_get_timer_event_source(TimerFPS));
	al_register_event_source(Fila_Eventos, al_get_timer_event_source(MagiaPersonagem));
	al_register_event_source(Fila_Eventos, al_get_timer_event_source(Regenera));
	for (i = 0; i < MAX_MONSTROS; i++)
	{
		al_register_event_source(Fila_Eventos, al_get_timer_event_source(AtkMonstros[i]));
		al_register_event_source(Fila_Eventos, al_get_timer_event_source(TimerDropItens[i]));
		al_register_event_source(Fila_Eventos, al_get_timer_event_source(TimerRespawMonster[i]));
	}

	/* Seta o Titulo da Tela, o nome do APP */
	al_set_window_title(Display, "Side Quest v1.0.1");
	al_set_app_name("Side Quest");

	al_flip_display();

	return true;
}

void FinalizarJogo()
{
	/* Destroi as Imagens */
	al_destroy_bitmap(ImagemHeroi);
	al_destroy_bitmap(ImagemHeroiAtk);
	al_destroy_bitmap(ImagemMonstros);
	al_destroy_bitmap(ImagemMagiaMonstros);
	al_destroy_bitmap(ImagemItem);
	al_destroy_bitmap(ImagemNPC);

	al_destroy_bitmap(ImagemBoss[Humano]);
	al_destroy_bitmap(ImagemBoss[Dragao]);

	al_destroy_timer(MagiaPersonagem);
	al_destroy_timer(Regenera);

	for (i = 0; i < MAX_MAPA; i++)
		al_destroy_bitmap(ImagemMapa[i]);

	for (i = 0; i < 3; i++)
		al_destroy_bitmap(ImagemMagiaHeroi[i]);

	/* Destroi os Timers */
	al_destroy_timer(TimerFPS);
	for (i = 0; i < MAX_MONSTROS; i++)
	{
		al_destroy_timer(TimerRespawMonster[i]);
		al_destroy_timer(AtkMonstros[i]);
		al_destroy_timer(TimerDropItens[i]);
	}

	/* Destroi os Audios */
	for (i = 0; i < 4; i++)
		al_destroy_sample(Samples[i]);

	for (i = 0; i < 3; i++)
		al_destroy_sample(SamplesAtk[i]);

	for (i = 0; i < MAX_MAPA; i++)
	{
		al_destroy_sample(MusicaPrincipal[i]);
		al_destroy_sample_instance(songInstance[i]);
	}

	/* Destroi o que sobrou */
	al_destroy_display(Display);
	al_destroy_event_queue(Fila_Eventos);
	al_destroy_font(Fonte);
	al_destroy_font(Fonte12);
}

void IniciarVariaveis()
{
	/* Inicia Somente As Variaveis Globais */
	LARGURA_TELA = 800;
	ALTURA_TELA = 460;

	MAX_MONSTROS = 10;
	MAX_MAPA = 10;

	FPS = 15;
	redraw = true;
	GameOver = false;
	MatouBoss = false;

	IDMapa = Casa;
	JaFezEvento = false;
	TrocouMapa = true;
}

void CarregaSistema(bool CodigoFonte)
{
	if (!CodigoFonte)
	{
		ALLEGRO_TIMER *CarregandoSistema;
		ALLEGRO_EVENT_QUEUE *FilaEventoCarregarSistema;
		int Flag = 1;
		float QtdBarra = 0;
		int QtdBarraAux;
		bool Sair = false;

		CarregandoSistema = al_create_timer(0.5);
		FilaEventoCarregarSistema = al_create_event_queue();
		al_register_event_source(FilaEventoCarregarSistema, al_get_timer_event_source(CarregandoSistema));

		al_start_timer(CarregandoSistema);
		while (!Sair)
		{
			ALLEGRO_EVENT events;
			al_wait_for_event(FilaEventoCarregarSistema, &events);
			if (events.type == ALLEGRO_EVENT_TIMER)
			{
				if (events.timer.source == CarregandoSistema)
				{
					switch (Flag)
					{
						case 1:
							QtdBarraAux = (100 / 7) / 4;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Heroi...");
							ImagemHeroi = al_load_bitmap("Heroi/Heroi.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando NPCs...");
							ImagemNPC = al_load_bitmap("Heroi/NPC.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Heroi...");
							ImagemHeroiAtk = al_load_bitmap("Heroi/HeroiAtack.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Monstros...");
							ImagemMonstros = al_load_bitmap("Monstros/DragonMonster.png");
							ImagemBoss[Humano] = al_load_bitmap ("Monstros/Monstro.png");
							ImagemBoss[Dragao] = al_load_bitmap("Monstros/ImagemBoss.png");
							break;
						case 2:
							QtdBarraAux = (100 / 7) / 5;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Magias...");
							ImagemMagiaHeroi[0] = al_load_bitmap("Magias/Magias2.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Magias...");
							ImagemMagiaHeroi[1] = al_load_bitmap("Magias/Regenera.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Magias...");
							ImagemMagiaHeroi[2] = al_load_bitmap("Magias/MagiaMort.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Magias...");
							ImagemMagiaMonstros = al_load_bitmap("Magias/Magias2.png");

							/* Itens */
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Itens...");
							ImagemItem = al_load_bitmap("Itens/Itens.png");
							break;
						case 3:
							QtdBarraAux = (100 / 7) / 9;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Casa] = al_load_bitmap("Mapas/Casa.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Floresta] = al_load_bitmap("Mapas/Floresta.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Cidade] = al_load_bitmap("Mapas/Cidade.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Loja] = al_load_bitmap("Mapas/Loja.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Curandeira] = al_load_bitmap("Mapas/Curandeira.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Montanha] = al_load_bitmap("Mapas/Montanha.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Caverna] = al_load_bitmap("Mapas/Caverna.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[Castelo] = al_load_bitmap("Mapas/Castelo.png");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas...");
							ImagemMapa[CasteloInterior] = al_load_bitmap("Mapas/CasteloInterior.png");
							ImagemMapa[Campo] = al_load_bitmap("Mapas/Campo.png");
							break;
						case 4:
							QtdBarraAux = (100 / 7) / 1;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Mapas de Colisao...");
							break;
						case 5:
							QtdBarraAux = (100 / 7) / 2;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Fontes...");
							Fonte = al_load_font("Arial.ttf", 14, 0);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Fontes...");
							Fonte12 = al_load_font("Arial.ttf", 12, 0);
							break;
						case 6:
							/* Som das Magias */
							QtdBarraAux = (100 / 7) / 16;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							Samples[0] = al_load_sample("Audio/Magias/Fire.wav");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							Samples[1] = al_load_sample("Audio/Magias/Ice.wav");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							Samples[2] = al_load_sample("Audio/Magias/Life.wav");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							Samples[3] = al_load_sample("Audio/Magias/Fire.wav");

							/* Som de Ataques */
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							SamplesAtk[0] = al_load_sample("Audio/Hits/Sword.wav");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							SamplesAtk[1] = al_load_sample("Audio/Hits/SwordMiss.wav");
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							SamplesAtk[2] = al_load_sample("Audio/Hits/Hit.wav");

							/* Carregando Som dos Mapas  */
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Casa] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Casa] = al_create_sample_instance(MusicaPrincipal[Casa]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Floresta] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Floresta] = al_create_sample_instance(MusicaPrincipal[Floresta]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Cidade] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Cidade] = al_create_sample_instance(MusicaPrincipal[Cidade]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Loja] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Loja] = al_create_sample_instance(MusicaPrincipal[Loja]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Curandeira] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Curandeira] = al_create_sample_instance(MusicaPrincipal[Curandeira]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Montanha] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Montanha] = al_create_sample_instance(MusicaPrincipal[Montanha]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Caverna] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Caverna] = al_create_sample_instance(MusicaPrincipal[Caverna]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[Castelo] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Castelo] = al_create_sample_instance(MusicaPrincipal[Castelo]);
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Sons...");
							MusicaPrincipal[CasteloInterior] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[CasteloInterior] = al_create_sample_instance(MusicaPrincipal[CasteloInterior]);
							MusicaPrincipal[Campo] = al_load_sample("Audio/Mapas/titlescreen.wav");
							songInstance[Campo] = al_create_sample_instance(MusicaPrincipal[Campo]);
							break;
						case 7:
							QtdBarraAux = (100 / 7) / 1;
							QtdBarra += QtdBarraAux;
							ColocaBarraLoading(QtdBarra, "Carregando Variaveis...");
							break;
						default:
							if (QtdBarra < 100)
								QtdBarra += 100 - QtdBarra;
							ColocaBarraLoading(QtdBarra, "Carregando Arquivos Necessarios...");
							Sair = true;
							break;
					}
					Flag++;
				}
			}
		}
		al_destroy_timer(CarregandoSistema);
		al_destroy_event_queue(FilaEventoCarregarSistema);
	}
}

void VerificaFullScreen()
{
	FULLSCREEN = false;
	if (al_show_native_message_box(NULL, "Full Screen - Rpg Game", "", "Deseja executar em FullScreen?", NULL, ALLEGRO_MESSAGEBOX_YES_NO))
		FULLSCREEN = true;
}
