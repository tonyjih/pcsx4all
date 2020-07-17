#ifndef __PSXPORT_H__
#define __PSXPORT_H__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <assert.h>
#include <SDL.h>

struct ps1_controller {
	uint8_t id;
	uint8_t joy_right_ax0;
	uint8_t joy_right_ax1;
	uint8_t joy_left_ax0;
	uint8_t joy_left_ax1;
	uint8_t Vib[2];
	uint8_t VibF[2];
	uint8_t pad_mode;
	uint8_t pad_controllertype;
	uint8_t configmode;
	uint8_t player;				// player-1: 0, player-2: 1
	uint_least8_t but_map[16];	// mapping of SDL buttons, the index is the SDL id of the button
	SDL_Joystick* sdl_joy;		// used for native analog sticks and USB joysticks
};

// 0 for native sticks, 1 for external js1, 2 for external js2
extern struct ps1_controller controllers[3];

///////////////////////////
// Windows compatibility //
///////////////////////////
#if defined(_WIN32) && !defined(__CYGWIN__)
// Windows lacks fsync():
static inline int fsync(int f) { return 0; }
#endif

#define	CONFIG_VERSION	0

unsigned get_ticks(void);
void wait_ticks(unsigned s);
void pad_update(void);
unsigned short pad_read(int num);

void video_flip(void);
#ifdef GPU_DFXVIDEO
void video_set(unsigned short* pVideo,unsigned int width,unsigned int height);
#endif
void video_clear(void);
void video_clear_cache();
void port_printf(int x, int y, const char *text);

extern unsigned short *SCREEN;
extern int SCREEN_WIDTH, SCREEN_HEIGHT;

int state_load(int slot);
int state_save(int slot);

void update_memcards(int load_mcd);
const char *bios_file_get();
void bios_file_set(const char *filename);
void check_spec_bios();

int SelectGame();
int GameMenu();

#endif
