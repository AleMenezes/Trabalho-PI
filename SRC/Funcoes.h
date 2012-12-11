#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#include "Entidades.h"

/* Funcoes do FuncoesGeraisMenu.c */
void DesenhaMenu(char *CaminhoImagem, char *TituloMenu, int Posx, int Posy);
void FadeInMenu(char *CaminhoImagem, int velocidade);
void FadeOutMenu(int velocidade);
void MovimentaLogo(char *CaminhoImagem);
void PressioneQualquerTecla(char *CaminhoImagem);
void TocaEfeitoMenu(char *CaminhoMusica);
void TocaMusicaFundo(char *CaminhoMusica);

/* Funcoes do Menu.c e do GameOver.c e do GanhouJogo.c */
bool MenuLopping();
bool Menu();
void F_GameOver();
void F_GanhouJogo();

/* Funcoes do FuncoesUteis.c */
void TocaEfeito(ALLEGRO_SAMPLE *Sample, bool Life);
void TocaMusicaPrincipal (ALLEGRO_SAMPLE_INSTANCE *SongInstance);
void ParaMusicaPrincipal (ALLEGRO_SAMPLE_INSTANCE *SongInstance);
void FadeOut(int velocidade, int TamanhoAlfa);
void PauseGame();
void LoadGame(Heroi *Heroi);
void SaveGame(Mapas Mapa, Heroi Heroi);
void FadeIn(char *CaminhoImagem, int velocidade);

/* Funcoes do IniciarFinalizar.c */
bool IniciarJogo();
void FinalizarJogo();
void IniciarVariaveis();
void CarregaSistema(bool CodigoFonte);

/* Funcoes do Game.c */
void GameLooping();

/* Funcoes do Heroi.c */
void IniciaHeroi(Heroi *Heroi, ALLEGRO_BITMAP *ImagemHeroi);
void DrawHeroi(Heroi Heroi);
void MovimentaHeroi(Heroi *Heroi, int iSentido);
void ValidaColisaoHeroi(Heroi *Heroi, MagiasHeroi *MagiasHeroi, Monstros *Monstros, int Tipo);
void AtkFisicoHeroi(Heroi *Heroi, Mapas Mapa, Monstros Monstros[], int Flag);
void VerificaSentidoHeroi (Heroi *Heroi);

/* Funcoes do Mapas.c */
void IniciaMapa(Mapas *Mapa, int ID);
void DrawMapa(Mapas Mapa);
void MovimentaTela(float *cameraPosition, float x, float y, int width, int height);
void TrocaMapa(Heroi *Heroi, Mapas *Mapa);
void EventoBoss (Heroi *Heroi, Monstros Monstros[], Mapas Mapa);
void EventoBossTwo(Heroi *Heroi, Monstros Monstros[], Mapas Mapa);

/* Funcoes do InformacoesTela.c */
void ColocaInformacoesHeroi(Heroi Heroi, Mapas Mapa);
void ColocaBarraLoading(float QtdBarra, char *Mensagem);

/* Funcoes do Monstros.c */
void IniciaMonstros(Monstros Monstros[], ALLEGRO_BITMAP *ImagemMonstro, int QtdMonstros, bool Boss);
void DrawMonstros(Monstros Monstros[], int QtdMonstros);
void MovimentaMonstros(Monstros Monstros[], Heroi Heroi, int QtdMonstros);
void IA(Monstros Monstros, Heroi Heroi);

/* Funcoes do Colisao.c */
bool ColisaoTotal(Heroi Heroi, Monstros Monstros, MagiasHeroi MagiasHeroi, MagiasMonstros MagiasMonstros, Itens Itens, NPC NPC, int TipoColisao, int QuaisEntidades);
int TemColisao(Heroi Heroi);
int TemColisaoMonster(Monstros Monstros, int Sentido);
void CarregaMapaColisaoMonster(Mapas Mapa);
void CarregaMapaColisao(Mapas Mapa);

/* Funcoes do MagiasHeroi.c */
void IniciaMagia(Heroi Heroi, MagiasHeroi *MagiasHeroi, ALLEGRO_BITMAP *ImagemMagia, int Tipo);
void DrawMagic(MagiasHeroi MagiasHeroi);
void AtkMagia(MagiasHeroi *MagiasHeroi, Heroi *Heroi);
void RegeneraVidaPersonagem(Heroi *Heroi);
void RegeneraMana(Heroi *Heroi);

/* Funcoes do Itens.c */
void CriaItem(Itens *Item, Monstros Monstro, int Tipo, ALLEGRO_BITMAP *ImagemItem);
void DrawItem(Itens Item[]);
void ValidaColisaoItem(Heroi *Heroi, Itens *Item);

/* Funcoes do MagiasMonstros.c */
void AtkMagiaMonstros(MagiasMonstros *MagiasMonstros, Monstros *Monstros);
void IniciaMagiasMonstros(MagiasMonstros *MagiasMonstros, Monstros Monstros, ALLEGRO_BITMAP *ImagemMagia, int Tipo);
void DrawMagicMonster(MagiasMonstros MagiasMonstros[], int QtdMonstros);
void RegeneraVidaMonstros(Monstros *Monstros);

/* Funções do NPC.c */
void CriaNPC(NPC *NPC, int Tipo, int x, int y, ALLEGRO_BITMAP *ImagemNPCs, int Estado, int QtdDialogos,  ...);
void DrawNPC(struct NPC NPC[], int QtdNPC);
void MovimentaNPC(NPC NPC[], int QtdNPC, Heroi Heroi);
void ValidaNPC(NPC *NPC, Heroi *Heroi, int QtdNPC);
void NPCFalando (NPC *NPC);
void InsereNPCMapa (NPC NPC[], Mapas Mapa);
