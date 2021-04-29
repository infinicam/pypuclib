#pragma once

#include "Common.h"
#include "Exception.h"
#include "Utility.h"
#include "XferData.h"


class Decoder;
class Camera
{
public:
	Camera(int deviceNo);
	~Camera();

	PY_DOC(DOC_OPEN,
	"\"\"This opens camera and initialization.         \n"
	"                                                  \n"
	"See CameraFactory to instance camera object.      \n"
	"                                                  \n"
	"\"\"                                              \n");
	void open();
	
	PY_DOC(DOC_CLOSE,
	"\"\"This closes camera.                           \n"
	"                                                  \n"
	"Close camera using this when no longer need it.   \n"
	"                                                  \n"
	"\"\"                                              \n");
	void close();

	PY_DOC(DOC_RESOLUTION,
	"\"\"Get resolution of the device.                 \n"
	"                                                  \n"
	"Get resolution as Resolution obj.                 \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"Resolution obj                                    \n"
	"    Device resolution.                            \n"
	"\"\"                                              \n");
	Resolution resolution() const;

	PY_DOC(DOC_RESOLUTION_MAX,
	"\"\"Get Maximum resolution of the device.         \n"
	"                                                  \n"
	"Get Maximum resolution on current framerate.      \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"Resolution obj                                    \n"
	"    Maximum resolution.                           \n"
	"\"\"                                              \n");
	Resolution resolutionMax() const;

	PY_DOC(DOC_RESOLUTION_LIMIT,
	"\"\"Get resolution limit info of the device.      \n"
	"                                                  \n"
	"Get resolution limit info as ResolutionLimit obj. \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"ResolutionLimit obj                               \n"
	"    Limit info of resolution.                     \n"
	"\"\"                                              \n");
	ResolutionLimit resolutionLimit() const;

	PY_DOC(DOC_SET_RESOLUTION_A,
	"\"\"Set resolution to the device.                 \n"
	"                                                  \n"
	"This is overload function of setResolurion using  \n"
	"resolution obj.                                   \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"resolution : Resolution obj                       \n"
	"    Resolution to set the device                  \n"
	"\"\"                                              \n");
	void setResolution(const Resolution& res);

	PY_DOC(DOC_SET_RESOLUTION_B,
	"\"\"Set resolution to the device.                 \n"
	"                                                  \n"
	"This is overload function of setResolution using  \n"
	"width and height.                                 \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"width : int                                       \n"
	"    width of resolution to set.                   \n"
	"height : int                                      \n"
	"    height of resolution to set.                  \n"
	"\"\"                                              \n");
	void setResolution(const int& w, const int& h);

	PY_DOC(DOC_FRAMERATE,
	"\"\"Get framerate of the device.                  \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Framerate of the device.                      \n"
	"\"\"                                              \n");
	int framerate() const;

	PY_DOC(DOC_FRAMERATE_MAX,
	"\"\"Get maximum framerate of the device.          \n"
	"                                                  \n"
	"Get maximum framerate on current resolution.      \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Maximum framerate.                            \n"
	"\"\"                                              \n");
	int framerateMax() const;

	PY_DOC(DOC_SHUTTER,
	"\"\"Get shutter speed of the device.              \n"
	"                                                  \n"
	"Get shutter speed in 1/x[sec] units.              \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Shutter speed 1/x[sec]                        \n"
	"\"\"                                              \n");
	int shutter() const;

	PY_DOC(DOC_FRAMERATE_SHUTTER,
	"\"\"Get framerate and shutter speed of the device.\n"
	"                                                  \n"
	"Get framerate and shutter speed in one function.  \n"
	"Shutter speed in 1/x[sec] units.                  \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"(int, int)                                        \n"
	"    (framerate, shutter speed 1/x[sec])           \n"
	"\"\"                                              \n");
	std::tuple<int, int> framerateShutter() const;

	PY_DOC(DOC_SET_FRAMERATE,
	"\"\"Set framerate to the device.                  \n"
	"                                                  \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"framerate : int                                   \n"
	"    Framerate to set.                             \n"
	"\"\"                                              \n");
	void setFramerate(const int& framerate);

	PY_DOC(DOC_SET_SHUTTER,
	"\"\"Set shutter speed  to the device.             \n"
	"                                                  \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"shutter : int                                     \n"
	"    Shutter speed 1/x[sec] to set.                \n"
	"\"\"                                              \n");
	void setShutter(const int& shutter);

	PY_DOC(DOC_SET_FRAMERATE_SHUTTER,
	"\"\"Set Framerate and shutter speed to the device.\n"
	"                                                  \n"
	"Set Framerate and shutter speed 1/x[sec] to the   \n"
	"device same time.                                 \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"framerate : int                                   \n"
	"    Framerate to set.                             \n"
	"shutter speed : int                               \n"
	"    Shutter speed 1/x[sec] to set.                \n"
	"                                                  \n"
	"\"\"                                              \n");
	void setFramerateShutter(const int& framerate, const int& shutter);

	PY_DOC(DOC_COLORTYPE,
	"\"\"Get color type of the device.                 \n"
	"                                                  \n"
	"Get Color type of the device defined in           \n"
	"PUC_COLOR_TYPE enum.                              \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"PUC_COLOR_TYPE(enum)                              \n"
	"    Color type of the device.                     \n"
	"\"\"                                              \n");
	PUC_COLOR_TYPE colortype() const;

