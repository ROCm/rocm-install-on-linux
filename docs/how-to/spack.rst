.. meta::
  :description: How to use Spack to install ROCm.
  :keywords: Spack, package management tool, AMD, ROCm

************************************
Using Spack to install ROCm packages
************************************

Spack is a package management tool designed to support multiple software
versions and configurations on a wide variety of platforms and environments. It
was designed for large supercomputing centers, where many users share common
software installations on clusters with exotic architectures using libraries
that do not have a standard ABI. Spack is non-destructive: installing a new
version does not break existing installations, so many configurations can
coexist on the same system.

Most importantly, Spack is simple. It offers a simple ``spec`` syntax, so users
can concisely specify versions and configuration options. Spack is also simple
for package authors: package files are written in pure Python, and specs allow
package authors to maintain a single file for many different builds of the same
package.

See the `official Spack documentation <https://spack-tutorial.readthedocs.io/en/latest/>`_ for more information.

Installing prerequisites for Spack
==================================

.. note::
    You must install all prerequisites before installing Spack.


.. tab-set::
    .. tab-item:: Ubuntu
        :sync: Ubuntu

        .. code-block:: shell

            # Install some essential utilities:
            apt-get update
            apt-get install make patch bash tar gzip unzip bzip2 file gnupg2 git gawk
            apt-get update -y
            apt-get install -y xz-utils
            apt-get install build-essential
            apt-get install vim
            apt-get install libpci-dev
            # Install Python:
            apt-get install python3
            apt-get upgrade python3-pip
            # Install Compilers:
            apt-get install gcc
            apt-get install gfortran

    .. tab-item:: SLES
        :sync: SLES

        .. code-block:: shell

            # Install some essential utilities:
            zypper update
            zypper install make patch bash tar gzip unzip bzip xz file gnupg2 git awk
            zypper in -t pattern
            zypper install vim
            # Install Python:
            zypper install python3
            zypper install python3-pip
            # Install Compilers:
            zypper install gcc
            zypper install gcc-fortran
            zypper install gcc-c++

Building ROCm components using Spack
===================================================

1. To use the Spack package manager, clone the Spack project from `<https://github.com/spack/spack>`__.

   .. code-block:: shell

      git clone https://github.com/spack/spack.git

2. Initialize Spack.

   The ``setup-env.sh`` script initializes the Spack environment.

   .. code-block:: shell

      cd spack
      . share/spack/setup-env.sh

   Spack commands are available once the above steps are completed. To list the available commands, use ``help``.

   .. code-block:: shell

      spack help


ROCm packages in Spack
===================================================

