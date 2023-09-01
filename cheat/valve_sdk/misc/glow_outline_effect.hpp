#pragma once

#include "UtlVector.hpp"
#include "../Interfaces/IClientEntity.hpp"

class glow_object_definition_t
{
public:
    bool unused()
    {
        return next_free_slot != -2;
    }

    int next_free_slot;
    player_t* entity;
    union
    {
        Vector glow_color;

        struct
        {
            float   red;          
            float   green;        
            float   blue;         
        };
    };
    float alpha;
    char unknown0[8];
    float bloom_amount;
    char unknown1[4];
    bool render_when_occluded;
    bool render_when_unoccluded;
    bool full_bloom_render;
    char unknown2[5];
    int glow_style;
    int splitscreen_slot;
};

class glow_manager_t
{
public:
    glow_object_definition_t* objects;
    char pad[8];
    int size;
};