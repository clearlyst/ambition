#include "glow.hpp"

void glow::run()
{
    if (!variables::config::esp::enable)
    {
        return;
    }

    if (!Utils::bind(variables::config::esp::key, variables::config::esp::key_type))
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player)
    {
        return;
    }

    for (auto i = 0; i < g_GlowObjManager->size; i++) 
    {
        if (g_GlowObjManager->objects[i].unused() || !g_GlowObjManager->objects[i].entity || g_GlowObjManager->objects[i].entity->IsDormant())
        {
            continue;
        }

        if (g_GlowObjManager->objects[i].entity->team() == csgo::local_player->team() && !variables::config::esp::teammates)
        {
            continue;
        }

        auto glow = &g_GlowObjManager->objects[i];
        auto class_id = glow->entity->GetClientClass()->m_ClassID;

        if (class_id == C_CS_PLAYER)
        {
            bool is_visible = csgo::local_player->can_see_player_pos(glow->entity, glow->entity->get_eye_pos());

            if (variables::config::glow::occluded && !is_visible)
            {
                glow->red = variables::config::glow::occluded_clr[0] / 255.0f;
                glow->green = variables::config::glow::occluded_clr[1] / 255.0f;
                glow->blue = variables::config::glow::occluded_clr[2] / 255.0f;
                glow->alpha = variables::config::glow::occluded_clr[3] / 255.0f;
            }
           
            if (variables::config::glow::visible && is_visible)
            {
                glow->red = variables::config::glow::visible_clr[0] / 255.0f;
                glow->green = variables::config::glow::visible_clr[1] / 255.0f;
                glow->blue = variables::config::glow::visible_clr[2] / 255.0f;
                glow->alpha = variables::config::glow::visible_clr[3] / 255.0f;

                glow->glow_style = variables::config::glow::visible_style;
            }
        }

        if (variables::config::glow::visible || variables::config::glow::occluded)
        {
            glow->render_when_occluded = true;
            glow->render_when_unoccluded = false;
        }
    }
}