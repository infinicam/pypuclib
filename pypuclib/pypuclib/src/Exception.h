#pragma once

#include "Common.h"

static const std::map<PUCRESULT, std::string> messages =
{
	{PUC_SUCCEEDED,						"succeeded"},
	{PUC_ERROR_UNINITIALIZE,			"puclib is not initialized."},
	{PUC_ERROR_INITIALIZED,				"initialization has already completed."},
	{PUC_ERROR_NOT_EXIST_DEVICE_NO,		"the specified deviceNo doesn't exist."},
	{PUC_ERROR_ILLEGAL_DEVICE_HANDLE,	"the specified device handle may be null."},
	{PUC_ERROR_ILLEGAL_ARG,				"the specified argument may be null." },
	{PUC_ERROR_ILLEGAL_RESOLUTION,		"the specified resolution cannot be set."},
	{PUC_ERROR_ILLEGAL_FRAME_RATE,		"the specified framerate cannot be set."},
	{PUC_ERROR_ILLEGAL_EXPOSE_CLOCK,	"the specified exposure time or non-exposure time (clock units) cannot be set."},
	{PUC_ERROR_DEVICE_OPEN,				"failed to open the device."},
	{PUC_ERROR_DEVICE_NOTOPEN,			"the device is not open."},
	{PUC_ERROR_DEVICE_READ,				"failed to read data from the device."},
	{PUC_ERROR_DEVICE_WRITE,			"failed to write data from the device."},
	{PUC_ERROR_MODULE_LOAD,				"couldn't load sdk modules."},
	{PUC_ERROR_LOCK_TIMEOUT,			"exclusive process of the function has timed out."},
	{PUC_ERROR_GET_CMD,					"failed to send a GET command to the device."},
	{PUC_ERROR_SET_CMD,					"failed to send a SET command to the device."},
	{PUC_ERROR_NOTEQUAL_READ_SIZE,		"the data of specified size could not be read from the device."},
	{PUC_ERROR_NOTEQUAL_WRITE_SIZE,		"the data of specified size could not be written from the device."},
	{PUC_ERROR_XFER_DATA_INVALID_HEADER,"the header information in the data received from the device is invalid."},
	{PUC_ERROR_XFER_DATA_BEGIN,			"unable to start data transfer."},
	{PUC_ERROR_XFER_DATA_WAIT,			"an unexpected error occurred during waiting for a data transfer from the device."},
	{PUC_ERROR_XFER_DATA_FINISH,		"the data transfer ended abnormally."},
	{PUC_ERROR_XFERRING,				"unable to process as a data transfer is in progress."},
	{PUC_ERROR_RING_BUF_COUNT,			"the specified ring buffer count is invalid." },
	{PUC_ERROR_SYNC_EXTERNAL,			"unable to process as a synchronize to external signal is in progress." },
};


class PUCException : public std::exception
{
public:
    PUCException(const std::string& funcName, PUCRESULT errorCode)
		:std::exception(converToMessage(funcName, errorCode).c_str())
	{
	}
	PUCException(const std::string& message)
		:std::exception(message.c_str())
	{
	}
    virtual ~PUCException() {}

private:
	static const std::string converToMessage(const std::string& func, PUCRESULT error)
	{
		std::string ret = func + ":" + 
						  std::to_string(error) + " ";

		auto it = messages.find(error);
		if(it == messages.end()){
			return ret;
		}
		return ret + it->second;
	}
};


class WrapperException : public std::exception
{
public:
	WrapperException(const std::string& message)
		:std::exception(message.c_str())
	{
	}
	virtual ~WrapperException() {}
};