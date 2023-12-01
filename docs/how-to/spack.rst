**************************************************************
Introduction to Spack
**************************************************************

Spack is a package management tool designed to support multiple software versions and
configurations on a wide variety of platforms and environments. It was designed for large
supercomputing centers, where many users share common software installations on clusters with
exotic architectures using libraries that do not have a standard ABI. Spack is non-destructive: installing
a new version does not break existing installations, so many configurations can coexist on the same
system.

Most importantly, Spack is *simple*. It offers a simple *spec* syntax, so users can concisely specify
versions and configuration options. Spack is also simple for package authors: package files are written
in pure Python, and specs allow package authors to maintain a single file for many different builds of
the same package. For more information on Spack, see the
`Spack tutorial <https://spack-tutorial.readthedocs.io/en/latest/>`_.

ROCM packages in Spack
===================================================

.. csv-table::
  :widths: 30, 70
  :header: "Component", "Package name"

    ``rocm-cmake``, ``rocm-cmake``
    ``thunk``, ``hsakmt-roct``
    ``rocm-smi-lib``, ``rocm-smi-lib``
    ``hsa``, ``hsa-rocr-dev``
    ``lightning``, ``llvm-amdgpu``
    ``devicelibs``, ``rocm-device-libs``
    ``comgr``, ``comgr``
    ``rocclr (vdi)``, ``hip-rocclr``
    ``hipify_clang``, ``hipify-clang``
    ``hip (hip_in_vdi)``, ``hip``
    ``ocl (opencl_on_vdi )``, ``rocm-opencl``
    ``rocminfo``, ``rocminfo``
    ``clang-ocl``, ``rocm-clang-ocl``
    ``rccl``, ``rccl``
    ``atmi``, ``atmi``
    ``rocm_debug_agent``, ``rocm-debug-agent``
    ``rocm_bandwidth_test``, ``rocm-bandwidth-test``
    ``rocprofiler``, ``rocprofiler-dev``
    ``roctracer-dev-api``, ``roctracer-dev-api``
    ``roctracer``, ``roctracer-dev``
    ``dbgapi``, ``rocm-dbgapi``
    ``rocm-gdb``, ``rocm-gdb``
    ``openmp-extras``, ``rocm-openmp-extras``
    ``rocBLAS``, ``rocblas``
    ``hipBLAS``, ``hipblas``
    ``rocFFT``, ``rocfft``
    ``rocRAND``, ``rocrand``
    ``rocSPARSE``, ``rocsparse``
    ``hipSPARSE``, ``hipsparse``
    ``rocALUTION``, ``rocalution``
    ``rocSOLVER``, ``rocsolver``
    ``rocPRIM``, ``rocprim``
    ``rocThrust``, ``rocthrust``
    ``hipCUB``, ``hipcub``
    ``hipfort``, ``hipfort``
    ``ROCmValidationSuite``, ``rocm-validation-suite``
    ``MIOpenGEMM``, ``miopengemm``
    ``MIOpen(Hip variant)``, ``miopen-hip``
    ``MIOpen(opencl)``, ``miopen-opencl``
    ``MIVisionX``, ``mivisionx``
    ``AMDMIGraphX``, ``migraphx``
    ``rocm-tensile``, ``rocm-tensile``
    ``hipfft``, ``hipfft``
    ``RDC``, ``rdc``
    ``hipsolver``, ``hipsolver``
    ``mlirmiopen``, ``mlirmiopen``

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
            apt-get build-essential
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

    .. tab-item:: CentOS
        :sync: CentOS

        .. code-block:: shell

            # Install some essential utilities:
            yum update
            yum install make
            yum install patch bash tar yum install gzip unzip bzip2 xz file gnupg2 git gawk
            yum group install "Development Tools"
            yum install vim
            # Install Python:
            yum install python3
            pip3 install --upgrade pip
            # Install compilers:
            yum install gcc
            yum install gcc-gfortran
            yum install gcc-c++

Building ROCm components using Spack
===================================================

1. To use the spack package manager, clone the Spack project from GitHub.

    .. code-block:: shell

        git clone https://github.com/spack/spack.git

