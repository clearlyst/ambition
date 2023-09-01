#pragma once

#include <array>

#include "sdk.hpp"
#include "../helpers/math.hpp"
#include "../helpers/utils.hpp"

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

class anim_state
{
public:
	char u0[0x18];
	float anim_update_timer;
	char u1[0xC];
	float started_moving_time;
	float last_move_time;
	char u2[0x10];
	float last_lby_time;
	char u3[0x8];
	float run_amount;
	char u4[0x10];
	void* entity;
	__int32 active_weapon;
	__int32 last_active_weapon;
	float last_clientside_anim_update_time;
	__int32 last_clientside_anim_update_framecount;
	float eye_timer;
	float eye_angles_y;
	float eye_angles_x;
	float goal_feet_yaw;
	float current_feet_yaw;
	float torso_yaw;
	float last_move_yaw;
	float lean_amount;
	char u5[0x4];
	float feet_cycle;
	float feet_yaw_rate;
	char u6[0x4];
	float duck_amount;
	float landing_duck_amount;
	char u7[0x4];
	Vector current_origin;
	Vector last_origin;
	float velocity_x;
	float velocity_y;
	char u8[0x10];
	float move_direction_1;
	float move_direction_2;
	char u9[0x4];
	float velocity;
	float jump_fall_velocity;
	float clamped_velocity;
	float feet_speed_forwards_or_sideways;
	float feet_speed_unknown_forwards_or_sideways;
	float last_time_started_moving;
	float last_time_stopped_moving;
	bool on_ground;
	bool hit_in_ground_anim;
	char u10[0x4];
	float last_origin_z;
	float head_from_ground_distance_standing;
	float stop_to_full_running_fraction;
	char u11[0x14];
	__int32 is_not_moving;
	char u12[0x20];
	float last_anim_update_time;
	float moving_direction_x;
	float moving_direction_y;
	float moving_direction_z;
	char u13[0x44];
	__int32 started_moving;
	char u14[0x8];
	float lean_yaw;
	char u15[0x8];
	float poses_speed;
	char u16[0x8];
	float ladder_speed;
	char u17[0x8];
	float ladder_yaw;
	char u18[0x8];
	float some_pose;
	char u19[0x14];
	float body_yaw;
	char u20[0x8];
	float body_pitch;
	char u21[0x8];
	float death_yaw;
	char u22[0x8];
	float stand;
	char u23[0x8];
	float jump_fall;
	char u24[0x8];
	float aim_blend_stand_idle;
	char u25[0x8];
	float aim_blend_crouch_idle;
	char u26[0x8];
	float strafe_yaw;
	char u27[0x8];
	float aim_blend_stand_walk;
	char u28[0x8];
	float aim_blend_stand_run;
	char u29[0x8];
	float aim_blend_crouch_walk;
	char u30[0x8];
	float move_blend_walk;
	char u31[0x8];
	float move_blend_run;
	char u32[0x8];
	float move_blend_crouch;
	char u33[0x4];
	float speed;
	__int32 moving_in_any_direction;
	float acceleration;
	char u34[0x74];
	float crouch_height;
	__int32 is_full_crouched;
	char u35[0x4];
	float velocity_subtract_x;
	float velocity_subtract_y;
	float velocity_subtract_z;
	float standing_head_height;
};

class entity_t : public IClientEntity
{
public:
	static __forceinline entity_t* GetEntityByIndex(int index)
	{
		return static_cast<entity_t*>(g_EntityList->GetClientEntity(index));
	}

	static __forceinline entity_t* get_entity_from_handle(CBaseHandle h)
	{
		return static_cast<entity_t*>(g_EntityList->GetClientEntityFromHandle(h));
	}

