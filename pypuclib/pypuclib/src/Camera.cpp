#include "Camera.h"
#include "Decoder.h"
#include "Exception.h"
#include <pybind11/pybind11.h>


Camera::Camera(int deviceNo)
	:
	m_handle(nullptr),
	m_deviceNo(deviceNo),
	m_enableCallback(false)
{
	memset(m_quntize, 0, sizeof(m_quntize));
}

Camera::~Camera()
{
	if (m_handle) {
		close();
	}
}

void Camera::open()
{
	auto ret = PUC_OpenDevice(m_deviceNo, &m_handle);
	if (PUC_CHK_FAILED(ret))
	{
		m_handle = nullptr;
		throw(PUCException("PUC_OpenDevice", ret));
	}

	for (int i = 0; i < PUC_Q_COUNT; ++i) {
		ret = PUC_GetQuantization(m_handle, i, &m_quntize[i]);
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_GetQuantization", ret));
		}
	}
}

void Camera::close()
{
	if (m_handle != nullptr)
	{
		try
		{
			if (isXferring()) {
				endXfer();
			}

			auto ret = PUC_CloseDevice(m_handle);
			if (PUC_CHK_FAILED(ret)) {
				throw(PUCException("PUC_CloseDevice", ret));
			}
			m_handle = nullptr;
		}
		catch (PUCException&)
		{
			// do nothing
		}
	}
}

Resolution Camera::resolution() const
{
	unsigned int w, h;
	auto ret = PUC_GetResolution(m_handle, &w, &h);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetResolution", ret));
	}
	return Resolution(w, h);
}

Resolution Camera::resolutionMax() const
{
	unsigned int w, h;
	auto ret = PUC_GetMaxResolution(m_handle, &w, &h);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetMaxResolution", ret));
	}

	return Resolution(w, h);
}

ResolutionLimit Camera::resolutionLimit() const
{
	PUC_RESO_LIMIT_INFO limit;
	auto ret = PUC_GetResolutionLimit(m_handle, &limit);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetResolutionLimit", ret));
	}

	Limit lw(limit.nMinWidth, limit.nMaxWidth, limit.nUnitWidth);
	Limit lh(limit.nMinHeight, limit.nMaxHeight, limit.nUnitHeight);

	return ResolutionLimit(lw, lh);
}

void Camera::setResolution(const Resolution& res)
{
	auto ret = PUC_SetResolution(m_handle, res.width, res.height);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_SetResolution", ret));
	}
}

void Camera::setResolution(const int& w, const int& h)
{
	setResolution(Resolution(w, h));
}

int Camera::framerate() const
{
	return std::get<0>(framerateShutter());
}

int Camera::framerateMax() const
{
	unsigned int f;
	auto ret = PUC_GetMaxFramerate(m_handle, &f);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetMaxFramerate", ret));
	}

	return (int)f;
}

int Camera::shutter() const
{
	return std::get<1>(framerateShutter());
}

std::tuple<int, int> Camera::framerateShutter() const
{
	unsigned int f, s;
	auto ret = PUC_GetFramerateShutter(m_handle, &f, &s);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetFramerateShutter", ret));
	}
	return std::tuple<int, int>(f, s);
}

void Camera::setFramerate(const int& framerate)
{
	auto values = framerateShutter();

	auto shutter = std::get<1>(values);

	if (framerate > shutter)
		shutter = framerate;

	setFramerateShutter(framerate, shutter);
}

void Camera::setShutter(const int& shutter)
{
	auto ret = framerateShutter();

	setFramerateShutter(std::get<0>(ret), shutter);
}

void Camera::setFramerateShutter(const int& framerate, const int& shutter)
{
	auto ret = PUC_SetFramerateShutter(m_handle, framerate, shutter);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_SetFramerateShutter", ret));
	}
}

PUC_COLOR_TYPE Camera::colortype() const
{
	PUC_COLOR_TYPE type;
	auto ret = PUC_GetColorType(m_handle, &type);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetColorType", ret));
	}

	return type;
}