2. Initialize Spack.

    The ``setup-env.sh`` script initializes the Spack environment.

    .. code-block:: shell

        cd spack

        ./share/spack/setup-env.sh

    Spack commands are available once the above steps are completed. To list the available commands,
    use ``help``.

    .. code-block:: shell

        root@computername:~$ spack help

Installing ROCm components using Spack
===================================================

1. ``rocm-cmake``

    Install the default variants and the latest version of ``rocm-cmake``.

    .. code-block:: shell

        spack install rocm-cmake

    To install a specific version of ``rocm-cmake``, use:

    .. code-block:: shell

        spack install rocm-cmake@<version number>

    For example, ``spack install rocm-cmake@5.2.0``

2. ``info``

    The ``info`` command displays basic package information. It shows the preferred, safe, and
    deprecated versions, in addition to the available variants. It also shows the dependencies with other
    packages.

    .. code-block:: shell

        spack info mivisionx

    For example:

    .. code-block:: shell

        root@computername:~$ spack info mivisionx
        CMakePackage: mivisionx

        Description:
        MIVisionX toolkit is a set of comprehensive computer vision and machine
        intelligence libraries, utilities, and applications bundled into a
        single toolkit.

        Homepage: <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX>

        Preferred version:
        5.3.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.3.0.tar.gz>

        Safe versions:
        5.3.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.3.0.tar.gz>
        5.2.3 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.2.3.tar.gz>
        5.2.1 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.2.1.tar.gz>
        5.2.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.2.0.tar.gz>
        5.1.3 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.1.3.tar.gz>
        5.1.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.1.0.tar.gz>
        5.0.2 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.0.2.tar.gz>
        5.0.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-5.0.0.tar.gz>
        4.5.2 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.5.2.tar.gz>
        4.5.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.5.0.tar.gz>

        Deprecated versions:
        4.3.1 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.3.1.tar.gz>
        4.3.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.3.0.tar.gz>
        4.2.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.2.0.tar.gz>
        4.1.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.1.0.tar.gz>
        4.0.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-4.0.0.tar.gz>
        3.10.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-3.10.0.tar.gz>
        3.9.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-3.9.0.tar.gz>
        3.8.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-3.8.0.tar.gz>
        3.7.0 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/rocm-3.7.0.tar.gz>
        1.7 <https://github.com/GPUOpen-ProfessionalCompute-Libraries/MIVisionX/archive/1.7.tar.gz>

        Variants:
        Name [Default] When Allowed values Description
        ==================== ==== ==================== ==================

        build_type [Release] -- Release, Debug, CMake build type
        RelWithDebInfo
        hip [on] -- on, off Use HIP as backend
        ipo [off] -- on, off CMake interprocedural optimization
        opencl [off] -- on, off Use OPENCL as the backend

        Build Dependencies:
        cmake ffmpeg libjpeg-turbo miopen-hip miopen-opencl miopengemm opencv openssl protobuf rocm-cmake rocm-opencl

        Link Dependencies:
        miopen-hip miopen-opencl miopengemm openssl rocm-opencl

        Run Dependencies:
        None

Installing variants for ROCm components
===================================================

The variants listed above indicate that the ``mivisionx`` package is built by
default with ``build_type=Release`` and the ``hip`` backend, and without the
``opencl`` backend. ``build_type=Debug`` and ``RelWithDebInfo``, with ``opencl``
and without ``hip``, are also supported.

For example:

.. code-block:: shell

    spack install mivisionx build_type=Debug (Backend will be hip since it is the default one)
    spack install mivisionx+opencl build_type=Debug (Backend will be opencl and hip will be disabled as per the conflict defined in recipe)


* ``spack spec`` command

    To display the dependency tree, the ``spack spec`` command can be used with the same format.

    For example:

    .. code-block:: shell

        root@computername:~$ spack spec mivisionx
        Input spec
        --------------------------------
        mivisionx

        Concretized
        --------------------------------
        mivisionx@5.3.0%gcc@9.4.0+hip\~ipo\~opencl build_type=Release arch=linux-ubuntu20.04-skylake_avx512

Creating an environment
===================================================

You can create an environment with all the required components of your version.

