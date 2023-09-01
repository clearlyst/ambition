#pragma once

#include "IAppSystem.hpp"
#include "IRefCounted.hpp"
#include "../misc/UtlVector.hpp"
#include "IKeyValues.hpp"
#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define MAXSTUDIOSKINS		32

// These are given to FindMaterial to reference the texture groups that Show up on the 
#define TEXTURE_GROUP_LIGHTMAP						        "Lightmaps"
#define TEXTURE_GROUP_WORLD							          "World textures"
#define TEXTURE_GROUP_MODEL							          "Model textures"
#define TEXTURE_GROUP_VGUI							          "VGUI textures"
#define TEXTURE_GROUP_PARTICLE						        "Particle textures"
#define TEXTURE_GROUP_DECAL							          "Decal textures"
#define TEXTURE_GROUP_SKYBOX						          "SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				      "ClientEffect textures"
#define TEXTURE_GROUP_OTHER							          "Other textures"
#define TEXTURE_GROUP_PRECACHED						        "Precached"
#define TEXTURE_GROUP_CUBE_MAP						        "CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					      "RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					        "Unaccounted textures"
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		  "Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			    "Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			  "Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			  "Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					      "DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					        "ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					      "Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				      "Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			  "RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					      "Morph Targets"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
class IMaterial;
class IMesh;
class IVertexBuffer;
class IIndexBuffer;
struct MaterialSystem_Config_t;
class VMatrix;
class matrix3x4_t;
struct MaterialSystemHWID_t;
class KeyValues;
class IShader;
class IVertexTexture;
class IMorph;
class ICallQueue;
struct MorphWeight_t;
class IFileList;
struct VertexStreamSpec_t;
struct ShaderStencilState_t;
struct MeshInstanceData_t;
class IClientMaterialSystem;
class CPaintMaterial;
class IPaintMapDataManager;
class IPaintMapTextureManager;
class GPUMemoryStats;
struct AspectRatioInfo_t;
struct CascadedShadowMappingState_t;

class IMaterialProxyFactory;

class IMaterialSystemHardwareConfig;
class CShadowMgr;
struct IDirect3DTexture9;
class LightDesc_t;


struct Texture_t
{
    std::byte			pad0[0xC];		// 0x0000
    IDirect3DTexture9* lpRawTexture;	// 0x000C
};

class ITexture
{
private:
    template <typename T, typename ... args_t>
    constexpr T CallVFunc(void* thisptr, std::size_t nIndex, args_t... argList)
    {
        using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
        return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
    }
private:
    std::byte	pad0[0x50];		 // 0x0000
public:
    Texture_t** pTextureHandles; // 0x0050

    int GetActualWidth()
    {
        return CallVFunc<int>(this, 3);
    }

    int GetActualHeight()
    {
        return CallVFunc<int>(this, 4);
    }

    void IncrementReferenceCount()
    {
        CallVFunc<void>(this, 10);
    }

    void DecrementReferenceCount()
    {
        CallVFunc<void>(this, 11);
    }
};

enum CompiledVtfFlags
{
    TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
    TEXTUREFLAGS_TRILINEAR = 0x00000002,
    TEXTUREFLAGS_CLAMPS = 0x00000004,
    TEXTUREFLAGS_CLAMPT = 0x00000008,
    TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
    TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
    TEXTUREFLAGS_PWL_CORRECTED = 0x00000040,
    TEXTUREFLAGS_NORMAL = 0x00000080,
    TEXTUREFLAGS_NOMIP = 0x00000100,
    TEXTUREFLAGS_NOLOD = 0x00000200,
    TEXTUREFLAGS_ALL_MIPS = 0x00000400,
    TEXTUREFLAGS_PROCEDURAL = 0x00000800,
    TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
    TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,
    TEXTUREFLAGS_ENVMAP = 0x00004000,
    TEXTUREFLAGS_RENDERTARGET = 0x00008000,
    TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
    TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
    TEXTUREFLAGS_SINGLECOPY = 0x00040000,
    TEXTUREFLAGS_PRE_SRGB = 0x00080000,
    TEXTUREFLAGS_UNUSED_00100000 = 0x00100000,
    TEXTUREFLAGS_UNUSED_00200000 = 0x00200000,
    TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,
    TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,
    TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,
    TEXTUREFLAGS_CLAMPU = 0x02000000,
    TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,
    TEXTUREFLAGS_SSBUMP = 0x08000000,
    TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,
    TEXTUREFLAGS_BORDER = 0x20000000,
    TEXTUREFLAGS_UNUSED_40000000 = 0x40000000,
    TEXTUREFLAGS_UNUSED_80000000 = 0x80000000
};

