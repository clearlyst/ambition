#pragma once
#include <string>
#include "valve_sdk/misc/Color.hpp"

namespace variables
{
	namespace hack
	{
		inline bool unload = false;
	}

	namespace config
	{
		namespace movement
		{
			inline bool bunnyhop = false;
			inline bool edgejump = false;
			inline bool edgejump_blockbuttons = false;
			inline int edgejump_key = 0;
			inline int edgejump_key_type = 2;
			inline bool minijump = false;
			inline bool minijump_blockbuttons = false;
			inline bool minijump_forceedgejump = false;
			inline int minijump_key = 0;
			inline int minijump_key_type = 2;
			inline bool longjump = false;
			inline bool longjump_blockbuttons = false;
			inline bool longjump_forceedgejump = false;
			inline int longjump_key = 0;
			inline int longjump_key_type = 2;
			inline bool jumpbug = false;
			inline int jumpbug_key = 0;
			inline int jumpbug_key_type = 2;
			inline bool blockbutton_forward = false;
			inline bool blockbutton_back = false;
			inline bool blockbutton_left = false;
			inline bool blockbutton_right = false;
			inline bool infinityduck = false;
			inline bool autoduck = false;
			inline int autoduck_key = 0;
			inline int autoduck_key_type = 2;
			inline float autoduck_time = 0.4f;
			inline bool edgebug = false;
			inline bool edgebug_strafetoedge = false;
			inline int edgebug_ticks = 64;
			inline float edgebug_lock = 10.0f;
			inline int edgebug_key = 0;
			inline int edgebug_key_type = 2;
			inline bool autoalign = false;
			inline int autoalign_key = 0;
			inline int autoalign_key_type = 1;
			inline bool pixelsurf = false;
			inline int pixelsurf_key = 0;
			inline int pixelsurf_key_type = 1;
			inline bool msl = false;
			inline int msl_key = 0;
			inline int msl_key_type = 1;
			inline float msl_strength_x = 20.0f;
			inline float msl_strength_y = 20.0f;
			inline bool staminahop = false;
			inline int staminahop_key = 0;
			inline int staminahop_key_type = 1;
			inline int staminahop_ticks = 2;
			inline bool blockbot = false;
			inline int blockbot_key = 0;
			inline int blockbot_key_type = 2;
			inline bool ladderedgejump = false;
			inline bool ladderedgejump_blockbuttons = false;
			inline int ladderedgejump_key = 0;
			inline int ladderedgejump_key_type = 2;
			inline bool jumpstats = false;
		}

		namespace indicators
		{
			inline bool velocity = true;
			inline int velocity_style = 0;
			inline float velocity_rainbow_hue = 360.0f;
			inline float velocity_rainbow_saturation = 0.50f;
			inline float velocity_fade_strength = 280.0f;
			inline bool stamina = false;
			inline int stamina_style = 0;
			inline float stamina_rainbow_hue = 36.0f;
			inline float stamina_rainbow_saturation = 0.50f;
			inline float stamina_fade_strength = 35.0f;
			inline bool velocity_takeoff_on_ground = true;
			inline bool stamina_takeoff_on_ground = false;
			inline int velocity_from_clr[4]{ 255, 255, 255, 0 };
			inline int velocity_to_clr[4]{ 23, 238, 103, 255 };
			inline int stamina_from_clr[4]{ 255, 255, 255, 0 };
			inline int stamina_to_clr[4]{ 23, 238, 103, 255 };
			inline int velocity_positive_clr[3]{ 23, 238, 103 };
			inline int velocity_neutral_clr[3]{ 255, 200, 100 };
			inline int velocity_negative_clr[3]{ 225, 100, 100 };
			inline bool velocitygraph = false;
			inline bool staminagraph = false;
			inline int indicator_position = 100;
			inline float graph_scale = 1.0f;
			inline bool indicators = false;
			inline bool edgejump = true;
			inline int edgejump_detection_color[3]{ 174, 232, 153 };
			inline bool minijump = true;
			inline int minijump_detection_color[3]{ 174, 232, 153 };
			inline bool longjump = true;
			inline int longjump_detection_color[3]{ 174, 232, 153 };
			inline bool jumpbug = true;
			inline int jumpbug_detection_color[3]{ 191, 153, 232 };
			inline bool edgebug = true;
			inline int edgebug_detection_color[3]{ 232, 206, 153 };
			inline bool autoduck = true;
			inline int autoduck_detection_color[3]{ 232, 206, 153 };
			inline bool staminahop = true;
			inline int staminahop_detection_color[3]{ 232, 206, 153 };
			inline bool pixelsurf = true;
			inline int pixelsurf_detection_color[3]{ 232, 206, 153 };
			inline bool autoalign = true;
			inline int autoalign_detection_color[3]{ 232, 206, 153 };
			inline bool msl = true;
			inline int msl_detection_color[3]{ 232, 206, 153 };
			inline float sameline = 2.0f;
			inline float speed = 1.25f;
		}

