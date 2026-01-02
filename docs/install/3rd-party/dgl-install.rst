.. meta::
  :description: Install Deep Graph Library (DGL) on ROCm
  :keywords: installation, docker, DGL, AMD, ROCm

********************************************************************************
DGL on ROCm
********************************************************************************

Deep Graph Library `(DGL) <https://www.dgl.ai/>`_ is an easy-to-use, high-performance and scalable
Python package for deep learning on graphs. DGL is framework agnostic, meaning
if a deep graph model is a component in an end-to-end application, the rest of
the logic is implemented using PyTorch.

.. |br| raw:: html

   <br/>

For hardware, software, and third-party framework compatibility between ROCm and DGL, 
see the following resources:

* :ref:`system-requirements`

* :doc:`rocm:compatibility/ml-compatibility/dgl-compatibility`

Install DGL
================================================================================

To install DGL on ROCm, you have the following options:

- :ref:`Use the prebuilt Docker image <using-docker-with-dgl-pre-installed>` **(recommended)**
- :ref:`Build your own docker image <build-dgl-rocm-docker-image>`

.. _using-docker-with-dgl-pre-installed:

Use a prebuilt Docker image with DGL pre-installed
--------------------------------------------------------------------------------

The recommended way to set up a DGL environment and avoid potential installation issues is with Docker. 
The tested, prebuilt image includes DGL, PyTorch, ROCm, and other dependencies.

.. important::

   To follow these instructions, input your chosen tag into ``<TAG>``. Example: ``dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.6.0``.

   You can download Docker images for DGL with specific ROCm, PyTorch, Python and operating system versions. 
   See the available tags on `Docker Hub <https://hub.docker.com/r/rocm/dgl/tags>`_ and see :ref:`docker image support <dgl-docker-support>` below.


1. Download your required public `DGL Docker image <https://hub.docker.com/r/rocm/dgl/tags>`_

   .. code-block:: bash

      docker pull rocm/dgl:<TAG>

2. Launch and connect to the Docker container using the image

   .. code-block:: bash

      docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
      --device=/dev/kfd --device=/dev/dri --group-add video \
      --ipc=host --shm-size 8G rocm/dgl:<TAG>

   .. note::

      This will automatically download the image if it does not exist on the host. You can also pass 
      the ``-v`` argument to mount any data directories from the host onto the container.


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
              `rocm/dgl:dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.6.0 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.6.0/images/sha256-8ce2c3bcfaa137ab94a75f9e2ea711894748980f57417739138402a542dd5564>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`_
              * `PyTorch 2.6.0 <https://github.com/ROCm/pytorch/tree/release/2.6>`_

   .. tab-item:: PyTorch 2.4.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/dgl:dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.4.1 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.4.1/images/sha256-cf1683283b8eeda867b690229c8091c5bbf1edb9f52e8fb3da437c49a612ebe4>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`_
              * `PyTorch 2.4.1 <https://github.com/ROCm/pytorch/tree/release/2.4>`_

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/dgl:dgl-2.4_rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.4.1 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4_rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.4.1/images/sha256-4834f178c3614e2d09e89e32041db8984c456d45dfd20286e377ca8635686554>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `PyTorch 2.4.1 <https://github.com/ROCm/pytorch/tree/release/2.4>`_

   .. tab-item:: PyTorch 2.3.0

      .. tab-set::

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/dgl:dgl-2.4_rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.3.0 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4_rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.3.0/images/sha256-88740a2c8ab4084b42b10c3c6ba984cab33dd3a044f479c6d7618e2b2cb05e69B>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `PyTorch 2.3.0 <https://github.com/ROCm/pytorch/tree/release/2.3>`_

.. _build-dgl-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------

1. Clone the `https://github.com/ROCm/dgl <https://github.com/ROCm/dgl>`_ repository 

   .. code-block:: bash

      git clone --recurse-submodules https://github.com/ROCm/dgl
      cd dgl

2. Build the Docker container

   .. tab-set::

      .. tab-item:: DGL on Ubuntu 22.04 + ROCm 6.4 + Py 3.10 + PyTorch 2.4.1

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 22.04 + ROCm 6.4 + Py 3.10 + PyTorch 2.4.1
            docker build \
               -t dgl:dgl-2.4_rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.4.1 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.4.1 \
               --build-arg ARG_CONDA_ENV=py_3.10 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               -f Dockerfile.rocm \
               .

      .. tab-item:: DGL on Ubuntu 22.04 + ROCm 6.4 + Py 3.10 + PyTorch 2.3.0

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 22.04 + ROCm 6.4 + Py 3.10 + PyTorch 2.3.0
            docker build \
               -t dgl:dgl-2.4_rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.3.0 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm6.4_ubuntu22.04_py3.10_pytorch_release_2.3.0 \
               --build-arg ARG_CONDA_ENV=py_3.10 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               -f Dockerfile.rocm \
               .

      .. tab-item:: DGL on Ubuntu 24.04 + ROCm 6.4 + Py 3.12 + PyTorch 2.4.1

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 24.04 + ROCm 6.4 + Py 3.12 + PyTorch 2.4.1
            docker build \
               -t dgl:dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.4.1 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.4.1 \
               --build-arg ARG_CONDA_ENV=py_3.12 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               -f Dockerfile.rocm \
               .

      .. tab-item:: DGL on Ubuntu 24.04 + ROCm 6.4 + Py 3.12 + PyTorch 2.6.0

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 24.04 + ROCm 6.4 + Py 3.12 + PyTorch 2.6.0
            docker build \
               -t dgl:dgl-2.4_rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.6.0 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm6.4_ubuntu24.04_py3.12_pytorch_release_2.6.0 \
               --build-arg ARG_CONDA_ENV=py_3.12 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               -f Dockerfile.rocm \
               .

Test the DGL installation
================================================================================

To verify that DGL has been successfully installed, run the Docker container as described in the :ref:`installing DGL section <using-docker-with-dgl-pre-installed>`. 
Once inside the container, ensure you have access to the Bash shell.

To check for a shared library:

.. code-block:: bash

   find / -name libdgl.so -print -quit 2>/dev/null && echo "libdgl.so found" || echo "libdgl.so NOT found"

To check for Python import:

.. code-block:: shell

   conda activate py_<python version> #You can check this with conda info --envs

   export DGLBACKEND=pytorch

   python -c "import dgl; print('dgl import successful, version:', dgl.__version__)" || echo "Failed to import DGL"

Run a DGL example
================================================================================

Multiple use cases of DGL have been tested and verified.
However, a recommended example follows a drug discovery pipeline using the ``SE3Transformer``.
This detailed procedure and steps will be outlined in the `AMD ROCm blog <https://rocm.blogs.amd.com/>`_, where you can search for DGL examples.

Troubleshooting
================================================================================

- **Unable to access Docker or GPU in user accounts?** Ensure the user is added to ``docker``, ``video``, and ``render`` groups. See :ref:`group_permissions`.

- **Profiling DGL workloads?** Use the PyTorch Profiler, as explained in :ref:`mi300x-pytorch-profiler` to profile GPU kernels on ROCm.
