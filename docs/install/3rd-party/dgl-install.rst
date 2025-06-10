.. meta::
  :description: Install Deep Graph Library (DGL) on ROCm
  :keywords: installation, docker, DGL, AMD, ROCm

********************************************************************************
DGL on ROCm
********************************************************************************

Deep Graph Library `(DGL) <https://www.dgl.ai/>`_ is an easy-to-use, high-performance and scalable 
Python package for deep learning on graphs. DGL is framework agnostic, meaning 
if a deep graph model is a component in an end-to-end application, the rest of 
the logic is implemented using Pytorch.  


To install DGL on ROCm, you have the following options:

- :ref:`Use the prebuilt Docker image <using-docker-with-DGL-pre-installed>` **(recommended)**
- :ref:`Use a wheels package <using-wheels-package>` 
- :ref:`build your own docker image <using-pytorch-rocm-docker-image>`



.. |br| raw:: html

   <br/>

For hardware, software, and third-party framework compatibility between ROCm and DGL, 
see the following resources:

* :ref:`system-requirements`

* :doc:`ROCm compatibility guide <rocm:compatibility/ml-compatibility/dgl-compatibility>`

.. _using-docker-with-dgl-pre-installed:

Using a Docker image with DGL pre-installed
================================================================================

The recommended way to set up a DGL environment and avoid potential installation issues is with Docker. 
The tested, prebuilt image includes DGL, PyTorch, ROCm, and other dependencies.

1. Download the latest public `DGL Docker image <https://hub.docker.com/r/rocm/dgl>`_.

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
--------------------------------------------------------------------------------

AMD validates and publishes ready-made `DGL Docker images <https://hub.docker.com/r/rocm/dgl>`_  
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
================================================================================

DGL supports the ROCm platform by providing tested wheels packages. For the correct 
wheels package, you must select **Linux**, **Python**, **pip**, and **ROCm** in the matrix, 
and its corresponding link.


.. note::

   The available ROCm release varies between the **PyTorch Build** of ``Stable`` or ``Nightly``.
   More recent releases are generally available through the ``Nightly`` builds.

1. Choose one of the following two following options:

.. tab-set::

	.. tab-item:: **Option 1: Docker (Recommended)**

            a. Download a base Docker image with your specified ROCm and Pytorch version.

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


	.. tab-item:: Option 2: Bare metal 

               Install on bare metal. Check :ref:`system-requirements` and install ROCm using the 
               directions in the  :ref:`rocm-install-overview` section.
               
               a. Install ``torch``, ``torchvision``, and ``torchaudio``, as specified in the 
               `installation matrix <https://pytorch.org/get-started/locally/>`_.

               .. note::

                  The following command uses the ROCm 6.4.0 PyTorch wheel. For a different version of ROCm,
                  modify the command accordingly.

               .. code-block:: bash
                  :substitutions:

                  pip3 install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/rocm6.4/
               b. (Optional) Use MIOpen kernel debug (kdb) files with ROCm PyTorch wheels.

               To speed up PyTorch startup, you can use MIOpen `MIOpen <https://github.com/ROCm/MIOpen>`_ kernel debug (kdb) files, which provide precompiled kernels. 
               These work with ROCm PyTorch wheels but must be placed in the correct directory relative to the PyTorch install.
               
               A helper script is available for Ubuntu to automate this, using your ROCm version and GPU architecture as inputs.
               Download the helper script here:
               `install_kdb_files_for_pytorch_wheels.sh <https://raw.githubusercontent.com/wiki/ROCm/pytorch/files/install_kdb_files_for_pytorch_wheels.sh>`_, or use:

               .. code-block:: bash

                  wget https://raw.githubusercontent.com/wiki/ROCm/pytorch/files/install_kdb_files_for_pytorch_wheels.sh

               After installing ROCm PyTorch wheels, run the following code:

               .. code-block:: bash

                  #Optional: replace 'gfx90a' with your GPU architecture
                  export GFX_ARCH=gfx90a

                  #Optional: specify ROCm version
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
================================================================================

DGL unit tests to validate your installation are optional if you used a 
**prebuilt PyTorch Docker image from AMD ROCm Docker Hub** or installed an 
**official wheels package**.

To run unit tests manually and validate your installation fully, follow these steps:


   .. note::

      Run the following from the DGL root.

   .. code-block:: bash

      ${SRC}/dgl/tests/scripts/task_cpp_unit_test.sh
      ${SRC}/dgl/tests/scripts/task_unit_test_rocm.sh

Once the tests pass, the script will end with the number of tests ran, and those that passed.
Prebuilt docker containers have tests from all supported features passed. 
Those that will be skipped are unimplemented due to restrictions on the GPU, 
either from NVIDIA CUDA or AMD ROCm.


Running a DGL example
================================================================================

Recommended example: a drug discovery pipeline using `SE3Transformer`.
For more information, see the `DGL blog <https://rocm.blogs.amd.com/blog/tag/dgl.html>`_.



Troubleshooting
================================================================================

- **Unable to access Docker or GPU in user accounts?** Ensure the user is added to `docker`, `video`, and `render` groups. See :ref:`group_permissions`.

- **Profiling DGL workloads?** Use the PyTorch Profiler, as explained in :ref:`mi300x-pytorch-profiler` to profile GPU kernels on ROCm.
