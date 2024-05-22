#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <Windows.h>
#include <string>
#include <SDL_video.h>
#include <vector>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iomanip>


const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

const int NUM_THREATS = 8;
const int NUM_THREATS3 = 6;

const int TOCDOTHREATS1 = 5;
const int TOCDOTHREATS2 = 20;
const int TOCDOTHREATS3 = 7;

#define VATCAN_1_X 60
#define VATCAN_1_Y 380
#define VATCAN_1_W 160
#define VATCAN_1_H 20

#define VATCAN_2_X 350
#define VATCAN_2_Y 250
#define VATCAN_2_W 160
#define VATCAN_2_H 20

#define VATCAN_3_X 800
#define VATCAN_3_Y 150
#define VATCAN_3_W 300
#define VATCAN_3_H 20

#define VATCAN_4_X 1200
#define VATCAN_4_Y 400
#define VATCAN_4_W 100
#define VATCAN_4_H 20

#define VATCAN_5_X 1500
#define VATCAN_5_Y 360
#define VATCAN_5_W 50
#define VATCAN_5_H 20

#define VATCAN_6_X 1750
#define VATCAN_6_Y 350
#define VATCAN_6_W 200
#define VATCAN_6_H 20

#define VATCAN_7_X 2000
#define VATCAN_7_Y 200
#define VATCAN_7_W 320
#define VATCAN_7_H 20

#define VATCAN_8_X 3100
#define VATCAN_8_Y 380
#define VATCAN_8_W 150
#define VATCAN_8_H 20

#define VATCAN_9_X 3400
#define VATCAN_9_Y 200
#define VATCAN_9_W 200
#define VATCAN_9_H 20

#define VATCAN_0_X 2600
#define VATCAN_0_Y 320
#define VATCAN_0_W 320
#define VATCAN_0_H 20


#define DIEMBATDAU 400

const int FRAME_PER_SECOND = 30;


static SDL_Surface* g_screen = NULL;
static SDL_Window* g_window = NULL;
static SDL_Event g_event;

static Mix_Chunk* g_sound[5];

static Mix_Music* g_music = NULL;

static TTF_Font* g_font_text = NULL;
static TTF_Font* g_font_menu = NULL;

using namespace std;



SDL_Surface* LoadImage(string file_path)
{
    SDL_Surface* load_image = NULL;
    SDL_Surface* optimize_image = NULL;
    Uint32 color_key;

    load_image = IMG_Load(file_path.c_str());
    if (load_image != NULL) {
        optimize_image = SDL_ConvertSurface(load_image, load_image->format, 0);
        SDL_FreeSurface(load_image);

        if (optimize_image != NULL) {
            color_key = SDL_MapRGB(optimize_image->format, 0x0, 0xFF, 0xFF);
            SDL_SetColorKey(optimize_image, SDL_TRUE, color_key);
        }
    }
    return optimize_image;
}


void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);
}

void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, clip, des, &offset);
}

void CleanUp()
{
    for (int i = 0; i < 5; i++) {
        if (g_sound[i] != NULL) {
            Mix_FreeChunk(g_sound[i]);
            g_sound[i] = NULL;
        }
    }
    Mix_CloseAudio();
    SDL_DestroyWindow(g_window);
}


int GetRandom(int min, int max) {
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
    return false;
}

int CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2, const int& x_vantoc)
{
    int left_a = x_vantoc;
    int right_a = x_vantoc + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a >= left_b && left_a <= right_b)
    {
        if (top_a >= top_b && top_a <= bottom_b)
        {
            return 1;
        }
    }

    if (left_a >= left_b && left_a <= right_b)
    {
        if (bottom_a >= top_b && bottom_a <= bottom_b)
        {
            return 2;
        }
    }

    if (right_a >= left_b && right_a <= right_b)
    {
        if (top_a >= top_b && top_a <= bottom_b)
        {
            return 3;
        }
    }

    if (right_a >= left_b && right_a <= right_b)
    {
        if (bottom_a >= top_b && bottom_a <= bottom_b)
        {
            return 4;
        }
    }

    if (left_b >= left_a && left_b <= right_a)
    {
        if (top_b >= top_a && top_b <= bottom_a)
        {
            return 5;

        }
    }

    if (left_b >= left_a && left_b <= right_a)
    {
        if (bottom_b >= top_a && bottom_b <= bottom_a)
        {
            return 6;
        }
    }

    if (right_b >= left_a && right_b <= right_a)
    {
        if (top_b >= top_a && top_b <= bottom_a)
        {
            return 7;
        }
    }

    if (right_b >= left_a && right_b <= right_a)
    {
        if (bottom_b >= top_a && bottom_b <= bottom_a)
        {
            return 8;
        }
    }

    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return 9;
    }

    return 0;
}



bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

