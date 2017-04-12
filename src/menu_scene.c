#include "menu_scene.h"
#include "game_scene.h"
#include "sprite.h"

void menu_option_init(menu_option_t * opt, const char * text, void (*selected)(menu_scene_t *), vec2_t pos)
{
    assert(NULL != opt);

    opt->parent = NULL;

    if (NULL != text)
    {
        sprite_text_init(&opt->sprite, g_fnt_large, text);
        sprite_text_set_pos(&opt->sprite, pos);
    }

    opt->num_options = 0;
    opt->selected = selected;
    opt->options = NULL;
}

void menu_option_cleanup(menu_option_t * opt)
{
    sprite_text_cleanup(&opt->sprite);

    for (int i = 0; i < opt->num_options; ++i)
    {
        menu_option_cleanup(&opt->options[i]);
    }
    free(opt->options);
}

menu_option_t * menu_option_add_sub_option(menu_option_t * opt, const char * text, void (*selected)(menu_scene_t *), vec2_t pos)
{
    assert(NULL != opt);

    ++opt->num_options;
    opt->options = (menu_option_t *)realloc(opt->options, sizeof(menu_option_t) * opt->num_options);
    menu_option_init(&opt->options[opt->num_options - 1], text, selected, pos);
    opt->options[opt->num_options - 1].parent = opt;

    return &opt->options[opt->num_options - 1];
}

void option_quit_cb(menu_scene_t * scn)
{
    g_running = false;
}

void option_local_game_cb(menu_scene_t * scn)
{
    scn->game_scene = (game_scene_t *)malloc(sizeof(game_scene_t));
    game_scene_init_local(scn->game_scene, 2);

    scene_push((scene_t *)scn->game_scene);
}

void option_host_two_game_cb(menu_scene_t * scn)
{
    scn->game_scene = (game_scene_t *)malloc(sizeof(game_scene_t));
    game_scene_init_host(scn->game_scene, 2);

    scene_push((scene_t *)scn->game_scene);
}

void option_host_four_game_cb(menu_scene_t * scn)
{
    scn->game_scene = (game_scene_t *)malloc(sizeof(game_scene_t));
    game_scene_init_host(scn->game_scene, 4);

    scene_push((scene_t *)scn->game_scene);
}

void option_connect_game_cb(menu_scene_t * scn)
{
    scn->game_scene = (game_scene_t *)malloc(sizeof(game_scene_t));
    game_scene_init_connect(scn->game_scene, "127.0.0.1");

    scene_push((scene_t *)scn->game_scene);
}

void menu_scene_init(menu_scene_t * scn)
{
    assert(NULL != scn);

    scene_t * base = (scene_t *)scn;
    scene_init(base);

    base->start = &menu_scene_start_cb;
    base->stop = &menu_scene_stop_cb;
    base->cleanup = &menu_scene_cleanup_cb;
    base->update = &menu_scene_update_cb;
    base->render = &menu_scene_render_cb;

    scn->game_scene = NULL;

    vec2_t title_pos = { 50, 50 };
    sprite_init(&scn->title, TITLE_ASSET_PATH);
    sprite_set_pos(&scn->title, title_pos);

    vec2_t arrow_size = { 20, 20 };
    sprite_init(&scn->arrow, PIXEL_ASSET_PATH);
    sprite_set_size(&scn->arrow, arrow_size);

    menu_option_t * menu_ptr;
    vec2_t root_mpos = { 50, 150 };
    menu_option_init(&scn->root_option_group, NULL, NULL, root_mpos);

    menu_ptr = menu_option_add_sub_option(&scn->root_option_group, "Local Game", &option_local_game_cb, root_mpos);
    root_mpos.y += MENU_OPTION_HEIGHT;

    menu_ptr = menu_option_add_sub_option(&scn->root_option_group, "Host Game", NULL, root_mpos);
    root_mpos.y += MENU_OPTION_HEIGHT;

    vec2_t host_mpos = { 50, 150 };
    menu_option_add_sub_option(menu_ptr, "Two Player", &option_host_two_game_cb, host_mpos);
    host_mpos.y += MENU_OPTION_HEIGHT;
    menu_option_add_sub_option(menu_ptr, "Four Player", &option_host_four_game_cb, host_mpos);

    menu_ptr = menu_option_add_sub_option(&scn->root_option_group, "Connect to Game", NULL, root_mpos);
    root_mpos.y += MENU_OPTION_HEIGHT;

    menu_ptr = menu_option_add_sub_option(&scn->root_option_group, "Quit", &option_quit_cb, root_mpos);
    root_mpos.y += MENU_OPTION_HEIGHT;
}

