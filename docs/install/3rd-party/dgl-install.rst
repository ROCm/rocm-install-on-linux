.. meta::
  :description: Installing DGL for ROCm
  :keywords: installation instructions, DGL, AMD, ROCm

***************
DGL on ROCm
***************

`DGL <https://www.dgl.ai/>`_ easy-to-use, high performance and scalable Python package for deep learning on graphs.
 DGL is framework agnostic, meaning if a deep graph model is a component of an end-to-end application, 
 the rest of the logics is implemented using Pytorch. 


To install DGL for ROCm, you have the following options:
* :ref:`using-docker-with-DGL-pre-installed` (recommended)

* :ref:`using-wheels-package`

* :ref:`building-a-DGL-rocm-docker-image`



.. |br| raw:: html

   <br/>

For hardware, software, and third-party framework compatibility between ROCm and DGL, see the following resources:

* :ref:`system-requirements`

* :doc:`rocm:compatibility/ml-compatibility/dgl-compatibility`

.. _using-docker-with-dgl-pre-installed:

Using a Docker image with DGL pre-installed
===============================================================

The recommended option to get a DGL environment is through Docker. This image encompasses DGL and its dependencies,
including Pytorch Rocm, and others. 

Using Docker provides portability and access to a prebuilt Docker image that
has been rigorously tested within AMD. This can also save compilation time and
should perform as tested and mitigate potential installation issues.

1. Download the latest public (Not updated Yet) `DGL Docker image <https://hub.docker.com/r/rocm/dgl>`_.

   .. code-block:: bash

      docker pull rocm/dgl:latest

   .. _pytorch-docker-latest-note:

   .. important::

      The ``rocm/dgl:latest`` tags point to
      a Docker image with the latest ROCm-tested release of DGL.


   You can download Docker images for DGL with specific ROCm, PyTorch, Python and operating
   system versions. See the available tags on
   `Docker Hub <https://hub.docker.com/r/rocm/dgl/tags>`_.

2. Start a Docker container using the image.

   .. code-block:: bash

       docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
       --device=/dev/kfd --device=/dev/dri --group-add video \
       --ipc=host --shm-size 8G rocm/dgl:latest

   .. note::

       This will automatically download the image if it does not exist on the host. You can also pass 
       the '-v' argument to mount any data directories from the host onto the container.

.. _dgl-docker-support:

Docker image support
--------------------

AMD validates and publishes ready-made `DGL <https://hub.docker.com/r/rocm/dgl>`_ images
with ROCm backends on Docker Hub. The following Docker image tags and associated inventories are
validated for ROCm 6.4.

.. tab-set::

   .. tab-item:: PyTorch 2.6.0

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/pytorch:rocm6.4_ubuntu24.04_py3.12_dgl_release_2.6.0 <https://hub.docker.com/layers/rocm/dgl/rocm6.4_ubuntu24.04_py3.12_dgl_release_2.6.0/images/STUB>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`_
              * `PyTorch 2.6.0 <https://github.com/ROCm/pytorch/tree/release/2.6>`_


   .. tab-item:: PyTorch 2.4.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/pytorch:rocm6.4_ubuntu24.04_py3.12_dgl_release_2.4.1 <https://hub.docker.com/layers/rocm/dgl/rocm6.4_ubuntu24.04_py3.12_dgl_release_2.4.1/images/STUB>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`_
              * `PyTorch 2.4.1 <https://github.com/ROCm/pytorch/tree/release/2.4>`_


         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/pytorch:rocm6.4_ubuntu22.04_py3.10_dgl_release_2.4.1 <https://hub.docker.com/layers/rocm/dgl/rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.4.1/images/STUB>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `PyTorch 2.4.1 <https://github.com/ROCm/pytorch/tree/release/2.4>`_


   .. tab-item:: PyTorch 2.3.0

      .. tab-set::

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/pytorch:rocm6.4_ubuntu22.04_py3.10_dgl_release_2.3.0 <https://hub.docker.com/layers/rocm/dgl/rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.3.0/images/STUB>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `PyTorch 2.3.0 <https://github.com/ROCm/pytorch/tree/release/2.3>`_

.. _install_pytorch_wheels:
.. _using-wheels-package:

Using a wheels package
======================

DGL supports the ROCm platform by providing tested wheels packages. For the correct
wheels package, you must select **Linux**, **Python**, **pip**, and **ROCm** in the matrix, and its corresponding link.


.. note::

   The available ROCm release varies between the **PyTorch Build** of ``Stable`` or ``Nightly``.
   More recent releases are generally available through the Nightly builds.

