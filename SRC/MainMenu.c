#include "Variaveis.h"

bool CriaBotoes();
void FinalizaBotoes();

//Variaveis Cria Botao
ALLEGRO_BITMAP *BotaoSair = NULL, *BotaoIniciar = NULL, *BotaoCarrega = NULL, *BotaoHistoria = NULL;
bool sair = false; // Flag que condicionará nosso looping

bool Menu()
{
	/* LogoSenac */
	/* -------------------------------------------------------------- */
	DesenhaMenu("Menu/ImagensMenu/FundoBranco.jpg", "Senac", 0, 0);
	FadeInMenu("Menu/ImagensMenu/FundoBranco.jpg", 1);
	TocaEfeitoMenu("Audio/AudioMenu/MenuSenac.wav");
	DesenhaMenu("Menu/ImagensMenu/LogoSenac.jpg", "Senac", 280, 160);
	al_rest(1.0);
	FadeOutMenu(1.0);
	al_destroy_sample(sample);
	/* -------------------------------------------------------------- */

	/* LogoUpGame */
	/* -------------------------------------------------------------- */
	FadeInMenu("Menu/ImagensMenu/FundoBranco.jpg", 1);
	DesenhaMenu("Menu/ImagensMenu/FundoBranco.jpg", "UpGame", 0, 0);
	TocaEfeitoMenu("Audio/AudioMenu/UpGame.wav");
	MovimentaLogo("Menu/ImagensMenu/LogoUpGame.jpg");
	al_rest(0.05);
	FadeOutMenu(1.0);
	al_destroy_sample(Music);
	/* -------------------------------------------------------------- */

	/* Imagem ET */
	/* -------------------------------------------------------------- */
	FadeInMenu("Menu/ImagensMenu/FundoBranco.jpg", 1);
	DesenhaMenu("Menu/ImagensMenu/ET.jpg", "Menu", 0, 0);
	TocaMusicaFundo("Audio/AudioMenu/ET.wav");
	PressioneQualquerTecla("Menu/ImagensMenu/ET.jpg");
	al_destroy_sample(sample);
	/* -------------------------------------------------------------- */

	/* Lopping Principal do Menu */
	FadeInMenu("Menu/ImagensMenu/FundoBranco.jpg", 1);
	DesenhaMenu("Menu/ImagensMenu/ImagemMenuInicio.jpg", "Menu Principal", 0, 0);
	TocaMusicaFundo("Audio/AudioMenu/MusicaMenuPrincipal.wav");

	if(!MenuLopping())
		return false;

	al_destroy_sample(Music);

	return true;
}

bool MenuLopping()
{
	BotaoCarrega = false;
	BotaoIniciar = false;
	BotaoSair = false;

	if (!CriaBotoes())
	{
		fprintf(stderr, "Falha ao criar os botoes.\n");
		FinalizaBotoes();
		return false;
	}

	/* Lopping Principal do Menu */
	while (!sair)
	{
		// Verificamos se há eventos na fila
		while (!al_is_event_queue_empty(Fila_Eventos))
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(Fila_Eventos, &evento);

			//Evento do botao Iniciar
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 700 - al_get_bitmap_width(BotaoIniciar) / 2 &&
						evento.mouse.x <= 700 + al_get_bitmap_width(BotaoIniciar) / 2 &&
						evento.mouse.y >= 360 - al_get_bitmap_height(BotaoIniciar) / 2 &&
						evento.mouse.y <= 360 + al_get_bitmap_height(BotaoIniciar) / 2)
				{
					NovoJogo = true;
					FadeOutMenu(1);
					sair = true;
				}
			}

			/////////////////Evento do botao Carregar
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 670 - al_get_bitmap_width(BotaoCarrega) / 2 &&
						evento.mouse.x <= 670 + al_get_bitmap_width(BotaoCarrega) / 2 &&
						evento.mouse.y >= 385 - al_get_bitmap_height(BotaoCarrega) / 2 &&
						evento.mouse.y <= 385 + al_get_bitmap_height(BotaoCarrega) / 2)
				{
					CarregarJogo = true;
					FadeOutMenu(1);
					sair = true;
				}
			}

			///////////////////Evento do botao Historia
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 690 - al_get_bitmap_width(BotaoHistoria) / 2 &&
						evento.mouse.x <= 690 + al_get_bitmap_width(BotaoHistoria) / 2 &&
						evento.mouse.y >= 410 - al_get_bitmap_height(BotaoHistoria) / 2 &&
						evento.mouse.y <= 410 + al_get_bitmap_height(BotaoHistoria) / 2)
				{
					/* Evento do Clique do Botão de Historia */
					//FadeOutMenu(1);
					//sair = true;
				}
			}

			///////////////// Evento do botao Sair
			if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
			{
				if (evento.mouse.x >= 720 - al_get_bitmap_width(BotaoSair) / 2 &&
						evento.mouse.x <= 720 + al_get_bitmap_width(BotaoSair) / 2 &&
						evento.mouse.y >= 440 - al_get_bitmap_height(BotaoSair) / 2 &&
						evento.mouse.y <= 440 + al_get_bitmap_height(BotaoSair) / 2)
				{
					SairJogo = true;
					FadeOutMenu(1);
					sair = true;
				}
			}

		}

		al_flip_display();
	}
	return true;
}

bool CriaBotoes()
{
	// Torna apto o uso de mouse na aplicação
	if (!al_install_mouse())
	{
		fprintf(stderr, "Falha ao inicializar o mouse.\n");
		return false;
	}

	// Alocamos o retângulo botaoiniciar
	BotaoIniciar = al_create_bitmap(130, 20);
	if (!BotaoIniciar)
	{
		fprintf(stderr, "Falha ao criar bitmap.\n");
		return false;
	}

	// Alocamos o retângulo Carregar Jogo
	BotaoCarrega = al_create_bitmap(190, 20);
	if (!BotaoCarrega)
	{
		fprintf(stderr, "Falha ao criar bitmap.\n");
		return false;
	}

	// Alocamos o retângulo Carregar Jogo
	BotaoHistoria = al_create_bitmap(130, 20);
	if (!BotaoHistoria)
	{
		fprintf(stderr, "Falha ao criar bitmap.\n");
		return false;
	}

	// Alocamos o botão para fechar a aplicação
	BotaoSair = al_create_bitmap(70, 20);
	if (!BotaoSair)
	{
		fprintf(stderr, "Falha ao criar botão de saída.\n");
		return false;
	}


	// Dizemos que vamos tratar os eventos vindos do mouse
	al_register_event_source(Fila_Eventos, al_get_mouse_event_source());

	return true;
}

void FinalizaBotoes()
{
	al_destroy_bitmap(BotaoIniciar);
	al_destroy_bitmap(BotaoCarrega);
	al_destroy_bitmap(BotaoHistoria);
	al_destroy_bitmap(BotaoSair);
}