1. In the root folder, create a new folder when you can create a ``.yaml`` file. This file is used to
create an environment.

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
        - [rocm-cmake@5.3.2, rocm-dbgapi@5.3.2, rocm-debug-agent@5.3.2, rocm-gdb@5.3.2,
        rocminfo@5.3.2, rocm-opencl@5.3.2, rocm-smi-lib@5.3.2, rocm-tensile@5.3.2, rocm-validation-suite@4.3.1,
        rocprim@5.3.2, rocprofiler-dev@5.3.2, rocrand@5.3.2, rocsolver@5.3.2, rocsparse@5.3.2,
        rocthrust@5.3.2, roctracer-dev@5.3.2]
        view: true

3. Once you've created the ``.yaml`` file, you can use it to create an environment.

    .. code-block:: shell

        spack env create -d /localscratch/MyEnvironment /localscratch/sample.yaml

4. Activate the environment.

    .. code-block:: shell

    spack env activate /localscratch/MyEnvironment

5. Verify that you want all the component versions.

    .. code-block:: shell

        spack find # this command will list out all components been in the environment (and 0 installed )

6. Install all the components in the ``.yaml`` file.

    .. code-block:: shell

        cd /localscratch/MyEnvironment
        spack install -j 50

7. Check that all components are successfully installed.

    .. code-block:: shell

        spack find

8. If any modification is made to the ``.yaml`` file, you must deactivate the existing environment and create a new one in order for the modications to be reflected.

    To deactivate, use:

    .. code-block:: shell

        spack env deactivate

Creating and applying a patch before installation
===================================================

Spack installs ROCm packages after pulling the source code from GitHub and building it locally. In
order to build a component with any modification to the  source code, you must generate a patch and
apply it before the build phase.

To generate a patch and build with the changes:

1. Stage the source code.

    .. code-block:: shell

        spack stage hip@5.2.0 # (This will pull the 5.2.0 release version source code of hip and display the path to spack-src directory where entire source code is available)

        root@computername:~/spack$ spack stage hip@5.2.0
        ==> Fetching <https://github.com/ROCm-Developer-Tools/HIP/archive/rocm-5.2.0.tar.gz>
        ==> Fetching <https://github.com/ROCm-Developer-Tools/hipamd/archive/rocm-5.2.0.tar.gz>
        ==> Fetching <https://github.com/ROCm-Developer-Tools/ROCclr/archive/rocm-5.2.0.tar.gz>
        ==> Moving resource stage
        source: /tmp/root/spack-stage/resource-hipamd-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src/
        destination: /tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src/hipamd
        ==> Moving resource stage
        source: /tmp/root/spack-stage/resource-opencl-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src/
        destination: /tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src/opencl
        ==> Moving resource stage
        source: /tmp/root/spack-stage/resource-rocclr-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src/
        destination: /tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src/rocclr
        ==> Staged hip in /tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7

2. Change directory to ``spack-src`` inside the staged directory.

    .. code-block:: shell

        root@computername:~/spack$ cd /tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7
        root@computername:/tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7$ cd spack-src/

3. Create a new Git repository.

    .. code-block:: shell

        root@computername:/tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src$ git init

4. Add the entire directory to the repository.

    .. code-block:: shell

        root@computername:/tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src$ git add .

5. Make the required changes to the source code.

    .. code-block:: shell

        root@computername:/tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src$ vi hipamd/CMakeLists.txt
        (Make required changes in the source code)

6. Generate the patch using the ``git diff`` command.

    .. code-block:: shell

        diff > /spack/var/spack/repos/builtin/packages/hip/0001-modifications.patch

7. Update the recipe with the patch file name and any conditions you want to apply.

    .. code-block:: shell

        root@computername:/tmp/root/spack-stage/spack-stage-hip-5.2.0-wzo5y6ysvmadyb5mvffr35galb6vjxb7/spack-src$ spack edit hip

    Provide the patch file name and the conditions for the patch:

    ``patch("0001-modifications.patch", when="@5.2.0")``

    Spack applies ``0001-modifications.patch`` on the ``5.2.0`` release code before starting the ``hip`` build.

   After each modification, you must update the recipe. If there is no change to the recipe, run
   ``touch /spack/var/spack/repos/builtin/packages/hip/package.py``