PUC_DATA_MODE Camera::datamode() const
{
	PUC_DATA_MODE mode;
	auto ret = PUC_GetXferDataMode(m_handle, &mode);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetXferDataMode", ret));
	}

	return mode;
}

void Camera::setDatamode(const PUC_DATA_MODE& mode)
{
	auto ret = PUC_SetXferDataMode(m_handle, mode);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_SetXferDataMode", ret));
	}
}

unsigned int Camera::xferDataSize() const
{
	auto mode = datamode();
	unsigned int dataSize;

	auto ret = PUC_GetXferDataSize(m_handle, mode, &dataSize);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetXferDataSize", ret));
	}

	return dataSize;
}

unsigned int Camera::maxXferDataSize() const
{
	auto mode = datamode();
	unsigned int dataSize;

	auto ret = PUC_GetMaxXferDataSize(m_handle, mode, &dataSize);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetXferDataSize", ret));
	}

	return dataSize;
}

int Camera::ringBufferCount() const
{
	unsigned int count;

	auto ret = PUC_GetRingBufferCount(m_handle, &count);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetRingBufferCount", ret));
	}

	return (int)count;
}

void Camera::setRingBufferCount(const int &count)
{
	auto ret = PUC_SetRingBufferCount(m_handle, count);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_SetRingBufferCount", ret));
	}
}

std::tuple<int, int> Camera::xferTimeout() const
{
	unsigned int single, continuous;

	auto ret = PUC_GetXferTimeOut(m_handle, &single, &continuous);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetXferTimeOut", ret));
	}

	return std::tuple<int, int>(single, continuous);
}

void Camera::setXferTimeout(const int& single, const int& continuos)
{
	auto ret = PUC_SetXferTimeOut(m_handle, single, continuos);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_SetXferTimeOut", ret));
	}
}

void Camera::beginXfer(std::function<void(XferData*)> f)
{
	auto ret = PUC_BeginXferData(m_handle, this->continuousCallback, (void*)this);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_BeginXferData", ret));
	}

	m_pythonCallback = f;
	startCallback();
}

void Camera::endXfer()
{
	stopCallback();

	py::gil_scoped_release release;

	auto ret = PUC_EndXferData(m_handle);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_EndXferData", ret));
	}
}

bool Camera::isXferring()
{
	BOOL xferring = FALSE;

	auto ret = PUC_IsXferring(m_handle, &xferring);
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_IsXferring", ret));
	}

	return xferring == TRUE;
}

std::unique_ptr<Decoder> Camera::decoder()
{
	std::unique_ptr<Decoder> p =
		std::make_unique<Decoder>(m_quntize, PUC_Q_COUNT);

	if (!p) {
		throw(WrapperException("bad memory allocation"));
	}

	return p;
}

std::unique_ptr<XferData> Camera::grab()
{
	std::unique_ptr<XferData> p =
		std::make_unique<XferData>(xferDataSize(), resolution(), datamode());
	
	if (!p) {
		throw(WrapperException("bad memory allocation"));
	}

	auto ret = PUC_GetSingleXferData(m_handle, p->dataInfo());
	if (PUC_CHK_FAILED(ret)) {
		throw(PUCException("PUC_GetSingleXferData", ret));
	}

	return p;
}

void Camera::continuousCallback(PPUC_XFER_DATA_INFO pInfo, void* pArg)
{
	Camera* cam = (Camera*)pArg;

	if (cam) 
	{
		cam->callbackWork(pInfo);
	}
}

void Camera::callbackWork(PPUC_XFER_DATA_INFO pInfo)
{
	if (m_enableCallback)
	{
		std::unique_ptr<XferData> p =
			std::make_unique<XferData>(pInfo, resolution(), datamode());

		if (!p) {
			throw(WrapperException("bad memory allocation"));
		}

		m_pythonCallback(p.get());
	}
}