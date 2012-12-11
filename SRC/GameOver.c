#include "Variaveis.h"

void F_GameOver()
{
	bool SairLoop = false; // Flag que condicionará nosso looping

	FadeIn("Menu/ImagensMenu/gameover.bmp", 1);
	DesenhaMenu("Menu/ImagensMenu/gameover.bmp", "GameOver", cameraPosition[0],cameraPosition[1]);

	/* Toca os Efeitos Musicas */
	ALLEGRO_SAMPLE *sample = al_load_sample("Audio/AudioMenu/EfeitoET.wav");
	al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );

	while (!SairLoop)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(Fila_Eventos, &evento);
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			SairLoop = true;
		}
	}

	FadeOut(1, 255);
	al_destroy_sample(sample);
}
