#include "Variaveis.h"

void ColocaInformacoesHeroi(Heroi Heroi, Mapas Mapa)
{
	/* Coloca as coordenadas do personagem na tela */
	al_draw_textf(Fonte, al_map_rgb(255, 255, 255), cameraPosition[0] + (LARGURA_TELA - 200), cameraPosition[1], 0, "Posx: %d", Heroi.x);
	al_draw_textf(Fonte, al_map_rgb(255, 255, 255), cameraPosition[0] + (LARGURA_TELA - 200), cameraPosition[1] + 15, 0, "Posy: %d", Heroi.y);

	/* Coloca as informações do Personagem Na Tela */
	/*------------------------------------------------------- */
	/* Barra de Vida */
	al_draw_text(Fonte, al_map_rgb(255, 255, 255), cameraPosition[0] + 13, cameraPosition[1] + 2, 0, "Life:");
	al_draw_filled_rectangle(cameraPosition[0] + 45, cameraPosition[1] + 7, cameraPosition[0] + (45 + (200.00 / Heroi.MaxLife) * Heroi.Life), cameraPosition[1] + 16, al_map_rgb(255, 0, 0));
	al_draw_rectangle(cameraPosition[0] + 45, cameraPosition[1] + 7, cameraPosition[0] + 245, cameraPosition[1] + 16, al_map_rgb(255, 153, 153), 0);
	al_draw_textf(Fonte12, al_map_rgb(255, 255, 255), cameraPosition[0] + 100, cameraPosition[1] + 5, 0, "%d / %d", Heroi.Life, Heroi.MaxLife);

	/* ADICIONAR MANA NO PERSONAGEM */
	al_draw_text(Fonte, al_map_rgb(255, 255, 255), cameraPosition[0] + 2, cameraPosition[1] + 17, 0, "Mana:");
	al_draw_filled_rectangle(cameraPosition[0] + 45, cameraPosition[1] + 22, cameraPosition[0] + (45 + (200.00 / Heroi.MaxMana) * Heroi.Mana), cameraPosition[1] + 32, al_map_rgb(0, 0, 255));
	al_draw_rectangle(cameraPosition[0] + 45, cameraPosition[1] + 22, cameraPosition[0] + 245, cameraPosition[1] + 32, al_map_rgb(255, 255, 255), 0);
	al_draw_textf(Fonte12, al_map_rgb(255, 255, 255), cameraPosition[0] + 100, cameraPosition[1] + 20, 0, "%d / %d", Heroi.Mana, Heroi.MaxMana);

	al_draw_textf(Fonte, al_map_rgb(255, 255, 255), cameraPosition[0] + (LARGURA_TELA - 200), cameraPosition[1] + 30, 0, "Vida: %d", Heroi.QtdVida);
	al_draw_textf(Fonte, al_map_rgb(255, 255, 255), cameraPosition[0] + (LARGURA_TELA - 200), cameraPosition[1] + 45, 0, "Mana: %d", Heroi.QtdMana);
}

void ColocaBarraLoading(float QtdBarra, char *Mensagem)
{
	ALLEGRO_FONT *FonteTemp = al_load_font("Arial.ttf", 12, 0);
	ALLEGRO_FONT *Fonte10Temp = al_load_font("Arial.ttf", 10, 0);

	char *MsgAguade = "Aguarde, Carregando o Sistema...";

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_textf(FonteTemp, al_map_rgb(255, 255, 255), 200, (ALTURA_TELA / 2) + 5, 0, "%s", MsgAguade);
	al_draw_rectangle(200, (ALTURA_TELA / 2) + 22, LARGURA_TELA - 200, (ALTURA_TELA / 2) + 32, al_map_rgb(255, 255, 255), 0);
	al_draw_filled_rectangle(200, (ALTURA_TELA / 2) + 22, (200 + ((LARGURA_TELA - 400) / 100) * QtdBarra), (ALTURA_TELA / 2) + 32, al_map_rgb(225, 255, 255));
	al_draw_textf(Fonte10Temp, al_map_rgb(255, 255, 255), 200, (ALTURA_TELA / 2) + 37, 0, "%s", Mensagem);
	al_flip_display();

	al_destroy_font(FonteTemp);
	al_destroy_font(Fonte10Temp);
}
