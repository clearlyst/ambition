#pragma once

#include "IAppSystem.hpp"
#include "../Misc/Studio.hpp"
#include "../misc/Studio.hpp"

enum MDLCacheDataType_t
{
	// Callbacks to Get called when data is loaded or unloaded for these:
	MDLCACHE_STUDIOHDR = 0,
	MDLCACHE_STUDIOHWDATA,
	MDLCACHE_VCOLLIDE,

	// Callbacks NOT called when data is loaded or unloaded for these:
	MDLCACHE_ANIMBLOCK,
	MDLCACHE_VIRTUALMODEL,
	MDLCACHE_VERTEXES,
	MDLCACHE_DECODEDANIMBLOCK
};

enum MDLCacheFlush_t
{
	MDLCACHE_FLUSH_STUDIOHDR = 0x01,
	MDLCACHE_FLUSH_STUDIOHWDATA = 0x02,
	MDLCACHE_FLUSH_VCOLLIDE = 0x04,
	MDLCACHE_FLUSH_ANIMBLOCK = 0x08,
	MDLCACHE_FLUSH_VIRTUALMODEL = 0x10,
	MDLCACHE_FLUSH_AUTOPLAY = 0x20,
	MDLCACHE_FLUSH_VERTEXES = 0x40,

	MDLCACHE_FLUSH_IGNORELOCK = 0x80000000,
	MDLCACHE_FLUSH_ALL = 0xFFFFFFFF
};

class IMDLCacheNotify
{
public:
	virtual void OnDataLoaded(MDLCacheDataType_t type, MDLHandle_t handle) = 0;
	virtual void OnDataUnloaded(MDLCacheDataType_t type, MDLHandle_t handle) = 0;
};

