# CastarSDK-Windows Demo

This is a sample project that demonstrates how to integrate and use CastarSDK。

## Features

- Demonstrate the basic initialization process of CastarSDK
- Demonstrate how to use the core functions
- Provides complete Windows C++ sample code

## System requirements

- visual studio 2022+
- c++ 11+

## Installation Instructions

1. Clone this repository:
   ```bash
   git clone https://github.com/Castar-SDK/Castar-windows-example.git
   ```

2. Download `SDK for Windows` from Castar official website

3. Put the dll file in the downloaded SDK into the `Run` directory of the project

4. Open `Castar.sln` and run the project

## How to use

1. Loading the dll:
   
   ```
   g_handDll = LoadLibrary(L"client_386.dll");
   ```
2. Initialize the SDK:
   ```
   GoString gsTemp;
   gsTemp.p = _strdup("Your Key");
   gsTemp.n = strlen(gsTemp.p);
   SetDevKeyFunction(gsTemp);
   ```

3. Get function address:
   ```swift
   SetDevKeyFunction = (SetDevKey)GetProcAddress(g_handDll, "SetDevKey");
   SetDevSnFunction = (SetDevSn)GetProcAddress(g_handDll, "SetDevSn");
   StartFunction = (Start)GetProcAddress(g_handDll, "Start");
   StopFunction = (Stop)GetProcAddress(g_handDll, "Stop");
   ```
4. Start up
   ```
	void runDll() {
		rintf("runDll running\n");
		StartFunction();
		printf("runDll end\n");
	}
    std::thread t(runDll);
    t.detach();
   ```
5. Stop
   ```swift
   StopFunction();
   ```
   
## Precautions

- Before use, you need to register on the official website and obtain the developer key (DevKey)
- This sample code is for reference only. Please follow the official documentation for actual use.
- SDK for Windows is not included in this repository and needs to be downloaded separately

## License

MIT License - See the [LICENSE](LICENSE) file for details

## Related links

- [Castar official website](https://www.castarsdk.com/)
- [SDK Documentation](https://www.castarsdk.com/document)