		namespace misc
		{
			inline int menukeybind = 0x2D;

			inline bool unlockinventory = false;
			inline bool snipercrosshair = false;
			inline bool forcecrosshair = false;
			inline bool recoilcrosshair = false;
			inline bool watermark = true;
			inline bool spotify = false;
			inline bool autoaccept = false;
			inline bool spectatorlist = false;
			inline bool spectatorlist_mode = false;
			inline bool changeviewmodeloffsets = false;
			inline float viewmodeloffset_x = 0.0f;
			inline float viewmodeloffset_y = 0.0f;
			inline float viewmodeloffset_z = 0.0f;
			inline bool changeviewmodelfov = false;
			inline float viewmodelfov = 68.0f;
			inline bool changeweaponswayscale = false;
			inline float weaponswayscale = 1.60f;
			inline bool rankreveal = false;
			inline bool usekeyspam = false;
			inline bool regionchanger = false;
			inline int regionchanger_type = 0;
			inline bool chatmessage_rainbow = false;
			inline int chatmessage_color = 0;
			inline unsigned char screenmessage_color[3]{ 255, 0, 0 };
		}

		namespace glow
		{
			inline bool visible = false;
			inline int visible_style = 0;
			inline bool occluded = false;
			inline color visible_clr = color(60, 0, 255, 180);
			inline color occluded_clr = color(60, 0, 255, 180);
		}

		namespace chams
		{
			inline bool visible = false;
			inline int visible_style = 0;
			inline bool occluded = false;
			inline int occluded_style = 0;
			inline bool visible_overlay = false;
			inline bool visible_wireframe_overlay = false;
			inline int visible_style_overlay = 0;
			inline bool occluded_overlay = false;
			inline bool occluded_wireframe_overlay = false;
			inline int occluded_style_overlay = 0;
			inline color visible_clr = color(255, 0, 0, 255);
			inline color occluded_clr = color(255, 0, 0, 255);
			inline color visible_clr_overlay = color(255, 255, 255, 255);
			inline color occluded_clr_overlay = color(255, 255, 255, 255);
		}

