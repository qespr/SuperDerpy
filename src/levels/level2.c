/*! \file level2.c
 *  \brief Level 2 code.
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
#include "../gamestates/level.h"
#include "../timeline.h"
#include "actions.h"
#include "level2.h"
#include "modules/derpControlls.h"

void Level2_Load(struct Game *game) {
  DerpControlls_Load(game);
  TM_AddBackgroundAction(&FadeIn, NULL, 0, "fadein");
  TM_AddDelay(1000);
  TM_AddBackgroundAction(&FadeIn, NULL, 0, "fadein");
  TM_AddDelay(1000);
  TM_AddQueuedBackgroundAction(&Welcome, NULL, 0, "welcome");
  TM_AddDelay(1000);
  TM_AddAction(&Walk, NULL, "walk");
  TM_AddAction(&Move, NULL, "move");
  TM_AddAction(&Stop, NULL, "stop");
  TM_AddDelay(1000);
  TM_AddAction(&Letter, NULL, "letter");
  TM_AddDelay(200);
  TM_AddQueuedBackgroundAction(&Accelerate, NULL, 0, "accelerate");
  TM_AddAction(&Fly, NULL, "fly");
  TM_AddDelay(500);
  /* first part gameplay goes here */

  /* actions for generating obstacles should go here
   * probably as regular actions. When one ends, harder one
   * begins. After last one part with muffins starts. */
  TM_AddAction(&GenerateObstacles, NULL, "obstacles");
  TM_AddDelay(3*1000);
  /* wings disappear, deccelerate */
  TM_AddAction(&Run, NULL, "run");
  TM_AddDelay(3*1000);
  /* FadeGameState(game, true); */
}

void Level2_Unload(struct Game *game) {
}

void Level2_UnloadBitmaps(struct Game *game) {
}

void Level2_Preload(struct Game *game) {
}

int Level2_PreloadSteps(void) {
	return 0;
}

void Level2_PreloadBitmaps(struct Game *game, void (*progress)(struct Game*, float)) {
	//PROGRESS_INIT(Level2_PreloadSteps());
}

void Level2_Draw(struct Game *game) {

}

void Level2_Logic(struct Game *game) {
}

void Level2_Keydown(struct Game *game, ALLEGRO_EVENT *ev) {

}

void Level2_ProcessEvent(struct Game *game, ALLEGRO_EVENT *ev) {
}

void Level2_Resume(struct Game *game) {
}

void Level2_Pause(struct Game *game) {
}
