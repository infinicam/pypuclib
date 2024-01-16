#pragma once

#include <pybind11/numpy.h>
#include "Common.h"
#include "Exception.h"
#include "XferData.h"
#include "CameraFactory.h"

namespace py = pybind11;

class Decoder
{
public:
	Decoder()
		:
		m_numThread(1)
	{
		CameraFactory::initialize();
		memset(m_quantize, 0, sizeof(unsigned short) * PUC_Q_COUNT);
	}
	Decoder(const std::vector<int>& q)
		:Decoder()
	{
		setQuantization(q);
	}
	Decoder(unsigned short* q, int qsize)
		:Decoder()
	{
		if (q == nullptr || qsize != PUC_Q_COUNT) {
			throw(WrapperException("quantization may be illegal size or not defined."));
		}
		memcpy(m_quantize, q, sizeof(unsigned short) * qsize);
	}
	~Decoder() 
	{

	}
	
	PY_DOC(DOC_QUANTIZATION,
	"\"\"Get Quantization of decoder.                  \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"list(int)                                         \n"
	"    Quantization value list.                      \n"
	"\"\"                                              \n");
	std::vector<int> quantization() 
	{
		return std::vector<int>(std::begin(m_quantize), std::end(m_quantize));
	}
	
	PY_DOC(DOC_SET_QUANTIZATION,
	"\"\"Set quantization list to decoder.             \n"
	"                                                  \n"
	"Set quantization list to decoder using list.      \n"
	"List size must be 64 and range is 0 to 65535      \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"q : list(int)                                     \n"
	"    Quantization list to set.                     \n"
	"\"\"                                              \n");
	void setQuantization(const std::vector<int>& q) 
	{
		if (q.size() != PUC_Q_COUNT) {
			throw(WrapperException("quantization may be illegal size."));
		}
		for (unsigned int i = 0; i < q.size(); ++i)
		{
			if (q[i] < 0)
				m_quantize[i] = 0;
			else if (q[i] > USHRT_MAX)
				m_quantize[i] = USHRT_MAX;
			else
				m_quantize[i] = (unsigned short)q[i];
		}
	}

	PY_DOC(DOC_DECODE_A,
	"\"\"Decode compressed data.                       \n"
	"                                                  \n"
	"This is overload function using XferData obj.     \n"
	"This decode data in XferData to full resolution.  \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"data : XferData obj                               \n"
	"    XferData to decode.                           \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"numpy array(uint8)                                \n"
	"    Numpy array of the decompressed image.        \n"
	"\"\"                                              \n");
	py::array_t<uint8_t> decode(XferData* data)
	{
		auto res = data->resolution();

		py::array_t<uint8_t> buf({ res.height, res.width });
		decode(data->dataInfo()->pData, buf.mutable_data(), 0, 0, res.width, res.height, res.width);

		return buf;
	}

	PY_DOC(DOC_DECODE_B,
	"\"\"Decode compressed data.                       \n"
	"                                                  \n"
	"This is overload function using XferData obj.     \n"
	"This decode data in XferData to specified roi     \n"
	"image.                                            \n" 
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"data : XferData obj                               \n"
	"    XferData to decode.                           \n"
	"x : int                                           \n"
	"    Decode start position of x coordinate.        \n"
	"y : int                                           \n"
	"    Decode start position of y coordinate.        \n"
	"w : int                                           \n"
	"    Decode width start from x.                    \n"
	"h : int                                           \n"
	"    Decode height start form y.                   \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"numpy array(uint8)                                \n"
	"    Numpy array of the decompressed image.        \n"
	"    Array size is (h, w).                         \n"
	"\"\"                                              \n");
	py::array_t<uint8_t> decode(XferData* data, int x, int y, int w, int h)
	{
		py::array_t<uint8_t> buf({ h, w });
		decode(data->dataInfo()->pData, buf.mutable_data(), x, y, w, h, w);
		return buf;
	}

