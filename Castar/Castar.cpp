#include <iostream>
#include <Windows.h>
#include <iphlpapi.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>

#pragma comment(lib, "iphlpapi.lib")

typedef struct { const char* p; ptrdiff_t n; } _GoString_;
typedef _GoString_ GoString;

static HMODULE g_handDll = NULL;
typedef void(*SetDevKey)(GoString);
typedef void(*SetDevSn)(GoString);
typedef void(*Start)();
typedef void(*Stop)();
typedef void(*DebugStart)();

SetDevKey SetDevKeyFunction;
SetDevSn SetDevSnFunction;
Start StartFunction;
Stop StopFunction;
DebugStart DebugStartFunction;

std::string GetMacAddress() {
    std::string strRet = "";
    IP_ADAPTER_INFO adapterInfo[16];
    DWORD dwBufLen = sizeof(adapterInfo);
    DWORD dwStatus = GetAdaptersInfo(adapterInfo, &dwBufLen);

    std::stringstream macAddress;

    if (dwStatus == ERROR_SUCCESS) {
        PIP_ADAPTER_INFO pAdapterInfo = adapterInfo;
        while (pAdapterInfo) {
            if (macAddress.str() != "")
                break;
            for (int i = 0; i < pAdapterInfo->AddressLength; i++) {
                macAddress << std::hex << std::setw(2) << std::setfill('0') << (int)pAdapterInfo->Address[i];
                if (i < pAdapterInfo->AddressLength - 1) {
                    macAddress << ":";
                }
            }
            strRet = macAddress.str();
            pAdapterInfo = pAdapterInfo->Next;
        }
    }
    else {
        std::cerr << "Error retrieving adapter information." << std::endl;
    }
    return strRet;
}

void runDll() {
    printf("runDll running\n");
    StartFunction();
    printf("runDll end\n");
}

int main(int argc, char* argv[])
{
    g_handDll = LoadLibrary(L"client_386.dll");
    if (NULL == g_handDll || INVALID_HANDLE_VALUE == g_handDll) {
        printf("LoadLibrary error\n");
        getchar();
        return -1;
    }

    SetDevKeyFunction = (SetDevKey)GetProcAddress(g_handDll, "SetDevKey");
    SetDevSnFunction = (SetDevSn)GetProcAddress(g_handDll, "SetDevSn");
    StartFunction = (Start)GetProcAddress(g_handDll, "Start");
    StopFunction = (Stop)GetProcAddress(g_handDll, "Stop");

    if (!SetDevKeyFunction || !SetDevSnFunction || !StartFunction || !StopFunction)
    {
        printf("GetProcAddress error\n");
        getchar();
        return -1;
    }

    std::string strMac = GetMacAddress();
    printf("mac: %s\n", strMac.c_str());

    GoString gsTemp;
    gsTemp.p = _strdup("Your Key");
    gsTemp.n = strlen(gsTemp.p);
    SetDevKeyFunction(gsTemp);

    GoString gsTemp_1;
    gsTemp_1.p = _strdup(strMac.c_str());
    gsTemp_1.n = strlen(gsTemp_1.p);
    SetDevSnFunction(gsTemp_1);

    std::thread t(runDll);
    t.detach();

    while (true)
    {
        Sleep(1000);
    }

    StopFunction();
    return 0;
}