	bool is_player() 
	{
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn**)this)[158](this);
	}

	bool is_weapon()
	{
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn**)this)[166](this);
	}

	void update() 
	{
		using original_fn = void(__thiscall*)(entity_t*);
		(*(original_fn**)this)[218](this);
	}

	void set_angles(Vector angles)
	{
		using original_fn = void(__thiscall*)(void*, const Vector&);
		static original_fn set_angles_fn = (original_fn)((DWORD)Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1")));
		set_angles_fn(this, angles);
	}

	void set_position(Vector position) 
	{
		using original_fn = void(__thiscall*)(void*, const Vector&);
		static original_fn set_position_fn = (original_fn)((DWORD)Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8")));
		set_position_fn(this, position);
	}

	void set_model_index(int index)
	{
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)this)[75](this, index);
	}

	NETVAR("DT_CSPlayer", "m_fFlags", flags, int)
	NETVAR("DT_BaseEntity", "m_hOwnerEntity", owner_handle, unsigned long)
	NETVAR("DT_CSPlayer", "m_flSimulationTime", simulation_time, float)
	NETVAR("DT_BasePlayer", "m_vecOrigin", origin, Vector)
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", view_offset, Vector)
	NETVAR("DT_CSPlayer", "m_iTeamNum", team, int)
	NETVAR("DT_BaseEntity", "m_bSpotted", spotted, bool)
	NETVAR("DT_CSPlayer", "m_nSurvivalTeam", survival_team, int)
	NETVAR("DT_CSPlayer", "m_flHealthShotBoostExpirationTime", health_boost_time, float)

	const matrix3x4_t& coordinate_frame()
	{
		static auto _coordinate_frame = netvarsystem::get().get_net_var(fnv::hash("DT_BaseEntity"), fnv::hash("m_CollisionGroup")) - 0x30;
		return *(matrix3x4_t*)((uintptr_t)this + _coordinate_frame);
	}

	void invalidate_bone_cache()
	{
		static DWORD addr = (DWORD)Utils::PatternScan(GetModuleHandleA("client.dll"), "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");

		*(int*)((uintptr_t)this + 0xA30) = g_GlobalVars->framecount; //we'll skip occlusion checks now
		*(int*)((uintptr_t)this + 0xA28) = 0;//clear occlusion flags

		unsigned long g_iModelBoneCounter = **(unsigned long**)(addr + 10);
		*(float*)((DWORD)this + 0x2928) = -FLT_MAX;
		*(int*)((DWORD)this + 0x2690) = g_iModelBoneCounter - 1;
	}
};

class econ_view_item_t 
{
public:
	NETVAR("DT_ScriptCreatedItem", "m_bInitialized", is_initialized, bool)
	NETVAR("DT_ScriptCreatedItem", "m_iEntityLevel", entity_level, int)
	NETVAR("DT_ScriptCreatedItem", "m_iAccountID", account_id, int)
	NETVAR("DT_ScriptCreatedItem", "m_iItemIDLow", item_id_low, int)
};

class base_view_model_t : public entity_t
{
public:
	NETVAR("DT_BaseViewModel", "m_nModelIndex", model_index, int)
	NETVAR("DT_BaseViewModel", "m_nViewModelIndex", view_model_index, int)
	NETVAR("DT_BaseViewModel", "m_hWeapon", weapon, int)
	NETVAR("DT_BaseViewModel", "m_hOwner", owner, int)
};

class attributable_item_t : public entity_t 
{
private:
	using str_32 = char[32];
public:
	NETVAR("DT_BaseViewModel", "m_nModelIndex", model_index, int);
	NETVAR("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow", original_owner_xuid_low, int);
	NETVAR("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh", original_owner_xuid_high, int);
	NETVAR("DT_BaseAttributableItem", "m_nFallbackStatTrak", fallback_stattrak, int);
	NETVAR("DT_BaseAttributableItem", "m_nFallbackPaintKit", fallback_paint_kit, int);
	NETVAR("DT_BaseAttributableItem", "m_nFallbackSeed", fallback_seed, int);
	NETVAR("DT_BaseAttributableItem", "m_iEntityQuality", entity_quality, int);
	NETVAR("DT_BaseAttributableItem", "m_flFallbackWear", fallback_wear, float);
	NETVAR("DT_BaseCombatWeapon", "m_hWeaponWorldModel", world_model_handle, unsigned long);
	NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short);
	NETVAR("DT_BaseAttributableItem", "m_iItemIDHigh", item_id_high, int);
	NETVAR("DT_BaseAttributableItem", "m_iAccountID", account_id, int);
	NETVAR("DT_BaseAttributableItem", "m_szCustomName", get_custom_name, str_32);
};

enum e_weapon_type 
{
	WEAPON_TYPE_INVALID,
	WEAPON_TYPE_KNIFE,
	WEAPON_TYPE_PISTOL,
	WEAPON_TYPE_HEAVYPISTOL,
	WEAPON_TYPE_TASER,
	WEAPON_TYPE_SHOTGUN,
	WEAPON_TYPE_SMG,
	WEAPON_TYPE_RIFLE,
	WEAPON_TYPE_MG,
	WEAPON_TYPE_SNIPER,
	WEAPON_TYPE_GRENADE,
};

