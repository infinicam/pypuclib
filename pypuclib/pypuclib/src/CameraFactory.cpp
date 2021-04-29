#include "CameraFactory.h"
#include "Camera.h"
#include "Exception.h"

CameraFactory& CameraFactory::instance()
{
	static CameraFactory factory;
	return factory;
}

bool CameraFactory::isInit = false;

bool CameraFactory::initialize()
{
	if (!CameraFactory::isInit)
	{
		auto ret = PUC_Initialize();
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_Initialize", ret));
		}
		CameraFactory::isInit = true;
	}

	return CameraFactory::isInit;
}

CameraFactory::CameraFactory()
{
	initialize();
	return;
}

CameraFactory::~CameraFactory()
{
	for (int i = 0; i < m_instancedCamera.size(); ++i)
	{
		m_instancedCamera[i]->close();
		if (m_instancedCamera[i])
		{
			delete m_instancedCamera[i];
			m_instancedCamera[i] = nullptr;
		}
	}
	m_instancedCamera.clear();
}

std::list<int> CameraFactory::detect()
{
	std::list<int> detecedNoList;

	PUC_DETECT_INFO detectInfo;
	auto ret = PUC_DetectDevice(&detectInfo);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_DetectDevice", ret));
	}

	for (int i = 0; i < detectInfo.nDeviceCount; ++i) {
		detecedNoList.push_back(detectInfo.nDeviceNoList[i]);
	}
	return detecedNoList;
}

Camera* CameraFactory::create(int deviceNo, bool openAuto)
{
	auto list = this->detect();
	if (list.empty() || std::find(list.begin(), list.end(), deviceNo) == list.end()) {
		throw(PUCException("couldn't find any camera"));
	}

	Camera* cam = new Camera(deviceNo);
	m_instancedCamera.push_back(cam);

	if(openAuto)
		cam->open();

	return cam;
}