from glob import glob
from setuptools import setup

from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import os, sys

__version__ = "0.0.1"

ext_modules = [
    Pybind11Extension(
        "pypuclib",
        sorted(glob("src/*.cpp")),
        define_macros = [('VERSION_INFO', __version__)],
        ),
]

setup(
    name="pypuclib",
    version=__version__,
    author="PHOTRON LIMITED",
    author_email="dev-infinicam@photron.co.jp",
    url="https://www.photron.co.jp/",
    description="The python package for PUCLIB to control INFINICAM",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    data_files=[("lib/site-packages", ["dll/PUCLIB.dll"]),
                ("lib/site-packages", ["dll/ICYUSB.dll"])],
    zip_safe=False,
)