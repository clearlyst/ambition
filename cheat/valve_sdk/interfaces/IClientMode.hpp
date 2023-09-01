#pragma once

#include "../Math/VMatrix.hpp"
class bf_read;
class bf_write;
class INetMessage
{
public:
    virtual	~INetMessage() {};

    virtual void SetNetChannel(void* netchan) = 0;
    virtual void SetReliable(bool state) = 0;

    virtual bool Process(void) = 0;

    virtual	bool ReadFromBuffer(bf_read& buffer) = 0;
    virtual	bool WriteToBuffer(bf_write& buffer) = 0;

    virtual bool IsReliable(void) const = 0;

    virtual int GetType(void) const = 0;
    virtual int GetGroup(void) const = 0;
    virtual const char* GetName(void) const = 0;
    virtual void* GetNetChannel(void) const = 0;
    virtual const char* ToString(void) const = 0;
};

class cnetmsg_clientinfo {
private:
    char __PAD0[0x8];
public:
    uint32_t send_table_crc;
    uint32_t server_count;
    bool is_hltv;
    bool is_replay;
    uint32_t friends_id;
};

template<typename T>
class CNetMessagePB : public INetMessage, public T {};
using cclcmsg_clientinfo_t = CNetMessagePB<cnetmsg_clientinfo>;
class IPanel;
class C_BaseEntity;

enum class MotionBlurMode_t
{
    MOTION_BLUR_DISABLE = 1,
    MOTION_BLUR_GAME = 2,
    MOTION_BLUR_SFM = 3
};

#include <cstddef>

#define CONCAT(a, b) a##b
#define PAD_NAME(n) CONCAT(pad, n)

#define PAD(size) \
private: \
    std::byte PAD_NAME(__COUNTER__) [size]; \
public:

/*
class CViewSetup
{
public:
    PAD(172);
    void* csm;
    float fov;
    PAD(4);
    Vector origin;
    Vector angles;
    PAD(4);
    float farZ;
    PAD(8)
    float aspectRatio;
};
*/

class CViewSetup
{
public:
    int            iX;
    int            iUnscaledX;
    int            iY;
    int            iUnscaledY;
    int            iWidth;
    int            iUnscaledWidth;
    int            iHeight;
    int            iUnscaledHeight;
    bool        bOrtho;
    std::byte    pad0[0x8F];
    float        flFOV;
    float        flViewModelFOV;
    Vector        vecOrigin;
    Vector        angView;
    float        flNearZ;
    float        flFarZ;
    float        flNearViewmodelZ;
    float        flFarViewmodelZ;
    float        flAspectRatio;
    float        flNearBlurDepth;
    float        flNearFocusDepth;
    float        flFarFocusDepth;
    float        flFarBlurDepth;
    float        flNearBlurRadius;
    float        flFarBlurRadius;
    float        flDoFQuality;
    MotionBlurMode_t nMotionBlurMode;
    float        flShutterTime;
    Vector        vecShutterOpenPosition;
    QAngle        vecShutterOpenAngles;
    Vector        vecShutterClosePosition;
    QAngle        vecShutterCloseAngles;
    float        flOffCenterTop;
    float        flOffCenterBottom;
    float        flOffCenterLeft;
    float        flOffCenterRight;
    bool        bOffCenter;
    bool        bRenderToSubrectOfLargerScreen;
    bool        bDoBloomAndToneMapping;
    bool        bDoDepthOfField;
    bool        bHDRTarget;
    bool        bDrawWorldNormal;
    bool        bCullFontFaces;
    bool        bCacheFullSceneState;
    bool        bCSMView;
};

class IClientMode
{
public:
    virtual             ~IClientMode() {}
    virtual int         ClientModeCSNormal(void *) = 0;
    virtual void        Init() = 0;
    virtual void        InitViewport() = 0;
    virtual void        Shutdown() = 0;
    virtual void        Enable() = 0;
    virtual void        Disable() = 0;
    virtual void        Layout() = 0;
    virtual IPanel*     GetViewport() = 0;
    virtual void*       GetViewportAnimationController() = 0;
    virtual void        ProcessInput(bool bActive) = 0;
    virtual bool        ShouldDrawDetailObjects() = 0;
    virtual bool        ShouldDrawEntity(C_BaseEntity *pEnt) = 0;
    virtual bool        ShouldDrawLocalPlayer(C_BaseEntity *pPlayer) = 0;
    virtual bool        ShouldDrawParticles() = 0;
    virtual bool        ShouldDrawFog(void) = 0;
    virtual void        OverrideView(CViewSetup *pSetup) = 0;
    virtual int         KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0;
    virtual void        StartMessageMode(int iMessageModeType) = 0;
    virtual IPanel*     GetMessagePanel() = 0;
    virtual void        OverrideMouseInput(float *x, float *y) = 0;
    virtual bool        CreateMove(float flInputSampleTime, void* usercmd) = 0;
    virtual void        LevelInit(const char *newmap) = 0;
    virtual void        LevelShutdown(void) = 0;
};