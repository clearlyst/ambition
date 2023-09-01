#pragma once

#include "../Math/QAngle.hpp"
#include "../Misc/CUserCmd.hpp"
#include "IMoveHelper.hpp"

class CMoveData
{
public:
    bool    m_bFirstRunOfFunctions : 1;
    bool    m_bGameCodeMovedPlayer : 1;
    int     m_nPlayerHandle;        // edict index on server, client entity handle on client=
    int     m_nImpulseCommand;      // Impulse command issued.
    Vector  m_vecViewAngles;        // Command view angles (local space)
    Vector  m_vecAbsViewAngles;     // Command view angles (world space)
    int     m_nButtons;             // Attack buttons.
    int     m_nOldButtons;          // From host_client->oldbuttons;
    float   m_flForwardMove;
    float   m_flSideMove;
    float   m_flUpMove;
    float   m_flMaxSpeed;
    float   m_flClientMaxSpeed;
    Vector  m_vecVelocity;          // edict::velocity        // Current movement direction.
    Vector  m_vecAngles;            // edict::angles
    Vector  m_vecOldAngles;
    float   m_outStepHeight;        // how much you climbed this move
    Vector  m_outWishVel;           // This is where you tried 
    Vector  m_outJumpVel;           // This is your jump velocity
    Vector  m_vecConstraintCenter;
    float   m_flConstraintRadius;
    float   m_flConstraintWidth;
    float   m_flConstraintSpeedFactor;
    float   m_flUnknown[5];
    Vector  m_vecAbsOrigin;
};

class player_t;

class IGameMovement
{
public:
    virtual			~IGameMovement(void) {}

    virtual void	          ProcessMovement(player_t* pPlayer, CMoveData* pMove) = 0;
    virtual void	          Reset(void) = 0;
    virtual void	          StartTrackPredictionErrors(player_t* pPlayer) = 0;
    virtual void	          FinishTrackPredictionErrors(player_t* pPlayer) = 0;
    virtual void	          DiffPrint(char const* fmt, ...) = 0;
    virtual Vector const& GetPlayerMins(bool ducked) const = 0;
    virtual Vector const& GetPlayerMaxs(bool ducked) const = 0;
    virtual Vector const& GetPlayerViewOffset(bool ducked) const = 0;
    virtual bool		        IsMovingPlayerStuck(void) const = 0;
    virtual player_t* GetMovingPlayer(void) const = 0;
    virtual void		        UnblockPusher(player_t* pPlayer, player_t* pPusher) = 0;
    virtual void            SetupMovementBounds(CMoveData* pMove) = 0;
};

class CGameMovement : public IGameMovement
{
public:
    virtual ~CGameMovement(void) {}
};

class IPrediction
{
public:
    bool& m_bInPrediction()
    {
        return *(bool*)((uintptr_t)(this) + 0x8);
    }

    bool& m_bEnginePaused()
    {
        return *(bool*)((uintptr_t)(this) + 0xA);
    }

    bool& m_bIsFirstTimePredicted()
    {
        return *(bool*)((uintptr_t)(this) + 0x18);
    }

    int& m_nCommandsPredicted()
    {
        return *(int*)((uintptr_t)(this) + 0x1C);
    }

    void Update(int start_frame, bool valid_frame, int inc_ack, int out_cmd)
    {
        typedef void(__thiscall* oUpdate)(void*, int, bool, int, int);
        return CallVFunction<oUpdate>(this, 3)(this, start_frame, valid_frame, inc_ack, out_cmd);
    }

    bool InPrediction()
    {
        typedef bool(__thiscall* oInPrediction)(void*);
        return CallVFunction<oInPrediction>(this, 14)(this);
    }

    void RunCommand(player_t* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
    {
        typedef void(__thiscall* oRunCommand)(void*, player_t*, CUserCmd*, IMoveHelper*);
        return CallVFunction<oRunCommand>(this, 19)(this, player, ucmd, moveHelper);
    }

    void SetupMove(player_t* player, CUserCmd* ucmd, IMoveHelper* moveHelper, void* pMoveData)
    {
        typedef void(__thiscall* oSetupMove)(void*, player_t*, CUserCmd*, IMoveHelper*, void*);
        return CallVFunction<oSetupMove>(this, 20)(this, player, ucmd, moveHelper, pMoveData);
    }

    void FinishMove(player_t* player, CUserCmd* ucmd, void* pMoveData)
    {
        typedef void(__thiscall* oFinishMove)(void*, player_t*, CUserCmd*, void*);
        return CallVFunction<oFinishMove>(this, 21)(this, player, ucmd, pMoveData);
    }
};