enum StandardLightmap_t
{
    MATERIAL_SYSTEM_LIGHTMAP_PAGE_WHITE = -1,
    MATERIAL_SYSTEM_LIGHTMAP_PAGE_WHITE_BUMP = -2,
    MATERIAL_SYSTEM_LIGHTMAP_PAGE_USER_DEFINED = -3
};


struct MaterialSystem_SortInfo_t
{
    IMaterial* material;
    int			lightmapPageID;
};

enum MaterialThreadMode_t
{
    MATERIAL_SINGLE_THREADED,
    MATERIAL_QUEUED_SINGLE_THREADED,
    MATERIAL_QUEUED_THREADED
};

enum MaterialContextType_t
{
    MATERIAL_HARDWARE_CONTEXT,
    MATERIAL_QUEUED_CONTEXT,
    MATERIAL_NULL_CONTEXT
};

enum
{
    MATERIAL_ADAPTER_NAME_LENGTH = 512
};

struct MaterialTextureInfo_t
{
    int iExcludeInformation;
};

struct ApplicationPerformanceCountersInfo_t
{
    float msMain;
    float msMST;
    float msGPU;
    float msFlip;
    float msTotal;
};

struct ApplicationInstantCountersInfo_t
{
    uint32_t m_nCpuActivityMask;
    uint32_t m_nDeferredWordsAllocated;
};
struct MaterialAdapterInfo_t
{
    char m_pDriverName[MATERIAL_ADAPTER_NAME_LENGTH];
    unsigned int m_VendorID;
    unsigned int m_DeviceID;
    unsigned int m_SubSysID;
    unsigned int m_Revision;
    int m_nDXSupportLevel;			// This is the *preferred* dx support level
    int m_nMinDXSupportLevel;
    int m_nMaxDXSupportLevel;
    unsigned int m_nDriverVersionHigh;
    unsigned int m_nDriverVersionLow;
};

struct MaterialVideoMode_t
{
    int m_Width;			// if width and height are 0 and you select 
    int m_Height;			// windowed mode, it'll use the window size
    ImageFormat m_Format;	// use ImageFormats (ignored for windowed mode)
    int m_RefreshRate;		// 0 == default (ignored for windowed mode)
};
enum HDRType_t
{
    HDR_TYPE_NONE,
    HDR_TYPE_INTEGER,
    HDR_TYPE_FLOAT,
};

enum RestoreChangeFlags_t
{
    MATERIAL_RESTORE_VERTEX_FORMAT_CHANGED = 0x1,
    MATERIAL_RESTORE_RELEASE_MANAGED_RESOURCES = 0x2,
};

enum RenderTargetSizeMode_t
{
    RT_SIZE_NO_CHANGE = 0,
    RT_SIZE_DEFAULT = 1,
    RT_SIZE_PICMIP = 2,
    RT_SIZE_HDR = 3,
    RT_SIZE_FULL_FRAME_BUFFER = 4,
    RT_SIZE_OFFSCREEN = 5,
    RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6
};

enum MaterialRenderTargetDepth_t
{
    MATERIAL_RT_DEPTH_SHARED = 0x0,
    MATERIAL_RT_DEPTH_SEPARATE = 0x1,
    MATERIAL_RT_DEPTH_NONE = 0x2,
    MATERIAL_RT_DEPTH_ONLY = 0x3,
};

class IVTFTexture;

class ICompositeTexture
{
public:
    virtual bool IsReady() const = 0;
    virtual bool GenerationComplete() const = 0;
    virtual IVTFTexture* GetResultVTF() = 0;
    virtual	const char* GetName() = 0;
};

class ICustomMaterial
{
public:
    virtual void func() = 0;
    virtual void func2() = 0;
    virtual IMaterial* GetMaterial() = 0;
    virtual ICompositeTexture* GetTexture(int nIndex) = 0;
    virtual bool IsValid() const = 0;
    virtual const char* GetBaseMaterialName(void) = 0;
};


