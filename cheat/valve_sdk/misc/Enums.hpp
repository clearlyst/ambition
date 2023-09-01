#pragma once

enum CollisionGroup : int
{
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_DEBRIS_TRIGGER,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,
	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,
	LAST_SHARED_COLLISION_GROUP
};

enum ECstrike15UserMessages
{
	CS_UM_VGUIMenu = 1,
	CS_UM_Geiger = 2,
	CS_UM_Train = 3,
	CS_UM_HudText = 4,
	CS_UM_SayText = 5,
	CS_UM_SayText2 = 6,
	CS_UM_TextMsg = 7,
	CS_UM_HudMsg = 8,
	CS_UM_ResetHud = 9,
	CS_UM_GameTitle = 10,
	CS_UM_Shake = 12,
	CS_UM_Fade = 13,
	CS_UM_Rumble = 14,
	CS_UM_CloseCaption = 15,
	CS_UM_CloseCaptionDirect = 16,
	CS_UM_SendAudio = 17,
	CS_UM_RawAudio = 18,
	CS_UM_VoiceMask = 19,
	CS_UM_RequestState = 20,
	CS_UM_Damage = 21,
	CS_UM_RadioText = 22,
	CS_UM_HintText = 23,
	CS_UM_KeyHintText = 24,
	CS_UM_ProcessSpottedEntityUpdate = 25,
	CS_UM_ReloadEffect = 26,
	CS_UM_AdjustMoney = 27,
	CS_UM_UpdateTeamMoney = 28,
	CS_UM_StopSpectatorMode = 29,
	CS_UM_KillCam = 30,
	CS_UM_DesiredTimescale = 31,
	CS_UM_CurrentTimescale = 32,
	CS_UM_AchievementEvent = 33,
	CS_UM_MatchEndConditions = 34,
	CS_UM_DisconnectToLobby = 35,
	CS_UM_PlayerStatsUpdate = 36,
	CS_UM_DisplayInventory = 37,
	CS_UM_WarmupHasEnded = 38,
	CS_UM_ClientInfo = 39,
	CS_UM_XRankGet = 40,
	CS_UM_XRankUpd = 41,
	CS_UM_CallVoteFailed = 45,
	CS_UM_VoteStart = 46,
	CS_UM_VotePass = 47,
	CS_UM_VoteFailed = 48,
	CS_UM_VoteSetup = 49,
	CS_UM_ServerRankRevealAll = 50,
	CS_UM_SendLastKillerDamageToClient = 51,
	CS_UM_ServerRankUpdate = 52,
	CS_UM_ItemPickup = 53,
	CS_UM_ShowMenu = 54,
	CS_UM_BarTime = 55,
	CS_UM_AmmoDenied = 56,
	CS_UM_MarkAchievement = 57,
	CS_UM_MatchStatsUpdate = 58,
	CS_UM_ItemDrop = 59,
	CS_UM_GlowPropTurnOff = 60,
	CS_UM_SendPlayerItemDrops = 61,
	CS_UM_RoundBackupFilenames = 62,
	CS_UM_SendPlayerItemFound = 63,
	CS_UM_ReportHit = 64,
	CS_UM_XpUpdate = 65,
	CS_UM_QuestProgress = 66,
	CS_UM_ScoreLeaderboardData = 67,
	CS_UM_PlayerDecalDigitalSignature = 68,
	MAX_ECSTRIKE15USERMESSAGES
};


enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10,
	VIEW_CLEAR_STENCIL = 0x20,
};
enum ItemDefinitionIndex {
	WEAPON_INVALID = -1,
	ITEM_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_CSS = 503,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_CORD = 517,
	WEAPON_KNIFE_CANIS = 518,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
	WEAPON_KNIFE_NAVAJA,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	WEAPON_KNIFE_TALON,
	WEAPON_KNIFE_OUTDOOR = 521,
	WEAPON_KNIFE_SKELETON = 525,

	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA,
	MAX_ITEMDEFINITIONINDEX
};