void menu_scene_cleanup_cb(scene_t * scn)
{
    menu_scene_t * mscn = (menu_scene_t *)scn;

    menu_option_cleanup(&mscn->root_option_group);

    sprite_cleanup(&mscn->title);
    sprite_cleanup(&mscn->arrow);
}

void menu_scene_start_cb(scene_t * scn)
{
    menu_scene_t * mscn = (menu_scene_t *)scn;

    mscn->menu_ind = 0;
    mscn->input_wait = false;
    mscn->cur_option_group = &mscn->root_option_group;

    if (NULL != mscn->game_scene)
    {
        mscn->game_scene->base.cleanup((scene_t *)mscn->game_scene);
        free(mscn->game_scene);
    }
}

void menu_scene_stop_cb(scene_t * scn)
{

}

void menu_scene_update_cb(scene_t * scn, SDL_Event * ev, float delta)
{
    menu_scene_t * mscn = (menu_scene_t *)scn;

    if (NULL == mscn->cur_option_group)
    {
        return;
    }

    vec2_t arrow_pos = { 20, 170 };
    arrow_pos.y += (mscn->menu_ind * MENU_OPTION_HEIGHT);
    sprite_set_pos(&mscn->arrow, arrow_pos);

    if (SDL_KEYDOWN == ev->type)
    {
        if (SDLK_UP == ev->key.keysym.sym)
        {
            if (!mscn->input_wait)
            {
                mscn->input_wait = true;
                --mscn->menu_ind;
                if (0 > mscn->menu_ind)
                {
                    mscn->menu_ind = mscn->cur_option_group->num_options - 1;
                }
            }
        }
        else if (SDLK_DOWN == ev->key.keysym.sym)
        {
            if (!mscn->input_wait)
            {
                mscn->input_wait = true;
                ++mscn->menu_ind;
                if (mscn->menu_ind >= mscn->cur_option_group->num_options)
                {
                    mscn->menu_ind = 0;
                }
            }
        }
        else if (SDLK_RETURN == ev->key.keysym.sym)
        {
            if (!mscn->input_wait)
            {
                mscn->input_wait = true;
                menu_option_t * opt = &mscn->cur_option_group->options[mscn->menu_ind];
                if (NULL != opt->selected)
                {
                    opt->selected(mscn);
                }
                else
                {
                    mscn->menu_ind = 0;
                    mscn->cur_option_group = opt;
                }
            }
        }
        else if (SDLK_ESCAPE == ev->key.keysym.sym)
        {
            if (!mscn->input_wait)
            {
                mscn->input_wait = true;
                if (NULL != mscn->cur_option_group->parent)
                {
                    mscn->menu_ind = 0;
                    mscn->cur_option_group = mscn->cur_option_group->parent;
                }
            }
        }
    }
    else if (SDL_KEYUP == ev->type)
    {
        mscn->input_wait = false;
    }
}

void menu_scene_render_cb(scene_t * scn)
{
    menu_scene_t * mscn = (menu_scene_t *)scn;

    sprite_render(&mscn->title);
    sprite_render(&mscn->arrow);

    if (mscn->cur_option_group)
    {
        for (int i = 0; i < mscn->cur_option_group->num_options; ++i)
        {
            sprite_text_render(&mscn->cur_option_group->options[i].sprite);
        }
    }
}

