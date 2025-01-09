.. meta::
  :description: How to use Spack to install ROCm.
  :keywords: Spack, package management tool, AMD, ROCm

*********
Use Spack
*********

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

   * - aqlprofile
     - ``aqlprofile``
     - 5.5.0
     - 6.3.0

   * - comgr
     - ``comgr``
     - 5.5.0
     - 6.3.0

   * - Composable Kernel
     - ``composable-kernel``
     - 5.5.0
     - 6.3.0

   * - devicelibs
     - ``rocm-device-libs``
     - 5.5.0
     - 6.3.0

   * - HIP (hip_in_vdi)
     - ``hip``
     - 5.5.0
     - 6.3.0

   * - hipBLAS
     - ``hipblas``
     - 5.5.0
     - 6.3.0

   * - hipBLASLt
     - ``hipblaslt``
     - 6.0.0
     - 6.3.0

   * - HIPCC
     - ``hipcc``
     - 5.7.0
     - 6.3.0

   * - hipCUB
     - ``hipcub``
     - 5.5.0
     - 6.3.0

   * - hipFFT
     - ``hipfft``
     - 5.5.0
     - 6.3.0

   * - hipfort
     - ``hipfort``
     - 5.5.0
     - 6.3.0

   * - HIPIFY
     - ``hipify-clang``
     - 5.5.0
     - 6.3.0

   * - hipRAND
     - ``hiprand``
     - 5.5.0
     - 6.3.0

   * - hipSOLVER
     - ``hipsolver``
     - 5.5.0
     - 6.3.0

   * - hipSPARSE
     - ``hipsparse``
     - 5.5.0
     - 6.3.0

   * - hipSPARSELt
     - ``hipsparselt``
     - 6.0.0
     - 6.2.4

   * - hipTensor
     - ``hip-tensor``
     - 5.7.0
     - 6.3.0

   * - lightning
     - ``llvm-amdgpu``
     - 5.5.0
     - 6.3.0

   * - MIOpen (HIP)
     - ``miopen-hip``
     - 5.5.0
     - 6.3.0

   * - MIGraphX
     - ``migraphx``
     - 5.5.0
     - 6.3.0

   * - MIVisionX
     - ``mivisionx``
     - 5.5.0
     - 6.3.0

   * - OpenCL
     - ``rocm-opencl``
     - 5.5.0
     - 6.3.0

   * - openmp-extras
     - ``rocm-openmp-extras``
     - 5.5.0
     - 6.3.0

   * - RCCL
     - ``rccl``
     - 5.5.0
     - 6.3.0

   * - rocAL
     - ``rocal``
     - 6.2.0
     - 6.3.0

   * - rocALUTION
     - ``rocalution``
     - 5.5.0
     - 6.3.0

   * - rocBLAS
     - ``rocblas``
     - 5.5.0
     - 6.3.0

   * - ROCdbgapi
     - ``rocm-dbgapi``
     - 5.5.0
     - 6.3.0

   * - rocDecode
     - ``rocdecode``
     - 6.1.0
     - 6.3.0

   * - rocFFT
     - ``rocfft``
     - 5.5.0
     - 6.3.0

   * - rocm-core
     - ``rocm-core``
     - 5.5.0
     - 6.3.0

   * - rocminfo
     - ``rocminfo``
     - 5.5.0
     - 6.3.0

   * - ROCm Bandwidth Test
     - ``rocm-bandwidth-test``
     - 5.5.0
     - 6.3.0

   * - rocm-cmake
     - ``rocm-cmake``
     - 5.5.0
     - 6.3.0

   * - ROCm Compute Profiler (rocprofiler-compute)
     - ``omniperf``
     - 6.2.0
     - 6.3.0

   * - ROCm Data Center Tool (RDC)
     - ``rdc``
     - 5.5.0
     - 6.3.0

   * - ROCm Debug Agent
     - ``rocm-debug-agent``
     - 5.5.0
     - 6.3.0

   * - ROCm Debugger (ROCgdb)
     - ``rocm-gdb``
     - 5.5.0
     - 6.3.0

   * - rocMLIR
     - ``rocmlir``
     - 5.4.0
     - 6.3.0

   * - ROCm SMI Library
     - ``rocm-smi-lib``
     - 5.5.0
     - 6.3.0

   * - ROCm Systems Profiler (rocprofiler-systems)
     - ``omnitrace``
     - 6.2.0
     - 6.3.0

   * - ROCm Validation Suite
     - ``rocm-validation-suite``
     - 5.5.0
     - 6.3.0

   * - rocPRIM
     - ``rocprim``
     - 5.5.0
     - 6.3.0

   * - ROCProfiler
     - ``rocprofiler-dev``
     - 5.5.0
     - 6.3.0

   * - rocprofiler-register
     - ``rocprofiler-register``
     - 6.1.0
     - 6.3.0

   * - rocPyDecode
     - ``rocpydecode``
     - 6.2.0
     - 6.3.0

   * - rocRAND
     - ``rocrand``
     - 5.5.0
     - 6.3.0

   * - ROCr Runtime
     - ``hsa-rocr-dev``
     - 5.5.0
     - 6.3.0

   * - rocSOLVER
     - ``rocalution``
     - 5.5.0
     - 6.3.0

   * - rocSPARSE
     - ``rocsparse``
     - 5.5.0
     - 6.3.0

   * - rocThrust
     - ``rocthrust``
     - 5.5.0
     - 6.3.0

   * - ROCTracer
     - ``roctracer-dev``
     - 5.5.0
     - 6.3.0

   * - roctracer-dev-api
     - ``roctracer-dev-api``
     - 5.5.0
     - 6.3.0

   * - rocWMMA
     - ``rocwmma``
     - 5.5.0
     - 6.3.0

   * - ROCm Performance Primitives (RPP)
     - ``rpp``
     - 5.7.0
     - 6.3.0

   * - Tensile
     - ``rocm-tensile``
     - 5.5.0
     - 6.3.0

   * - atmi
     - ``atmi``
     - 5.5.0
     - 5.5.1 (final)

   * - clang-ocl
     - ``rocm-clang-ocl``
     - 5.5.0
     - 6.1.2 (final)

   * - MIOpen (GEMM)
     - ``miopengemm``
     - 5.5.0
     - 5.5.1 (final)

   * - MIOpen (OpenCL)
     - ``miopen-opencl``
     - 5.5.0
     - 5.5.1 (final)

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

   For example, ``spack install rocm-cmake@6.3.0``