enum ClassId
{
	C_AI_BASE_NPC,
	C_WEAPON_AK47,
	C_BASE_ANIMATING,
	C_BASE_ANIMATING_OVERLAY,
	C_BASE_ATTRIBUTABLE_ITEM,
	C_BASE_BUTTON,
	C_BASE_COMBAT_CHARACTER,
	C_BASE_COMBAT_WEAPON,
	C_BASE_CS_GRENADE,
	C_BASE_CS_GRENADE_PROJECTILE,
	C_BASE_DOOR,
	C_BASE_ENTITY,
	C_BASE_FLEX,
	C_BASE_GRENADE,
	C_BASE_PARTICLE_ENTITY,
	C_BASE_PLAYER,
	C_BASE_PROP_DOOR,
	C_BASE_TEAM_OBJECTIVE_RESOURCE,
	C_BASE_TEMP_ENTITY,
	C_BASE_TOGGLE,
	C_BASE_TRIGGER,
	C_BASE_VIEWMODEL,
	C_BASE_VPHYSICS_TRIGGER,
	C_BASE_WEAPON_WORLD_MODEL,
	C_BEAM,
	C_BEAM_SPOTLIGHT,
	C_BONE_FOLLOWER,
	C_BR_C4_TARGET,
	C_BREACH_CHARGE,
	C_BREACH_CHARGE_PROJECTILE,
	C_BREAKABLE_PROP,
	C_BREAKABLE_SURFACE,
	C_BUMP_MINE,
	C_BUMP_MINE_PROJECTILE,
	C_C4,
	C_CASCADE_LIGHT,
	C_CHICKEN,
	C_COLOR_CORRECTION,
	C_COLOR_CORRECTION_VOLUME,
	C_CS_GAMERULES_PROXY,
	C_CS_PLAYER,
	C_CS_PLAYER_RESOURCE,
	C_CS_RAGDOLL,
	C_CS_TEAM,
	C_DANGERZONE,
	C_DANGERZONE_CONTROLLER,
	C_DEAGLE,
	C_DECOY_GRENADE,
	C_DECOY_PROJECTILE,
	C_DRONE,
	C_DRONE_GUN,
	C_DYNAMIC_LIGHT,
	C_DYNAMIC_PROP,
	C_ECON_ENTITY,
	C_ECON_WEARABLE,
	C_EMBERS,
	C_ENTITY_DISSOLVE,
	C_ENTITY_FLAME,
	C_ENTITY_FREEZING,
	C_ENTITY_PARTICLE_TRAIL,
	C_ENV_AMBIENT_LIGHT,
	C_ENV_DETAIL_CONTROLLER,
	C_ENV_DOF_CONTROLLER,
	C_ENV_GAS_CANISTER,
	C_ENV_PARTICLE_SCRIPT,
	C_ENV_PROJECTED_TEXTURE,
	C_ENV_QUADRATIC_BEAM,
	C_ENV_SCREEN_EFFECT,
	C_ENV_SCREEN_OVERLAY,
	C_ENV_TONEMAP_CONTROLLER,
	C_ENV_WIND,
	C_FE_PLAYER_DECAL,
	C_FIRECRACKER_BLAST,
	C_FIRE_SMOKE,
	C_FIRE_TRAIL,
	C_FISH,
	C_FISTS,
	C_FLASHBANG,
	C_FOG_CONTROLLER,
	C_FOOTSTEP_CONTROL,
	C_FUNC_DUST,
	C_FUNC_LOD,
	C_FUNC_AREA_PORTAL_WINDOW,
	C_FUNC_BRUSH,
	C_FUNC_CONVEYOR,
	C_FUNC_LADDER,
	C_FUNC_MONITOR,
	C_FUNC_MOVE_LINEAR,
	C_FUNC_OCCLUDER,
	C_FUNC_REFLECTIVE_GLASS,
	C_FUNC_ROTATING,
	C_FUNC_SMOKE_VOLUME,
	C_FUNC_TRACK_TRAIN,
	C_GAMERULES_PROXY,
	C_GRASS_BURN,
	C_HANDLE_TEST,
	C_HE_GRENADE,
	C_HOSTAGE,
	C_HOSTAGE_CARRIABLE_PROP,
	C_INCENDIARY_GRENADE,
	C_INFERNO,
	C_INFO_LADDER_DISMOUNT,
	C_INFO_MAP_REGION,
	C_INFO_OVERLAY_ACCESSOR,
	C_ITEM_HEALTHSHOT,
	C_ITEM_CASH,
	C_ITEM_DOGTAGS,
	C_KNIFE,
	C_KNIFE_GG,
	C_LIGHT_GLOW,
	C_MAP_VETO_PICK_CONTROLLER,
	C_MATERIAL_MODIFY_CONTROL,
	C_MELEE,
	C_MOLOTOV_GRENADE,
	C_MOLOTOV_PROJECTILE,
	C_MOVIE_DISPLAY,
	C_PARADROP_CHOPPER,
	C_PARTICLE_FIRE,
	C_PARTICLE_PERFORMANCE_MONITOR,
	C_PARTICLE_SYSTEM,
	C_PHYS_BOX,
	C_PHYS_BOX_MULTIPLAYER,
	C_PHYSICS_PROP,
	C_PHYSICS_PROP_MULTIPLAYER,
	C_PHYS_MAGNET,
	C_PHYS_PROP_AMMO_BOX,
	C_PHYS_PROP_LOOT_CRATE,
	C_PHYS_PROP_RADAR_JAMMER,
	C_PHYS_PROP_WEAPON_UPGRADE,
	C_PLANTED_C4,
	C_PLASMA,
	C_PLAYER_PING,
	C_PLAYER_RESOURCE,
	C_POINT_CAMERA,
	C_POINT_COMMENT_ARYNODE,
	C_POINT_WORLD_TEXT,
	C_POSE_CONTROLLER,
	C_POST_PROCESS_CONTROLLER,
	C_PRECIPITATION,
	C_PRECIPITATION_BLOCKER,
	C_PREDICTED_VIEW_MODEL,
	C_PROP_HALLUCINATION,
	C_PROP_COUNTER,
	C_PROP_DOOR_ROTATING,
	C_PROP_JEEP,
	C_PROP_VEHICLE_DRIVEABLE,
	C_RAGDOLL_MANAGER,
	C_RAGDOLL_PROP,
	C_RAGDOLL_PROP_ATTACHED,
	C_ROPE_KEYFRAME,
	C_WEAPON_SCAR17,
	C_SCENE_ENTITY,
	C_SENSOR_GRENADE,
	C_SENSOR_GRENADE_PROJECTILE,
	C_SHADOW_CONTROL,
	C_SLIDE_SHOW_DISPLAY,
	C_SMOKE_GRENADE,
	C_SMOKE_GRENADE_PROJECTILE,
	C_SMOKE_STACK,
	C_SNOWBALL,
	C_SNOWBALL_PILE,
	C_SNOWBALL_PROJECTILE,
	C_SPATIAL_ENTITY,
	C_SPOTLIGHT_END,
	C_SPRITE,
	C_SPRITE_ORIENTED,
	C_SPRITE_TRAIL,
	C_STATUE_PROP,
	C_STEAMJET,
	C_SUN,
	C_SUNLIGHT_SHADOW_CONTROL,
	C_SURVIVAL_SPAWN_CHOPPER,
	C_TABLET,
	C_TEAM,
	C_TEAM_PLAYROUND_BASED_RULES_PROXY,
	C_TEAR_MORRICOCHET,
	C_TE_BASE_BEAM,
	C_TE_BEAM_ENT_POINT,
	C_TE_BEAM_ENTS,
	C_TE_BEAM_FOLLOW,
	C_TE_BEAM_LASER,
	C_TE_BEAM_POINTS,
	C_TE_BEAM_RING,
	C_TE_BEAM_RING_POINT,
	C_TE_BEAM_SPLINE,
	C_TE_BLOOD_SPRITE,
	C_TE_BLOOD_STREAM,
	C_TE_BREAK_MODEL,
	C_TE_BSP_DECAL,
	C_TE_BUBBLES,
	C_TE_BUBBLE_TRAIL,
	C_TE_CLIENT_PROJECTILE,
	C_TE_DECAL,
	C_TE_DUST,
	C_TE_DYNAMIC_LIGHT,
	C_TE_EFFECT_DISPATCH,
	C_TE_ENERGY_SPLASH,
	C_TE_EXPLOSION,
	C_TE_FIRE_BULLETS,
	C_TE_FIZZ,
	C_TE_FOOTPRINT_DECAL,
	C_TE_FOUNDRY_HELPERS,
	C_TE_GAUSS_EXPLOSION,
	C_TE_GLOW_SPRITE,
	C_TE_IMPACT,
	C_TE_KILL_PLAYER_ATTACHMENTS,
	C_TE_LARGE_FUNNEL,
	C_TE_METAL_SPARKS,
	C_TE_MUZZLE_FLASH,
	C_TE_PARTICLE_SYSTEM,
	C_TE_PHYSICS_PROP,
	C_TE_PLANT_BOMB,
	C_TE_PLAYER_ANIM_EVENT,
	C_TE_PLAYER_DECAL,
	C_TE_PROJECTED_DECAL,
	C_TE_RADIOICON,
	C_TE_SHATTER_SURFACE,
	C_TE_SHOW_LINE,
	C_TE_SLA,
	C_TE_SMOKE,
	C_TE_SPARKS,
	C_TE_SPRITE,
	C_TE_SPRITE_SPRAY,
	C_TEST_PROXY_TOGGLE_NETWORKABLE,
	C_TEST_TRACE_LINE,
	C_TE_WORLD_DECAL,
	C_TRIGGER_PLAYER_MOVEMENT,
	C_TRIGGER_SOUND_OPERATOR,
	C_VGUI_SCREEN,
	C_VOTE_CONTROLLER,
	C_WATER_BULLET,
	C_WATER_LOD_CONTROL,
	C_WEAPON_AUG,
	C_WEAPON_AWP,
	C_WEAPON_BASE_ITEM,
	C_WEAPON_PPBIZON,
	C_WEAPON_CS_BASE,
	C_WEAPON_CS_BASE_GUN,
	C_WEAPON_CYCLER,
	C_WEAPON_DUAL_BERETTAS,
	C_WEAPON_FAMAS,
	C_WEAPON_FIVESEVEN,
	C_WEAPON_G3SG1,
	C_WEAPON_GALIL,
	C_WEAPON_GALIL_AR,
	C_WEAPON_GLOCK18,
	C_WEAPON_P2000,
	C_WEAPON_M249,
	C_WEAPON_M3,
	C_WEAPON_M4A4,
	C_WEAPON_MAC10,
	C_WEAPON_MAG7,
	C_WEAPON_MP5SD,
	C_WEAPON_MP7,
	C_WEAPON_MP9,
	C_WEAPON_NEGEV,
	C_WEAPON_NOVA,
	C_WEAPON_P228,
	C_WEAPON_P250,
	C_WEAPON_P90,
	C_WEAPON_SAWEDOFF,
	C_WEAPON_SCAR20,
	C_WEAPON_SCOUT,
	C_WEAPON_SG550,
	C_WEAPON_SG552,
	C_WEAPON_SG553,
	C_WEAPON_BALLISTIC_SHIELD,
	C_WEAPON_SSG08,
	C_WEAPON_ZEUSX27,
	C_WEAPON_TEC9,
	C_WEAPON_TMP,
	C_WEAPON_UMP45,
	C_WEAPON_USP,
	C_WEAPON_XM1014,
	C_WORLD,
	C_WORLD_VGUI_TEXT,
	DUST_TRAIL,
	MOVIE_EXPLOSION,
	PARTICLE_SMOKE_GRENADE,
	ROCKET_TRAIL,
	SMOKE_TRAIL,
	SPORE_EXPLOSION,
	SPORE_TRAIL
};


