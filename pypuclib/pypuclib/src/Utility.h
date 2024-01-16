#pragma once

#include "Common.h"

class Resolution
{
public:
	PY_DOC(DOC_CLASS_RESOLUTION,
	"\"\"                                              \n"
	"                                                  \n"
	"Camera resolution information.                    \n"
	"                                                  \n"
	"Attributes                                        \n"
	"----------                                        \n"
	"width : int                                       \n"
	"    width of resolution                           \n"
	"height : int                                      \n"
	"    height of resolution                          \n"
	"\"\"                                              \n");
public:
	Resolution() : width(0), height(0) {}
	Resolution(const int &w, const int &h) : width(w), height(h) {}
	~Resolution() {}
	bool operator==(Resolution& res) {
		return (this->width == res.width && this->height == res.height);
	}
	bool operator!=(Resolution& res) {
		return (this->width != res.width || this->height != res.height);
	}
	int width;
	int height;
};

class Limit
{
public:
	PY_DOC(DOC_CLASS_LIMIT,
	"\"\"                                              \n"
	"                                                  \n"
	"Limit information includes min, mas, step.        \n"
	"                                                  \n"
	"Attributes                                        \n"
	"----------                                        \n"
	"min : int                                         \n"
	"    Minimum limit value.                          \n"
	"max : int                                         \n"
	"    Maximum limit value.                          \n"
	"step : int                                        \n"
	"    Step value fro parameter.                     \n"
	"\"\"                                              \n");
public:
	Limit(const int& minimum, const int& maximum, const int& steps) 
	: min(minimum), max(maximum), step(steps){}
	Limit(const int& minimum, const int& maximum)
		: min(minimum), max(maximum) {}
	~Limit() {}

	int min;
	int max;
	int step;
};

class ResolutionLimit
{
public:
	PY_DOC(DOC_CLASS_RESOLUTION_LIMIT,
	"\"\"                                              \n"
	"                                                  \n"
	"Limit information for resolution.                 \n"
	"                                                  \n"
	"Attributes                                        \n"
	"----------                                        \n"
	"limitW : Limit obj                                \n"
	"    Limit information of width.                   \n"
	"limitH : Limit obj                                \n"
	"    Limit information of height.                  \n"
	"\"\"                                              \n");
public:
	ResolutionLimit(const Limit& w, const Limit& h) : limitW(w), limitH(h) {}
	~ResolutionLimit() {}
	Limit limitW;
	Limit limitH;
};

class FramerateLimit
{
public:
	PY_DOC(DOC_CLASS_FRAMERATE_LIMIT,
		"\"\"                                              \n"
		"                                                  \n"
		"Limit information for framerate.                  \n"
		"                                                  \n"
		"Attributes                                        \n"
		"----------                                        \n"
		"min : minimum value                               \n"
		"    Minimum framerate.							   \n"
		"max : max value                                   \n"
		"    Max framerate.								   \n"
		"\"\"                                              \n");

public:
	FramerateLimit() : min(0), max(0) {}
	FramerateLimit(const int& min, const int& max) :  min(min), max(max) {}
	~FramerateLimit() {}

	int min;
	int max;
};

class GPUSetup
{
public:
	PY_DOC(DOC_CLASS_GPU_SETUP,
		"");

public:
	GPUSetup() : width(1246), height(1008) {}
	GPUSetup(const int& w, const int& h) : width(w), height(h) {}
	~GPUSetup() {};

	int width;
	int height;
};