#include "pch.h"

#if defined(ALICEUI_SHARED)

#include <clocale>

extern "C" {
    static AFX_EXTENSION_MODULE sAliceUIDLL = { 0, };

    int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {
        UNREFERENCED_PARAMETER(lpReserved);

        if (dwReason == DLL_PROCESS_ATTACH)
        {
            TRACE("[AliceUI] Prepare initialization.\n");

            // Init MFC Extension
            if (!AfxInitExtensionModule(sAliceUIDLL, hInstance))
                return 0;

            // Register Extension DLL
            new CDynLinkLibrary(sAliceUIDLL);

            TRACE("[AliceUI] Initialized.\n");
        }
        else if (dwReason == DLL_PROCESS_DETACH)
        {
            TRACE("[AliceUI] Finalizing.\n");

            // Terminate MFC Extension
            AfxTermExtensionModule(sAliceUIDLL);
        }
        return 1;
    }
}

#endif
