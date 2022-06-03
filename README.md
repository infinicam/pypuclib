# pypuclib

pypuclib is python package for INFINICAM SDK [PUCLIB](https://www.photron.co.jp/products/hsvcam/infinicam/tech.html).
This package allows user to control  [INFINICAM UC-1](https://www.photron.co.jp/products/hsvcam/infinicam/) on python.

## How to Use

1. Install INFINICAM SDK [PUCLIB](https://www.photron.co.jp/products/hsvcam/infinicam/tech.html), driver, and Visual C++ Redistributable 2019.
2. See [Install](#Install) section to install pypuclib package.
3. See [Quick Start](#Quick-start-for-image-processing) section to start programming.

## Install

You can install it in any of the following ways:

* Open command prompt and install using pip from [pypi](https://pypi.org/).

  ```
  pip install pypuclib
  ```

  If you don't register environment variable for python path, use this command instead.

  ```
  py -m pip install pypuclib
  ```

* Install from source code.
  
  ```
  git clone repositryURL
  ```

  Move current directory to pypuclib/pypuclib/ and install using this command.
  
  ```
  pip install ./
  ```

## Quick Start for Image Processing

To connect the first detected camera:

  ```python
  cam = CameraFactory().create()
  ```

And grab the image:

  ```python
  xferdata = cam.grab()
  ```

To decode image, get decoder object from camera and use it like:

  ```python
  decoder = cam.decoder()
  img = decoder.decode(xferdata)
  ```

Decoded array is numpy array, so now you can use to imageprocessing package like opencv directory.

If you want to use only the resion of interest:

  ```python
  x = 0, y = 0, w = 128, h = 128
  img = decoder.decode(xferdata, x, y, w, h)
  ```

This can reduce the decoding time.

## For High Speed Processing

Use beginXfer and endXfer to get callback from C++.

```python
  # xfercallback from c++
  def callback(data) :
    seq = data.sequenceNo()
    if oldSeq != seq:
      # avoid same sequence number.


  # beginn xfer and start callback background
  cam.beginXfer(callback)

  ~~ # some processing here

  cam.endXfer()
```

## How to Run Samples

1. Install pypuclib using pip.

2. Download following sample source code.

3. Run on python.

```python
  python hello_world.py
```

* [hello_world](pypuclib/pypuclib_sample/hello_world.py)

  Sample of streaming a live image and saving a bitmap.

* [create_movie](pypuclib/pypuclib_sample/create_movie.py)

  Sample of saving videos with high speed streaming.

* [tracking_sample](pypuclib/pypuclib_sample/tracking_sample.py)

  Sample of real-time tracking at 1,000 fps.

* [gui_sample](pypuclib/pypuclib_sample/gui_sample.py)

  GUI sample for controlling camera parameters and recording.

* [find_1000](pypuclib/pypuclib_sample/find1000/README.md)

  This sample code implements the a deep learning network to detect objects such as people, cellphones etc.

## Source Code Structure

This repository consists of three projects.

* [pypuclib](pypuclib/pypuclib)
  
  Source code of python wrapper of PUCLIB

* [pupuclib_sample](pypuclib/pypuclib_sample)

  Python sample code using pypucilib

* [pypuclib_test](pypuclib/pypuclib_test)

  Unit test of pypuclib

## Prerequisites

To build pypuclib, the following environment is required.

* Installed Visual Studio 2019

　  :warning: The MSVC compiler is required to build the package.

　  :warning: This package is available for Windows only. 

## Issues

Don't hesitate to ask any questions or issues on GitHub.

#### developped by:
<img src="doc/Photron_logo.png" width="100">
