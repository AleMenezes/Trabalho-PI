#include "Funcoes.h"

/* Variaveis do ALLEGRO */
ALLEGRO_DISPLAY *Display;
ALLEGRO_TRANSFORM camera;

ALLEGRO_EVENT_QUEUE *Fila_Eventos;
ALLEGRO_KEYBOARD_STATE keyState;

ALLEGRO_FONT *Fonte;
ALLEGRO_FONT *Fonte12;

ALLEGRO_TIMER *TimerFPS;
ALLEGRO_TIMER *MagiaPersonagem;
ALLEGRO_TIMER *TimerDropItens[10];
ALLEGRO_TIMER *AtkMonstros[10];
ALLEGRO_TIMER *TimerRespawMonster[10];
ALLEGRO_TIMER *Regenera;

ALLEGRO_BITMAP *ImagemHeroi;
ALLEGRO_BITMAP *ImagemNPC;
ALLEGRO_BITMAP *ImagemHeroiAtk;
ALLEGRO_BITMAP *ImagemMonstros;
ALLEGRO_BITMAP *ImagemBoss[2];
ALLEGRO_BITMAP *ImagemItem;
ALLEGRO_BITMAP *ImagemMapa[10];
ALLEGRO_BITMAP *ImagemMagiaMonstros;
ALLEGRO_BITMAP *ImagemMagiaHeroi[3];

/* Variaveis para Audio */
ALLEGRO_SAMPLE *Samples[4];
ALLEGRO_SAMPLE *SamplesAtk[3];
ALLEGRO_SAMPLE_INSTANCE *songInstance[10];
ALLEGRO_SAMPLE *MusicaPrincipal[10];

/*Variaveis Utilizadas no Menu Inicial */
ALLEGRO_SAMPLE *sample;
ALLEGRO_SAMPLE *Music;

/* Variaveis do Projeto */
int LARGURA_TELA;
int ALTURA_TELA;
int FPS;
int MAX_MONSTROS;
int MAX_MAPA;
float cameraPosition[2];
int i;
int IDMapa;
int LastID;
int Estado;
int AuxItemRaro;
bool TrocouMapa;
bool redraw;
bool GameOver;
bool FULLSCREEN;
int MatrizMapaColisao[100][100];
int MatrizMapaColisaoMonster[256][256];
bool EhBoss;
bool MatouBoss;
bool JaFezEvento;

/* Variaveis Auxiliares nos eventos do Menu */
bool SairJogo;
bool CarregarJogo;
bool NovoJogo;

/* ENUMS UTILIZADOS NO JOGO */
enum ANDANDO
{
	Up, Down, Left, Right, Parado, Andando
};

enum TipoMagia
{
	Fire, Ice, Life, Mort
};

enum TipoColisao
{
	Movimentacao, AtaqueFisico, AtaqueMagico
};

enum GrupoDeColisao
{
	HeroiEMonstros, MonstrosEHeroi, HeroiEItens, HeroiENPC
};

enum TipoDoItem
{
	PotionVida, PotionMana
};

enum TipoNPC
{
	NPCMagia, NPCArmadura, NPCCurandeira, NPCCivil, NPCGuarda, NPCAgricultor, NPCIdoso, Placa
};

enum EstadoNPC
{
	Falando, Mudo
};

enum TipoSomAtak
{
	Sword, SwordMiss, AtackMonstros
};

enum Mapa
{
	Casa, Floresta, Cidade, Loja, Curandeira, Montanha, Caverna, Castelo, CasteloInterior, Campo
};

enum EstadoBoss
{
	Humano, Dragao
};
