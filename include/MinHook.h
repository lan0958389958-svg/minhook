/*
 *  MinHook - 微型攔截 (Hook) （Hooking）函式庫 - 適用於 Windows x64/x86 平台  
 *  版權所有 (C) 2009-2017 Tsuda Kageyu. 保留所有權利。
 *  
 *
 * 
 *  原始碼或二進位檔案，不論修改、散佈與使用。
 *  符合以下條件均被允許：
 *
 *   1. 原始碼散佈必須保留上述版權聲明、條件清單與免責聲明。
 *   2. 二進位散佈必須保留上述版權聲明、條件清單與免責聲明，並在文件或其他提供的材料中保留。 
 *   
 *  本軟體由版權持有人與貢獻者「按原樣」提供。    
 *  不附帶任何明示或暗示的保證，包括但不限於適售性或特定用途適用性的暗示保證。
 *  在任何情況下，版權持有人或貢獻者均不負責任何直接、間接、偶然、特殊、懲罰性或後續損害，
 *  包括但不限於購買替代商品或服務、使用損失、資料遺失或利潤損失、或業務中斷，
 *  不論是基於合約、嚴格責任或侵權行為，包括疏忽或其他原因，即使已被告知可能發生此類損害。
 * 
 *  
 *  
 *  
 *  
 * 
 *  
 *  
 */

#pragma once

#if !(defined _M_IX86) && !(defined _M_X64) && !(defined __i386__) && !(defined __x86_64__)
    #error MinHook 僅支援 x86 與 x64 系統。
#endif

#include <windows.h>

// MinHook 錯誤碼。
typedef enum MH_STATUS
{
    // 未知錯誤。不應返回。
    MH_UNKNOWN = -1,

    // 成功。
    MH_OK = 0,

    // MinHook 已初始化。
    MH_ERROR_ALREADY_INITIALIZED,

    // MinHook 尚未初始化，或已解除初始化。
    MH_ERROR_NOT_INITIALIZED,

    // 指定目標函式的攔截 (Hook) 已建立。
    MH_ERROR_ALREADY_CREATED,

    // 指定目標函式的攔截 (Hook) 未建立。
    MH_ERROR_NOT_CREATED,

    // 指定目標函式的攔截 (Hook) 已啟用。
    MH_ERROR_ENABLED,

    // 指定目標函式的攔截 (Hook) 未啟用/已停用。
    MH_ERROR_DISABLED,

    // 指定指標無效: 指向未配置或不可執行區域。
    MH_ERROR_NOT_EXECUTABLE,

    // 指定目標函式無法攔截 (Hook) 。
    MH_ERROR_UNSUPPORTED_FUNCTION,

    // 記憶體配置失敗。
    MH_ERROR_MEMORY_ALLOC,

    // 記憶體保護設定失敗。
    MH_ERROR_MEMORY_PROTECT,

    // 指定模組未載入。
    MH_ERROR_MODULE_NOT_FOUND,

    // 指定函式未找到。
    MH_ERROR_FUNCTION_NOT_FOUND
}
MH_STATUS;

// 
// 可作為 MH_EnableHook、MH_DisableHook、MH_QueueEnableHook 或 MH_QueueDisableHook 的參數。
#define MH_ALL_HOOKS NULL

#ifdef __cplusplus
extern "C" {
#endif

    // 初始化 MinHook 函式庫。
    // 只在程式開始時「調用一次」。
    MH_STATUS WINAPI MH_Initialize(VOID);

    // 解除初始化 MinHook 函式庫。
    // 只在程式結束時「調用一次」。
    MH_STATUS WINAPI MH_Uninitialize(VOID);

    // 建立指定目標函式的攔截 (Hook) 。
    // 初始為停用狀態。
    // 參數：
    //   pTarget     [in]  指向目標函式的指標。
    //                     將被 detour 函式覆蓋。
    //   pDetour     [in]  指向 detour 函式的指標。
    //                     會取代目標函式。
    //   ppOriginal  [out] 指向 trampoline 函式的指標。
    //                     用於呼叫原始目標函式。
    //                     此參數可為 NULL。
    MH_STATUS WINAPI MH_CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID *ppOriginal);

    // 建立指定 API 函式的攔截 (Hook) 。
    // 初始為停用狀態。
    // 參數：
    //   pszModule   [in]  已載入模組名稱的指標。
    //                     該模組包含目標函式。
    //   pszProcName [in]  目標函式名稱的指標。
    //                     將被 detour 函式覆蓋。
    //   pDetour     [in]  指向 detour 函式的指標。
    //   ppOriginal  [out] 指向 trampoline 函式的指標。
    //                     用於呼叫原始目標函式。
    //                     此參數可為 NULL。
    MH_STATUS WINAPI MH_CreateHookApi(
        LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal);

    // 建立指定 API 函式的攔截 (Hook) 。
    // 初始為停用狀態。
    // 參數：
    //   pszModule   [in]  已載入模組名稱的指標。
    //                     該模組包含目標函式。
    //   pszProcName [in]  目標函式名稱的指標。
    //                     將被 detour 函式覆蓋。
    //   pDetour     [in]  指向 detour 函式的指標。
    //   ppOriginal  [out] 指向 trampoline 函式的指標。
    //                     用於呼叫原始目標函式。
    //                     此參數可為 NULL。
    //   ppTarget    [out] 指向目標函式的指標。
    //                     可與其他函式搭配使用。
    //                     此參數可為 NULL。
    MH_STATUS WINAPI MH_CreateHookApiEx(
        LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal, LPVOID *ppTarget);

    // 移除已建立的攔截 (Hook) 。
    // 參數：
    //   pTarget [in] 指向目標函式的指標。
    MH_STATUS WINAPI MH_RemoveHook(LPVOID pTarget);

    // 啟用已建立的攔截 (Hook) 。
    // 參數：
    //   pTarget [in] 指向目標函式的指標。
    //                若此參數為 MH_ALL_HOOKS，
    //                則一次啟用所有攔截 (Hook) 。
    MH_STATUS WINAPI MH_EnableHook(LPVOID pTarget);

    // 停用已建立的攔截 (Hook) 。
    // 參數：
    //   pTarget [in] 指向目標函式的指標。
    //                若此參數為 MH_ALL_HOOKS，
    //                則一次停用所有攔截 (Hook) 。
    MH_STATUS WINAPI MH_DisableHook(LPVOID pTarget);

    // 將已建立的攔截 (Hook) 加入佇列。
    // 等待啟用。
    // 參數：
    //   pTarget [in] 指向目標函式的指標。
    //                若此參數為 MH_ALL_HOOKS，
    //                則一次佇列所有攔截 (Hook) 。
    MH_STATUS WINAPI MH_QueueEnableHook(LPVOID pTarget);

    // 將已建立的攔截 (Hook) 加入佇列。
    // 等待停用。
    // 參數：
    //   pTarget [in] 指向目標函式的指標。
    //                若此參數為 MH_ALL_HOOKS，
    //                則一次佇列所有攔截 (Hook) 。
    MH_STATUS WINAPI MH_QueueDisableHook(LPVOID pTarget);

    // 一次套用所有佇列中的變更。
    MH_STATUS WINAPI MH_ApplyQueued(VOID);

    // 將 MH_STATUS 狀態碼轉換為字串名稱。
    const char *WINAPI MH_StatusToString(MH_STATUS status);

#ifdef __cplusplus
}
#endif