enum ECSPlayerBones
{
	PELVIS = 0,
	SPINE_0,
	SPINE_1,
	SPINE_2,
	SPINE_3,
	NECK_0,
	HEAD_0,
	CLAVICLE_L,
	ARM_UPPER_L,
	ARM_LOWER_L,
	HAND_L,
	FINGER_MIDDLE_META_L,
	FINGER_MIDDLE_0_L,
	FINGER_MIDDLE_1_L,
	FINGER_MIDDLE_2_L,
	FINGER_PINKY_META_L,
	FINGER_PINKY_0_L,
	FINGER_PINKY_1_L,
	FINGER_PINKY_2_L,
	FINGER_INDEX_META_L,
	FINGER_INDEX_0_L,
	FINGER_INDEX_1_L,
	FINGER_INDEX_2_L,
	FINGER_THUMB_0_L,
	FINGER_THUMB_1_L,
	FINGER_THUMB_2_L,
	FINGER_RING_META_L,
	FINGER_RING_0_L,
	FINGER_RING_1_L,
	FINGER_RING_2_L,
	WEAPON_HAND_L,
	ARM_LOWER_L_TWIST,
	ARM_LOWER_L_TWIST1,
	ARM_UPPER_L_TWIST,
	ARM_UPPER_L_TWIST1,
	CLAVICLE_R,
	ARM_UPPER_R,
	ARM_LOWER_R,
	HAND_R,
	FINGER_MIDDLE_META_R,
	FINGER_MIDDLE_0_R,
	FINGER_MIDDLE_1_R,
	FINGER_MIDDLE_2_R,
	FINGER_PINKY_META_R,
	FINGER_PINKY_0_R,
	FINGER_PINKY_1_R,
	FINGER_PINKY_2_R,
	FINGER_INDEX_META_R,
	FINGER_INDEX_0_R,
	FINGER_INDEX_1_R,
	FINGER_INDEX_2_R,
	FINGER_THUMB_0_R,
	FINGER_THUMB_1_R,
	FINGER_THUMB_2_R,
	FINGER_RING_META_R,
	FINGER_RING_0_R,
	FINGER_RING_1_R,
	FINGER_RING_2_R,
	WEAPON_HAND_R,
	ARM_LOWER_R_TWIST,
	ARM_LOWER_R_TWIST1,
	ARM_UPPER_R_TWIST,
	ARM_UPPER_R_TWIST1,
	LEG_UPPER_L,
	LEG_LOWER_L,
	ANKLE_L,
	BALL_L,
	LFOOT_LOCK,
	LEG_UPPER_L_TWIST,
	LEG_UPPER_L_TWIST1,
	LEG_UPPER_R,
	LEG_LOWER_R,
	ANKLE_R,
	BALL_R,
	RFOOT_LOCK,
	LEG_UPPER_R_TWIST,
	LEG_UPPER_R_TWIST1,
	FINGER_PINKY_L_END,
	FINGER_PINKY_R_END,
	VALVEBIPED_WEAPON_BONE,
	LH_IK_DRIVER,
	PRIMARY_JIGGLE_JNT,
	MAX_ECSPLAYERBONES
};

