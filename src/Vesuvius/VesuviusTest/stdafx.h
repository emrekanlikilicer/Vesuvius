// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

#include "vulkan.h"

#include "CVkInstance.h"
#include "CVkPhysicalDevice.h"
#include "CVkDevice.h"

#include "Helper.h"

#include <vector>
#include <memory>

// define ToString method for additional data types.

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<> 
			static std::wstring ToString<VkResult>(const VkResult& t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}

