#pragma once

#include "Types.h"

#if defined(WINDOWS_PLATFORM)
#include "Platform_Win32.h"
#elif defined(LINUX_PLATFORM)

#elif defined(MACOS_PLATFORM)

#elif defined(FREEBSD_PLATFORM)

#endif

#include "../base/Allocator.h"

#define ALIGN( alignment )              __declspec( align(alignment) )
#define ALIGN_SIZE(Size, AlSize)        ((Size + (AlSize-1)) & (~(AlSize-1)))
#define ALIGN_SIZE_64K(Size)            ALIGN_SIZE(Size, 65536)
#define ALIGN_SIZE_16(Size)             ALIGN_SIZE(Size, 16)

int
OMCMain(
	char** argv,
	int argc
);