	PY_DOC(DOC_DATAMODE,
	"\"\"Get datamode of transfer image.               \n"
	"                                                  \n"
	"Get datamode of transfer image in PUC_DATA_MODE.  \n"	
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"PUC_DATA_MODE(enum)                               \n"
	"    Transfer image data mode.                     \n"
	"\"\"                                              \n");
	PUC_DATA_MODE datamode() const;

	PY_DOC(DOC_SET_DATAMODE,
	"\"\"Set transfer datamode to sdk.                 \n"
	"                                                  \n"
	"Set transfer datamode using PUC_DATA_MODE(enum).  \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"mode : PUC_DATA_MODE(enum)                        \n"
	"    Transfer mode to set                          \n"
	"\"\"                                              \n");
	void setDatamode(const PUC_DATA_MODE& mode);

	PY_DOC(DOC_RINGBUFFER_COUNT,
	"\"\"Get ring buffer count of continuous transfer. \n"
	"                                                  \n"
	"Get ring buffer count of internal transfer thread.\n"
	"This parameter effects stability of transfer and  \n"
	"memory usage. Default is 1024.                    \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Ring buffer count of transfer.                \n"
	"\"\"                                              \n");
	int ringBufferCount() const;

	PY_DOC(DOC_SET_RINGBUFEFR_COUNT,
	"\"\"Set ring buffer count for continuous transfer.\n"
	"                                                  \n"
	"Set ring buffer count of internal transfer thread.\n"
	"This parameter effects stability of transfer and  \n"
	"memory usage.                                     \n"
	"Minimum count=4, Maximum count = 65535            \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"count : int                                       \n"
	"    Ring buffer count to set.                     \n"
	"\"\"                                              \n");
	void setRingBufferCount(const int& count);

	PY_DOC(DOC_XFER_TIMEOUT,
	"\"\"Get transfer timeout duration.                \n"
	"                                                  \n"
	"Get timeout duration[ms] for single transfer and  \n"
	"continuous transfer as tuple(int, int).           \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"(int, int)                                        \n"
	"    (single, continuous) timeout in msec.         \n"
	"\"\"                                              \n");
	std::tuple<int, int> xferTimeout() const;

	PY_DOC(DOC_SET_XFER_TIMEOUT,
	"\"\"Set timeout duration for transfer.            \n"
	"                                                  \n"
	"Set timeout duration for single and continuous    \n"
	"transfer. If set to 0, duration will automatically\n"
	"decided based on framerate.                       \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"single : int                                      \n"
	"    Duration of timeout[ms] for single transfer.  \n"
	"continuous : int                                  \n"
	"    Duration of timeout[ms] for continuous        \n"
	"    transfer.                                     \n"
	"\"\"                                              \n");
	void setXferTimeout(const int &single, const int &continuos);

	PY_DOC(DOC_BEGIN_XFER,
	"\"\"Begin continuous transfer and start callback. \n"
	"                                                  \n"
	"Begin continuous transfer on internal thread and  \n"
	"callback starts immediately to argument function. \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"function : function<void(XferData*)>              \n"
	"    Callback function from C++ to Python.         \n"
	"\"\"                                              \n");
	void beginXfer(std::function<void(XferData*)> f);

	PY_DOC(DOC_END_XFER,
	"\"\"Finish continuous transfer.                   \n"
	"                                                  \n"
	"Stop internal continuous transfer thread and stop \n"
	"callback.                                         \n"
	"                                                  \n"
	"\"\"                                              \n");
	void endXfer();

	PY_DOC(DOC_IS_XFERRING,
	"\"\"Check if continuous transfer is in progress.  \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"bool                                              \n"
	"    True during transfer, false otherwise.        \n"
	"\"\"                                              \n");
	bool isXferring();

	PY_DOC(DOC_DECODER,
	"\"\"Get Decoder obj from the device.              \n"
	"                                                  \n"
	"Get Decoder obj using current quantization        \n"
	"settings. this decoder can use for decode image.  \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"Decoder obj                                       \n"
	"    Decoder obj based on quantization             \n"
	"\"\"                                              \n");
	std::unique_ptr<Decoder> decoder();
	
	PY_DOC(DOC_GRAB,
	"\"\"Grab the image data from the device.          \n"
	"                                                  \n"
	"Grab the single image as XferData object. this    \n"
	"Xferdata has image data based on datamode.        \n"
	"If datamode is PUC_DATA_COMPRESSED, XferData has  \n"
	"compressed data. To make it image, need to use    \n"
	"decoder to decode image.                          \n"
	"If datamode is PUC_DATA_DECOMPRESSED_GLAY,        \n"
	"XferData has decompressed full size image data.   \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"data : Xferdata obj                               \n"
	"    Image data obj based on PUC_DATA_MODE.        \n"
	"\"\"                                              \n");
	std::unique_ptr<XferData> grab();

private:
	int deviceNo() const { return m_deviceNo; }
	unsigned int xferDataSize() const;
	unsigned int maxXferDataSize() const;

private: // for continuous callback
	static void continuousCallback(PPUC_XFER_DATA_INFO pInfo, void* pArg);
	void callbackWork(PPUC_XFER_DATA_INFO pInfo);
	void startCallback() { m_enableCallback = true; }
	void stopCallback() { m_enableCallback = false; }
	std::function<void(XferData*)> m_pythonCallback;
	bool m_enableCallback;

private:
	void* m_handle;
	int m_deviceNo;
	unsigned short m_quntize[PUC_Q_COUNT];
};