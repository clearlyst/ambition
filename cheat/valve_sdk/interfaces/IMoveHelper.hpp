#pragma once

class IClientEntity;
class IPhysicsSurfaceProps;
enum ESoundLevel;

class IMoveHelper
{
public:
    virtual	const char* GetName(void* hEntity) const = 0;
    virtual void				SetHost(IClientEntity* pHost) = 0;
    virtual void				ResetTouchList() = 0;
    virtual bool				AddToTouched(const CGameTrace& trace, const Vector& vecImpactVelocity) = 0;
    virtual void				ProcessImpacts() = 0;
    virtual void				Con_NPrintf(int nIndex, char const* fmt, ...) = 0;
    virtual void				StartSound(const Vector& vecOrigin, int iChannel, char const* szSample, float flVolume, ESoundLevel soundlevel, int fFlags, int iPitch) = 0;
    virtual void				StartSound(const Vector& vecOrigin, const char* soundname) = 0;
    virtual void				PlaybackEventFull(int fFlags, int nClientIndex, unsigned short uEventIndex, float flDelay, Vector& vecOrigin, Vector& vecAngles, float flParam1, float flParam2, int iParam1, int iParam2, int bParam1, int bParam2) = 0;
    virtual bool				PlayerFallingDamage() = 0;
    virtual void				PlayerSetAnimation(int playerAnimation) = 0;
    virtual IPhysicsSurfaceProps* GetSurfaceProps() = 0;
    virtual bool				IsWorldEntity(const unsigned long& hEntity) = 0;
};
