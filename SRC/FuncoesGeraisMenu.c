#include "Variaveis.h"

void DesenhaMenu(char *CaminhoImagem, char *TituloMenu, int Posx, int Posy)
{
	/*Coloca a Imagem do Menu na tela */
	ALLEGRO_BITMAP *ImagemMapa;

	ImagemMapa = al_load_bitmap(CaminhoImagem);
	al_draw_bitmap(ImagemMapa, Posx, Posy, 0);
	al_flip_display();

	al_destroy_bitmap(ImagemMapa);

	al_set_window_title(Display, TituloMenu);

}

void FadeInMenu(char *CaminhoImagem, int velocidade)
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
		al_draw_tinted_bitmap(ImagemFadeIn, al_map_rgba(alfa, alfa, alfa, alfa), 0, 0, 0);
		al_flip_display();
		al_rest(0.005); // Não é necessário caso haja controle de FPS
	}

	al_destroy_bitmap(ImagemFadeIn);
}

void FadeOutMenu(int velocidade)
{
	ALLEGRO_BITMAP *buffer;
	buffer = al_create_bitmap(LARGURA_TELA, ALTURA_TELA);
	al_set_target_bitmap(buffer);
	al_draw_bitmap(al_get_backbuffer(Display), 0, 0, 0);
	al_set_target_bitmap(al_get_backbuffer(Display));

	if (velocidade <= 0)
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
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
		al_flip_display();
		al_rest(0.005); // Não é necessário caso haja controle de FPS
	}

	al_destroy_bitmap(buffer);
}

void MovimentaLogo(char *CaminhoImagem)
{

	ALLEGRO_BITMAP *EfeitoLogo = al_load_bitmap(CaminhoImagem);

	bool sair = false;
	int cont = 0;

	float raio = 10.0;
	float x = raio;
	float y = raio;
	int dir_x = 1, dir_y = 1;

	while (!sair)
	{
		al_draw_bitmap(EfeitoLogo, x, y, 0);
		al_flip_display();

		x += 1.0 * dir_x;
		y += 1.0 * dir_y;

		if (cont < 1750)
		{
			cont = cont + 1;

			if (x >= LARGURA_TELA - raio)
			{
				dir_x = -1;
				x = LARGURA_TELA - raio;
			}
			else if (x <= raio)
			{
				dir_x = 1;
				x = raio;
			}

			if (y >= ALTURA_TELA - raio)
			{
				dir_y = -1;
				y = ALTURA_TELA - raio;
			}
			else if (y <= raio)
			{
				dir_y = 1;
				y = raio;
			}

			al_rest(0.004);
		}
		else
		{
			sair = true;
		}
	}

	al_destroy_bitmap(EfeitoLogo);
}

void PressioneQualquerTecla(char *CaminhoImagem)
{
	bool sair = false;

	ALLEGRO_BITMAP *Imagem = al_load_bitmap(CaminhoImagem);

	while (!sair)
	{
		al_rest(0.5);
		al_draw_bitmap(Imagem, 0, 0, 0);
		al_draw_text(Fonte, al_map_rgb(255, 255, 255), LARGURA_TELA / 2, 450 - al_get_font_ascent(Fonte) / 2, ALLEGRO_ALIGN_CENTRE, "Pressione Enter...");
		al_flip_display();
		al_rest(0.5);
		al_draw_bitmap(Imagem, 0, 0, 0);
		al_flip_display();

		while (!al_is_event_queue_empty(Fila_Eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(Fila_Eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
			{
				al_destroy_sample(Music); //Destroi a musica anterior para iniciar uma Nova.
				TocaEfeitoMenu("Audio/AudioMenu/EfeitoET.wav");
				al_rest(2.0);
				sair = true;
				break;
			}
		}
	}
	al_destroy_bitmap(Imagem);
}

void TocaEfeitoMenu(char *CaminhoMusica)
{
	/* Toca os Efeitos Musicas */
	sample = al_load_sample(CaminhoMusica);
	al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
}

void TocaMusicaFundo(char *CaminhoMusica)
{
	Music = al_load_sample(CaminhoMusica);
	al_play_sample(Music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL );
}
