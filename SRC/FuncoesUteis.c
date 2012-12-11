#include "Variaveis.h"

void TocaEfeito(ALLEGRO_SAMPLE *Sample, bool Life)
{
	/* Toca os Efeitos Musicas */
	if (!Life)
		al_play_sample(Sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
	else
		al_play_sample(Sample, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
}

void TocaMusicaPrincipal(ALLEGRO_SAMPLE_INSTANCE *SongInstance)
{
	al_set_sample_instance_playmode(SongInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(SongInstance, al_get_default_mixer());
	al_play_sample_instance(SongInstance); //Começa a tocar a Musica
}

void ParaMusicaPrincipal(ALLEGRO_SAMPLE_INSTANCE *SongInstance)
{
	al_stop_sample_instance(SongInstance);
}

void FadeOut(int velocidade, int TamanhoAlfa)
{
	ALLEGRO_BITMAP *buffer;

	buffer = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(al_get_backbuffer(Display), 0, 0, 0);
	al_set_target_bitmap(al_get_backbuffer(Display));

	if (velocidade <= 0)
		velocidade = 1;
	else if (velocidade > 15)
		velocidade = 15;

	int alfa;
	for (alfa = 0; alfa <= TamanhoAlfa; alfa += velocidade)
	{
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), cameraPosition[0], cameraPosition[1], 0);
		al_flip_display();
		al_rest(0.005); // Não é necessário caso haja controle de FPS
	}
	al_destroy_bitmap(buffer);
}

void FadeIn(char *CaminhoImagem, int velocidade)
{
	ALLEGRO_BITMAP *ImagemFadeIn = al_load_bitmap(CaminhoImagem);

	if (velocidade < 0)
	{
		velocidade = 1;
	}
	else if (velocidade > 15)
	{
		velocidade = 15;
	}

	int alfa;
	for (alfa = 0; alfa <= 255; alfa += velocidade)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(ImagemFadeIn, al_map_rgba(alfa, alfa, alfa, alfa), cameraPosition[0], cameraPosition[1], 0);
		al_flip_display();
		al_rest(0.005); // Não é necessário caso haja controle de FPS
	}

	al_destroy_bitmap(ImagemFadeIn);
}

void PauseGame()
{
	bool pause;

	FadeOut(5, 150);
	pause = true;

	ALLEGRO_EVENT evento;
	ALLEGRO_TIMEOUT timeout;
	al_init_timeout(&timeout, 0.05);

	al_draw_text(Fonte, al_map_rgb(255, 255, 255), (cameraPosition[0] + LARGURA_TELA / 2 - al_get_font_ascent(Fonte)), (cameraPosition[1] + ALTURA_TELA / 2 - al_get_font_ascent(Fonte)), ALLEGRO_ALIGN_CENTRE, "Pause Game! Pressione Enter.");
	al_flip_display();
	while (pause)
	{
		int tem_eventos = al_wait_for_event_until(Fila_Eventos, &evento, &timeout);
		if (tem_eventos)
		{
			if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
			{
				pause = false;
			}
		}
	}
	redraw = true;
}

void SaveGame(Mapas Mapa, Heroi Heroi)
{
	bool salvando;

	FadeOut(5, 150);
	salvando = true;

	ALLEGRO_EVENT evento;
	ALLEGRO_TIMEOUT timeout;
	al_init_timeout(&timeout, 0.05);

	FILE *save;
	save = fopen("SaveLoadGame/SaveLoadGame.bin", "w");

	fprintf(save, "%d\n", Mapa.ID);
	fprintf(save, "%d\n", Heroi.x);
	fprintf(save, "%d\n", Heroi.y);
	fprintf(save, "%d\n", Heroi.LinhaAnimacao);
	fprintf(save, "%d\n", Heroi.ColunaAnimacao);
	fprintf(save, "%d\n", Heroi.Life);
	fprintf(save, "%d\n", Heroi.MaxLife);
	fprintf(save, "%d\n", Heroi.Mana);
	fprintf(save, "%d\n", Heroi.MaxMana);
	fprintf(save, "%d\n", Heroi.QtdVida);
	fprintf(save, "%d\n", Heroi.QtdMana);

	fclose(save);

	al_draw_text(Fonte, al_map_rgb(255, 255, 255), (cameraPosition[0] + LARGURA_TELA / 2 - al_get_font_ascent(Fonte)), (cameraPosition[1] + ALTURA_TELA / 2 - al_get_font_ascent(Fonte)), ALLEGRO_ALIGN_CENTRE, "Jogo Salvo. Preciso Enter!");
	al_flip_display();

	while (salvando)
	{
		int tem_eventos = al_wait_for_event_until(Fila_Eventos, &evento, &timeout);
		if (tem_eventos)
		{
			if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
			{
				salvando = false;
			}
		}
	}
}

void LoadGame(Heroi *Heroi)
{
	FILE *Load;
	Load = fopen("SaveLoadGame/SaveLoadGame.bin", "r");

	al_clear_to_color(al_map_rgb(0, 0, 0));
	if (!Load)
	{
		al_draw_text(Fonte, al_map_rgb(255, 255, 255), (LARGURA_TELA / 2 - al_get_font_ascent(Fonte)), (ALTURA_TELA / 2 - al_get_font_ascent(Fonte)), ALLEGRO_ALIGN_CENTRE, "Nenhum Save Game Encontrado...");
		al_flip_display();
		al_rest(3.0);
	}
	else
	{
		al_draw_text(Fonte, al_map_rgb(255, 255, 255), (LARGURA_TELA / 2 - al_get_font_ascent(Fonte)), (ALTURA_TELA / 2 - al_get_font_ascent(Fonte)), ALLEGRO_ALIGN_CENTRE, "Carregando Jogo...");
		al_flip_display();
		al_rest(3.0);
	}

	fscanf(Load, "%d", &IDMapa);
	fscanf(Load, "%d", &Heroi->x);
	fscanf(Load, "%d", &Heroi->y);
	fscanf(Load, "%d", &Heroi->LinhaAnimacao);
	fscanf(Load, "%d", &Heroi->ColunaAnimacao);
	fscanf(Load, "%d", &Heroi->Life);
	fscanf(Load, "%d", &Heroi->MaxLife);
	fscanf(Load, "%d", &Heroi->Mana);
	fscanf(Load, "%d", &Heroi->MaxMana);
	fscanf(Load, "%d", &Heroi->QtdVida);
	fscanf(Load, "%d", &Heroi->QtdMana);

	fclose(Load);
}
