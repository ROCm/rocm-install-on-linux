ROCm installation can be tailored to your requirements using one more combinations of ROCm meta packages:

- To use pre-built ROCm libraries and tools, include :ref:`ROCm runtime packages <rocm-runtime>` in the installation step.

- To develop and build individual ROCm libraries and tools, include :ref:`ROCm developer packages <rocm-dev>` in the installation step.

.. _rocm-runtime:

ROCm runtime packages
---------------------

.. csv-table::
  :widths: 20, 50, 30
  :delim: ;
  :header: Meta package; Description; Legacy use case [#legacy]_

    ``rocm``; All ROCm core packages, tools, and libraries.; ``rocm``
    ``rocm-hip-libraries``; HIP libraries optimized for the AMD platform.; Legacy use case does not exist.
    ``rocm-hip-runtime``; Run HIP applications written for the AMD platform.; ``hip``
    ``rocm-language-runtime``; ROCm runtime environment for running applications on the AMD platform.; ``lrt``
    ``rocm-ml-libraries``; Key machine learning libraries. Includes MIOpen.; ``mllib``
    ``rocm-opencl-runtime``; Run OpenCL-based applications on the AMD platform.; ``opencl``
    ;;
    **Other packages**;
    ``amdgpu-lib``; For users of graphics applications which require the open source Mesa 3D graphics and multimedia libraries. This package is primarily used for Radeon GPUs.; ``graphics``
    ``hsa-runtime-rocr4wsl-amdgpu``; For users of ROCm in a Windows Subsystem for Linux (WSL) context. This package is only supported for Ubuntu.; ``wsl``

.. _rocm-dev:

ROCm developer packages
-----------------------

.. csv-table::
  :widths: 20, 50, 30
  :delim: ;
  :header: Meta package; Description; Legacy use case [#legacy]_

    ``rocm-developer-tools``; Debug and profile HIP applications.; ``rocmdevtools``
    ``rocm-hip-runtime-devel``; Develop applications on HIP or port from CUDA.; Legacy use case does not exist.
    ``rocm-hip-sdk``; Develop or port HIP applications and libraries for the AMD platform.; ``hiplibsdk``
    ``rocm-ml-sdk``; Develop and run machine learning applications for AMD.; ``mlsdk``
    ``rocm-opencl-sdk``; Develop OpenCL-based applications for the AMD platform.; ``openclsdk``
    ``rocm-openmp-sdk``; Develop OpenMP-based applications for the AMD software.; ``openmpsdk``

.. rubric:: Footnotes

.. [#legacy] Starting from ROCm 6.4.2, "Legacy use cases" in ``amdgpu-install`` are replaced by the equivalent meta package. In addition, the following amdgpu-install use cases: ``asan``, ``rocmdev``, ``multimedia``, ``multimediasdk``, ``amf``, and ``workstation`` are deprecated.