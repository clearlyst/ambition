#pragma once

#include <cstdint>

#include "..//math/Vector.hpp"
#include "..//math/Vector4D.hpp"
#include "..//misc/Studio.hpp"

#include "..//misc/vfunc.hpp"

#include "IVModelRender.hpp"

class LightDesc_t;
class lightpos_t;

enum LightType_t {
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

class LightDesc_t {
public:
	LightType_t m_Type;                 //0x0000
	Vector m_Color;                     //0x0004
	Vector m_Position;                  //0x0010
	Vector m_Direction;                 //0x001C
	float m_Range;                      //0x0028
	float m_Falloff;                    //0x002C
	float m_Attenuation0;               //0x0030
	float m_Attenuation1;               //0x0034
	float m_Attenuation2;               //0x0038
	float m_Theta;                      //0x003C
	float m_Phi;                        //0x0040
	float m_ThetaDot;                   //0x0044
	float m_PhiDot;                     //0x0048
	float m_OneOverThetaDotMinusPhiDot; //0x004C
	__int32 m_Flags;                    //0x0050
	float m_RangeSquared;               //0x0054

}; //Size=0x0058

class lightpos_t {
public:
	Vector delta;  //0x0000
	float falloff; //0x000C
	float dot;     //0x0010

}; //Size=0x0014

struct MaterialLightingState_t {
	Vector m_vecAmbientCube[6]; // ambient, and lights that aren't in locallight[]
	Vector m_vecLightingOrigin; // The position from which lighting state was computed
	int m_nLocalLightCount;
	LightDesc_t m_pLocalLightDesc[4];
};

struct DrawModelInfo_t {
	studiohdr_t* m_pStudioHdr;
	studiohwdata_t* m_pHardwareData;
	StudioDecalHandle_t m_Decals;
	int m_Skin;
	int m_Body;
	int m_HitboxSet;
	IClientRenderable* m_pClientEntity;
	int m_Lod;
	ColorMeshInfo_t* m_pColorMeshes;
	bool m_bStaticLighting;
	MaterialLightingState_t m_LightingState;
};

class C_MemAlloc
{
public:
	virtual void* Alloc(size_t nSize) = 0;
	virtual void* Realloc(void* pMem, size_t nSize) = 0;
	virtual void  Free(void* pMem) = 0;
	virtual void* Expand_NoLongerSupported(void* pMem, size_t nSize) = 0;
	virtual void* Alloc(size_t nSize, const char* pFileName, int nLine) = 0;
	virtual void* Realloc(void* pMem, size_t nSize, const char* pFileName, int nLine) = 0;
	virtual void  Free(void* pMem, const char* pFileName, int nLine) = 0;
	virtual void* Expand_NoLongerSupported(void* pMem, size_t nSize, const char* pFileName, int nLine) = 0;
	virtual size_t GetSize(void* pMem) = 0;
	virtual void PushAllocDbgInfo(const char* pFileName, int nLine) = 0;
	virtual void PopAllocDbgInfo() = 0;
	virtual long CrtSetBreakAlloc(long lNewBreakAlloc) = 0;
	virtual	int CrtSetReportMode(int nReportType, int nReportMode) = 0;
	virtual int CrtIsValidHeapPointer(const void* pMem) = 0;
	virtual int CrtIsValidPointer(const void* pMem, unsigned int size, int access) = 0;
	virtual int CrtCheckMemory(void) = 0;
	virtual int CrtSetDbgFlag(int nNewFlag) = 0;
	virtual void CrtMemCheckpoint(_CrtMemState* pState) = 0;
	virtual int heapchk() = 0;
	virtual void DumpStats() = 0;
	virtual void DumpStatsFileBase(char const* pchFileBase) = 0;
};

enum class OverrideType 
{
	Normal = 0,
	BuildShadows,
	DepthWrite,
	CustomMaterial,
	SSaoDepthWrite
};

/*class C_StudioRender
{
	std::byte pad_0[592];
	IMaterial* materialOverride;
	std::byte pad_1[12];
	OverrideType overrideType;
private:
	template <typename T, typename ... args_t>
	constexpr T CallVFunc(void* thisptr, std::size_t nIndex, args_t... argList)
	{
		using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
	}
public:
	void SetAmbientLightColors(const Vector4D* pAmbientOnlyColors)
	{
		CallVFunc<void>(this, 20, pAmbientOnlyColors);
	}
	void SetAmbientLightColors(const Vector* pAmbientOnlyColors)
	{
		CallVFunc<void>(this, 21, pAmbientOnlyColors);
	}
	void SetLocalLights(int nLights, const LightDesc_t* pLights)
	{
		CallVFunc<void>(this, 22, nLights, pLights);
	}

	void SetColorModulation(float const* arrColor)
	{
		CallVFunc<void>(this, 27, arrColor);
	}

	void SetAlphaModulation(float flAlpha)
	{
		CallVFunc<void>(this, 28, flAlpha);
	}

	void ForcedMaterialOverride(IMaterial* pMaterial, OverrideType_t nOverrideType = 0, int nOverrides = 0)
	{
		CallVFunc<void>(this, 33, pMaterial, nOverrideType, nOverrides);
	}

	bool IsForcedMaterialOverride() 
	{
		if (!materialOverride)
			return overrideType == OverrideType::DepthWrite || overrideType == OverrideType::SSaoDepthWrite;
		return std::string_view{ materialOverride->GetName() }._Starts_with("dev/glow");
	}
};*/

class C_StudioRender {
public:
	void* vtable;
	float fEyeShiftX;                      //0x0004
	float fEyeShiftY;                      //0x0008
	float fEyeShiftZ;                      //0x000C
	float fEyeSize;                        //0x0010
	float fEyeGlintPixelWidthLODThreshold; //0x0014
	__int32 maxDecalsPerModel;             //0x0018
	__int32 drawEntities;                  //0x001C
	__int32 skin;                          //0x0020
	__int32 fullbright;                    //0x0024
	bool bEyeMove : 1;                     // look around
	bool bSoftwareSkin : 1;
	bool bNoHardware : 1;
	bool bNoSoftware : 1;
	bool bTeeth : 1;
	bool bEyes : 1;
	bool bFlex : 1;
	bool bWireframe : 1;
	bool bDrawNormals : 1;
	bool bDrawTangentFrame : 1;
	bool bDrawZBufferedWireframe : 1;
	bool bSoftwareLighting : 1;
	bool bShowEnvCubemapOnly : 1;
	bool bWireframeDecals : 1;
	int m_nReserved[5];
	Vector m_ViewTarget;           //0x0040
	Vector m_ViewOrigin;           //0x004C
	Vector m_ViewRight;            //0x0058
	Vector m_ViewUp;               //0x0064
	Vector m_ViewPlaneNormal;      //0x0070
	Vector4D m_LightBoxColors[6];  //0x00CC
	LightDesc_t m_LocalLights[4];  //0x01E4
	__int32 m_NumLocalLights;      //0x023C
	float m_ColorMod[3];           //0x0248
	float m_AlphaMod;              //0x024C
	IMaterial* m_pForcedMaterial;  //0x0250
	__int32 m_nForcedMaterialType; //0x0254
	char pad_0x0258[0xC];          //0x0258
	__int32 unkhandle1;            //0x0264
	__int32 unkhandle2;            //0x0268
	__int32 unkhandle3;            //0x026C
	__int32 unkhandle4;            //0x0270
	char pad_0x0274[0x4];          //0x0274
	lightpos_t m_pLightPos[16];    //0x0278
private:
	template <typename T, typename ... args_t>
	constexpr T CallVFunc(void* thisptr, std::size_t nIndex, args_t... argList)
	{
		using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
	}
public:
	void SetAmbientLightColors(const Vector4D* pAmbientOnlyColors)
	{
		CallVFunc<void>(this, 20, pAmbientOnlyColors);
	}
	void SetAmbientLightColors(const Vector* pAmbientOnlyColors)
	{
		CallVFunc<void>(this, 21, pAmbientOnlyColors);
	}
	void SetLocalLights(int nLights, const LightDesc_t* pLights)
	{
		CallVFunc<void>(this, 22, nLights, pLights);
	}

	void SetColorModulation(float const* arrColor)
	{
		CallVFunc<void>(this, 27, arrColor);
	}

	void SetAlphaModulation(float flAlpha)
	{
		CallVFunc<void>(this, 28, flAlpha);
	}

	inline void ForcedMaterialOverride(IMaterial* material, OverrideType_t nOverrideType = 0) {
		m_pForcedMaterial = material;
		m_nForcedMaterialType = nOverrideType;
	}

	inline bool IsForcedMaterialOverride()
	{
		return m_pForcedMaterial;
	}
};

static_assert(FIELD_OFFSET(C_StudioRender, m_pForcedMaterial) == 0x250, "Wrong m_pForcedMaterial offset");