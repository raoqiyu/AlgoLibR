import os
import shutil
from Cython.Build import cythonize
from setuptools.extension import Extension
from setuptools import setup, find_packages
from distutils.sysconfig import get_python_lib
from cmake_setuptools import CMakeBuildExt, CMakeExtension, \
    convert_to_manylinux, InstallHeaders, distutils_dir_name


name = 'AlgoLibR'
version = '0.1'

install_requires = [
    'numpy',
    'cython>=0.29<0.30',
]

cuda_include_dir = '/usr/local/cuda/include'
cuda_lib_dir = "/usr/local/cuda/lib"

if os.environ.get('CUDA_HOME', False):
    cuda_lib_dir = os.path.join(os.environ.get('CUDA_HOME'), 'lib64')
    cuda_include_dir = os.path.join(os.environ.get('CUDA_HOME'), 'include')


libs = ['AlgoLibR++']
runtime_lib_dirs=['/usr/local/lib/']
include_dirs = ['../cpp/']

if os.environ.get('BUILD_ALGOLIBR_WITH_GPU', 'False') == 'True':
    libs.append('CUDA')
    runtime_lib_dirs.append(cuda_lib_dir)
    include_dirs.append(cuda_include_dir)
    exc_list = []
else:
    exc_list = ['AlgoLibR/**/*gpu.pyx']

cython_files = ['AlgoLibR/**/**.pyx']

extensions = [
    Extension("*",
              sources=cython_files,
              include_dirs=include_dirs,
              library_dirs=[get_python_lib()],
              libraries=libs,
              language='c++',
              runtime_library_dirs= runtime_lib_dirs,
              extra_compile_args=['-std=c++11'],#,'-fopenmp'],
              #extra_link_args=['-lgomp']
)
]


shutil.rmtree('build', ignore_errors=True)

setup(name=name,
      description='AlgoLibR - Algorithms Lib R',
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
      packages=find_packages(),
      license='Apache 2.0',
      install_requires=install_requires,
      # cmdclass=versioneer.get_cmdclass(),
      cmdclass={
          'build_ext': CMakeBuildExt,
          'install_headers': InstallHeaders
      },
      zip_safe=False
      )

# shutil.rmtree('build', ignore_errors=True)
# shutil.rmtree('AlgoLibR.egg-info', ignore_errors=True)
# shutil.rmtree('dist', ignore_errors=True)
