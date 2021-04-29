#pragma once

#include "Common.h"

class Camera;

class CameraFactory
{
public:
	static CameraFactory& instance();
	static bool initialize();

    PY_DOC(DOC_DETECT,
    "\"\"Detect the camera.                            \n"
    "                                                  \n"
    "This detect the all camera connected and returns  \n"
    "list of device number.                            \n"
    "                                                  \n"
    "Returns                                           \n"
    "-------                                           \n"
    "int                                               \n"
    "    Device number list of detected camera.        \n"
    "\"\"                                              \n");
	std::list<int> detect();

    PY_DOC(DOC_CREATE,
    "\"\"Create the camera of device number.           \n"
    "                                                  \n"
    "This returns Camera obj of device number to       \n"
    "control.                                          \n"
    "                                                  \n"
    "Parameters                                        \n"
    "----------                                        \n"
    "deviceNo : int                                    \n"
    "    Device number of the camera.(default=0)       \n"
    "openAuto : bool                                   \n"
    "    Open camera automatically.(default=true)      \n"
    "                                                  \n"
    "Returns                                           \n"
    "-------                                           \n"
    "Camera obj                                        \n"
    "    Camera object of device.                      \n"
    "\"\"                                              \n");
	Camera* create(int deviceNo = 0, bool openAuto = true);

private:
	CameraFactory();
	CameraFactory(const CameraFactory& obj) = delete;
	CameraFactory& operator=(const CameraFactory& obj) = delete;
	~CameraFactory();

	static bool isInit;
	std::vector<Camera*> m_instancedCamera;
};