.. list-table::
   :header-rows: 1

   * - Component
     - Spack package name
     - Minimum supported version
     - Latest supported version

   * - AMD SMI
     - ``amdsmi``
     - 5.6.0
     - 6.4.2

   * - aqlprofile
     - ``aqlprofile``
     - 5.6.0
     - 6.4.2

   * - comgr
     - ``comgr``
     - 5.6.0
     - 6.4.2

   * - Composable Kernel
     - ``composable-kernel``
     - 5.6.0
     - 6.4.2

   * - devicelibs
     - ``rocm-device-libs``
     - 5.6.0
     - 6.4.2

   * - HIP (hip_in_vdi)
     - ``hip``
     - 5.6.0
     - 6.4.2

   * - hipBLAS
     - ``hipblas``
     - 5.6.0
     - 6.4.2

   * - hipBLASLt
     - ``hipblaslt``
     - 6.0.0
     - 6.4.2

   * - HIPCC
     - ``hipcc``
     - 5.7.0
     - 6.4.2

   * - hipCUB
     - ``hipcub``
     - 5.6.0
     - 6.4.2

   * - hipFFT
     - ``hipfft``
     - 5.6.0
     - 6.4.2

   * - hipfort
     - ``hipfort``
     - 5.6.0
     - 6.4.2

   * - HIPIFY
     - ``hipify-clang``
     - 5.6.0
     - 6.4.2

   * - hipRAND
     - ``hiprand``
     - 5.6.0
     - 6.4.2

   * - hipSOLVER
     - ``hipsolver``
     - 5.6.0
     - 6.4.2

   * - hipSPARSE
     - ``hipsparse``
     - 5.6.0
     - 6.4.2

   * - hipSPARSELt
     - ``hipsparselt``
     - 6.0.0
     - 6.4.2

   * - hipTensor
     - ``hip-tensor``
     - 5.7.0
     - 6.4.2

   * - HIP Tests
     - ``hip-tests``
     - 6.1.0
     - 6.4.2

   * - lightning
     - ``llvm-amdgpu``
     - 5.6.0
     - 6.4.2

   * - MIOpen (HIP)
     - ``miopen-hip``
     - 5.6.0
     - 6.4.2

   * - MIGraphX
     - ``migraphx``
     - 5.6.0
     - 6.4.2

   * - MIVisionX
     - ``mivisionx``
     - 5.6.0
     - 6.4.2

   * - OpenCL
     - ``rocm-opencl``
     - 5.6.0
     - 6.4.2

   * - openmp-extras
     - ``rocm-openmp-extras``
     - 5.6.0
     - 6.4.2

   * - RCCL
     - ``rccl``
     - 5.6.0
     - 6.4.2

   * - rocAL
     - ``rocal``
     - 6.2.0
     - 6.4.2

   * - rocALUTION
     - ``rocalution``
     - 5.6.0
     - 6.4.2

   * - rocBLAS
     - ``rocblas``
     - 5.6.0
     - 6.4.2

   * - ROCdbgapi
     - ``rocm-dbgapi``
     - 5.6.0
     - 6.4.2

   * - rocDecode
     - ``rocdecode``
     - 6.1.0
     - 6.4.2

   * - rocFFT
     - ``rocfft``
     - 5.6.0
     - 6.4.2

   * - rocJPEG
     - ``rocjpeg``
     - 6.3.0
     - 6.4.2

   * - rocm-core
     - ``rocm-core``
     - 5.6.0
     - 6.4.2

   * - rocminfo
     - ``rocminfo``
     - 5.6.0
     - 6.4.2

   * - rocMLIR
     - ``rocmlir``
     - 5.4.0
     - 6.4.2

   * - ROCm Bandwidth Test
     - ``rocm-bandwidth-test``
     - 5.6.0
     - 6.4.2

   * - rocm-cmake
     - ``rocm-cmake``
     - 5.6.0
     - 6.4.2

   * - ROCm Compute Profiler

     - ``rocprofiler-compute``
     - 6.3.2
     - 6.4.2

   * - ROCm Data Center Tool (RDC)
     - ``rdc``
     - 5.6.0
     - 6.4.2

   * - ROCm Debug Agent
     - ``rocm-debug-agent``
     - 5.6.0
     - 6.4.2

   * - ROCm Debugger (ROCgdb)
     - ``rocm-gdb``
     - 5.6.0
     - 6.4.2

   * - ROCm Examples
     - ``rocm-examples``
     - 6.2.0
     - 6.4.2

   * - ROCm SMI Library
     - ``rocm-smi-lib``
     - 5.6.0
     - 6.4.2

   * - ROCm Systems Profiler
     - ``rocprofiler-systems``
     - 6.3.0
     - 6.4.2

   * - ROCm Validation Suite
     - ``rocm-validation-suite``
     - 5.6.0
     - 6.4.2

   * - rocPRIM
     - ``rocprim``
     - 5.6.0
     - 6.4.2

   * - ROCProfiler
     - ``rocprofiler-dev``
     - 5.6.0
     - 6.4.2

   * - rocprofiler-register
     - ``rocprofiler-register``
     - 6.1.0
     - 6.4.2

   * - ROCprofiler-SDK
     - ``rocprofiler-sdk``
     - 6.2.4
     - 6.4.2

   * - rocPyDecode
     - ``rocpydecode``
     - 6.2.0
     - 6.4.2

   * - rocRAND
     - ``rocrand``
     - 5.6.0
     - 6.4.2

   * - ROCr Runtime
     - ``hsa-rocr-dev``
     - 5.6.0
     - 6.4.2

   * - rocSHMEM
     - ``rocshmem``
     - 6.4.0
     - 6.4.2

   * - rocSOLVER
     - ``rocsolver``
     - 5.6.0
     - 6.4.2

   * - rocSPARSE
     - ``rocsparse``
     - 5.6.0
     - 6.4.2

   * - rocThrust
     - ``rocthrust``
     - 5.6.0
     - 6.4.2

   * - ROCTracer
     - ``roctracer-dev``
     - 5.6.0
     - 6.4.2

   * - roctracer-dev-api
     - ``roctracer-dev-api``
     - 5.6.0
     - 6.4.2

   * - rocWMMA
     - ``rocwmma``
     - 5.6.0
     - 6.4.2

   * - ROCm Performance Primitives (RPP)
     - ``rpp``
     - 5.7.0
     - 6.4.2

   * - Tensile
     - ``rocm-tensile``
     - 5.6.0
     - 6.4.2

   * - TransferBench
     - ``transferbench``
     - 6.3.0
     - 6.4.2

   * - atmi
     - ``atmi``
     - 5.5.0
     - 5.5.1 (final)

   * - clang-ocl
     - ``rocm-clang-ocl``
     - 5.5.0
     - 6.1.2 (final)

   * - mlirmiopen
     - ``mlirmiopen``
     - 5.3.0
     - 5.4.0 (deprecated)

   * - MIOpen (GEMM)
     - ``miopengemm``
     - 5.5.0
     - 5.5.1 (final)

   * - MIOpen (OpenCL)
     - ``miopen-opencl``
     - 5.5.0
     - 5.5.1 (final)

   * - Omniperf
     - ``omniperf``
     - 6.2.0
     - 6.3.1 (final)

   * - Omnitrace
     - ``omnitrace``
     - rocm-6.2.0
     - rocm-6.3.0 (final)

   * - rocclr (vdi)
     - ``hip-rocclr``
     - 5.5.0
     - 5.6.1 (final)

   * - ROCT Thunk Interface
     - ``hsakmt-roct``
     - 5.5.0
     - 6.2.4 (final)

