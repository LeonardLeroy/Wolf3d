/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** sound.c
*/

#include "wolf3d.h"

static sfSound *create_and_play_sound(sfSoundBuffer **buffer, const char *snd,
    int vol)
{
    sfSound *temp = sfSound_create();

    *buffer = sfSoundBuffer_createFromFile(sound(snd));
    if (!vol || vol < 0)
        vol = DEFAULT_SFX_VOLUME;
    if (!(*buffer) || !temp) {
        if (*buffer)
            sfSoundBuffer_destroy(*buffer);
        if (temp)
            sfSound_destroy(temp);
        return NULL;
    }
    sfSound_setBuffer(temp, *buffer);
    sfSound_setVolume(temp, vol);
    sfSound_play(temp);
    return temp;
}

static void cleanup_sound_at_index(sound_handler_t *sound_handler, int index)
{
    if (sound_handler->sound_player[index] == NULL)
        return;
    sfSound_destroy(sound_handler->sound_player[index]->sound);
    sfSoundBuffer_destroy(sound_handler->sound_player[index]->buffer);
    free(sound_handler->sound_player[index]);
    sound_handler->sound_player[index] = NULL;
    sound_handler->active_sound_count--;
}

static int find_and_free_completed_sound(sound_handler_t *sound_handler)
{
    for (int i = 0; i < MAX_SOUND_BUFFER; i++) {
        if (sound_handler->sound_player[i] &&
            sfSound_getStatus(sound_handler->sound_player[i]->sound)
                != sfPlaying) {
            cleanup_sound_at_index(sound_handler, i);
            return 1;
        }
    }
    return 0;
}

static void insert_sound_in_player(sound_handler_t *sound_handler,
    sfSound *sound, sfSoundBuffer *buffer)
{
    int slot_found = 0;

    for (int i = 0; i < MAX_SOUND_BUFFER; i++) {
        if (sound_handler->sound_player[i] == NULL) {
            sound_handler->sound_player[i] = salloc(sizeof(sound_player_t));
            sound_handler->sound_player[i]->sound = sound;
            sound_handler->sound_player[i]->buffer = buffer;
            sound_handler->active_sound_count++;
            slot_found = 1;
            break;
        }
    }
    if (!slot_found) {
        sfSound_destroy(sound);
        sfSoundBuffer_destroy(buffer);
    }
}

void play_sound(sfml_t *sfml, const char *snd, int vol)
{
    sfSoundBuffer *buffer;
    sfSound *sound;
    sound_handler_t *sound_handler = sfml->sound;
    float volume;

    if (sound_handler->active_sound_count >= MAX_SOUND_BUFFER) {
        if (!find_and_free_completed_sound(sound_handler))
            return;
    }
    volume = vol * sound_handler->sfx_volume;
    volume /= 100;
    sound = create_and_play_sound(&buffer, snd, volume);
    if (!sound)
        return;
    insert_sound_in_player(sound_handler, sound, buffer);
}

void sound_update(sfml_t *sfml)
{
    sound_handler_t *sound_handler = sfml->sound;

    if (sound_handler->active_sound_count < 1)
        return;
    for (int i = 0; i < MAX_SOUND_BUFFER; i++) {
        if (sound_handler->sound_player[i] == NULL)
            continue;
        if (sfSound_getStatus(sound_handler->sound_player[i]->sound)
            != sfPlaying)
            cleanup_sound_at_index(sound_handler, i);
    }
}

void destroy_sounds(sfml_t *sfml)
{
    sound_handler_t *sound_handler = sfml->sound;

    if (sound_handler->active_sound_count < 1)
        return;
    for (int i = 0; i < MAX_SOUND_BUFFER; i++) {
        if (sound_handler->sound_player[i] != NULL)
            cleanup_sound_at_index(sound_handler, i);
    }
}

void init_sounds(sfml_t *sfml)
{
    sfml->sound = salloc(sizeof(sound_handler_t));
    sfml->sound->active_sound_count = 0;
    sfml->sound->sfx_volume = 50;
    for (int i = 0; i < MAX_SOUND_BUFFER; i++)
        sfml->sound->sound_player[i] = NULL;
}

void free_sounds(sfml_t *sfml)
{
    destroy_sounds(sfml);
    free(sfml->sound);
    sfml->sound = NULL;
}