2. ``info``

   The ``info`` command displays basic package information. It shows the preferred, safe, and
   deprecated versions, in addition to the available variants. It also shows the dependencies with other
   packages.

   .. code-block:: shell

      spack info mivisionx

   For example:

   .. code-block:: shell

      spack info mivisionx
      CMakePackage: mivisionx

      Description:
      MIVisionX toolkit is a set of comprehensive computer vision and machine
      intelligence libraries, utilities, and applications bundled into a
      single toolkit.

      Homepage: <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX>

      Preferred version:
          6.3.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.3.0.tar.gz

      Safe versions:
          6.3.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.3.0.tar.gz
          6.2.4    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.2.4.tar.gz
          6.2.1    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.2.1.tar.gz
          6.2.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.2.0.tar.gz
          6.1.2    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.1.2.tar.gz
          6.1.1    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.1.1.tar.gz
          6.1.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.1.0.tar.gz
          6.0.2    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.0.2.tar.gz
          6.0.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-6.0.0.tar.gz
          5.7.1    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.7.1.tar.gz
          5.7.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.7.0.tar.gz
          5.6.1    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.6.1.tar.gz
          5.6.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.6.0.tar.gz
          5.5.1    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.5.1.tar.gz
          5.5.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.5.0.tar.gz

      Deprecated versions:
          5.4.3    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.4.3.tar.gz
          5.4.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.4.0.tar.gz
          5.3.3    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.3.3.tar.gz
          5.3.0    https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.3.0.tar.gz

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
          cmake   gmake  libjpeg-turbo  migraphx    miopen-opencl  ninja   openssl   py-future                    py-numpy     py-pybind11  py-setuptools  python     rocm-core    rpp
          ffmpeg  hip    lmdb           miopen-hip  miopengemm     opencv  protobuf  py-google-api-python-client  py-protobuf  py-pytz      py-wheel       rapidjson  rocm-opencl

      Link Dependencies:
          hip   migraphx    miopen-opencl  openssl    py-google-api-python-client  py-pybind11  py-setuptools  rapidjson  rocm-opencl
          lmdb  miopen-hip  miopengemm     py-future  py-numpy                     py-pytz      py-wheel       rocm-core  rp

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

     spack spec mivisionx
     mivisionx@6.3.0%clang@3.4.2~add_tests~asan+hip~ipo~opencl build_system=cmake build_type=Release generator=make arch=linux-centos7-x86_64
              ^cmake@3.31.0%clang@3.4.2~doc+ncurses+ownlibs~qtgui build_system=generic build_type=Release arch=linux-centos7-x86_64
                  ^curl@8.10.1%clang@3.4.2~gssapi~ldap~libidn2~librtmp~libssh~libssh2+nghttp2 build_system=autotools libs=shared,static tls=openssl arch=linux-centos7-x86_64
                      ^nghttp2@1.64.0%clang@3.4.2 build_system=autotools arch=linux-centos7-x86_64
                  ^ncurses@6.5%clang@3.4.2~symlinks+termlib abi=none build_system=autotools patches=7a351bc arch=linux-centos7-x86_64
                  ^zlib-ng@2.2.1%clang@3.4.2+compat+new_strategies+opt+pic+shared build_system=autotools arch=linux-centos7-x86_64
              ^ffmpeg@4.4.4%clang@3.4.2~X~avresample+bzlib~doc~drawtext+gpl~libaom~libmp3lame~libopenjpeg~libopus~libsnappy~libspeex~libssh~libvorbis~libvpx~libwebp~libx264~libxml2~libzmq~lzma~nonfree~openssl~sdl2+shared+version3 build_system=autotools patches=f070ac1 arch=linux-centos7-x86_64

