[![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause)

這是 MinHook 的改版歷程及使用說明：

# ```MinHook```

微型攔截/接管 API 工具（```Hooking```）函式庫 - 適用於 ```Windows```  ```x86/x64``` 平台

[https://www.codeproject.com/articles/MinHook-The-Minimalistic-x-x-API-Hooking-Libra](https://www.codeproject.com/articles/MinHook-The-Minimalistic-x-x-API-Hooking-Libra)

### **改版歷程**

* **v1.3.4 - 2025年3月28日**  
  * 改進 **列舉/暫停** 執行緒時的錯誤處理。  
  * 支援 ```Visual Studio 2022```。  
  * 支援 ```CMake```。  
  * 修復 ```Clang``` 編譯問題。  
  * 修復 ```C++``` 程式碼編譯的問題。  
* **v1.3.3 - 2017年1月8日**  
  * 新增輔助函式 ```MH_CreateHookApiEx```。  
  * 支援 ```Visual Studio 2017 RC```。  
* **v1.3.2.1 - 2015年11月9日** (僅限 ```NuGet``` 套件)  
  * 修復對 ```Visual Studio 2015``` 支援不足的問題。  
* **v1.3.2 - 2015年11月1日**  
  * 支援 ```Visual Studio 2015```。  
  * 支援 ```MinGW```。  
* **v1.3.2-beta3 - 2015年7月21日** (僅限 ```NuGet``` 套件)  
  * 支援 ```MinGW``` (實驗性)。  
* **v1.3.2-beta2 - 2015年5月18日**  
  * 修復一些細微錯誤。  
  * 新增輔助函式 ```MH_StatusToString```。  
* **v1.3.2-beta - 2015年5月12日**  
  * 修復 x64 模式下可能發生的執行緒鎖死 (```Deadlock```)。  
  * 進一步減少記憶體佔用。  
  * 支援 ```Visual Studio 2015 RC``` (實驗性)。  
* **v1.3.1.1 - 2015年4月7日** (僅限 ```NuGet``` 套件)  
  * 支援 ```WDK``` 8.0 與 8.1。  
* **v1.3.1 - 2015年3月19日**  
  * 無重大變更。  
* **v1.3.1-beta - 2015年3月11日**  
  * 新增輔助函式 ```MH_CreateHookApi```。  
  * 修復某些工具回報的假性記憶體洩漏。  
  * 修復相容性下降的問題。  
* **v1.3 - 2014年9月13日**  
  * 無重大變更。  
* **v1.3-beta3 - 2014年7月31日**  
  * 修復小錯誤。  
  * 改進記憶體管理。  
* **v1.3-beta2 - 2014年7月21日**  
  * 將參數變更為對 ```Windows``` 更友善的型別 (由 ```void*``` 改為 ```LPVOID```)。  
  * 修復小錯誤。  
  * 重新整理原始碼檔案。  
  * 進一步減少記憶體佔用。  
* **v1.3-beta - 2014年7月17日**  
  * 以純 C 語言重寫，以減少記憶體佔用與使用量。  
  * 簡化程式碼架構，提升可讀性與維護性。  
  * 授權條款由 ```3-clause BSD``` 改為 ```2-clause BSD```。  
* **v1.2 - 2013年9月28日**  
  * 移除對 ```Boost``` 的依賴。  
  * 修復 ```GetRelativeBranchDestination``` 函式中的小錯誤。  
  * 新增 ```MH_RemoveHook``` 函式，用於移除由 ```MH_CreateHook``` 建立的掛鉤。  
  * 新增批量 **啟用/停用** 攔截的函式：```MH_QueueEnableHook```、```MH_QueueDisableHook```、```MH_ApplyQueued```。
   
    這是處理多個攔截的推薦方式，因為每次呼叫 ```MH_EnableHook``` 或 ```MH_DisableHook``` 都會暫停並恢復所有執行緒。
    
  * 當傳入 ```MH_ALL_HOOKS``` 參數時，```MH_EnableHook``` 和 ```MH_DisableHook``` 會啟用/停用所有已建立的攔截，這也是處理多個攔截的高效方式。  
  * 若目標函式太小而無法進行跳轉 (Jump) 修補，```MinHook``` 會嘗試在該函式上方放置跳轉。若依然失敗 ```MH_CreateHoo``` 則傳回 ```MH_ERROR_UNSUPPORTED_FUNCTION```。  
* **v1.1 - 2009年11月26日**  
  * 修改介面: 一次性操作中同時建立 ```Hook``` 與 ```Trampoline``` 函式，避免在 ```Trampoline``` 函式尚未建立前 ```Detour``` 函式被呼叫。
  * 將函式名稱從 ```MinHook_*``` 縮短為 ```MH_*``` 以便於使用。  
* **v1.0 - 2009年11月22日**  
  * 初始版本。

### 建置 ```MinHook``` - 使用 ```vcpkg```

您可以使用 [vcpkg](https://github.com/Microsoft/vcpkg) 套件管理器下載並安裝 ```MinHook```:

    git clone https://github.com/microsoft/vcpkg
    .\vcpkg\bootstrap-vcpkg.bat
    .\vcpkg\vcpkg integrate install
    .\vcpkg\vcpkg install minhook

- ```MinHook``` 的 ```vcpkg``` 埠 (port) 由微軟團隊成員與社群貢獻者共同維護。
- 若版本過舊，請在 vcpkg 儲存庫中建立問題 (```Issue```) 或合併請求 (```Pull Request```)。
