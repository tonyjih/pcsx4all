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

#define MAX_JS_BUTTONS 16
#define MAX_JS_PROFILES 10
#define MAX_CONTROLLERS 3

typedef struct ps1_controller {
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
	uint8_t player;              // player_1: 0, player_2: 1
	uint8_t analog_deadzone;     // int between 0 and 100
	uint8_t profile_id;          // 0 to MAX_JS_PROFILES
	SDL_Joystick* sdl_joy;       // used for native analog sticks and USB joysticks
} Ps1Controller;

// 0 for native sticks, 1 for external js1, 2 for external js2
extern struct ps1_controller controllers[MAX_CONTROLLERS];

// mapping of SDL buttons, line = profile, column = mapping SDL -> PSX
extern uint8_t profiles[MAX_JS_PROFILES][MAX_JS_BUTTONS];

enum PSX_BUTTON {
	DKEY_SELECT = 0,
	DKEY_L3,
	DKEY_R3,
	DKEY_START,
	DKEY_UP,
	DKEY_RIGHT,
	DKEY_DOWN,
	DKEY_LEFT,
	DKEY_L2,
	DKEY_R2,
	DKEY_L1,
	DKEY_R1,
	DKEY_TRIANGLE,
	DKEY_CIRCLE,
	DKEY_CROSS,
	DKEY_SQUARE,

	DKEY_TOTAL,
	DKEY_NONE
};



// enum {
// 	DKEY_TRIANGLE = 0,
// 	DKEY_CIRCLE,
// 	DKEY_CROSS,
// 	DKEY_SQUARE,
// 	DKEY_L1,
// 	DKEY_R1,
// 	DKEY_L2,
// 	DKEY_R2,
// 	DKEY_SELECT,
// 	DKEY_START,
// 	DKEY_L3,
// 	DKEY_R3,
// 	DKEY_UP,
// 	DKEY_RIGHT,
// 	DKEY_DOWN,
// 	DKEY_LEFT,

// 	DKEY_TOTAL
// };


///////////////////////////
// Windows compatibility //
///////////////////////////
#if defined(_WIN32) && !defined(__CYGWIN__)
// Windows lacks fsync():
static inline int fsync(int f) { return 0; }
#endif

#define	CONFIG_VERSION	0
#define JS_CONFIG_VERSION 0
#define JS_PROFILE_VERSION 0

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

void controller_config_load(int js_id);
void controller_config_save(int js_id);
void controller_profile_load(int js_id);
void controller_profile_save(int profile_id, uint8_t *but_map);
void controller_profile_set_to_default(int profile_id);

void update_memcards(int load_mcd);
const char *bios_file_get();
void bios_file_set(const char *filename);
void check_spec_bios();

int SelectGame();
int GameMenu();

#endif