Installing ROCm components using Spack
===================================================

1. ``rocm-cmake``

   Install the default variants and the latest version of ``rocm-cmake``.

   .. code-block:: shell

      spack install rocm-cmake

   To install a specific version of ``rocm-cmake``, use:

   .. code-block:: shell

      spack install rocm-cmake@<version number>

   For example, ``spack install rocm-cmake@6.4.2``

2. ``info``

   The ``info`` command displays basic package information. It shows the preferred, safe, and
   deprecated versions, in addition to the available variants. It also shows the dependencies with other
   packages.

   .. code-block:: shell

      spack info mivisionx

   For example:

   .. code-block:: shell-session

      $ spack info mivisionx
      CMakePackage:   mivisionx

      Description:
          MIVisionX toolkit is a set of comprehensive computer vision and machine
          intelligence libraries, utilities, and applications bundled into a
          single toolkit.

      Homepage: https://github.com/ROCm/MIVisionX

      Preferred version:
          6.4.2    https://github.com/ROCm/MIVisionX/archive/rocm-6.4.2.tar.gz

      Safe versions:
          6.4.2    https://github.com/ROCm/MIVisionX/archive/rocm-6.4.2.tar.gz
          6.4.1    https://github.com/ROCm/MIVisionX/archive/rocm-6.4.1.tar.gz
          6.4.0    https://github.com/ROCm/MIVisionX/archive/rocm-6.4.0.tar.gz
          6.3.3    https://github.com/ROCm/MIVisionX/archive/rocm-6.3.3.tar.gz
          6.3.2    https://github.com/ROCm/MIVisionX/archive/rocm-6.3.2.tar.gz
          6.3.1    https://github.com/ROCm/MIVisionX/archive/rocm-6.3.1.tar.gz
          6.3.0    https://github.com/ROCm/MIVisionX/archive/rocm-6.3.0.tar.gz
          6.2.4    https://github.com/ROCm/MIVisionX/archive/rocm-6.2.4.tar.gz
          6.2.1    https://github.com/ROCm/MIVisionX/archive/rocm-6.2.1.tar.gz
          6.2.0    https://github.com/ROCm/MIVisionX/archive/rocm-6.2.0.tar.gz
          6.1.2    https://github.com/ROCm/MIVisionX/archive/rocm-6.1.2.tar.gz
          6.1.1    https://github.com/ROCm/MIVisionX/archive/rocm-6.1.1.tar.gz
          6.1.0    https://github.com/ROCm/MIVisionX/archive/rocm-6.1.0.tar.gz
          6.0.2    https://github.com/ROCm/MIVisionX/archive/rocm-6.0.2.tar.gz
          6.0.0    https://github.com/ROCm/MIVisionX/archive/rocm-6.0.0.tar.gz
          5.7.1    https://github.com/ROCm/MIVisionX/archive/rocm-5.7.1.tar.gz
          5.7.0    https://github.com/ROCm/MIVisionX/archive/rocm-5.7.0.tar.gz

      Deprecated versions:
          5.6.1    https://github.com/ROCm/MIVisionX/archive/rocm-5.6.1.tar.gz
          5.6.0    https://github.com/ROCm/MIVisionX/archive/rocm-5.6.0.tar.gz

      Variants:
          add_tests [false]           false, true
              add tests and samples folder
          asan [false]                false, true
              Build with address-sanitizer enabled or disabled
          build_system [cmake]        cmake
              Build systems supported by the package
          hip [true]                  false, true
              Use HIP as backend
          opencl [false]              false, true
              Use OPENCL as the backend

          when build_system=cmake
            build_type [Release]      Debug, MinSizeRel, RelWithDebInfo, Release
                CMake build type
            generator [make]          none
                the build system generator to use

          when build_system=cmake ^cmake@3.9:
            ipo [false]               false, true
                CMake interprocedural optimization

      Build Dependencies:
          cmake  ffmpeg  hip           libjpeg-turbo  lmdb      miopen-hip  opencv   protobuf   py-google-api-python-client  py-protobuf  py-pytz        py-wheel  rapidjson  rpp
          cxx    gmake   hsa-rocr-dev  llvm-amdgpu    migraphx  ninja       openssl  py-future  py-numpy                     py-pybind11  py-setuptools  python    rocm-core

      Link Dependencies:
          hip  hsa-rocr-dev  llvm-amdgpu  lmdb  migraphx  miopen-hip  openssl  py-future  py-google-api-python-client  py-numpy  py-pybind11  py-pytz  py-setuptools  py-wheel  rapidjson  rocm-core  rpp

      Run Dependencies:
          py-protobuf

      Licenses:
          MIT