1. Choose one of the following two options:

   **Option 1:**

   a. Download a base Docker image with the correct ROCm and Pytorch version.

      .. list-table::
          :header-rows: 1

          * - Base OS
            - Docker Image
          * - Ubuntu 22.04
            - 'Python 3.10 with PyTorch 2.3.0 <https://hub.docker.com/layers/rocm/pytorch/rocm6.4_ubuntu22.04_py3.10.16_dgl_release_2.3.0/>'_
            - 'Python 3.10 with PyTorch 2.4.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.4_ubuntu22.04_py3.10.16_dgl_release_2.4.1/>'_
          * - Ubuntu 24.04
            - 'Python 3.12 with PyTorch 2.4.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.4_ubuntu24.04_py3.12_dgl_release_2.4.1/>'_
            - 'Python 3.12 with PyTorch 2.6 <https://hub.docker.com/layers/rocm/pytorch/rocm6.4_ubuntu24.04_py3.12_dgl_release_2.6.0/>'_

   b. Pull the selected image.

      .. code-block:: bash

          docker pull rocm/"YOURTAG"

   c. Start a Docker container using the downloaded image.

      .. code-block:: bash

          docker run -it --device=/dev/kfd --device=/dev/dri --group-add video rocm/"YOURTAG"


   **Option 2:(Not Recommended)** 

   Install on bare metal. Check :ref:`system-requirements` and install ROCm using the
   directions in the  :ref:`rocm-install-overview` section.
   
   a. Install ``torch``, ``torchvision``, and ``torchaudio``, as specified in the
   `installation matrix <https://pytorch.org/get-started/locally/>`_.

   .. note::

      The following command uses the ROCm 6.4.0 PyTorch wheel. If you want a different version of ROCm,
      modify the command accordingly.

   .. code-block:: bash
      :substitutions:

       pip3 install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/rocm6.4/
   b. (Optional) Use MIOpen kdb files with ROCm PyTorch wheels.

   PyTorch uses `MIOpen <https://github.com/ROCm/MIOpen>`_ for machine learning
   primitives, which are compiled into kernels at runtime. Runtime compilation causes a small warm-up
   phase when starting PyTorch, and MIOpen kdb files contain precompiled kernels that can speed up
   application warm-up phases.

   MIOpen kdb files can be used with ROCm PyTorch wheels. However, the kdb files need to be placed in
   a specific location with respect to the PyTorch installation path. A helper script simplifies this task by
   taking the ROCm version and GPU architecture as inputs. This works for Ubuntu.

   You can download the helper script here:
   `install_kdb_files_for_pytorch_wheels.sh <https://raw.githubusercontent.com/wiki/ROCm/pytorch/files/install_kdb_files_for_pytorch_wheels.sh>`_, or use:

   .. code-block:: bash

       wget https://raw.githubusercontent.com/wiki/ROCm/pytorch/files/install_kdb_files_for_pytorch_wheels.sh

   After installing ROCm PyTorch wheels, run the following code:

   .. code-block:: bash

       #Optional: replace 'gfx90a' with your architecture and 6.2.4 with your preferred ROCm version
       export GFX_ARCH=gfx90a

       #Optional
       export ROCM_VERSION=6.2.4

       ./install_kdb_files_for_pytorch_wheels.sh

.. _using-pytorch-rocm-docker-image:

2. Install the required dependencies for the wheels package.

   .. code-block:: bash

       sudo apt update
       sudo apt install libjpeg-dev python3-dev python3-pip
       pip3 install wheel setuptools
       pip3 install dgl_STUB



Testing the DGL installation
================================

You can use DGL unit tests to validate your DGL installation. If you used a
**prebuilt PyTorch Docker image from AMD ROCm Docker Hub** or installed an
**official wheels package**, validation tests are not necessary, however they can be run.

If you want to manually run unit tests to validate your PyTorch installation fully, follow these steps:

1. This is one point where I can add more info after the wheels/container is released by CICDS


   Tentatively , this is our procedure. Run from the dgl root

      .. code-block:: bash

      ${SRC}/dgl/tests/scripts/task_cpp_unit_test.sh
      ${SRC}/dgl/tests/scripts/task_unit_test_rocm.sh



Running a DGL example
===============================

Our recommended and tested example is a drug discovery use_case that uses an SE3Transformer.
The instructions to build, install and run this example is described in ROCm Blogs `DGL Blog <https://www.amd.com/en/blogs.html>`_

The DGL examples repository provides basic examples that exercise the functionality of your
framework. These have not been tested, however. But scripts are provided to install and test them within the DGL ROCm repo.


Troubleshooting
===============

* What if you are unable to access Docker or GPU in user accounts?

  [NEED INPUT FROM LEADRERSHIP] Can we offer OCI like services

* What if you are unable to access Docker or GPU in user accounts?

  Ensure that the user is added to docker, video, and render Linux groups as described in :ref:`group_permissions`.


* How do you profile DGL workloads?

  Use the PyTorch Profiler as described in :ref:`mi300x-pytorch-profiler` to profile GPU kernels on ROCm. 