class weapon_t : public entity_t
{
public:
	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", next_primary_attack, float)
	NETVAR("DT_BaseCombatWeapon", "m_flNextSecondaryAttack", next_secondary_attack, float)
	NETVAR("DT_BaseCombatWeapon", "m_iClip1", clip1_count, int)
	NETVAR("DT_BaseCombatWeapon", "m_iClip2", clip2_count, int)
	NETVAR("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount", primary_reserve_ammo_acount, int)
	NETVAR("DT_WeaponCSBase", "m_flRecoilIndex", recoil_index, float)
	NETVAR("DT_WeaponCSBaseGun", "m_zoomLevel", zoom_level, float)
	NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short)
	NETVAR("DT_BaseCombatWeapon", "m_iEntityQuality", entity_quality, int)

	bool isgun()
	{
		switch (get_weapon_data()->m_iWeaponType)
		{
		case WEAPONTYPE_C4:
			return false;
		case WEAPONTYPE_GRENADE:
			return false;
		case WEAPONTYPE_KNIFE:
			return false;
		case WEAPON_TASER:
			return false;
		case WEAPONTYPE_UNKNOWN:
			return false;
		default:
			return true;
		}

		switch (GetClientClass()->m_ClassID)
		{
		case C_PHYS_PROP_AMMO_BOX:
			return false;
		case C_PHYS_PROP_LOOT_CRATE:
			return false;
		case C_PHYS_PROP_RADAR_JAMMER:
			return false;
		case C_PHYS_PROP_WEAPON_UPGRADE:
			return false;
		case C_DRONE:
			return false;
		case C_DRONE_GUN:
			return false;
		case C_ITEM_HEALTHSHOT:
			return false;
		case C_ITEM_CASH:
			return false;
		case C_BUMP_MINE:
			return false;
		default:
			return true;
		}
	}

	bool issniper()
	{
		switch (get_weapon_data()->m_iWeaponType)
		{
		case WEAPONTYPE_SNIPER_RIFLE:
			return true;
		default:
			return false;
		}
	}

	float inaccuracy()
	{
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[483](this);
	}

	float get_spread()
	{
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[453](this);
	}

	void update_accuracy_penalty()
	{
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[484](this);
	}

	CCSWeaponInfo* get_weapon_data()
	{
		using original_fn = CCSWeaponInfo*(__thiscall*)(void*);
		return (*(original_fn**)this)[461](this);
	}

	bool m_bInReload()
	{
		return *(bool*)(reinterpret_cast<DWORD>(this) + 0x32B5);
	}

	std::string weapon_name()
	{
		if (!this)
		{
			return ("");
		}

		int id = this->item_definition_index();

		switch (id) 
		{
		case WEAPON_DEAGLE:
			return xorstr("deagle");
		case WEAPON_AUG:
			return xorstr("aug");
		case WEAPON_G3SG1:
			return xorstr("g3sg1");
		case WEAPON_MAC10:
			return xorstr("mac10");
		case WEAPON_P90:
			return xorstr("p90");
		case WEAPON_SSG08:
			return xorstr("ssg08");
		case WEAPON_SCAR20:
			return xorstr("scar20");
		case WEAPON_UMP45:
			return xorstr("ump45");
		case WEAPON_ELITE:
			return xorstr("elite");
		case WEAPON_FAMAS:
			return xorstr("famas");
		case WEAPON_FIVESEVEN:
			return xorstr("fiveseven");
		case WEAPON_GALILAR:
			return xorstr("galil");
		case WEAPON_M4A1_SILENCER:
			return xorstr("m4a1");
		case WEAPON_M4A1:
			return xorstr("m4a4");
		case WEAPON_P250:
			return xorstr("p250");
		case WEAPON_M249:
			return xorstr("m249");
		case WEAPON_XM1014:
			return xorstr("xm1014");
		case WEAPON_GLOCK:
			return xorstr("glock");
		case WEAPON_USP_SILENCER:
			return xorstr("usp");
		case WEAPON_HKP2000:
			return xorstr("p2000");
		case WEAPON_AK47:
			return xorstr("ak-47");
		case WEAPON_AWP:
			return xorstr("awp");
		case WEAPON_BIZON:
			return xorstr("bizon");
		case WEAPON_MAG7:
			return xorstr("mag7");
		case WEAPON_NEGEV:
			return xorstr("neger");
		case WEAPON_SAWEDOFF:
			return xorstr("sawedoff");
		case WEAPON_TEC9:
			return xorstr("tec-9");
		case WEAPON_TASER:
			return xorstr("zeus");
		case WEAPON_NOVA:
			return xorstr("nova");
		case WEAPON_CZ75A:
			return xorstr("cz-75");
		case WEAPON_SG556:
			return xorstr("sg553");
		case WEAPON_REVOLVER:
			return xorstr("revolver");
		case WEAPON_MP7:
			return xorstr("mp-7");
		case WEAPON_MP9:
			return xorstr("mp-9");
		case WEAPON_MP5:  
			return xorstr("mp-5");
		case WEAPON_C4:
			return xorstr("plant");
		case WEAPON_FRAG_GRENADE:
			return xorstr("hegrenade");
		case WEAPON_SMOKEGRENADE:
			return xorstr("smoke");
		case WEAPON_MOLOTOV:
			return xorstr("molotov");
		case WEAPON_INCGRENADE:
			return xorstr("incendiary");
		case WEAPON_FLASHBANG:
			return xorstr("flashbang");
		case WEAPON_DECOY:
			return xorstr("decoy");
		default:
			return xorstr("knife");
		}
		return xorstr("");
	}

	std::string weapon_icons()
	{
		if (!this)
		{
			return ("");
		}

		int id = this->item_definition_index();

		switch (id)
		{
	    /*
		case WEAPON_DEAGLE:
			return "A";
		case WEAPON_ELITE:
			return "B";
		case WEAPON_FIVESEVEN:
			return "C";
		case WEAPON_GLOCK:
			return "D";
		case WEAPON_HKP2000:
			return "E";
		case WEAPON_P250:
			return "F";
		case WEAPON_USP_SILENCER:
			return "G";
		case WEAPON_TEC9:
			return "H";
		case WEAPON_CZ75A:
			return "I";
		case WEAPON_REVOLVER:
			return "J";
		case WEAPON_MAC10:
			return "K";
		case WEAPON_UMP45:
			return "L";
		case WEAPON_BIZON:
			return "M";
		case WEAPON_MP7:
			return "N";
		case WEAPON_MP9:
			return "O";
		case WEAPON_P90:
			return "P";
		case WEAPON_GALILAR:
			return "Q";
		case WEAPON_FAMAS:
			return "R";
		case WEAPON_M4A1_SILENCER:
			return "T";
		case WEAPON_M4A1:
			return "S";
		case WEAPON_AUG:
			return "U";
		case WEAPON_SG556:
			return "V";
		case WEAPON_AK47:
			return "W";
		case WEAPON_G3SG1:
			return "X";
		case WEAPON_SCAR20:
			return "Y";
		case WEAPON_AWP:
			return "Z";
		case WEAPON_SSG08:
			return "a";
		case WEAPON_XM1014:
			return "b";
		case WEAPON_SAWEDOFF:
			return "c";
		case WEAPON_MAG7:
			return "d";
		case WEAPON_NOVA:
			return "e";
		case WEAPON_NEGEV:
			return "f";
		case WEAPON_M249:
			return "g";
		case WEAPON_TASER:
			return "h";
		case WEAPON_FLASHBANG:
			return "k";
		case WEAPON_HEGRENADE:
			return "l";
		case WEAPON_SMOKEGRENADE:
			return "m";
		case WEAPON_MOLOTOV:
			return "n";
		case WEAPON_DECOY:
			return "o";
		case WEAPON_INCGRENADE:
			return "p";
		case WEAPON_C4:
			return "q";
		case WEAPON_KNIFE_T:
			return "i";
		case WEAPON_KNIFE:
			return "j";
		case WEAPON_KNIFE_FALCHION:
			return "0";
		case WEAPON_KNIFE_BAYONET:
			return "1";
		case WEAPON_KNIFE_FLIP:
			return "2";
		case WEAPON_KNIFE_GUT:
			return "3";
		case WEAPON_KNIFE_KARAMBIT:
			return "4";
		case WEAPON_KNIFE_M9_BAYONET:
			return "5";
		case WEAPON_KNIFE_TACTICAL:
			return "6";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "7";
		case WEAPON_KNIFE_BUTTERFLY:
			return "8";
		case WEAPON_KNIFE_URSUS:
			return "j";
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return "j";
		case WEAPON_KNIFE_STILETTO:
			return "j";
		case WEAPON_KNIFE_WIDOWMAKER:
			return "j";
		default:
			return xorstr("go fuck yourself");
	    */
		case WEAPON_KNIFE_BAYONET:
			return "1";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "7";
		case WEAPON_KNIFE_BUTTERFLY:
			return "8";
		case WEAPON_KNIFE:
			return "]";
		case WEAPON_KNIFE_FALCHION:
			return "0";
		case WEAPON_KNIFE_FLIP:
			return "2";
		case WEAPON_KNIFE_GUT:
			return "3";
		case WEAPON_KNIFE_KARAMBIT:
			return "4";
		case WEAPON_KNIFE_M9_BAYONET:
			return "5";
		case WEAPON_KNIFE_T:
			return "[";
		case WEAPON_KNIFE_TACTICAL:
			return "6";
		case WEAPON_KNIFE_PUSH:
			return "]";
		case WEAPON_DEAGLE:
			return "A";
		case WEAPON_ELITE:
			return "B";
		case WEAPON_FIVESEVEN:
			return "C";
		case WEAPON_GLOCK:
			return "D";
		case WEAPON_HKP2000:
			return "E";
		case WEAPON_P250:
			return "F";
		case WEAPON_USP_SILENCER:
			return "G";
		case WEAPON_TEC9:
			return "H";
		case WEAPON_REVOLVER:
			return "J";
		case WEAPON_MAC10:
			return "K";
		case WEAPON_UMP45:
			return "L";
		case WEAPON_BIZON:
			return "M";
		case WEAPON_MP7:
			return "N";
		case WEAPON_MP9:
			return "O";
		case WEAPON_P90:
			return "P";
		case WEAPON_GALILAR:
			return "Q";
		case WEAPON_FAMAS:
			return "R";
		case WEAPON_M4A1_SILENCER:
			return "T";
		case WEAPON_M4A1:
			return "S";
		case WEAPON_AUG:
			return "U";
		case WEAPON_SG556:
			return "V";
		case WEAPON_AK47:
			return "W";
		case WEAPON_G3SG1:
			return "X";
		case WEAPON_SCAR20:
			return "Y";
		case WEAPON_AWP:
			return "Z";
		case WEAPON_SSG08:
			return "a";
		case WEAPON_XM1014:
			return "b";
		case WEAPON_SAWEDOFF:
			return "c";
		case WEAPON_MAG7:
			return "d";
		case WEAPON_NOVA:
			return "e";
		case WEAPON_NEGEV:
			return "f";
		case WEAPON_M249:
			return "g";
		case WEAPON_TASER:
			return "h";
		case WEAPON_FLASHBANG:
			return "i";
		case WEAPON_HEGRENADE:
			return "j";
		case WEAPON_SMOKEGRENADE:
			return "k";
		case WEAPON_MOLOTOV:
			return "l";
		case WEAPON_DECOY:
			return "m";
		case WEAPON_INCGRENADE:
			return "n";
		case WEAPON_C4:
			return "o";
		case WEAPON_CZ75A:
			return "I";
		case WEAPON_KNIFE_URSUS:
			return "]";
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return "]";
		case WEAPON_KNIFE_STILETTO:
			return "]";
		case WEAPON_KNIFE_WIDOWMAKER:
			return "]";
		default:
			return "  ";
		}
		return xorstr("");
	}

	int get_weapon_type()
	{
		if (!this)
		{
			return -1;
		}

		if (!this->item_definition_index()) 
		{
			return -1;
		}

		switch (this->item_definition_index())
		{
		case WEAPON_DEAGLE:
			return WEAPON_TYPE_HEAVYPISTOL;
		case WEAPON_ELITE:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_FIVESEVEN:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_GLOCK:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_AK47:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_AUG:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_AWP:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_FAMAS:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_G3SG1:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_GALILAR:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_M249:
			return WEAPON_TYPE_MG;
		case WEAPON_M4A1:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_MAC10:
			return WEAPON_TYPE_SMG;
		case WEAPON_P90:
			return WEAPON_TYPE_SMG;
		case WEAPON_UMP45:
			return WEAPON_TYPE_SMG;
		case WEAPON_XM1014:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_BIZON:
			return WEAPON_TYPE_SMG;
		case WEAPON_MAG7:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_NEGEV:
			return WEAPON_TYPE_MG;
		case WEAPON_SAWEDOFF:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_TEC9:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_TASER:
			return WEAPON_TYPE_TASER;
		case WEAPON_HKP2000:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_MP7:
			return WEAPON_TYPE_SMG;
		case WEAPON_MP9:
			return WEAPON_TYPE_SMG;
		case WEAPON_NOVA:
			return WEAPON_TYPE_SHOTGUN;
		case WEAPON_P250:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_SCAR20:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_SG556:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_SSG08:
			return WEAPON_TYPE_SNIPER;
		case WEAPON_KNIFE:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_FLASHBANG:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_HEGRENADE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_SMOKEGRENADE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_MOLOTOV:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_DECOY:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_INCGRENADE:
			return WEAPON_TYPE_GRENADE;
		case WEAPON_C4:
			return WEAPON_TYPE_INVALID;
		case WEAPON_KNIFE_T:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_M4A1_SILENCER:
			return WEAPON_TYPE_RIFLE;
		case WEAPON_USP_SILENCER:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_CZ75A:
			return WEAPON_TYPE_PISTOL;
		case WEAPON_REVOLVER:
			return WEAPON_TYPE_HEAVYPISTOL;
		case WEAPON_KNIFE_BAYONET:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_CSS:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_FLIP:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_GUT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_KARAMBIT:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_M9_BAYONET:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_TACTICAL:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_FALCHION:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_BUTTERFLY:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_PUSH:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_CORD:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_CANIS:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_URSUS:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_OUTDOOR:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_STILETTO:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_WIDOWMAKER:
			return WEAPON_TYPE_KNIFE;
		case WEAPON_KNIFE_SKELETON:
			return WEAPON_TYPE_KNIFE;
		default:
			return WEAPON_TYPE_INVALID;
		}

		return false;
	}

};

