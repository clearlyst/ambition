#pragma once

#include "../Misc/CUserCmd.hpp"

#define MULTIPLAYER_BACKUP 150

class bf_write;
class bf_read;

class CInput
{
public:
    char pad0[0xC];
    bool m_fTrackIRAvailable; 
    bool m_fMouseInitialized; 
    bool m_fMouseActive;
    char pad1[0x9A];
    bool m_fCameraInThirdPerson;
    char pad2[0x2];
    Vector m_vecCameraOffset;
    char pad3[0x38];
    CUserCmd* m_pCommands;
    CVerifiedUserCmd* m_pVerifiedCommands;
    inline CUserCmd* GetUserCmd(int sequence_number);
    inline CUserCmd* GetUserCmd(int nSlot, int sequence_number);
    inline CVerifiedUserCmd* GetVerifiedCmd(int sequence_number);
};

CUserCmd* CInput::GetUserCmd(int sequence_number)
{
    using OriginalFn = CUserCmd * (__thiscall*)(void*, int, int);
    return CallVFunction<OriginalFn>(this, 8)(this, 0, sequence_number);
}

CUserCmd* CInput::GetUserCmd(int nSlot, int sequence_number)
{
    typedef CUserCmd* (__thiscall* GetUserCmd_t)(void*, int, int);
    return CallVFunction<GetUserCmd_t>(this, 8)(this, nSlot, sequence_number);
}

CVerifiedUserCmd* CInput::GetVerifiedCmd(int sequence_number)
{
    return &m_pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
}

class IBaseFileSystem
{
public:
    int read(void* output, int size, void* file) {
        typedef int(__thiscall* tRead)(void*, void*, int, void*);
        return CallVFunction<tRead>(this, 0)(this, output, size, file);
    }

    void* open(const char* file_name, const char* options, const char* path_id) {
        typedef void* (__thiscall* tOpen)(void*, const char*, const char*, const char*);
        return CallVFunction<tOpen>(this, 2)(this, file_name, options, path_id);
    }

    void close(void* file) {
        typedef void(__thiscall* tClose)(void*, void*);
        return CallVFunction<tClose>(this, 3)(this, file);
    }

    unsigned int size(void* file) {
        typedef unsigned int(__thiscall* tSize)(void*, void*);
        return CallVFunction<tSize>(this, 7)(this, file);
    }
};