//
// Created by Erick Barrantes on 9/19/2019.
//
#include "GameWindow.h"


void createGameWindow(){
    ALLEGRO_DISPLAY *gameWindowDisplay;
    al_init();

    gameWindowDisplay = al_create_display(GW_WIDTH, GW_HEIGHT);
    al_init_image_addon();

    ALLEGRO_TIMER *timer = NULL;
    timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);

    ALLEGRO_EVENT_QUEUE *eventQueue = setEventQueue(gameWindowDisplay, timer);

    createJunior();
    createPlatforms();
    createRopes();
    donkey = initializeEntity(0, DK_X_POS, DK_Y_POS, DK_X_POS, DK_Y_POS, "donkey", setBitmap("../sprites/dk.png"));

    gameLoop(eventQueue);

    closeGameWindow(gameWindowDisplay, eventQueue);
}

ALLEGRO_EVENT_QUEUE* setEventQueue(ALLEGRO_DISPLAY *gameWindowDisplay, ALLEGRO_TIMER *timer){
    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
    eventQueue = al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(gameWindowDisplay));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    return eventQueue;
}

void createJunior(){
    junior = (Junior*) malloc(sizeof(Junior));
    junior->entity = initializeEntity(1, JR_X_INITIAL, JR_Y_INITIAL, JR_X_INITIAL, JR_Y_INITIAL, "junior",
                                      setBitmap("../sprites/jr.png"));
    pushEntity(junior->entity);
}

void createPlatforms(){
    platforms = (Platform**) malloc(PLATFORMS_TOTAL * sizeof(Platform*));
    char* imgPath = NULL;
    float x, y;
    for(int i = 0; i < PLATFORMS_TOTAL; i++) {
        if(i < AMOUNT_PLATFORMS1){
            x = PLATFORM1_X_POS[i];
            y = PLATFORM1_Y_POS[i];
            imgPath = "../sprites/platform1.png";
        }else{
            x = PLATFORM2_X_POS[i - AMOUNT_PLATFORMS1];
            y = PLATFORM2_Y_POS[i - AMOUNT_PLATFORMS1];
            imgPath = "../sprites/platform2.png";
        }
        platforms[i] = initializePlatform(i+2, x, y, x, y, "platform", setBitmap(imgPath), PLATFORM_WIDTH,
                                           PLATFORM_HEIGHT);
    }
}

void createRopes(){
    ropes = (Rope**) malloc(AMOUNT_OF_ROPES * sizeof(Rope*));
    char* imgPath = "../sprites/rope.png";
    for(int i = 0; i < AMOUNT_OF_ROPES; i++)
        ropes[i] = initializeRope(0, ROPE_X_POSITION[i], ROPE_Y_POSITION[i], ROPE_X_POSITION[i], ROPE_Y_POSITION[i],
                                  "rope", setBitmap(imgPath), ROPE_WIDTH, ROPE_HEIGHT);
    free(imgPath);
}

ALLEGRO_BITMAP* setBitmap(char* imgPath){
    ALLEGRO_BITMAP *bitmap = NULL;
    bitmap = al_load_bitmap(imgPath);
    assert(bitmap != NULL);
    return bitmap;
}

void gameLoop(ALLEGRO_EVENT_QUEUE *eventQueue){
    int playing = TRUE, falling = FALSE, jumping = FALSE;
    float jumpCount = 0.0f;
    int timer = 0;
    ALLEGRO_KEYBOARD_STATE keyState;
    while (playing) {
        playing = eventManager(eventQueue);

        al_get_keyboard_state(&keyState);

        moveJrRight(junior, keyState);
        moveJrLeft(junior, keyState);
        if(!jumping) falling = moveJrDown(junior, keyState, platforms, ropes);
        if(!falling) jumping = moveJrUp(junior, keyState, &jumpCount, jumping, platforms, ropes);

        timer++;

        if(junior->entity->y > GW_HEIGHT)
            playing = false;

        if (timer > 30000) {
            clientUpdate();
            timer = 0;
        }
    }
}

int eventManager(ALLEGRO_EVENT_QUEUE *eventQueue){
    ALLEGRO_EVENT event;
    if (!al_is_event_queue_empty(eventQueue)) {
        al_wait_for_event(eventQueue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            return FALSE;
        if(event.type == ALLEGRO_EVENT_TIMER) {
            redrawDisplay();
        }
    }
    return TRUE;
}

void redrawDisplay(){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for(int i = 0; i < PLATFORMS_TOTAL; i++)
        drawBitmap(platforms[i]->entity);
    for(int i = 0; i < AMOUNT_OF_ROPES; i++)
        drawBitmap(ropes[i]->entity);
    drawBitmap(junior->entity);
    drawBitmap(donkey);
    al_flip_display();
}
void closeGameWindow(ALLEGRO_DISPLAY *gameWindowDisplay, ALLEGRO_EVENT_QUEUE *eventQueue){
    al_destroy_display(gameWindowDisplay);
    al_uninstall_keyboard();
    al_destroy_bitmap(junior->entity->bitmap);
    al_destroy_event_queue(eventQueue);
    free(junior);
    for(int i = 0; i < PLATFORMS_TOTAL; i++)
        free(platforms[i]);
    free(platforms);
}

void clientUpdate() {
    json_value *jsonEntities = serializeEntities();
    message(serializeGame(jsonEntities));
}

char *serializeGame(json_value *entities) {
    json_value *obj = json_object_new((size_t) length);

    json_value *game = json_integer_new(id);

    json_object_push(obj, "game", game);
    json_object_push(obj, "entities", entities);

    json_char *buf = malloc(json_measure(obj));
    json_serialize(buf, obj);
    return buf;
}