Installing variants for ROCm components
===================================================

The variants listed above indicate that the ``mivisionx`` package is built by
default with ``build_type=Release`` and the ``hip`` backend, and without the
``opencl`` backend. ``build_type=Debug`` and ``RelWithDebInfo``, with ``opencl``
and without ``hip``, are also supported.

For example:

.. code-block:: shell

   spack install mivisionx build_type=Debug #Backend will be hip since it is the default one
   spack install mivisionx+opencl build_type=Debug #Backend will be opencl and hip will be disabled as per the conflict defined in recipe


* ``spack spec`` command

  To display the dependency tree, the ``spack spec`` command can be used with the same format.

  For example:

  .. code-block:: shell-session

     $ spack spec mivisionx

     -   mivisionx@6.4.2~add_tests~asan+hip~ipo build_system=cmake build_type=Release generator=make platform=linux os=ubuntu22.04 target=zen2 %cxx=gcc@11.4.0
     -       ^cmake@3.31.8~doc+ncurses+ownlibs~qtgui build_system=generic build_type=Release platform=linux os=ubuntu22.04 target=zen2 %c,cxx=gcc@11.4.0
     -           ^curl@8.15.0~gssapi~ldap~libidn2~librtmp~libssh~libssh2+nghttp2 build_system=autotools libs:=shared,static tls:=openssl platform=linux os=ubuntu22.04 target=zen2 %c,cxx=gcc@11.4.0
     -               ^nghttp2@1.65.0 build_system=autotools platform=linux os=ubuntu22.04 target=zen2 %c,cxx=gcc@11.4.0
     ...

Creating an environment
===================================================

You can create an environment with all the required components of your version.

1. In the root folder, create a new folder when you can create a ``.yaml`` file. This file is used to create an environment.

   .. code-block:: shell

      mkdir /localscratch
      cd /localscratch
      vi sample.yaml

