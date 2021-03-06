#ifndef QUADPONG_H
#define QUADPONG_H

#define _MATH_DEFINES_DEFINED

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ws2tcpip.h>

#include <BaseTsd.h>
typedef SSIZE_T ssize_t;

#else

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define _strdup strdup

#endif // WIN32

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

typedef SDL_Rect  rect_t;
typedef SDL_Color color_t;

extern SDL_Window *   g_window;   /**< Global reference to the Window */
extern SDL_Renderer * g_renderer; /**< Global reference to the Renderer */

extern TTF_Font * g_fnt_large; /**< Global large font */
extern TTF_Font * g_fnt_small; /**< Global small font */

extern bool g_running;
extern bool g_cap_fps;
extern bool g_show_fps;
extern int  g_max_fps;

#define GAME_TITLE "Quadpong"

#define WIN_WIDTH (700)
#define WIN_HEIGHT (700 + 20)

#define FONT_LARGE_SIZE (40)
#define FONT_SMALL_SIZE (20)

#define PLAYER_SPEED (5.0f)
#define BALL_SPEED (5.0f)

#define PLAYER_V_WIDTH (32)
#define PLAYER_V_HEIGHT (128)
#define PLAYER_H_WIDTH (128)
#define PLAYER_H_HEIGHT (32)

#define BALL_SIZE (16)
#define WALL_PADDING (PLAYER_V_WIDTH / 2)
#define CORNER_SIZE (PLAYER_V_WIDTH + WALL_PADDING)

#define MAX_PLAYERS (4)

#define PORT "57664"
#define UPDATE_DELAY (60)
#define MAX_PLAYER_TTL (UPDATE_DELAY * 10)

#define ASSET_PATH "assets/"
#define PIXEL_ASSET_PATH ASSET_PATH "pixel.png"
#define TITLE_ASSET_PATH ASSET_PATH "title.png"
#define FONT_ASSET_PATH ASSET_PATH "roboto.ttf"

#endif // QUADPONG_H