	PY_DOC(DOC_DECODE_C,
	"\"\"Decode compressed data.                       \n"
	"                                                  \n"
	"This is overload function using numpy array input.\n"
	"This decode numpy array source to image.          \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"array : numpy array(uint8)                        \n"
	"    Numpy array of 1d compressed data.            \n"
	"resolution : Resolution obj                       \n"
	"    Resolution of original data resolution.       \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"numpy array(uint8)                                \n"
	"    Numpy array of the decompressed image.        \n"
	"\"\"                                              \n");
	py::array_t<uint8_t> decode(py::array_t<uint8_t>& array, const Resolution& res)
	{
		py::array_t<uint8_t> buf({ res.height, res.width });
		decode(array.mutable_data(), buf.mutable_data(), 0, 0, res.width, res.height, res.width);
		return buf;
	}

	PY_DOC(DOC_DECODE_D,
	"\"\"Decode compressed data.                       \n"
	"                                                  \n"
	"This is overload function using numpy array input.\n"
	"This decode data of numpy array to specified roi  \n"
	"image.                                            \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"array : numpy array(uint8)                        \n"
	"    Numpy array of 1d compressed data.            \n"
	"x : int                                           \n"
	"    Decode start position of x coordinate.        \n"
	"y : int                                           \n"
	"    Decode start position of y coordinate.        \n"
	"w : int                                           \n"
	"    Decode width start from x.                    \n"
	"h : int                                           \n"
	"    Decode height start form y.                   \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"numpy array(uint8)                                \n" 
	"    Numpy array of the decompressed image.        \n"
	"    Array size is (h, w).                         \n"
	"\"\"                                              \n");
	py::array_t<uint8_t> decode(py::array_t<uint8_t>& array, int x, int y, int w, int h)
	{
		py::array_t<uint8_t> buf({ h, w });
		decode(array.mutable_data(), buf.mutable_data(), x, y, w, h, w);
		return buf;
	}

	PY_DOC(DOC_DECODE_DC_A,
		"\"\"Decode compressed DC data.                    \n"
		"                                                  \n"
		"This function use numpy array input.              \n"
		"This decode data of numpy array to specified roi  \n"
		"image.                                            \n"
		"                                                  \n"
		"Parameters                                        \n"
		"----------                                        \n"
		"array : numpy array(uint8)                        \n"
		"    Numpy array of 1d compressed data.            \n"
		"bx : int                                          \n"
		"    Decode start block position of x coordinate.  \n"
		"by : int                                          \n"
		"    Decode start block position of y coordinate.  \n"
		"countX : int                                      \n"
		"    Decode block count start from bx.             \n"
		"countY : int                                      \n"
		"    Decode block count start from by.             \n"
		"                                                  \n"
		"Returns                                           \n"
		"-------                                           \n"
		"numpy array(uint8)                                \n"
		"    Numpy array of the decompressed image.        \n"
		"    Array size is (h, w).                         \n"
		"\"\"                                              \n");
	py::array_t<uint8_t> decodeDC(py::array_t<uint8_t>& array, int bx, int by, int countX, int countY)
	{
		py::array_t<uint8_t> buf({ countY, countX });
		decodeDC(array.mutable_data(), buf.mutable_data(), bx, by, countX, countY);
		return buf;
	}

	PY_DOC(DOC_DECODE_DC_B,
		"\"\"Decode compressed DC data.                    \n"
		"                                                  \n"
		"This function use numpy array input.              \n"
		"This decode data of numpy array to specified roi  \n"
		"image.                                            \n"
		"                                                  \n"
		"Parameters                                        \n"
		"----------                                        \n"
		"array : numpy array(uint8)                        \n"
		"    Numpy array of 1d compressed data.            \n"
		"bx : int                                          \n"
		"    Decode start block position of x coordinate.  \n"
		"by : int                                          \n"
		"    Decode start block position of y coordinate.  \n"
		"countX : int                                      \n"
		"    Decode block count start from bx.             \n"
		"countY : int                                      \n"
		"    Decode block count start from by.             \n"
		"                                                  \n"
		"Returns                                           \n"
		"-------                                           \n"
		"numpy array(uint8)                                \n"
		"    Numpy array of the decompressed image.        \n"
		"    Array size is (h, w).                         \n"
		"\"\"                                              \n");
	py::array_t<uint8_t> decodeDC(XferData* data, int bx, int by, int countX, int countY)
	{
		py::array_t<uint8_t> buf({ countY, countX });
		decodeDC(data->dataInfo()->pData, buf.mutable_data(), bx, by, countX, countY);
		return buf;
	}