class CCustomMaterialOwner
{
public:
    virtual ~CCustomMaterialOwner() { }
    virtual void SetCustomMaterial(ICustomMaterial* pCustomMaterial, int nIndex = 0) = 0;	// either replaces and existing material (releasing the old one), or adds one to the vector
    virtual void OnCustomMaterialsUpdated() {}
    virtual void DuplicateCustomMaterialsToOther(CCustomMaterialOwner* pOther) const = 0;

public:
    CUtlVector<ICustomMaterial*> vecCustomMaterials;
}; // Size: 0x0014


class IRenderToRTHelperObject
{
public:
    virtual void Draw(const matrix3x4_t& matRootToWorld) = 0;
    virtual bool BoundingSphere(Vector& vecCenter, float& flRadius) = 0;
    virtual ITexture* GetEnvCubeMap() = 0;
};

struct MDLSquenceLayer_t
{
    int		nSequenceIndex;
    float	flWeight;
};

struct SCompositeTextureInfo;

class ICustomMaterialManager
{
public:
    virtual bool Process() = 0;

    virtual ICustomMaterial* GetOrCreateCustomMaterial(KeyValues* pKeyValues, const CUtlVector< SCompositeTextureInfo >& vecTextureInfos, bool bIgnorePicMip = false) = 0;

    virtual void func() = 0;
    virtual int DebugGetNumActiveCustomMaterials() = 0;
    virtual bool GetVMTKeyValues(const char* pszVMTName, KeyValues** ppVMTKeyValues) = 0;
};


class CMaterialReference
{
public:
    // constructor, destructor
    CMaterialReference(char const* pMaterialName = 0, const char* pTextureGroupName = 0, bool bComplain = true);
    ~CMaterialReference();

    // Attach to a material
    void Init(const char* pMaterialName, const char* pTextureGroupName, bool bComplain = true);
    void Init(const char* pMaterialName, KeyValues* pVMTKeyValues);
    void Init(IMaterial* pMaterial);
    void Init(CMaterialReference& ref);
    void Init(const char* pMaterialName, const char* pTextureGroupName, KeyValues* pVMTKeyValues);

    // Detach from a material
    void Shutdown(bool bDeleteIfUnreferenced = false);
    bool IsValid() { return m_pMaterial != 0; }

    // Automatic casts to IMaterial
    operator IMaterial* () { return m_pMaterial; }
    operator const IMaterial* () const { return m_pMaterial; }
    IMaterial* operator->() { return m_pMaterial; }

    // Assignment operator
    const CMaterialReference& operator=(const CMaterialReference& ref);


public:
    CMaterialReference(CMaterialReference& ref) { }

    IMaterial* m_pMaterial;
};


class CCustomMaterial : public ICustomMaterial
{
public:
    virtual void func() = 0;
    virtual void func2() = 0;
    virtual IMaterial* GetMaterial() = 0;
    virtual ICompositeTexture* GetTexture(int nIndex) = 0;
    virtual bool IsValid() const = 0;
    virtual const char* GetBaseMaterialName(void) = 0;
public:
    CMaterialReference m_Material;
    CUtlVector< void* > m_pTextures;
    bool m_bValid;
    int m_nModelMaterialIndex;
    KeyValues* m_pVMTKeyValues;
    const char* m_szBaseMaterialName;

    static int m_nMaterialCount;
};


class CCustomMaterialManager : public ICustomMaterialManager
{
public:
    virtual ~CCustomMaterialManager();

    virtual bool Process() = 0;
    virtual ICustomMaterial* GetOrCreateCustomMaterial(KeyValues* pKeyValues, const CUtlVector< SCompositeTextureInfo >& vecTextureInfos, bool bIgnorePicMip = false) = 0;
    virtual void func() = 0;
    virtual int DebugGetNumActiveCustomMaterials() = 0;
    virtual bool GetVMTKeyValues(const char* pszVMTName, KeyValues** ppVMTKeyValues) = 0;
public:
    CUtlVector< CCustomMaterial* > m_pCustomMaterials;
    void* m_mapVMTKeyValues;
};


typedef void(*MaterialBufferReleaseFunc_t)(int nChangeFlags);	// see RestoreChangeFlags_t
typedef void(*MaterialBufferRestoreFunc_t)(int nChangeFlags);	// see RestoreChangeFlags_t
typedef void(*ModeChangeCallbackFunc_t)(void);
typedef void(*EndFrameCleanupFunc_t)(void);
typedef bool(*EndFramePriorToNextContextFunc_t)(void);
typedef void(*OnLevelShutdownFunc_t)(void* pUserData);