class bomb_t : public entity_t 
{
public:
	NETVAR("DT_PlantedC4", "m_flC4Blow", bomb_timer, float)
	NETVAR("DT_PlantedC4", "m_nBombSite", bomb_site, int)
};

class fogcontroller_t : public entity_t 
{
public:
	NETVAR("DT_FogController", "m_fog.enable", enable, int)
	NETVAR("DT_FogController", "m_fog.start", start, float)
	NETVAR("DT_FogController", "m_fog.end", end, float)
	NETVAR("DT_FogController", "m_fog.maxdensity", density, float)
	NETVAR("DT_FogController", "m_fog.colorPrimary", color, int)
};

class maptonecontroller_t : public entity_t 
{
public:
	NETVAR("DT_EnvTonemapController", "m_flCustomBloomScale", scale, float)
};

class cascadelight_t : public entity_t
{
public:
	NETVAR("DT_CascadeLight", "m_shadowDirection", shadow, Vector)
	NETVAR("DT_CascadeLight", "m_envLightShadowDirection", light, Vector)
};

class player_t : public entity_t {
private:
	template <typename T>
	T& read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data)
	{
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

public:
	static __forceinline player_t* GetPlayerByUserId(int id)
	{
		return static_cast<player_t*>(GetEntityByIndex(g_EngineClient->GetPlayerForUserID(id)));
	}
	static __forceinline player_t* GetPlayerByIndex(int i)
	{
		return static_cast<player_t*>(GetEntityByIndex(i));
	}

	NETVAR("DT_BasePlayer", "m_hViewModel[0]", view_model, int)
	NETVAR("DT_CSPlayer", "m_bHasDefuser", has_defuser, bool)
	NETVAR("DT_CSPlayer", "m_bGunGameImmunity", has_gun_game_immunity, bool)
	NETVAR("DT_CSPlayer", "m_iShotsFired", shots_fired, int)
	NETVAR("DT_CSPlayer", "m_angEyeAngles", eye_angles, Vector)
	NETVAR("DT_CSPlayer", "m_ArmorValue", armor, int)
	NETVAR("DT_CSPlayer", "m_bHasHelmet", has_helmet, bool)
	NETVAR("DT_CSPlayer", "m_bIsScoped", is_scoped, bool)
	NETVAR("DT_CSPlayer", "m_bIsDefusing", is_defusing, bool)
	NETVAR("DT_CSPlayer", "m_bIsRescuing", is_rescuing, bool)
	NETVAR("DT_CSPlayer", "m_iAccount", money, int)
	NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget", lower_body_yaw, float)
	NETVAR("DT_CSPlayer", "m_flNextAttack", next_attack, float)
	NETVAR("DT_CSPlayer", "m_flFlashDuration", flash_duration, float)
	NETVAR("DT_CSPlayer", "m_flFlashMaxAlpha", flash_alpha, float)
	NETVAR("DT_CSPlayer", "m_bHasNightVision", has_night_vision, bool)
	NETVAR("DT_CSPlayer", "m_bNightVisionOn", night_vision_on, bool)
	NETVAR("DT_CSPlayer", "m_iHealth", health, int)
	NETVAR("DT_CSPlayer", "m_lifeState", life_state, int)
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int)
	NETVAR("DT_BasePlayer", "m_viewPunchAngle", punch_angle, Vector)
	NETVAR("DT_BasePlayer", "m_aimPunchAngle", aim_punch_angle, Vector)
	NETVAR("DT_BasePlayer", "m_vecVelocity[0]", velocity, Vector)
	NETVAR("DT_CSPlayer", "m_flStamina", stamina, Vector)
	NETVAR("DT_CSPlayer", "m_flVelocityModifier", velocity_loss, float)
	NETVAR("DT_BasePlayer", "m_flMaxspeed", max_speed, float)
	NETVAR("DT_BasePlayer", "m_hObserverTarget", observer_target, CHandle<player_t>)
	NETVAR("DT_BasePlayer", "m_iObserverMode", obsserver_mode, int)
	NETVAR("DT_BasePlayer", "m_nHitboxSet", hitbox_set, int)
	NETVAR("DT_CSPlayer", "m_flDuckAmount", duck_amount, float)
	NETVAR("DT_CSPlayer", "m_bHasHeavyArmor", has_heavy_armor, bool)
	NETVAR("DT_CSPlayer", "m_nTickBase", get_tick_base, int)
	NETVAR("DT_BaseAnimating", "m_flModelScale", model_scale, float)
	NETVAR("DT_BasePlayer", "m_nNextThinkTick", m_nNextThinkTick, int)
	NETVAR("DT_BasePlayer", "m_flFallVelocity", fall_velocity, float)
	NETVAR("DT_BaseViewModel", "m_nSequence", m_nSequence, int)

	weapon_t* active_weapon()
	{
		auto active_weapon = read<uintptr_t>(netvarsystem::get().get_net_var(fnv::hash("DT_CSPlayer"), fnv::hash("m_hActiveWeapon"))) & 0xFFF;
		return reinterpret_cast<weapon_t*>(g_EntityList->GetClientEntity(active_weapon));
	}

	UINT* get_wearables() {
		return (UINT*)((uintptr_t)this + (netvarsystem::get().get_net_var(fnv::hash("DT_CSPlayer"), fnv::hash("m_hMyWearables"))));
	}

	UINT* get_weapons() {
		return (UINT*)((uintptr_t)this + (netvarsystem::get().get_net_var(fnv::hash("DT_CSPlayer"), fnv::hash("m_hMyWeapons"))));
	}

	bool PhysicsRunThink(int index)
	{
		using PhysicsRunThinkFn = bool(__thiscall*)(void*, int);
		static auto oPhysicsRunThink = (PhysicsRunThinkFn)Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8B EC 83 EC 10 53 56 57 8B F9 8B 87"));
		return oPhysicsRunThink(this, index);
	}

	void PostThink()
	{
		using fn = void(__thiscall*)(void*);
		static auto PostThinkVPhysics = (fn)Utils::PatternScan(GetModuleHandleA("client.dll"), "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 8B D9 56 57 83 BB ? ? ? ? ? 0F 84");
		static auto SimulatePlayerSimulatedEntities = (fn)Utils::PatternScan(GetModuleHandleA("client.dll"), "56 8B F1 57 8B BE ? ? ? ? 83 EF 01 78 74");

		g_MdlCache->BeginLock();

		if (is_alive())
		{
			UpdateCollisionBounds();

			if (flags() & FL_ONGROUND)
				fall_velocity() = 0.f;

			if (m_nSequence() == -1)
				SetSequence(0);

			StudioFrameAdvance();
			PostThinkVPhysics(this);
		}

		SimulatePlayerSimulatedEntities(this);

		g_MdlCache->EndLock();
	}

	void Think()
	{
		return CallVFunction< void(__thiscall*)(decltype(this)) >(this, 139)(this);
	}

	void SetSequence(int iSequence)
	{
		CallVFunction<float(__thiscall*)(void*, int)>(this, 219)(this, iSequence);
	}

	void StudioFrameAdvance()
	{
		return CallVFunction< void(__thiscall*)(decltype(this)) >(this, 220)(this);
	}

	void PreThink()
	{
		return CallVFunction< void(__thiscall*)(decltype(this)) >(this, 318)(this);
	}

	void UpdateCollisionBounds()
	{
		return CallVFunction< void(__thiscall*)(decltype(this)) >(this, 340)(this);
	}

	int ButtonDisabled()
	{
		return *(int*)((std::uintptr_t)this + 0x3330);
	}

	int ButtonForced()
	{
		return *(int*)((std::uintptr_t)this + 0x3334);
	}

	Vector get_eye_pos()
	{
		return origin() + view_offset();
	}

	anim_state* get_anim_state() 
	{
		return *reinterpret_cast<anim_state**>(this + 0x3914);
	}

	bool has_bomb() 
	{
		auto weapons = this->get_weapons();

		for (size_t i = 0; weapons[i] != 0xFFFFFFFF; i++) 
		{
			auto weapon = reinterpret_cast<weapon_t*>(g_EntityList->GetClientEntityFromHandle(weapons[i]));

			if (weapon && weapon->get_weapon_data()->m_iWeaponType == WEAPONTYPE_C4)
			{
				return true;
			}
		}

		return false;
	}

	bool can_see_player_pos(player_t* player, const Vector& pos)
	{
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;
		filter.pSkip = this;

		auto start = get_eye_pos();
		auto dir = (pos - start).Normalized();

		ray.Init(start, pos);
		g_EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

		return tr.hit_entity == player || tr.fraction > 0.97f;
	}

	Vector get_bone_position(int bone)
	{
		if (matrix3x4_t boneMatrices[256]; SetupBones(boneMatrices, 256, 256, 0.0f))
		{
			return boneMatrices[bone].origin();
		}
		else
		{
			return Vector{ };
		}
	}

	Vector get_hitbox_position(const int idx)
	{
		if (idx == -1)
		{
			return { 0.f, 0.f, 0.f };
		}

		matrix3x4_t matrices[128];

		if (!this->SetupBones(matrices, 128, 0x100, g_GlobalVars->curtime))
		{
			return { 0.f, 0.f, 0.f };
		}

		const auto model = this->GetModel();

		if (!model) 
		{
			return { 0.f, 0.f, 0.f };
		}

		const auto studio_hdr = g_MdlInfo->GetStudiomodel(model);

		if (!studio_hdr) 
		{
			return { 0.f, 0.f, 0.f };
		}

		const auto bbox = studio_hdr->GetHitboxSet(0)->GetHitbox(idx);

		if (!bbox)
		{
			return { 0.f, 0.f, 0.f };
		}

		const matrix3x4_t& matrix = matrices[bbox->bone];
		const float modifier = bbox->m_flRadius != -1.0f ? bbox->m_flRadius : 0.0f;

		const auto min = math::vector_transform(bbox->bbmin - modifier, matrix);
		const auto max = math::vector_transform(bbox->bbmax + modifier, matrix);

		return (min + max) * 0.5f;
	}

	bool is_alive() {
		if (!this) return false;
		return this->health() > 0;
	}

	bool is_in_air() {
		if (!this) return false;
		return !(this->flags() & FL_ONGROUND);
	}

	bool is_flashed() {
		if (!this) return false;
		return this->flash_duration() > 0.0f;
	}

	__forceinline bool IsBreakableEntity() {
		if (!this || !this->GetClientClass()) return false;

		const auto szObjectName = this->GetClientClass()->m_pNetworkName;

		if (szObjectName[0] == 'C')
		{
			if (szObjectName[7] == 't' || szObjectName[7] == 'b') return true;
		}

		return ((bool(__thiscall*)(player_t*))(Utils::PatternScan(xorstr("client.dll"), xorstr("55 8B EC 51 56 8B F1 85 F6 74 68"))))(this);
	}

	void update_client_side_animations() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[224](this);
	}

	Vector world_space_center() {
		using original_fn = Vector(__thiscall*)(void*);
		return (*(original_fn**)this)[79](this);
	}

	Vector& abs_origin() {
		using original_fn = Vector & (__thiscall*)(void*);
		return (*(original_fn**)this)[10](this);
	}

	Vector& abs_angles() {
		using original_fn = Vector & (__thiscall*)(void*);
		return (*(original_fn**)this)[11](this);
	}

	int move_type() {
		static int type = netvarsystem::get().get_net_var(fnv::hash("DT_BaseEntity"), fnv::hash("m_nRenderMode")) + 1;
		return read<int>(type);
	}
};
