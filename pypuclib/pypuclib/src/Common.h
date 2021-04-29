#pragma once

#define NOMINMAX
#include "windows.h"

#include "../include/PUCLIB.h"
#pragma comment(lib, "./lib/PUCLIB.lib")

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <list>
#include <stdexcept>
#include <string>
#include <map>

#define PY_DOC(name, str) static constexpr char name[] = str;

inline int ALIGN(int x, int align)
{
	return ((x + align - 1) & ~(align - 1));
}

inline void copyWithoutAlign(uint8_t* dst, uint8_t* src, int w, int h, int align = 4)
{
	if (!dst || !src || w <= 0 || h <= 0) {
		return;
	}

	size_t srcBytesPerLine = ALIGN(w, align);
	size_t dstBytesPerLine = w;

	for (int i = 0; i < h; ++i) {
		memcpy(dst + dstBytesPerLine * i, src + srcBytesPerLine * i, dstBytesPerLine);
	}
}