Creating an environment
===================================================

You can create an environment with all the required components of your version.

1. In the root folder, create a new folder when you can create a ``.yaml`` file. This file is used to create an environment.

   .. code-block:: shell

      mkdir /localscratch
      cd /localscratch
      vi sample.yaml

2. Add all the required components in the ``sample.yaml`` file:

   .. code-block:: shell

      spack:
      concretization: separately
      packages:
      all:
      compiler: [gcc@8.5.0]
      specs:
      - matrix:
      - ['%gcc@8.5.0\^cmake@3.19.7']
      - [rocm-cmake@6.3.0, rocm-dbgapi@6.3.0, rocm-debug-agent@6.3.0, rocm-gdb@6.3.0,
      rocminfo@6.3.0, rocm-opencl@6.3.0, rocm-smi-lib@6.3.0, rocm-tensile@6.3.0, rocm-validation-suite@6.3.0,
      rocprim@6.3.0, rocprofiler-dev@6.3.0, rocrand@6.3.0, rocsolver@6.3.0, rocsparse@6.3.0,
      rocthrust@6.3.0, roctracer-dev@6.3.0]
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
order to build a component with any modification to the  source code, you must generate a patch and
apply it before the build phase.

To generate a patch and build with the changes:

1. Stage the source code. For example:

   .. code-block:: shell

      spack stage hip@6.3.0
      # (This will pull the 6.3.0 release version source code of hip and display the path to spack-src directory where entire source code is available)

   You should see something like this:

   .. code-block:: shell-session

      ==> Using cached archive: /data/root/temp/rocm-6.3/spack/var/spack/cache/_source-cache/archive/d8/d8dba8cdf05463afb7879de2833983cafa6a006ba719815a35b96d9b92fc7fc4.tar.gz
      ==> Using cached archive: /data/root/temp/rocm-6.3/spack/var/spack/cache/_source-cache/archive/82/829e61a5c54d0c8325d02b0191c0c8254b5740e63b8bfdb05eec9e03d48f7d2c.tar.gz
      ==> Using cached archive: /data/root/temp/rocm-6.3/spack/var/spack/cache/_source-cache/archive/80/8081d4ab1a43ffa1cebd646668d83008b799ab98c14daf7b455922355a439c8a.tar.gz
      ==> Moving resource stage
              source: /tmp/root/spack-stage/resource-clr-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/
              destination: /tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/clr
      ==> Moving resource stage
              source: /tmp/root/spack-stage/resource-hip-tests-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/
              destination: /tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src/hip-tests
      ==> Staged hip in /tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46

2. Change directory to ``spack-src`` inside the staged directory.

   .. code-block:: shell-session

      root@computername:/spack$ cd /tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46
      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46$ cd spack-src/

3. Create a new Git repository.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ git init

4. Add the entire directory to the repository.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ git add .

5. Make the required changes to the source code.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src# vi hipamd/CMakeLists.txt
      # Make required changes in the source code

6. Generate the patch using the ``git diff`` command.

   .. code-block:: shell

      diff > /spack/var/spack/repos/builtin/packages/hip/0001-modifications.patch
      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ git diff > /spack/var/spack/repos/builtin/packages/hip/0001-modifications.patch

7. Update the recipe with the patch file name and any conditions you want to apply.

   .. code-block:: shell

      root@computername:/tmp/root/spack-stage/spack-stage-hip-6.3.0-zo53ondw3tevsr3gmoofbhre7asvis46/spack-src$ spack edit hip

8. Provide the patch file name and the conditions for the patch to be applied in the ``hip`` recipe as follows.

   .. code-block:: shell

      patch("0001-modifications.patch", when="@6.3.0")

   Spack applies ``0001-modifications.patch`` on the ``6.3.0`` release code before starting the ``hip`` build.
   Spack will apply ``0001-modifications.patch`` on the 6.3.0 release code before starting the ``hip`` build.

9. After each modification, you must update the recipe. If there is no change to the recipe, run

   .. code-block:: shell

      touch /spack/var/spack/repos/builtin/packages/hip/package.py
