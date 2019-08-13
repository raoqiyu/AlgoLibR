import os
import shutil
import versioneer
from Cython.Build import cythonize
from setuptools.extension import Extension
from setuptools import setup, find_packages
from distutils.sysconfig import get_python_lib


name = 'cumlRao'
version = '0.1'

install_requires = [
    'numpy',
    'cython>=0.29<0.30',
]

exc_list = []

cython_files = ['cumlRao/*/*.pyx']
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
      description='cuMLRao - RAPIDS ML Algorithms',
      long_description=open('README.md', encoding='UTF-8').read(),
      long_description_content_type='text/markdown',
      url='https://github.com/raoqiyu',
      version=versioneer.get_version(),
      classifiers=[
          "Intended Audience :: Developers",
          "Programming Language :: Python",
          "Programming Language :: Python :: 3.6",
          "Programming Language :: Python :: 3.7"
      ],
      packages=find_packages(include=['cumlRao', 'cumlRao.*']),
      author="WahahR",
      setup_requires=['cython'],
      license='Apache 2.0',
      install_requires=install_requires,
      python_requires='>=3.6,<3.8',
      ext_modules=cythonize(extensions,
                            exclude=exc_list),
      cmdclass=versioneer.get_cmdclass(),
      zip_safe=False
      )

#convert_to_manylinux(name, version)