typedef unsigned short MaterialHandle_t;
DECLARE_POINTER_HANDLE(MaterialLock_t);
#define CREATERENDERTARGETFLAGS_HDR				0x00000001
class IMaterialSystem : public IAppSystem
{
private:
    template <typename T, typename ... args_t>
    constexpr T CallVFunc(void* thisptr, std::size_t nIndex, args_t... argList)
    {
        using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
        return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
    }
public:
    auto GetBackBufferFormat() -> ImageFormat {
        using Fn = ImageFormat(__thiscall*)(void*);
        return CallVFunction< Fn >(this, 36)(this);
    }

    auto CreateMaterial(const char* name, c_key_values* key) -> IMaterial* {
        using Fn = IMaterial * (__thiscall*)(void*, const char*, c_key_values*);
        return CallVFunction< Fn >(this, 83)(this, name, key);
    }

    auto FindMaterial(const char* name, const char* texture_group_name = nullptr, bool complain = true, const char* complain_prefix = nullptr) -> IMaterial* {
        using Fn = IMaterial * (__thiscall*)(void*, const char*, const char*, bool, const char*);
        return CallVFunction< Fn >(this, 84)(this, name, texture_group_name, complain, complain_prefix);
    }

    auto FirstMaterial() -> MaterialHandle_t {
        using Fn = MaterialHandle_t(__thiscall*)(void*);
        return CallVFunction< Fn >(this, 86)(this);
    }

    auto NextMaterial(MaterialHandle_t h) -> MaterialHandle_t {
        using Fn = MaterialHandle_t(__thiscall*)(void*, MaterialHandle_t);
        return CallVFunction< Fn >(this, 87)(this, h);
    }

    auto InvalidMaterial() -> MaterialHandle_t {
        using Fn = MaterialHandle_t(__thiscall*)(void*);
        return CallVFunction< Fn >(this, 88)(this);
    }

    auto GetMaterial(MaterialHandle_t h) -> IMaterial* {
        using Fn = IMaterial * (__thiscall*)(void*, MaterialHandle_t);
        return CallVFunction< Fn >(this, 89)(this, h);
    }

    int get_current_adapter() {
        using fn = int(__thiscall*)(IMaterialSystem*);
        return (*(fn**)this)[25](this);
    }
    void get_display_adapter_info(int adapter, MaterialAdapterInfo_t* info) {
        using fn = void(__thiscall*)(IMaterialSystem*, int, MaterialAdapterInfo_t*);
        return (*(fn**)this)[26](this, adapter, info);
    }

    bool& gameStarted()
    {
        return *(bool*)(uint32_t(this) + 0x2C68);
    }

    auto BeginRenderTargetAllocation() -> void {
        using Fn = void(__thiscall*)(void*);
        return CallVFunction< Fn >(this, 94)(this);
    }

    auto EndRenderTargetAllocation() -> void {
        using Fn = void(__thiscall*)(void*);
        return CallVFunction< Fn >(this, 95)(this);
    }

    auto CreateNamedRenderTargetTextureEx(const char* name, int w, int h, RenderTargetSizeMode_t sizeMode, ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags) -> ITexture* {
        using Fn = ITexture * (__thiscall*)(void*, const char*, int, int, RenderTargetSizeMode_t, ImageFormat, MaterialRenderTargetDepth_t, unsigned int, unsigned int);
        return CallVFunction< Fn >(this, 97)(this, name, w, h, sizeMode, format, depth, textureFlags, renderTargetFlags);
    }

    auto GetRenderContext() -> IMatRenderContext* {
        using Fn = IMatRenderContext * (__thiscall*)(void*);
        return CallVFunction< Fn >(this, 115)(this);
    }

    auto FinishRenderTargetAllocation() -> void {
        using Fn = void(__thiscall*)(void*);
        return CallVFunction< Fn >(this, 136)(this);
    }

    ITexture* FindTexture(char const* szTextureName, const char* szTextureGroupName, bool bComplain = true, int nAdditionalCreationFlags = 0)
    {
        return CallVFunc<ITexture*>(this, 91, szTextureName, szTextureGroupName, bComplain, nAdditionalCreationFlags);
    }

    ITexture* createFullFrameRenderTarget(const char* name) {
        return CreateNamedRenderTargetTextureEx(
            name, 1, 1, RT_SIZE_FULL_FRAME_BUFFER, GetBackBufferFormat(),
            MATERIAL_RT_DEPTH_SHARED, TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
            0x00000001
        );
    }

