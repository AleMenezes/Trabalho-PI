typedef struct Heroi
{
	int x;
	int y;

	int maxFrame;
	int curFrame;
	int CurFramePadrao;
	int frameWidth;
	int frameHeight;
	int ColunaAnimacao;
	int LinhaAnimacao;
	int animationDirection;
	int frameCount;
	int frameDelay;

	int Life;
	int MaxLife;
	int Mana;
	int MaxMana;
	int ForcaAtk;
	bool Atacou;
	bool AtkMagia;

	int QtdVida;
	int QtdMana;

	int Sentido;
	int Velocidade;

	ALLEGRO_BITMAP *ImagemHeroi;
} Heroi;

typedef struct MagiasHeroi
{
	int x;
	int y;

	int maxFrame;
	int curFrame;
	int frameWidth;
	int frameHeight;
	int ColunaAnimacao;
	int LinhaAnimacao;

	int animationDirection;
	int frameCount;
	int frameDelay;

	int Velocidade;

	int Distancia; //Utilizada na Colisão
	int Atk;
	int GastoMana;
	int Tipo;
	bool Mostrar;
	bool Colisao;
	int Sentido;

	ALLEGRO_BITMAP *ImagemMagiasHeroi;
} MagiasHeroi;

typedef struct NPC
{
	int x;
	int y;

	int LimiteX1;
	int LimiteX2;
	int LimiteY1;
	int LimiteY2;

	int Velocidade;
	int Tipo;

	int maxFrame;
	int curFrame;
	int curFramePadrao;

	int frameWidth;
	int frameHeight;
	int ColunaAnimacao;
	int LinhaAnimacao;
	int animationDirection;
	int frameCount;
	int frameDelay;

	int Sentido;
	int Estado;
	char *FalaNPC[10];
	int QtdFalas;

	ALLEGRO_BITMAP *ImagemNPC;
} NPC;

typedef struct Monstros
{
	int x;
	int y;

	int maxFrame;
	int curFrame;
	int curFramePadrao;
	int frameWidth;
	int frameHeight;
	int ColunaAnimacao;
	int LinhaAnimacao;
	int animationDirection;
	int frameCount;
	int frameDelay;

	bool Vivo;
	bool Foge;
	bool DropItens;
	int Sentido;
	int ForcaAtk;

	int Life;
	int MaxLife;

	/* Variaveis auxiliares na movimentação do Monstro */
	bool AndandoEsquerda;
	bool AndandoDireita;
	bool AndandoCima;
	bool AndandoBaixo;

	bool Andar;

	int Velocidade;
	bool Boss;

	ALLEGRO_BITMAP *ImagemMonstros;
} Monstros;

typedef struct MagiasMonstros
{
	int x;
	int y;

	int maxFrame;
	int curFrame;
	int frameWidth;
	int frameHeight;
	int ColunaAnimacao;
	int LinhaAnimacao;

	int animationDirection;
	int frameCount;
	int frameDelay;

	int Velocidade;

	int Atk;
	int Tipo;
	bool Mostrar;
	int Sentido;

	ALLEGRO_BITMAP *ImagemMagiasMonstros;
} MagiasMonstros;

typedef struct Itens
{
	int x;
	int y;

	int maxFrame;
	int curFrame;
	int frameWidth;
	int frameHeight;
	int ColunaAnimacao;
	int LinhaAnimacao;

	int Tipo;
	bool Mostrar;

	ALLEGRO_BITMAP *ImagemItem;
} Itens;

typedef struct Mapas
{
	int ID;
	int QtdMonstros;
	int QtdNPC;
	char *CaminhoMapaColisao;
	int QtdColunaColisao;

	char *CaminhoMapaColisaoMonster;
	int QtdColunaColisaoMonster;
} Mapas;