2. Add all the required components in the ``sample.yaml`` file. For example:

   .. code-block:: yaml

      spack:
        concretization: separately
        packages:
          all:
            compiler: [gcc@8.5.0]
        specs:
        - matrix:
          - ['%gcc@8.5.0^cmake@3.19.7']
          - [rocm-cmake@6.4.2, rocm-dbgapi@6.4.2, rocm-debug-agent@6.4.2, rocm-gdb@6.4.2,
            rocminfo@6.4.2, rocm-opencl@6.4.2, rocm-smi-lib@6.4.2, rocm-tensile@6.4.2, rocm-validation-suite@6.4.2,
            rocprim@6.4.2, rocprofiler-dev@6.4.2, rocrand@6.4.2, rocsolver@6.4.2, rocsparse@6.4.2,
            rocthrust@6.4.2, roctracer-dev@6.4.2]
        view: true

3. Once you've created the ``.yaml`` file, you can use it to create an environment.

   .. code-block:: shell

      spack env create -d /localscratch/MyEnvironment /localscratch/sample.yaml

4. Activate the created environment.

   .. code-block:: shell

      spack env activate /localscratch/MyEnvironment

5. Before installing, verify that you want all the component versions.

   .. code-block:: shell

      spack find # this command will list out all components been in the environment (and 0 installed )

6. Install all the components in the ``.yaml`` file.

   .. code-block:: shell

      cd /localscratch/MyEnvironment
      spack install -j 50

7. Check that all components are successfully installed.

   .. code-block:: shell

      spack find

8. If any modification is made to the ``.yaml`` file, you must deactivate the existing environment and create a new one in order for the modifications to be reflected.

   To deactivate, use:

   .. code-block:: shell

      spack env deactivate

Creating and applying a patch before installation
===================================================

Spack installs ROCm packages after pulling the source code from GitHub and building it locally. In
order to build a component with any modification to the source code, you must generate a patch and
apply it before the build phase.

To generate a patch and build with the changes:

1. Stage the source code. For example:

   .. code-block:: shell

      spack stage hip@6.4.2
      # (This will pull the 6.4.2 release version source code of hip and display the path to spack-src directory where entire source code is available)

   You should see something like this:

   .. code-block:: shell-session

      ==> Using cached archive: /data/root/temp/rocm-6.4.2/spack/var/spack/cache/_source-cache/archive/d8/d8dba8cdf05463afb7879de2833983cafa6a006ba719815a35b96d9b92fc7fc4.tar.gz
      ==> Using cached archive: /data/root/temp/rocm-6.4.2/spack/var/spack/cache/_source-cache/archive/82/829e61a5c54d0c8325d02b0191c0c8254b5740e63b8bfdb05eec9e03d48f7d2c.tar.gz
      ==> Using cached archive: /data/root/temp/rocm-6.4.2/spack/var/spack/cache/_source-cache/archive/80/8081d4ab1a43ffa1cebd646668d83008b799ab98c14daf7b455922355a439c8a.tar.gz
      ==> Moving resource stage
              source: /tmp/root/spack-stage/resource-clr-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/
              destination: /tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/clr
      ==> Moving resource stage
              source: /tmp/root/spack-stage/resource-hip-tests-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/
              destination: /tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/hip-tests
      ==> Staged hip in /tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46

2. Change directory to ``spack-src`` inside the staged directory.

   .. code-block:: shell-session

      root@computername:/spack$ cd /tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46
      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46$ cd spack-src/

3. Create a new Git repository.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ git init

4. Add the entire directory to the repository.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ git add .

5. Make the required changes to the source code.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src# vi hipamd/CMakeLists.txt
      # Make required changes in the source code

6. Generate the patch using the ``git diff`` command.

   .. code-block:: shell

      diff > /spack/var/spack/repos/builtin/packages/hip/0001-modifications.patch
      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ git diff > /spack/var/spack/repos/builtin/packages/hip/0001-modifications.patch

7. Update the recipe with the patch file name and any conditions you want to apply.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.4.2-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ spack edit hip

8. Provide the patch file name and the conditions for the patch to be applied in the ``hip`` recipe as follows.

   .. code-block:: shell

      patch("0001-modifications.patch", when="@6.4.2")

   Spack will apply ``0001-modifications.patch`` on the 6.4.2 release code before starting the ``hip`` build.

9. After each modification, you must update the recipe. If there is no change to the recipe, run

   .. code-block:: shell

      touch /spack/var/spack/repos/builtin/packages/hip/package.py
