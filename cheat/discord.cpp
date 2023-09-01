#include "discord.hpp"

void discordrpc::initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize(xorstr(""), &Handle, 1, NULL); // lazy to change its fmb key lmfao

    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = xorstr("weiamware");
    discordPresence.largeImageKey = xorstr("weiamware");
    Discord_UpdatePresence(&discordPresence);
}

void discordrpc::release()
{
    Discord_Shutdown();
}