	PY_DOC(DOC_DECODE_GPU_A,
		"\"\"Decode compressed data from GPU.											\n"
		"																				\n"
		"This function use numpy array input.											\n"
		"																				\n"
		"Parameters																		\n"
		"----------																		\n"
		"array : numpy array(uint8)														\n"
		"    Numpy array of 1d compressed data.											\n"
		"																				\n"
		"download : bool																\n"
		"	If false is specified, the decoded data is stored in device (GPU) memory,	\n"
		"	if true is specified, it is stored in host (CPU) memory.					\n"
		"																				\n"
		"lineBytes : int																\n"
		"	The number of bytes of the buffer width at the unpacking destination		\n"
		"																				\n"
		"Returns																		\n"
		"-------																		\n"
		"numpy array(uint8)																\n"
		"    Numpy array of the decompressed image.										\n"
		"    Array size is (h, w).														\n"
		"\"\"																			\n");
	py::array_t<uint8_t> decodeGPU(py::array_t<uint8_t>& array, bool download, int lineBytes)
	{
		UINT32 width = m_param.width;
		UINT32 height = m_param.height;
		py::array_t<uint8_t> buf({ height, width });
		auto dst = buf.mutable_data();

		decodeGPU(download, array.mutable_data(), &dst, width);
		return buf;
	}

	PY_DOC(DOC_DECODE_GPU_B,
	"\"\"Decode compressed data from GPU.											\n"
	"																				\n"
	"This function use numpy array input.											\n"
	"																				\n"
	"Parameters																		\n"
	"----------																		\n"
	"array : XferData obj															\n"
	"   XferData to decode.															\n"
	"																				\n"
	"download : bool																\n"
	"	If false is specified, the decoded data is stored in device (GPU) memory,	\n"
	"	if true is specified, it is stored in host (CPU) memory.					\n"
	"																				\n"
	"lineBytes : int																\n"
	"	The number of bytes of the buffer width at the unpacking destination		\n"
	"																				\n"
	"Returns																		\n"
	"-------																		\n"
	"numpy array(uint8)																\n"
	"    Numpy array of the decompressed image.										\n"
	"    Array size is (h, w).														\n"
	"\"\"																			\n");
	py::array_t<uint8_t> decodeGPU(XferData* data, bool download, int lineBytes)
	{
		UINT32 width = m_param.width;
		UINT32 height = m_param.height;
		py::array_t<uint8_t> buf({ height, width });
		auto dst = buf.mutable_data();

		decodeGPU(download, data->dataInfo()->pData, &dst, width);
		return buf;
	}

	PY_DOC(DOC_EXTRACT_SEQUENCENO,
	"\"\"This extract sequence no.                     \n"
	"                                                  \n"
	"This extract sequence no from compressed data as  \n"
	"numpy array input.                                \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"array : numpy array(uint8)                        \n"
	"    Numpy array of 1d compressed data.            \n"
	"width : int                                       \n"
	"    Width of original resolution.                 \n"
	"height : int                                      \n"
	"    Height of original resolution.                \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Sequence number of compressed data.           \n"
	"\"\"                                              \n");
	int extractSequenceNo(py::array_t<uint8_t>& array, int width, int height)
	{
		unsigned short seq;
		auto ret = PUC_ExtractSequenceNo(array.mutable_data(), width, height, &seq);
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_ExtractSequenceNo", ret));
		}

