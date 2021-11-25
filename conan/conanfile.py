from conans import ConanFile


class VideoSequencerConan(ConanFile):
    name = "VideoSequencer"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    requires = "opencv/4.5.3"
    generators = "cmake_find_package", "cmake", "cmake_paths"