enum EntityFlags
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_ANIMDUCKING = (1 << 2),
	FL_WATERJUMP = (1 << 3),
	FL_ONTRAIN = (1 << 4),
	FL_INRAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_ATCONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKECLIENT = (1 << 9),
	FL_INWATER = (1 << 10),
	FL_FLY = (1 << 11),
	FL_SWIM = (1 << 12),
	FL_CONVEYOR = (1 << 13),
	FL_NPC = (1 << 14),
	FL_GODMODE = (1 << 15),
	FL_NOTARGET = (1 << 16),
	FL_AIMTARGET = (1 << 17),
	FL_PARTIALGROUND = (1 << 18),
	FL_STATICPROP = (1 << 19),
	FL_GRAPHED = (1 << 20),
	FL_GRENADE = (1 << 21),
	FL_STEPMOVEMENT = (1 << 22),
	FL_DONTTOUCH = (1 << 23),
	FL_BASEVELOCITY = (1 << 24),
	FL_WORLDBRUSH = (1 << 25),
	FL_OBJECT = (1 << 26),
	FL_KILLME = (1 << 27),
	FL_ONFIRE = (1 << 28),
	FL_DISSOLVING = (1 << 29),
	FL_TRANSRAGDOLL = (1 << 30),
	FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
};

enum LifeState : unsigned char
{
	LIFE_ALIVE = 0,// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2, // dead. lying still.
	MAX_LIFESTATE
};

enum WeaponSound_t
{
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE, // Can't be "DOUBLE" because windows.h uses it.
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	FAST_RELOAD,
	// Add new shoot sound types here
	REVERSE_THE_NEW_SOUND,
	NUM_SHOOT_SOUND_TYPES,
	MAX_WEAPONSOUND
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
	MAX_MOVETYPE
};



enum spectators_mode
{

	OBS_MODE_NONE,
	OBS_MODE_DEATHCAM,
	OBS_MODE_FREEZECAM,
	OBS_MODE_FIXED,
	OBS_MODE_IN_EYE,
	OBS_MODE_CHASE,
	OBS_MODE_ROAMING,
};