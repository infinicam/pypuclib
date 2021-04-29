#pragma once

#include <pybind11/numpy.h>
#include "Common.h"
#include "Utility.h"

class XferData
{
public:
	XferData(int bufferSize, const Resolution& res, const PUC_DATA_MODE& mode)
		:
		m_resolution(res),
		m_xfermode(mode),
		m_isReferred(false)
	{
		memset(&m_info, 0, sizeof(PUC_XFER_DATA_INFO));
		m_info.pData = new uint8_t[bufferSize];
	}
	XferData(PUC_XFER_DATA_INFO* reference, const Resolution& res, const PUC_DATA_MODE& mode)
		:
		m_resolution(res),
		m_xfermode(mode),
		m_isReferred(true)
	{
		m_info.pData = reference->pData;
		m_info.nDataSize = reference->nDataSize;
		m_info.nSequenceNo = reference->nSequenceNo;
	}
	~XferData()
	{
		if (!m_isReferred && m_info.pData != nullptr) {
			delete[] m_info.pData;
			m_info.pData = nullptr;
		}
	}

	PY_DOC(DOC_DATASIZE,
	"\"\"Get data size of xferdata.                    \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Data size of transferred data.                \n"
	"\"\"                                              \n");
	inline unsigned int dataSize() const { return m_info.nDataSize; }

	PY_DOC(DOC_SEQUENCENO,
	"\"\"Get sequence number of the data.              \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"int                                               \n"
	"    Sequence number of transferred data.          \n"
	"\"\"                                              \n");
	inline unsigned short sequenceNo() const { return m_info.nSequenceNo; }

	PY_DOC(DOC_RESOLUTION,
	"\"\"Get resolution of the data.                   \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"Resolution obj                                    \n"
	"    Resolution of transferred data.               \n"
	"\"\"                                              \n");
	inline Resolution resolution() const { return m_resolution; }

	PY_DOC(DOC_DATA,
	"\"\"Get image data based on transfer datamode.    \n"
	"                                                  \n"
	"This method returns numpy array based on datamode.\n"
	"If datamode is PUC_DATA_COMPRESSED, it returns    \n"
	"compressed data as 1d numpy array.                \n"
	"If datamode is PUC_DATA_DECOMPRESSED_GLAY, it     \n"
	"returns 2d numpy array same size as resolution.   \n"
	"                                                  \n"
	"Returns                                           \n"
	"-------                                           \n"
	"numpy array(uint8)                                \n"
	"    Sequence number of transferred data.          \n"
	"\"\"                                              \n");
	inline pybind11::array_t<uint8_t> data() const
	{
		if (compressed()) {
			return pybind11::array_t<uint8_t>({ m_info.nDataSize }, m_info.pData);
		}
		else {
			pybind11::array_t<uint8_t> buf({ m_resolution.height, m_resolution.width});

			copyWithoutAlign(buf.mutable_data(), 
				m_info.pData, m_resolution.width, m_resolution.height);

			return buf;
		}
	}

	inline bool compressed() const { return m_xfermode == PUC_DATA_COMPRESSED; }
	inline PUC_XFER_DATA_INFO* dataInfo() { return &m_info; }
private:
	PUC_XFER_DATA_INFO m_info;
	PUC_DATA_MODE m_xfermode;
	Resolution m_resolution;
	bool m_isReferred;
};