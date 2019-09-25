#pragma once

#if defined(ALICEUI_SHARED)
#   if defined(ALICEUI_EXPORTS)
#       if defined(_MSC_VER)
#           define ALICEUI_API  __declspec(dllexport)
#       else
#           define ALICEUI_API  __attribute__((visibility("default")))
#       endif
#   else
#       if defined(_MSC_VER)
#           define ALICEUI_API  __declspec(dllimport)
#       else
#           define ALICEUI_API
#       endif
#   endif
#else
#   define ALICEUI_API
#endif