		return seq;
	}

	PY_DOC(DOC_NUM_DECODE_THREAD,
	"\"\"Get number of thread to decode.               \n"
	"                                                  \n"
	"This return number of thread to decode. decode in \n"
	"this object use this number of thread.            \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Number of thread                              \n"
	"\"\"                                              \n");
	int numDecodeThread() { return m_numThread; }

	PY_DOC(DOC_SET_NUM_DECODE_THREAD,
	"\"\"Set number of thread to decode.               \n"
	"                                                  \n"
	"Set number of thread to decode. min = 1, max = 32.\n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"num : int                                         \n"
	"    Number of thread                              \n"
	"\"\"                                              \n");
	void setNumDecodeThread(int num) { m_numThread = num; }

	PY_DOC(DOC_GET_AVAILABLE_GPU_PROCESS,
	"\"\"This retrieves whether the PC is capable of GPU processing. \n"
	"																 \n"
	"Returns														 \n"
	"-------														 \n"
	"bool															 \n"
	"    Returns PUC_SUCCEEDED if GPU processing is possible,		 \n" 
	"	 otherwise returns false.									 \n"
	"\"\"															 \n");
	bool getAvailableGPUProcess()
	{
		if (PUC_CHK_FAILED(PUC_GetAvailableGPUProcess()))
			return false;
		
		return true;
	}

	PY_DOC(DOC_SETUP_GPU_DECODE,
	"\"\"Allocates memory for GPU processing.          \n"
	"                                                  \n"
	"Parameters                                        \n"
	"----------                                        \n"
	"param : GPUSetup obj							   \n"
	"        This is a configuration parameter.        \n"
	"                                                  \n"
	"\"\"                                              \n");
	void setupGPUDecode(GPUSetup param)
	{
		m_param.width = param.width;
		m_param.height = param.height;
		auto ret = PUC_SetupGPUDecode(m_param);
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_SetupGPUDecode", ret));
		}
	}

	PY_DOC(DOC_TEARDOWN_GPU_DECODE,
	"\"\"Releases memory used by GPU processing.       \n"
	"                                                  \n"
	"\"\"                                              \n");
	void teardownGPUDecode()
	{
		auto ret = PUC_TeardownGPUDecode();
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_TeardownGPUDecode", ret));
		}
	}

	PY_DOC(DOC_ISSETUP_GPU_DECODE,
	"\"\"Retrieves whether GPU decode memory is allocated.  \n"
	"														\n"
	"Parameters												\n"
	"----------											    \n"
	"status : bool							                \n"
	"        true : allocated, false : not allocated.       \n"
	"                                                       \n"
	"\"\"                                                   \n");
	void isSetupGPUDecode(bool& status)
	{
		PUC_IsSetupGPUDecode(status);
	}

	PY_DOC(DOC_GET_GPU_LAST_ERROR,
	"\"\"Retrieves the error code from the last GPU processing. \n"
	"															\n"
	"Parameters													\n"
	"----------													\n"
	"errorCode : int							                \n"
	"        The error code from GPU.							\n"
	"															\n"
	"\"\"														\n");
	void getGPULastError(int& errorCode)
	{
		PUC_GetGPULastError(errorCode);
	}

private:
	void decode(uint8_t* src, uint8_t* dst, int x, int y, int w, int h, int lb)
	{
		auto ret = PUC_DecodeDataMultiThread(dst, x, y, w, h, lb, src, m_quantize, m_numThread);
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_DecodeDataMultiThread", ret));
		}
	}

	void decodeDC(uint8_t* src, uint8_t* dst, int bx, int by, int countX, int countY)
	{
		auto ret = PUC_DecodeDCData(dst, bx, by, countX, countY, src);
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_DecodeDCData", ret));
		}
	}

	void decodeGPU(bool download, uint8_t* src, uint8_t** dst, int lineBytes)
	{
		auto ret = PUC_DecodeGPU(download, src, dst, lineBytes);
		if (PUC_CHK_FAILED(ret))
		{
			// GPUÉGÉâÅ[ÇéÊìæÇ∑ÇÈ
			int err;
			PUC_GetGPULastError(err);
			printf("GPU Error=%d", err);
			throw(PUCException("PUC_DecodeGPU", ret));
		}
	}

	unsigned short m_quantize[PUC_Q_COUNT];
	int m_numThread;
	PUC_GPU_SETUP_PARAM m_param;
};