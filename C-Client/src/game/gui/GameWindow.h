//
// Created by Erick Barrantes on 9/19/2019.
//

#ifndef C_CLIENT_GAMEWINDOW_H
#define C_CLIENT_GAMEWINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "../../util/var.h"
#include "../entities/Entities.h"
#include "../entities/Junior.h"
#include "../entities/Platform.h"
#include "../../client/Client.h"
#include "../entities/Rope.h"



Junior *junior;
Entity *donkey;
Platform **platforms;
Entity *key;
Rope **ropes;
int id;

void createGameWindow();
ALLEGRO_EVENT_QUEUE* setEventQueue(ALLEGRO_DISPLAY *gameWindowDisplay, ALLEGRO_TIMER *timer);
void createJunior();
void createPlatforms();
void createRopes();
ALLEGRO_BITMAP* setBitmap(char* imgPath);
int gameLoop(ALLEGRO_EVENT_QUEUE *eventQueue);
int eventManager(ALLEGRO_EVENT_QUEUE *eventQueue);
void redrawDisplay();
void closeGameWindow(ALLEGRO_DISPLAY *gameWindowDisplay, ALLEGRO_EVENT_QUEUE *eventQueue);
void clientUpdate();
char *serializeGame(json_value *);
#endif //C_CLIENT_GAMEWINDOW_H