class IMDLCache : public IAppSystem
{
public:
	virtual void SetCacheNotify(IMDLCacheNotify* pNotify) = 0;
	virtual MDLHandle_t FindMDL(const char* szMDLRelativePath) = 0;
	virtual int AddReference(MDLHandle_t hModel) = 0;
	virtual int Release(MDLHandle_t hModel) = 0;
	virtual int GetReference(MDLHandle_t hModel) = 0;
	virtual studiohdr_t* GetStudioHdr(MDLHandle_t hModel) = 0;
	virtual studiohwdata_t* GetHardwareData(MDLHandle_t hModel) = 0;
	virtual vcollide_t* GetVCollide(MDLHandle_t hModel) = 0;
	virtual vcollide_t* GetVCollide(MDLHandle_t hModel, float flScale) = 0;
	virtual unsigned char* GetAnimBlock(MDLHandle_t hModel, int nBlock, bool bPreloadIfMissing) = 0;
	virtual bool HasAnimBlockBeenPreloaded(MDLHandle_t hModel, int nBlock) = 0;
	virtual virtualmodel_t* GetVirtualModel(MDLHandle_t hModel) = 0;
	virtual int GetAutoplayList(MDLHandle_t hModel, unsigned short** pOut) = 0;
	virtual vertexFileHeader_t* GetVertexData(MDLHandle_t hModel) = 0;
	virtual void TouchAllData(MDLHandle_t hModel) = 0;
	virtual void SetUserData(MDLHandle_t hModel, void* pData) = 0;
	virtual void* GetUserData(MDLHandle_t hModel) = 0;
	virtual bool IsErrorModel(MDLHandle_t hModel) = 0;
	virtual bool IsOverBudget(MDLHandle_t hModel) = 0;
	virtual void Flush(MDLCacheFlush_t nFlushFlags = MDLCACHE_FLUSH_ALL) = 0;
	virtual void Flush(MDLHandle_t hModel, MDLCacheFlush_t nFlushFlags = MDLCACHE_FLUSH_ALL) = 0;
	virtual const char* GetModelName(MDLHandle_t hModel) = 0;
	virtual void* GetCacheSection(MDLCacheDataType_t nType) = 0;
	virtual virtualmodel_t* GetVirtualModelFast(const studiohdr_t* pStudioHdr, MDLHandle_t hModel) = 0;
	virtual void BeginLock() = 0;
	virtual void EndLock() = 0;
	virtual int* GetFrameUnlockCounterPtrOLD() = 0;
	virtual void FinishPendingLoads() = 0;
	virtual vcollide_t* GetVCollideEx(MDLHandle_t hModel, bool bSynchronousLoad = true) = 0;
	virtual bool GetVCollideSize(MDLHandle_t hModel, int* pVCollideSize) = 0;
	virtual bool GetAsyncLoad(MDLCacheDataType_t nType) = 0;
	virtual bool SetAsyncLoad(MDLCacheDataType_t nType, bool bAsync) = 0;
	virtual void BeginMapLoad() = 0;
	virtual void EndMapLoad() = 0;
	virtual void MarkAsLoaded(MDLHandle_t hModel) = 0;
	virtual void InitPreloadData(bool bRebuild) = 0;
	virtual void ShutdownPreloadData() = 0;
	virtual bool IsDataLoaded(MDLHandle_t hModel, MDLCacheDataType_t nType) = 0;
	virtual int* GetFrameUnlockCounterPtr(MDLCacheDataType_t nType) = 0;
	virtual studiohdr_t* LockStudioHdr(MDLHandle_t hModel) = 0;
	virtual void UnlockStudioHdr(MDLHandle_t hModel) = 0;
	virtual bool PreloadModel(MDLHandle_t hModel) = 0;
	virtual void ResetErrorModelStatus(MDLHandle_t hModel) = 0;
	virtual void MarkFrame() = 0;
	virtual void BeginCoarseLock() = 0;
	virtual void EndCoarseLock() = 0;
	virtual void ReloadVCollide(MDLHandle_t hModel) = 0;
	virtual bool ReleaseAnimBlockAllocator() = 0;
	virtual bool RestoreHardwareData(MDLHandle_t hModel, void* pAsyncVTXControl, void* pAsyncVVDControl) = 0;
	virtual void DisableVCollideLoad() = 0;
	virtual void EnableVCollideLoad() = 0;
	virtual void DisableFileNotFoundWarnings() = 0;
	virtual void EnableFileNotFoundWarnings() = 0;
	virtual bool ProcessPendingHardwareRestore() = 0;
	virtual void UnloadQueuedHardwareData() = 0;
	virtual void DumpDictionaryState() = 0;
	virtual MDLHandle_t	CreateCombinedModel(const char* szModelName) = 0;
	virtual bool CreateCombinedModel(MDLHandle_t hModel) = 0;
	virtual bool SetCombineModels(MDLHandle_t hModel, const CUtlVector<void*>& vecModelsToCombine) = 0;
	virtual bool FinishCombinedModel(MDLHandle_t hModel, void* pFunction, void* pUserData = nullptr) = 0;
	virtual bool IsCombinedPlaceholder(MDLHandle_t hModel) = 0;
	virtual bool IsCombinedModel(MDLHandle_t hModel) = 0;
	virtual int GetNumCombinedSubModels(MDLHandle_t hModel) = 0;
	virtual void GetCombinedSubModelFilename(MDLHandle_t hModel, int nSubModelIndex, char* szResult, int nResultSize) = 0;
	virtual KeyValues* GetCombinedMaterialKV(MDLHandle_t hModel, int nAtlasGroup = 0) = 0;
	virtual void UpdateCombiner() = 0;
	virtual void* GetCombinedInternalAsset(int nAssetType, const char* szAssetID = nullptr, int* nSize = nullptr) = 0;
	virtual void SetCombinerFlags(unsigned int nFlags) = 0;
	virtual void ClearCombinerFlags(unsigned int nFlags) = 0;
	virtual void DebugCombinerInfo() = 0;
};
