#include "Variaveis.h"

void GameLooping()
{
	/* Entidades */
	Heroi Heroi;
	MagiasHeroi MagiasHeroi;
	NPC NPC[10];
	Monstros Monstros[MAX_MONSTROS];
	MagiasMonstros MagiasMonstros[MAX_MONSTROS];
	Itens Itens[MAX_MONSTROS];
	Mapas Mapa;

	srand(time(NULL ));
	bool Sair = false; //Flag do Loop principal

	/* Inicia todas as entidades */
	IniciaHeroi(&Heroi, ImagemHeroi);
	IniciaMagia(Heroi, &MagiasHeroi, ImagemMagiaHeroi[0], -1);
	IniciaMapa(&Mapa, IDMapa);
	CarregaMapaColisao(Mapa);
	IniciaMonstros(Monstros, ImagemMonstros, Mapa.QtdMonstros, false);

	/* Menu */
	if (CarregarJogo)
	{
		LoadGame(&Heroi);
		TrocouMapa = true;
	}

	/* Itens deixados como false para não dar erro */
	for (i = 0; i < MAX_MONSTROS; i++)
	{
		Itens[i].Mostrar = false;
		MagiasMonstros[i].Mostrar = false;
	}


	al_start_timer(TimerFPS);
	al_start_timer(Regenera);
	while (!Sair)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(Fila_Eventos, &events);
		al_get_keyboard_state(&keyState);

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			//Fechou pela Janela ou Apertou Esc.
			Sair = true;
			redraw = false;
		}
		else if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
					Sair = true;
					redraw = false;
					break;
				case ALLEGRO_KEY_Z:
					if (!Heroi.Atacou)
					{
						AtkFisicoHeroi(&Heroi, Mapa, Monstros, 0);
						if (Mapa.QtdMonstros != 0)
						{
							for (i = 0; i < Mapa.QtdMonstros; i++)
								if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros[0], Itens[0], NPC[0], AtaqueFisico, HeroiEMonstros))
								{
									ValidaColisaoHeroi(&Heroi, &MagiasHeroi, &Monstros[i], AtaqueFisico);
									TocaEfeito(SamplesAtk[Sword], false);
								}
								else
									/* Efeito de Som */
									TocaEfeito(SamplesAtk[SwordMiss], false);
						}
						else
							/* Efeito de Som */
							TocaEfeito(SamplesAtk[SwordMiss], false);

					}
					break;
				case ALLEGRO_KEY_X:
					if (!Heroi.AtkMagia)
					{
						IniciaMagia(Heroi, &MagiasHeroi, ImagemMagiaHeroi[0], Fire);
						if (Heroi.Mana > MagiasHeroi.GastoMana)
						{
							MagiasHeroi.Mostrar = true;
							Heroi.Mana -= MagiasHeroi.GastoMana;
							Heroi.AtkMagia = true;
							al_start_timer(MagiaPersonagem);
							redraw = true;
							TocaEfeito(Samples[Fire], false);
						}
					}
					break;
				case ALLEGRO_KEY_C:
					if (!Heroi.AtkMagia)
					{
						IniciaMagia(Heroi, &MagiasHeroi, ImagemMagiaHeroi[0], Ice);
						if (Heroi.Mana > MagiasHeroi.GastoMana)
						{
							MagiasHeroi.Mostrar = true;
							Heroi.Mana -= MagiasHeroi.GastoMana;
							Heroi.AtkMagia = true;
							al_start_timer(MagiaPersonagem);
							redraw = true;
							TocaEfeito(Samples[Ice], false);
						}
					}
					break;
				case ALLEGRO_KEY_V:
					if (!Heroi.AtkMagia)
					{
						IniciaMagia(Heroi, &MagiasHeroi, ImagemMagiaHeroi[1], Life);
						if (Heroi.Mana > MagiasHeroi.GastoMana)
						{
							MagiasHeroi.Mostrar = true;
							Heroi.Mana -= MagiasHeroi.GastoMana;
							Heroi.AtkMagia = true;
							al_start_timer(MagiaPersonagem);
							RegeneraVidaPersonagem(&Heroi);
							redraw = true;
							TocaEfeito(Samples[Life], true);
						}
					}
					break;
				case ALLEGRO_KEY_B:
					if (!Heroi.AtkMagia)
					{
						IniciaMagia(Heroi, &MagiasHeroi, ImagemMagiaHeroi[2], Mort);
						if (Heroi.Mana > MagiasHeroi.GastoMana)
						{
							Heroi.Mana -= MagiasHeroi.GastoMana;
							MagiasHeroi.Mostrar = true;
							Heroi.AtkMagia = true;
							al_start_timer(MagiaPersonagem);
							redraw = true;
							TocaEfeito(Samples[Mort], false);
						}
					}
					break;
				case ALLEGRO_KEY_F1:
					/* Usa Potion de Vida */
					if (Heroi.QtdVida > 0)
					{
						RegeneraVidaPersonagem(&Heroi);
						Heroi.QtdVida--;
					}

					break;
				case ALLEGRO_KEY_F2:
					/* Usa Potion de Mana */
					if (Heroi.QtdMana > 0)
					{
						RegeneraMana(&Heroi);
						Heroi.QtdMana--;
					}
					break;
				case ALLEGRO_KEY_P:
					PauseGame();
					break;
				case ALLEGRO_KEY_ENTER:
					/* Esta falando com o NPC */
					ValidaNPC(NPC, &Heroi, Mapa.QtdNPC);

					/* Verificação só para fazer o desenho da magia e tocar o Efeito */
					if (Heroi.AtkMagia)
					{
						IniciaMagia(Heroi, &MagiasHeroi, ImagemMagiaHeroi[1], Life);
						MagiasHeroi.Mostrar = true;
						Heroi.AtkMagia = false;
						redraw = true;
						TocaEfeito(Samples[Life], true);
					}
					break;
				case ALLEGRO_KEY_S:
					/* Salvando o Jogo */
					SaveGame(Mapa, Heroi);
					break;
			}
		}

		else if (events.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) //Evento de Maximizar a tela
			redraw = true;

		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			if (events.timer.source == TimerFPS)
			{
				/* Movimenta o personagem */
				/*--------------------------------------------------------------------*/
				if (al_key_down(&keyState, ALLEGRO_KEY_UP) && (!Heroi.Atacou))
				{
					Heroi.Sentido = Up;
					if (!TemColisao(Heroi))
					{
						redraw = true;
						MovimentaHeroi(&Heroi, Up);
						TrocaMapa(&Heroi, &Mapa);
					}
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && (!Heroi.Atacou))
				{
					Heroi.Sentido = Down;
					if (!TemColisao(Heroi))
					{
						redraw = true;
						MovimentaHeroi(&Heroi, Down);
						TrocaMapa(&Heroi, &Mapa);
					}
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && (!Heroi.Atacou))
				{
					Heroi.Sentido = Left;
					if (!TemColisao(Heroi))
					{
						redraw = true;
						MovimentaHeroi(&Heroi, Left);
						TrocaMapa(&Heroi, &Mapa);
					}
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && (!Heroi.Atacou))
				{
					Heroi.Sentido = Right;
					if (!TemColisao(Heroi))
					{
						redraw = true;
						MovimentaHeroi(&Heroi, Right);
						TrocaMapa(&Heroi, &Mapa);
					}
				}
				/*--------------------------------------------------------------------*/
			}

			/*                        HEROI                             */
			/* --------------Referente ao Atk do Heroi-----------------*/
			if (Heroi.Sentido == Parado)
				VerificaSentidoHeroi(&Heroi); /* Funcao que corrige o bug de quando soltava a magia parado */

			AtkMagia(&MagiasHeroi, &Heroi);

			/* Colisao da Magia com o Monstro */
			for (i = 0; i < Mapa.QtdMonstros; i++)
				//Passa MagiasMonstros[0] só porque precisa do parametro, não faz nada com ela.
				if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros[0], Itens[0], NPC[0], AtaqueMagico, HeroiEMonstros))
					ValidaColisaoHeroi(&Heroi, &MagiasHeroi, &Monstros[i], AtaqueMagico);

			//Deve ter essa verificao, pos a magia de Mort dava varios hits nos monstros e só parava quando terminava a animação.
			if (MagiasHeroi.Colisao && i >= Mapa.QtdMonstros && MagiasHeroi.Tipo == Mort)
				MagiasHeroi.Colisao = false;

			/* Timer da Magia do Personagem - Verifica se já pode soltar novamente a Magia*/
			if (events.timer.source == MagiaPersonagem)
			{
				Heroi.AtkMagia = false;
				al_stop_timer(MagiaPersonagem);
			}

			/* Ataque Fisico do Personagem */
			AtkFisicoHeroi(&Heroi, Mapa, Monstros, 2);

			for (i = 0; i < Mapa.QtdMonstros; i++)
			{
				/* Colisao de Movimento do Personagem com os Monstros */
				if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros[0], Itens[0], NPC[0], Movimentacao, HeroiEMonstros))
					ValidaColisaoHeroi(&Heroi, &MagiasHeroi, &Monstros[i], Movimentacao);

				/* Verifica a colisão do Heroi com os Itens dropados */
				if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros[i], Itens[i], NPC[0], Movimentacao, HeroiEItens))
					ValidaColisaoItem(&Heroi, &Itens[i]);
			}

			/* Colisao de Movimento do Personagem com os NCPs */
			for (i = 0; i < Mapa.QtdNPC; i++)
				if (ColisaoTotal(Heroi, Monstros[0], MagiasHeroi, MagiasMonstros[0], Itens[0], NPC[i], Movimentacao, HeroiENPC))
					ValidaColisaoHeroi(&Heroi, &MagiasHeroi, &Monstros[i], Movimentacao);
			/* ---------------------------------------------*/

			/*                     MONSTROS                           */
			/*--------------------------------------------------------*/
			for (i = 0; i < Mapa.QtdMonstros; i++)
			{
				if (Monstros[i].Life <= 0 && Monstros[i].Vivo)
				{
					al_start_timer(TimerRespawMonster[i]); //Inicia o Timer do Respaw do Monstro
					al_start_timer(TimerDropItens[i]);
					CriaItem(&Itens[i], Monstros[i], rand() % 2, ImagemItem);
					Monstros[i].Vivo = false;

					if (Monstros[i].Boss)
					{
						MatouBoss = true;
						EhBoss = false;
					}
				}

				if (events.timer.source == TimerDropItens[i])
				{
					Itens[i].Mostrar = false;
					al_stop_timer(TimerDropItens[i]);
				}

				if (events.timer.source == TimerRespawMonster[i])
				{
					Monstros[i].x = rand() % 300 + 1;
					Monstros[i].y = rand() % 400 + 1;
					Monstros[i].Life = Monstros[i].MaxLife;
					Monstros[i].Vivo = true;
					Monstros[i].DropItens = rand() % 2;
					al_stop_timer(TimerRespawMonster[i]);
				}

				/* Ataque Fisico do Monstro - Existe um Timer de 2.5 seg */
				if (!Monstros[i].Boss)
				{
					if (sqrt(pow(Monstros[i].x - Heroi.x, 2) + pow(Monstros[i].y - Heroi.y, 2)) < 230)
						al_start_timer(AtkMonstros[i]);
					else
						al_stop_timer(AtkMonstros[i]);
				}
				else
					al_start_timer(AtkMonstros[i]);


				if (events.timer.source == AtkMonstros[i] && Monstros[i].Vivo)
				{
					IniciaMagiasMonstros(&MagiasMonstros[i], Monstros[i], ImagemMagiaMonstros, rand() % 2);
					MagiasMonstros[i].Mostrar = true;

					/* Toca Efeito Das Magias */
					if (MagiasMonstros[i].Tipo == Fire)
						TocaEfeito(Samples[Fire], false);
					else if (MagiasMonstros[i].Tipo == Ice)
						TocaEfeito(Samples[Ice], false);

					if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros[0], Itens[0], NPC[0], AtaqueFisico, MonstrosEHeroi))
					{
						if (!Monstros[i].Boss)
							Heroi.Life -= rand() % Monstros[i].ForcaAtk + 1;
						else
							Heroi.Life -= rand() % Monstros[i].ForcaAtk + 5;

						TocaEfeito(SamplesAtk[AtackMonstros], false);
					}
				}

				AtkMagiaMonstros(&MagiasMonstros[i], &Monstros[i]);

				if (MagiasMonstros[i].Mostrar)
					if (ColisaoTotal(Heroi, Monstros[i], MagiasHeroi, MagiasMonstros[i], Itens[0], NPC[0], AtaqueMagico, MonstrosEHeroi))
					{
						Heroi.Life -= rand() % MagiasMonstros[i].Atk + 3;
						MagiasMonstros[i].Mostrar = false;
					}
			}

			//Movimentacao e Ataque de Magia do Monstro - SE COMECAR A BUGAR COLOCAR DENTRO DO EVENTO DO TIMERFPS
			MovimentaMonstros(Monstros, Heroi, Mapa.QtdMonstros);
			/*--------------------------------------------------------*/

			/* -----------------------NPC-----------------------------*/
			MovimentaNPC(NPC, Mapa.QtdNPC, Heroi); //SE COMECAR A BUGAR COLOCAR DENTRO DO EVENTO DO TIMERFPS
			/* -------------------------------------------------------*/

			/* Regenera a Vida do Monstro e Mana do Heroi */
			if (events.timer.source == Regenera)
			{
				RegeneraMana(&Heroi);
				for (i = 0; i < Mapa.QtdMonstros; i++)
					RegeneraVidaMonstros(&Monstros[i]);
			}
		}

		/* Verifica se é Game Over */
		if (Heroi.Life <= 0)
			GameOver = true;

		//Se matou o boss sai do jogo ou perdeu sai do jogo.
		if (GameOver || MatouBoss)
		{
			Sair = true;
			redraw = false;
			break;
		}

		/* Verifica se Trocou de Mapa */
		if (TrocouMapa)
		{
			redraw = true;
			TrocouMapa = false;
			ParaMusicaPrincipal(songInstance[LastID]); //Para de tocar a musica anterior, para tocar a nova musica
			IniciaMapa(&Mapa, IDMapa);
			CarregaMapaColisao(Mapa); //Carrega o Mapa de Colisao
			CarregaMapaColisaoMonster(Mapa); //Carrega o Mapa de Colisao do Monstros
			TocaMusicaPrincipal(songInstance[Mapa.ID]);

			for (i = 0; i < Mapa.QtdMonstros; i++)
				IniciaMagiasMonstros(&MagiasMonstros[i], Monstros[i], ImagemMagiaMonstros, Fire);

			InsereNPCMapa(NPC, Mapa);

			/* Valida mapa para ver se coloca o Boss ou Não */
			if (Mapa.ID != CasteloInterior && Mapa.ID != Campo)
			{
				IniciaMonstros(Monstros, ImagemMonstros, Mapa.QtdMonstros, false);
			}


			else if (Mapa.ID == CasteloInterior)
			{
				if (!JaFezEvento)
				{
					// Função do Evento do Boss
					IniciaMonstros(Monstros, ImagemBoss[Humano], Mapa.QtdMonstros, true);
					EventoBoss(&Heroi, Monstros, Mapa);
				}
				/*-----------------------------------------*/
			}
			/* VIRA DU MAU */
			/*----------------------------------------- */
			else if (Mapa.ID == Campo)
			{
				IniciaMonstros(Monstros, ImagemBoss[Humano], Mapa.QtdMonstros, true);
				Monstros[0].Vivo = true;
				Monstros[0].x = 818;
				Monstros[0].y = 504;
				Monstros[0].LinhaAnimacao = 1;
				EventoBossTwo(&Heroi, Monstros, Mapa);

				IniciaMagiasMonstros(&MagiasMonstros[0], Monstros[0], ImagemMagiaHeroi[1], Life);
				MagiasMonstros[0].Mostrar = true;

				//Troca a Imagem do Monstro Boss
				Monstros[0].ImagemMonstros = ImagemBoss[Dragao];
				Monstros[0].frameHeight = 96;
				Monstros[0].frameWidth = 96;
			}

			/* ----------------------------------------------------------- */
		}

		if (redraw && al_is_event_queue_empty(Fila_Eventos))
		{
			redraw = false;

			/* Movimenta a tela - Técnicas Scrolling */
			MovimentaTela(cameraPosition, Heroi.x, Heroi.y, 32, 32);

			DrawMapa(Mapa);
			DrawItem(Itens);
			DrawMonstros(Monstros, Mapa.QtdMonstros);
			DrawNPC(NPC, Mapa.QtdNPC);
			DrawHeroi(Heroi);
			DrawMagic(MagiasHeroi);
			DrawMagicMonster(MagiasMonstros, Mapa.QtdMonstros);
			ColocaInformacoesHeroi(Heroi, Mapa);

			al_flip_display();
		}
	}

	if (GameOver)
	{
		/* Chama a Funcao do GameOver */
		ParaMusicaPrincipal(songInstance[Mapa.ID]);
		F_GameOver();
	}
	else if (MatouBoss)
	{
		ParaMusicaPrincipal(songInstance[Mapa.ID]);
		F_GanhouJogo();
	}
}
