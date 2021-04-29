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
		if (!data->compressed()) {
			throw(WrapperException("the data already decoded."));
		}

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
		if (!data->compressed()) {
			throw(WrapperException("the data already decoded."));
		}

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

private:
	void decode(uint8_t* src, uint8_t* dst, int x, int y, int w, int h, int lb)
	{
		auto ret = PUC_DecodeDataMultiThread(dst, x, y, w, h, lb, src, m_quantize, m_numThread);
		if (PUC_CHK_FAILED(ret)) {
			throw(PUCException("PUC_DecodeDataMultiThread", ret));
		}
	}

	unsigned short m_quantize[PUC_Q_COUNT];
	int m_numThread;
};