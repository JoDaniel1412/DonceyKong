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
#include "../../datastructures/LinkedList.h"
#include "CollisionHandler.h"
#include "../../lib/json.h"
#include "../../lib/cJSON.h"

Junior *junior;
Entity *donkey;
Platform **platforms;
Rope **ropes;
LinkedList *crocos;
Entity *key;
int id;
int ropeAmount;
ALLEGRO_EVENT_QUEUE *eventQueue;

void createGameWindow();
void startGame(ALLEGRO_DISPLAY *gameWindowDisplay);
void initializeWidgets(ALLEGRO_DISPLAY *gameWindowDisplay);
ALLEGRO_EVENT_QUEUE* setEventQueue(ALLEGRO_DISPLAY *gameWindowDisplay, ALLEGRO_TIMER *timer);
void createJunior();
void createPlatforms();
void createRopes();
void createCroco(int ropeNumber, int isRedCroco, int Id);
void createCrocoID(int ropeNumber, int isRedCroco, int Id);
int getRopePosition(int ropeColumn);
ALLEGRO_BITMAP* setBitmap(char* imgPath);
int gameLoop();
int eventManager();
void redrawDisplay();
void deleteWidgets();
void closeGameWindow(ALLEGRO_DISPLAY *gameWindowDisplay);
void clientUpdate();
char *serializeGame();
void parseGame(json_char *json);
#endif //C_CLIENT_GAMEWINDOW_H
