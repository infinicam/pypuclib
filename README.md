# pypuclib

pypuclib is python package for INFINICAM SDK [PUCLIB](https://www.photron.co.jp/products/hsvcam/infinicam/tech.html).
This package can control  [INFINICAM UC-1](https://www.photron.co.jp/products/hsvcam/infinicam/) on python.

## How to use

1. Install INFINICAM SDK [PUCLIB](https://www.photron.co.jp/products/hsvcam/infinicam/tech.html). and install driver, Visual C++ Redistributable 2019.
2. See [Install](#Install) section to install pypuclib package.
3. See [Quick start](#Quick-start-for-image-processing) section to start programming.

## Install

You can install it in any of the following ways:

* Open command prompt and install using pip from [pypi](https://pypi.org/) 

  ```
  pip install pypuclib
  ```

  If don't register environment variable for python path, use this command instead.

  ```
  py -m pip install pypuclib
  ```

* install from source code
  
  ```
  git clone repositryURL
  ```

  Move current directory to pypuclib/pypuclib/ and install using 
  
  ```
  pip install ./
  ```

## Quick start for image processing

To connect the camera first detected:

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

If want to use only resion of interest:

  ```python
  x = 0, y = 0, w = 128, h = 128
  img = decoder.decode(xferdata, x, y, w, h)
  ```

This can reduce the decoding time.

## For high speed processing

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

## How to run samples

1. Install pypuclib using pip.

2. download following sample source code.

3. run on python.

```python
  python hello_world.py
```

* [hellow_world](pypuclib/pypuclib_sample/hello_world.py)

  hello world sample to stream live image and save bitmap.

* [create_movie](pypuclib/pypuclib_sample/create_movie.py)

  High speed streaming to save video.

* [tracking_sample](pypuclib/pypuclib_sample/tracking_sample.py)

  1000fps realtime tracking sample.

* [gui_sample](pypuclib/pypuclib_sample/create_movie.py)

  GUI samples for control camera parameter and recording.

## Source code structure

This repository consists of three projects.

* [pypuclib](pypuclib/pypuclib)
  
  source code of python wrapper of PUCLIB

* [pupuclib_sample](pypuclib/pypuclib_sample)

  python sample code using pypucilib

* [pypuclib_test](pypuclib/pypuclib_test)

  unit test of pypuclib

## Build Enviroment

To build pypuclib, the following environment is required.

* Installed Visual Studio 2019

　  :warning: Needs MSVC compiler to build package.

　  :warning: This package can use for windows only. 

## Issues

Don't hesitate to ask any questions or issues on GitHub.

#### developped by:
<img src="doc/Photron_logo.png" width="100">
