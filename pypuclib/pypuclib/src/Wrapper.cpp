#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/functional.h>

#include "Common.h"
#include "Utility.h"

#include "CameraFactory.h"
#include "Camera.h"
#include "Decoder.h"
#include "XferData.h"
#include "Exception.h"

using std::unique_ptr;
using std::vector;
namespace py = pybind11;

PYBIND11_MODULE(pypuclib, m) {
    m.doc() = "This module is a Python Wrapper for SDK(PUCLIB) of PHOTRON high-speed camera INFINICAM \n"
        	  "See README to more instruction to control package \n"
              ""
              "Copyright (C) 2021 PHOTRON LIMITED";

    py::class_<CameraFactory, unique_ptr<CameraFactory, py::nodelete>>(m, "CameraFactory")
        .def(py::init([]() {
            return unique_ptr<CameraFactory, py::nodelete>(&CameraFactory::instance());
    }))
        .def("detect", &CameraFactory::detect, CameraFactory::DOC_DETECT)
        .def("create", &CameraFactory::create, CameraFactory::DOC_CREATE, py::arg("deviceNo") = 0, py::arg("openAuto") = true);

    py::class_<Camera, unique_ptr<Camera, py::nodelete>>(m, "Camera")
        .def("open", &Camera::open, Camera::DOC_OPEN)
        .def("close", &Camera::close, Camera::DOC_CLOSE)
        .def("resolution", &Camera::resolution, Camera::DOC_RESOLUTION)
        .def("setResolution", py::overload_cast<const int&, const int&>(&Camera::setResolution), Camera::DOC_SET_RESOLUTION_A)
        .def("setResolution", py::overload_cast<const Resolution&>(&Camera::setResolution), Camera::DOC_SET_RESOLUTION_B)
        .def("resolutionMax", &Camera::resolutionMax, Camera::DOC_RESOLUTION_MAX)
        .def("resolutionLimit", &Camera::resolutionLimit, Camera::DOC_RESOLUTION_LIMIT)
        .def("framerate", &Camera::framerate, Camera::DOC_FRAMERATE)
        .def("framerateMax", &Camera::framerateMax, Camera::DOC_FRAMERATE_MAX)
        .def("shutter", &Camera::shutter, Camera::DOC_SHUTTER)
        .def("framerateShutter", &Camera::framerateShutter, Camera::DOC_FRAMERATE_SHUTTER)
        .def("setFramerate", &Camera::setFramerate, Camera::DOC_SET_FRAMERATE)
        .def("setShutter", &Camera::setShutter, Camera::DOC_SET_SHUTTER)
        .def("setFramerateShutter", &Camera::setFramerateShutter, Camera::DOC_SET_FRAMERATE_SHUTTER)
        .def("colortype", &Camera::colortype, Camera::DOC_COLORTYPE)
        .def("ringBufferCount", &Camera::ringBufferCount, Camera::DOC_RINGBUFFER_COUNT)
        .def("setRingBufferCount", &Camera::setRingBufferCount, Camera::DOC_SET_RINGBUFEFR_COUNT)
        .def("xferTimeout", &Camera::xferTimeout, Camera::DOC_XFER_TIMEOUT)
        .def("setXferTimeout", &Camera::setXferTimeout, Camera::DOC_SET_XFER_TIMEOUT)
        .def("beginXfer", &Camera::beginXfer, Camera::DOC_BEGIN_XFER)
        .def("endXfer", &Camera::endXfer, Camera::DOC_END_XFER)
        .def("isXferring", &Camera::isXferring, Camera::DOC_IS_XFERRING)
        .def("decoder", &Camera::decoder, Camera::DOC_DECODER)
        .def("grab", &Camera::grab, Camera::DOC_GRAB)
        .def("resetDevice", &Camera::resetDevice, Camera::DOC_RESETDEVICE)
        .def("resetSequenceNo", &Camera::resetSequenceNo, Camera::DOC_RESETSEQUENCENO)
        .def("framerateLimit", &Camera::framerateLimit, Camera::DOC_FRAMERATE_LIMIT)
        .def("fanState", &Camera::fanState, Camera::DOC_FAN_STATE)
        .def("setFanState", &Camera::setFanState, Camera::DOC_SET_FAN_STATE)
        .def("sensorTemperature", &Camera::sensorTemperature, Camera::DOC_SENSOR_TEMPERATURE);

    py::class_<Resolution>(m, "Resolution", Resolution::DOC_CLASS_RESOLUTION)
        .def(py::init<>())
        .def(py::init<const int&, const int&>())
        .def("__eq__", &Resolution::operator==)
        .def_readwrite("width", &Resolution::width)
        .def_readwrite("height", &Resolution::height)
        .def("__repr__", [](const Resolution& res) {
            return "(" + std::to_string(res.width) + ","  + std::to_string(res.height) +")";
        });

    py::class_<Limit>(m, "Limit", Limit::DOC_CLASS_LIMIT)
        .def_readonly("min", &Limit::min)
        .def_readonly("max", &Limit::max)
        .def_readonly("step", &Limit::step)
        .def("__repr__", [](const Limit& lim) {
            return "(min=" + std::to_string(lim.min) +
                   ",max=" + std::to_string(lim.max) +
                   ",step=" + std::to_string(lim.step) + ")";
        });

    py::class_<ResolutionLimit>(m, "ResolutionLimit", ResolutionLimit::DOC_CLASS_RESOLUTION_LIMIT)
        .def_readonly("limitW", &ResolutionLimit::limitW)
        .def_readonly("limitH", &ResolutionLimit::limitH);

    py::class_<FramerateLimit>(m, "FramerateLimit", FramerateLimit::DOC_CLASS_FRAMERATE_LIMIT)
        .def_readonly("limitMin", &FramerateLimit::min)
        .def_readonly("limitMax", &FramerateLimit::max);

    py::class_<GPUSetup>(m, "GPUSetup", GPUSetup::DOC_CLASS_GPU_SETUP)
        .def(py::init<>())
        .def(py::init<const int&, const int&>())
        .def_readwrite("width", &GPUSetup::width)
        .def_readwrite("height", &GPUSetup::height);

    py::class_<XferData>(m, "XferData")
        .def("dataSize", &XferData::dataSize, XferData::DOC_DATASIZE)
        .def("sequenceNo", &XferData::sequenceNo, XferData::DOC_SEQUENCENO)
        .def("data", &XferData::data, XferData::DOC_DATA)
        .def("resolution", &XferData::resolution, XferData::DOC_RESOLUTION);

    py::class_<Decoder>(m, "Decoder")
        .def(py::init<>())
        .def(py::init<const vector<int>&>())
        .def("quantization", &Decoder::quantization, Decoder::DOC_QUANTIZATION)
        .def("setQuantization", &Decoder::setQuantization, Decoder::DOC_SET_QUANTIZATION)
        .def("decode", py::overload_cast<XferData*>(&Decoder::decode), Decoder::DOC_DECODE_A)
        .def("decode", py::overload_cast<XferData*, int, int, int, int>(&Decoder::decode), Decoder::DOC_DECODE_B)
        .def("decode", py::overload_cast<py::array_t<uint8_t>&, const Resolution&>(&Decoder::decode), Decoder::DOC_DECODE_C)
        .def("decode", py::overload_cast<py::array_t<uint8_t>&, int, int, int, int>(&Decoder::decode), Decoder::DOC_DECODE_D)
        .def("numDecodeThread", &Decoder::numDecodeThread, Decoder::DOC_NUM_DECODE_THREAD)
        .def("setNumDecodeThread", &Decoder::setNumDecodeThread, Decoder::DOC_SET_NUM_DECODE_THREAD)
        .def("extractSequenceNo", &Decoder::extractSequenceNo, Decoder::DOC_EXTRACT_SEQUENCENO)
        .def("decodeDC", py::overload_cast<py::array_t<uint8_t>&, int, int, int, int>(&Decoder::decodeDC), Decoder::DOC_DECODE_DC_A)
        .def("decodeDC", py::overload_cast<XferData*, int, int, int, int>(&Decoder::decodeDC), Decoder::DOC_DECODE_DC_B)
        .def("decodeGPU", py::overload_cast<py::array_t<uint8_t>&, bool, int>(&Decoder::decodeGPU), Decoder::DOC_DECODE_GPU_A)
        .def("decodeGPU", py::overload_cast<XferData*, bool, int>(&Decoder::decodeGPU), Decoder::DOC_DECODE_GPU_B)
        .def("getAvailableGPUProcess", &Decoder::getAvailableGPUProcess, Decoder::DOC_GET_AVAILABLE_GPU_PROCESS)
        .def("setupGPUDecode", &Decoder::setupGPUDecode, Decoder::DOC_SETUP_GPU_DECODE)
        .def("teardownGPUDecode", &Decoder::teardownGPUDecode, Decoder::DOC_TEARDOWN_GPU_DECODE)
        .def("isSetupGPUDecode", &Decoder::isSetupGPUDecode, Decoder::DOC_ISSETUP_GPU_DECODE)
        .def("getGPULastError", &Decoder::getGPULastError, Decoder::DOC_GET_GPU_LAST_ERROR);

    py::enum_<PUC_COLOR_TYPE>(m, "PUC_COLOR_TYPE")
        .value("PUC_COLOR_MONO", PUC_COLOR_MONO)
        .value("PUC_COLOR_COLOR", PUC_COLOR_COLOR)
        .export_values();


    static py::exception<PUCException> puc_exc(m, "PUCException", PyExc_RuntimeError);
    static py::exception<WrapperException> wrapper_exc(m, "WrapperException", PyExc_RuntimeError);
    py::register_exception_translator([](std::exception_ptr p) {
        try {
            if (p) std::rethrow_exception(p);
        }
        catch (const PUCException& e) {
            puc_exc(e.what());
        }
        catch (const WrapperException& e) {
            wrapper_exc(e.what());
        }
    });
}