		namespace esp
		{
			inline bool enable = false;
			inline int key = 0;
			inline int key_type = 1;
			inline bool teammates = false;
			inline bool fadeinout = false;
			inline float fadeinout_time = 1.0f;
			inline bool engine_radar = false;
			inline bool box = false;
			inline bool box_rect = true;
			inline bool box_corner = false;
			inline bool box_outline = false;
			inline bool box_inline = false;
			inline bool name = false;
			inline bool weapon = false;
			inline bool weapon_icon = false;
			inline bool flags = false;
			inline bool scoped = false;
			inline bool armour = false;
			inline bool flashed = false;
			inline bool balance = false;
			inline bool reloading = false;
			inline bool rescuing = false;
			inline bool defusing = false;
			inline bool health = false;
			inline bool health_hide_suffix = false;
			inline bool health_hide_at_max = false;
			inline bool health_rgb = false;
			inline bool health_bar = false;
			inline bool health_bar_background = false;
			inline bool health_bar_multicolor = false;
			inline int health_bar_size = 1;
			inline bool ammo_bar = false;
			inline bool ammo_bar_background = false;
			inline int ammo_bar_size = 1;
			inline bool ammo = false;
			inline bool skeleton = false;
			inline float skeleton_thickness = 0.5f;
			inline bool viewangle = false;
			inline float viewangle_thickness = 0.5f;
			inline float viewangle_distance = 50.0f;
			inline bool headbox = false;
			inline bool headbox_filled = false;
			inline bool dlight = false;
			inline float dlight_radius = 50.0f;
			inline bool outofview = false;
			inline bool outofview_occluded = false;
			inline float outofview_size = 7.5f;
			inline float outofview_distance = 30.0f;
			inline bool distance = false;
			inline bool snapline = false;
			inline bool snapline_occluded = false;
			inline bool snapline_bottom = true;
			inline bool snapline_center = false;
			inline bool snapline_upper = false;
			inline float snapline_thickness = 0.5f;
			inline bool throwngrenade = false;
			inline bool throwngrenade_icon = false;
			inline bool droppedweapon = false;
			inline bool droppedweapon_icon = false;
			inline bool droppedweapon_ammo = false;
			inline color visible_clr = color(255, 255, 255, 255);
			inline color occluded_clr = color(255, 255, 255, 255);
		}

		namespace aimbot
		{
			inline bool enable = false;
			inline bool shootataimkey = false;
			inline int key = 0;
			inline int key_type = 2;

			struct aimbot_value_t
			{
				bool override_general = false;
				bool backtrack = false;
				bool aimatbacktrack = false;
				bool teammates = false;
				bool flashcheck = false;
				bool smokecheck = false;
				bool selfinair = false;
				bool enemyinair = false;
				int priority = 0;
				float shotdelay = 0.0f;
				float killdelay = 0.0f;
				float fov = 180.f;
				float smooth = 0.0f;
				bool head = true;
				bool neck = false;
				bool chest = false;
				bool stomach = false;
				bool pelvis = false;
				bool foot = false;
				bool silent = false;
				bool autopistol = false;
				bool autowall = false;
				int mindamage = 0;
				bool compensaterecoil = false;

				aimbot_value_t() = default;
			};

			inline aimbot_value_t general = aimbot_value_t();
			inline aimbot_value_t pistols = aimbot_value_t();
			inline aimbot_value_t heavy_pistols = aimbot_value_t();
			inline aimbot_value_t smg = aimbot_value_t();
			inline aimbot_value_t shotguns = aimbot_value_t();
			inline aimbot_value_t rifles = aimbot_value_t();
			inline aimbot_value_t snipers = aimbot_value_t();
		}

		namespace triggerbot
		{
			inline bool enable = false;
			inline int key = 0;
			inline int key_type = 2;

			struct triggerbot_value_t
			{
				bool override_general = false;
				bool teammates = false;
				bool flashcheck = false;
				bool smokecheck = false;
				bool selfinair = false;
				bool enemyinair = false;
				float shotdelay = 0.0f;
				float killdelay = 0.0f;
				bool head = true;
				bool neck = false;
				bool chest = false;
				bool stomach = false;
				bool foot = false;
				bool autopistol = false;

				triggerbot_value_t() = default;
			};

			inline triggerbot_value_t general = triggerbot_value_t();
			inline triggerbot_value_t pistols = triggerbot_value_t();
			inline triggerbot_value_t heavy_pistols = triggerbot_value_t();
			inline triggerbot_value_t smg = triggerbot_value_t();
			inline triggerbot_value_t shotguns = triggerbot_value_t();
			inline triggerbot_value_t rifles = triggerbot_value_t();
			inline triggerbot_value_t snipers = triggerbot_value_t();
		}
	}
}