    void forceBeginRenderTargetAllocation() {
        bool oldState = gameStarted();
        gameStarted() = false;         // Fooling the game that loading is not finished yet
        BeginRenderTargetAllocation();
        gameStarted() = oldState;
    }

    void forceEndRenderTargetAllocation() {
        bool oldState = gameStarted();
        gameStarted() = false;
        EndRenderTargetAllocation();
        gameStarted() = oldState;
    }

    ICustomMaterialManager* GetCustomMaterialManager()
    {
        using Fn = ICustomMaterialManager * (__thiscall*)(void*);
        return CallVFunction< Fn >(this, 152)(this);
    }

};



class IMatRenderContext : public IRefCounted
{
private:
    template <typename T, typename ... args_t>
    constexpr T CallVFunc(void* thisptr, std::size_t nIndex, args_t... argList)
    {
        using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
        return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
    }
public:
    void BeginRender()
    {
        CallVFunc<void>(this, 2);
    }

    void EndRender()
    {
        CallVFunc<void>(this, 3);
    }

    void BindLocalCubemap(ITexture* pTexture)
    {
        CallVFunc<void>(this, 5, pTexture);
    }

    void SetRenderTarget(ITexture* pTexture)
    {
        CallVFunc<void>(this, 6, pTexture);
    }

    ITexture* GetRenderTarget()
    {
        return CallVFunc<ITexture*>(this, 7);
    }

    void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false)
    {
        CallVFunc<void>(this, 12, bClearColor, bClearDepth, bClearStencil);
    }

    void SetLights(int nCount, const LightDesc_t* pLights)
    {
        CallVFunc<void>(this, 17, nCount, pLights);
    }

    void SetAmbientLightCube(Vector4D vecCube[6])
    {
        CallVFunc<void>(this, 18, vecCube);
    }

    void SetIntRenderingParameter(int a1, int a2)
    {
        return CallVFunction < void(__thiscall*)(void*, int, int) >(this, 126)(this, a1, a2);
    }

    void Viewport(int x, int y, int iWidth, int iHeight)
    {
        CallVFunc<void>(this, 40, x, y, iWidth, iHeight);
    }

    void GetViewport(int& x, int& y, int& iWidth, int& iHeight)
    {
        CallVFunc<void, int&, int&, int&, int&>(this, 41, x, y, iWidth, iHeight);
    }

    void ClearColor3ub(unsigned char r, unsigned char g, unsigned char b)
    {
        CallVFunc<void>(this, 78, r, g, b);
    }

    void ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        CallVFunc<void>(this, 79, r, g, b, a);
    }

    void DrawScreenSpaceRectangle(IMaterial* pMaterial, int iDestX, int iDestY, int iWidth, int iHeight, float flTextureX0, float flTextureY0, float flTextureX1, float flTextureY1, int iTextureWidth, int iTextureHeight, void* pClientRenderable = nullptr, int nXDice = 1, int nYDice = 1)
    {
        CallVFunc<void>(this, 114, pMaterial, iDestX, iDestY, iWidth, iHeight, flTextureX0, flTextureY0, flTextureX1, flTextureY1, iTextureWidth, iTextureHeight, pClientRenderable, nXDice, nYDice);
    }

    void PushRenderTargetAndViewport()
    {
        CallVFunc<void>(this, 119);
    }

    void PopRenderTargetAndViewport()
    {
        CallVFunc<void>(this, 120);
    }

    void SetLightingOrigin(/*Vector vecLightingOrigin*/float x, float y, float z)
    {
        CallVFunc<void>(this, 158, x, y, z);
    }
};

template <class T>
class CBaseAutoPtr
{
public:
    CBaseAutoPtr() :
        pObject(nullptr) { }

    CBaseAutoPtr(T* pObject) :
        pObject(pObject) { }

    operator const void* () const
    {
        return pObject;
    }

    operator void* () const
    {
        return pObject;
    }

    operator const T* () const
    {
        return pObject;
    }

    operator const T* ()
    {
        return pObject;
    }

    operator T* ()
    {
        return pObject;
    }

    int	operator=(int i)
    {
        pObject = nullptr;
        return 0;
    }

    T* operator=(T* pSecondObject)
    {
        pObject = pSecondObject;
        return pSecondObject;
    }

