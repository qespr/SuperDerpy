/*! \file map.c
 *  \brief View with Map of levels.
 */
/*
 * Copyright (c) Sebastian Krzyszkowiak <dos@dosowisko.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include <stdio.h>
#include <math.h>
#include "../config.h"
#include "map.h"

void Map_Draw(struct Game *game) {
	al_draw_bitmap(game->map.map, 0, 0, 0);
	float x = 0, y = 0;
	switch (game->map.selected) {
		case 1:
			x=0.2;
			y=0.25;
			break;
		case 2:
			x=0.495;
			y=0.35;
			break;
		case 3:
			x=0.72;
			y=0.4;
			break;
		case 4:
			x=0.7;
			y=0.77;
			break;
		case 5:
			x=0.248;
			y=0.75;
			break;
		case 6:
			x=0.425;
			y=0.675;
			break;
	}
	al_draw_scaled_bitmap(game->map.arrow, 0, 0, al_get_bitmap_width(game->map.arrow), al_get_bitmap_height(game->map.arrow),
			      (game->viewportWidth-game->viewportHeight * 1.6) / 2 + game->viewportHeight * 1.6 * x, game->viewportHeight * y
			      + ((sin(game->map.arrowpos) + 0.5) / 20.0) * game->viewportHeight, game->viewportHeight * 1.6 * 0.1,
			      game->viewportHeight * 0.16, 0);
}

void Map_Logic(struct Game *game) {
	game->map.arrowpos += 0.1;
}

void Map_Load(struct Game *game) {
	al_play_sample_instance(game->map.music);
	FadeGameState(game, true);
}

int Map_Keydown(struct Game *game, ALLEGRO_EVENT *ev) {
        //Man, you could have just used <- and -> and everyone would get it, this is brutal
	if ((((game->map.selected < 4) || (game->map.selected == 6)) && (ev->keyboard.keycode == ALLEGRO_KEY_LEFT)) ||
	    ((game->map.selected > 4) && (game->map.selected != 6) && (ev->keyboard.keycode == ALLEGRO_KEY_RIGHT)) ||
	    ((game->map.selected == 4) && (ev->keyboard.keycode == ALLEGRO_KEY_UP)) ||
	    ((game->map.selected == 6) && (ev->keyboard.keycode == ALLEGRO_KEY_DOWN)))
	  {
		game->map.selected--;
		al_play_sample_instance(game->map.click);
	  }
	else if (((game->map.selected < 3) && (ev->keyboard.keycode == ALLEGRO_KEY_RIGHT)) ||
		 ((game->map.selected == 4) && (ev->keyboard.keycode == ALLEGRO_KEY_LEFT)) ||
		 ((game->map.selected == 3) && (ev->keyboard.keycode == ALLEGRO_KEY_DOWN)) ||
		 ((game->map.selected == 5) && (ev->keyboard.keycode == ALLEGRO_KEY_UP)))
	  {
		game->map.selected++;
		al_play_sample_instance(game->map.click);
	  }
	else if ((ev->keyboard.keycode == ALLEGRO_KEY_LEFT) || (ev->keyboard.keycode == ALLEGRO_KEY_RIGHT) ||
		 (ev->keyboard.keycode == ALLEGRO_KEY_UP) || (ev->keyboard.keycode == ALLEGRO_KEY_DOWN)) {
	        al_play_sample_instance(game->map.click);
	} else if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER) {
		al_play_sample_instance(game->map.click);
		game->level.input.current_level = game->map.selected;
		PrintConsole(game, "Selecting level %d...", game->map.selected);
		UnloadGameState(game);
		game->gamestate = GAMESTATE_LOADING;
		game->loadstate = GAMESTATE_LEVEL;
		return 0;
	} else if (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		UnloadGameState(game);
		game->loadstate = GAMESTATE_MENU;
		LoadGameState(game);
		return 0;
	} else { return 0; }
	if (game->map.selected < 1) game->map.selected = 1;
	if (game->map.selected > game->map.available) game->map.selected = game->map.available;
	return 0;
}

void Map_Preload(struct Game *game, void (*progress)(struct Game*, float)) {
	PROGRESS_INIT(7);

	game->map.available = atoi(GetConfigOptionDefault("MuffinAttack", "level", "1"));
	if ((game->map.available < 1) || (game->map.available > 6)) game->map.available = 1;
	game->map.selected = game->map.available;
	PrintConsole(game, "Last level available: %d", game->map.selected);
	game->map.arrowpos = 0;

	game->map.map_bg = LoadScaledBitmap("map/background.png", game->viewportHeight * 1.6, game->viewportHeight);
	PROGRESS;
	char filename[30] = { };
	sprintf(filename, "map/highlight%d.png", game->map.available);
	game->map.highlight = LoadScaledBitmap(filename, game->viewportHeight * 1.6, game->viewportHeight);
	PROGRESS;

	game->map.arrow = al_load_bitmap( GetDataFilePath("map/arrow.png") );
	PROGRESS;

	game->map.click_sample = al_load_sample( GetDataFilePath("menu/click.flac") );
	PROGRESS;
	game->map.sample = al_load_sample( GetDataFilePath("map/map.flac") );
	PROGRESS;

	game->map.music = al_create_sample_instance(game->map.sample);
	al_attach_sample_instance_to_mixer(game->map.music, game->audio.music);
	al_set_sample_instance_playmode(game->map.music, ALLEGRO_PLAYMODE_LOOP);

	game->map.click = al_create_sample_instance(game->map.click_sample);
	al_attach_sample_instance_to_mixer(game->map.click, game->audio.fx);
	al_set_sample_instance_playmode(game->map.click, ALLEGRO_PLAYMODE_ONCE);

	if (!game->map.sample){
		fprintf(stderr, "Audio clip sample not loaded!\n" );
		exit(-1);
	}
	if (!game->map.click_sample){
		fprintf(stderr, "Audio clip sample#2 not loaded!\n" );
		exit(-1);
	}

	game->map.map = LoadScaledBitmap("table.png", game->viewportWidth, game->viewportHeight);
	PROGRESS;
	al_set_target_bitmap(game->map.map);
	al_draw_bitmap(game->map.map_bg, (game->viewportWidth - game->viewportHeight * 1.6)/2, 0 ,0);
	al_draw_bitmap(game->map.highlight, (game->viewportWidth-game->viewportHeight * 1.6)/2, 0 ,0);
	al_set_target_bitmap(al_get_backbuffer(game->display));
	PROGRESS;
}

void Map_Unload(struct Game *game) {
	FadeGameState(game, false);
	al_destroy_bitmap(game->map.map);
	al_destroy_bitmap(game->map.map_bg);
	al_destroy_bitmap(game->map.highlight);
	al_destroy_bitmap(game->map.arrow);
	al_destroy_sample_instance(game->map.music);
	al_destroy_sample(game->map.sample);
	al_destroy_sample_instance(game->map.click);
	al_destroy_sample(game->map.click_sample);
}
