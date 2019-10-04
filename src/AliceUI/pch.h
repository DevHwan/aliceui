#pragma once

#if defined(_WIN32)
#   define NOMINMAX
#   define VC_EXTRALEAN
#   define WIN32_LEAN_AND_MEAN
#   include "AUIMFCCommon.h"
#endif

//////////////////////////////////////////////////////////////////////////
// STL Header
#include <cwctype>
#include <cstdio>
#include <regex>
#include <atomic>
#include <mutex>
#include <thread>
#include <limits>
#include <cmath>
#include <cassert>
#include <codecvt>
#include <functional>
#include <cstdint>
#include <chrono>
#include <string>
#include <sstream>
#include <memory>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <type_traits>
#include <typeindex>
#include <random>
#include <queue>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <exception>

//////////////////////////////////////////////////////////////////////////
// Rapid JSON
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

//////////////////////////////////////////////////////////////////////////
// GLM Header
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_query.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/optimum_pow.hpp>
#include <glm/gtx/projection.hpp>

//////////////////////////////////////////////////////////////////////////
// GL
#include "AUIOpenGL.h"


//////////////////////////////////////////////////////////////////////////
// Skia
#include "AUISkiaConfig.h"
#include "AUIColorDef.h"
#include "AUIDebug.h"