    bool operator!() const
    {
        return (!pObject);
    }

    bool operator==(const void* pSecondObject) const
    {
        return (pObject == pSecondObject);
    }

    bool operator!=(const void* pSecondObject) const
    {
        return (pObject != pSecondObject);
    }

    bool operator==(T* pSecondObject) const
    {
        return operator==(static_cast<void*>(pSecondObject));
    }

    bool operator!=(T* pSecondObject) const
    {
        return operator!=(static_cast<void*>(pSecondObject));
    }

    bool operator==(const CBaseAutoPtr<T>& pSecondPtr) const
    {
        return operator==(static_cast<const void*>(pSecondPtr));
    }

    bool operator!=(const CBaseAutoPtr<T>& pSecondPtr) const
    {
        return operator!=(static_cast<const void*>(pSecondPtr));
    }

    T* operator->()
    {
        return pObject;
    }

    T& operator*()
    {
        return *pObject;
    }

    T** operator&()
    {
        return &pObject;
    }

    const T* operator->() const
    {
        return pObject;
    }

    const T& operator*() const
    {
        return *pObject;
    }

    T* const* operator&() const
    {
        return &pObject;
    }

    CBaseAutoPtr(const CBaseAutoPtr<T>& pSecondPtr) :
        pObject(pSecondPtr.pObject) { }

    void operator=(const CBaseAutoPtr<T>& pSecondPtr)
    {
        pObject = pSecondPtr.pObject;
    }

    T* pObject;
};

//---------------------------------------------------------

template <class T>
class CRefPtr : public CBaseAutoPtr<T>
{
    typedef CBaseAutoPtr<T> CBaseClass;
public:
    CRefPtr() { }

    CRefPtr(T* pInit)
        : CBaseClass(pInit) { }

    CRefPtr(const CRefPtr<T>& pRefPtr)
        : CBaseClass(pRefPtr) { }

    ~CRefPtr()
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->Release();
    }

    void operator=(const CRefPtr<T>& pSecondRefPtr)
    {
        CBaseClass::operator=(pSecondRefPtr);
    }

    int operator=(int i)
    {
        return CBaseClass::operator=(i);
    }

    T* operator=(T* pSecond)
    {
        return CBaseClass::operator=(pSecond);
    }

    operator bool() const
    {
        return !CBaseClass::operator!();
    }

    operator bool()
    {
        return !CBaseClass::operator!();
    }

    void SafeRelease()
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->Release();

        CBaseClass::pObject = nullptr;
    }

    void AssignAddReference(T* pFrom)
    {
        if (pFrom != nullptr)
            pFrom->AddReference();

        SafeRelease();
        CBaseClass::pObject = pFrom;
    }

    void AddReferenceAssignTo(T*& pTo)
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->AddReference();

        SafeRelease(pTo);
        pTo = CBaseClass::pObject;
    }
};


class CMatRenderContextPtr : public CRefPtr<IMatRenderContext>
{
    typedef CRefPtr<IMatRenderContext> CBaseClass;
public:
    CMatRenderContextPtr() = default;

    CMatRenderContextPtr(IMatRenderContext* pInit) : CBaseClass(pInit)
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->BeginRender();
    }

    CMatRenderContextPtr(IMaterialSystem* pFrom) : CBaseClass(pFrom->GetRenderContext())
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->BeginRender();
    }

    ~CMatRenderContextPtr()
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->EndRender();
    }

    IMatRenderContext* operator=(IMatRenderContext* pSecondContext)
    {
        if (pSecondContext != nullptr)
            pSecondContext->BeginRender();

        return CBaseClass::operator=(pSecondContext);
    }

    void SafeRelease()
    {
        if (CBaseClass::pObject != nullptr)
            CBaseClass::pObject->EndRender();

        CBaseClass::SafeRelease();
    }

    void AssignAddReference(IMatRenderContext* pFrom)
    {
        if (CBaseClass::pObject)
            CBaseClass::pObject->EndRender();

        CBaseClass::AssignAddReference(pFrom);
        CBaseClass::pObject->BeginRender();
    }

    void GetFrom(IMaterialSystem* pFrom)
    {
        AssignAddReference(pFrom->GetRenderContext());
    }

private:
    CMatRenderContextPtr(const CMatRenderContextPtr& pRefPtr);
    void operator=(const CMatRenderContextPtr& pSecondRefPtr);
};