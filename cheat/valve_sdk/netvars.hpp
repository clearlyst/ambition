#pragma once
#include <map>
#include <fstream>
#include <utility>
#include <memory>
#include <iostream>
#include <unordered_map>

#include "sdk.hpp"
#include "Misc/Recv.hpp"
#include "../helpers/fnv.hpp"
#include "../helpers/singleton.hpp"

class netvarsystem : public singleton<netvarsystem>
{
public:
    uintptr_t get_net_var(uint32_t table, uint32_t prop);
};

#define NETVAR( table, prop, func_name, type ) type& func_name() { \
    static uintptr_t offset = 0; \
    if( !offset ) { \
        offset = netvarsystem::get().get_net_var( fnv::hash( table ), fnv::hash( prop ) ); \
    } \
    return *reinterpret_cast< type* >( uintptr_t( this ) + offset ); \
}

#define NETVAR_PTR( table, prop, func_name, type ) type* func_name() { \
    static uintptr_t offset = 0; \
    if( !offset ) { \
        offset = netvarsystem::get().get_net_var( fnv::hash( table ), fnv::hash( prop ) ); \
    } \
    return reinterpret_cast< type* >( uintptr_t( this ) + offset ); \
}

#define OFFSET( type, var, offset ) type& var() { \
    return *( type* )( uintptr_t( this ) + offset ); \
}
