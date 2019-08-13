import os
import shutil
from Cython.Build import cythonize
from setuptools.extension import Extension
from setuptools import setup, find_packages
from distutils.sysconfig import get_python_lib
from cmake_setuptools import CMakeBuildExt, CMakeExtension, \
    convert_to_manylinux, InstallHeaders, distutils_dir_name

name = 'cumlLib'
version = '0.1'

install_requires = [
    'numpy',
    'cython>=0.29<0.30',
]

exc_list = []

cython_files = ['cumlLib/*/*.pyx']
include_dirs = ['../cpp']

extensions = [
    Extension("*",
              sources=cython_files,
              include_dirs=include_dirs,
              library_dirs=[get_python_lib()],
              libraries=[],
              language='c++',
              runtime_library_dirs=[],
              extra_compile_args=['-std=c++11'])
]


shutil.rmtree('build', ignore_errors=True)

setup(name=name,
      description='cumlLib - ML Algorithms',
      #long_description=open('README.md', encoding='UTF-8').read(),
      #long_description_content_type='text/markdown',
      #url='https://github.com/raoqiyu',
      version=version,#versioneer.get_version(),
      classifiers=[
          "Intended Audience :: Developers",
          "Programming Language :: Python",
          "Programming Language :: Python :: 3.6",
          "Programming Language :: Python :: 3.7"
      ],
      author="WahahR",
      setup_requires=['cython'],
      ext_modules=cythonize(extensions,
                            exclude=exc_list),
      packages=find_packages(include=['cumlLib', 'cumlLib.*']),
      license='Apache 2.0',
      install_requires=install_requires,
      #cmdclass=versioneer.get_cmdclass(),
      cmdclass={
          'build_ext': CMakeBuildExt,
          'install_headers': InstallHeaders
      },
      zip_safe=False
      )

shutil.rmtree('build', ignore_errors=True)
shutil.rmtree('cumlLib.egg-info', ignore_errors=True)
shutil.rmtree('dist', ignore_errors=True)
