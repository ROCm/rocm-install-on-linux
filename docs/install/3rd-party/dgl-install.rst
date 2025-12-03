.. meta::
  :description: Install Deep Graph Library (DGL) on ROCm
  :keywords: installation, docker, DGL, deep learning, AMD, ROCm

********************************************************************************
DGL on ROCm installation
********************************************************************************

Deep Graph Library (`DGL <https://www.dgl.ai/>`__) is an easy-to-use, high-performance, and scalable
Python package for deep learning on graphs. 

This topic covers setup instructions and the necessary files to build, test, and run 
DGL with ROCm support in a Docker environment. To learn more about DGL on ROCm, 
including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/dgl-compatibility`.

.. note::

   DGL is supported on ROCm 7.0.0, 6.4.3, and 6.4.0. This topic provides installation 
   instructions for ROCm 7.0.0 and 6.4.3. For ROCm 6.4.0, see :doc:`previous-versions/dgl-history`.

Install DGL
================================================================================

To install DGL on ROCm, you have the following options:

- :ref:`Use the prebuilt Docker image <using-docker-with-dgl-pre-installed>` **(recommended)**
- :ref:`Build your own docker image <build-dgl-rocm-docker-image>`
- :ref:`Use a wheels package <dgl-wheels-package>`

.. _using-pre-docker-with-dgl-pre-installed:

Use a prebuilt Docker image with DGL pre-installed
--------------------------------------------------------------------------------

The recommended way to set up a DGL environment and avoid potential installation issues is with Docker. 
The tested, prebuilt image includes DGL, PyTorch, ROCm, and other dependencies.

.. important::

   To follow these instructions, input your chosen tag into ``<TAG>``. Example: ``dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.8.0``.

   You can download Docker images for DGL with specific ROCm, PyTorch, Python, and operating system versions. 
   See the available tags on `Docker Hub <https://hub.docker.com/r/rocm/dgl/tags>`_ and see :ref:`dgl-docker-support` below.

1. Download your required public `DGL Docker image <https://hub.docker.com/r/rocm/dgl/tags>`_

   .. code-block:: bash

      docker pull rocm/dgl:<TAG>

2. Launch and connect to the Docker container using the image

   .. code-block:: bash

      sudo docker run -it --network=host --device=/dev/kfd --device=/dev/dri \
      --group-add=video --ipc=host --cap-add=SYS_PTRACE --security-opt \
      seccomp=unconfined --shm-size 8G rocm/dgl:<TAG>

   .. note::

      This will automatically download the image if it does not exist on the host. You can also pass 
      the ``-v`` argument to mount any data directories from the host onto the container.

.. _dgl-docker-support:

Docker image support
--------------------------------------------------------------------------------

AMD validates and publishes ready-made `DGL Docker images <https://hub.docker.com/r/rocm/dgl/tags>`_  
with ROCm backends on Docker Hub. The following Docker image tags and associated inventories are
validated for their respective ROCm versions listed below.

.. tab-set::

   .. tab-item:: ROCm 7.0.0

      .. tab-set::

         .. tab-item:: PyTorch 2.8.0

            Tag
              `rocm/dgl:dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.8.0 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.8.0/images/sha256-943698ddf54c22a7bcad2e5b4ff467752e29e4ba6d0c926789ae7b242cbd92dd>`_

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`__
              * `PyTorch 2.8.0 <https://github.com/pytorch/pytorch/releases/tag/v2.8.0>`__

         .. tab-item:: PyTorch 2.6.0

            Tag
              `rocm/dgl:dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.6.0 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.6.0/images/sha256-b2ec286a035eb7d0a6aab069561914d21a3cac462281e9c024501ba5ccedfbf7>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`__
              * `PyTorch 2.6.0 <https://github.com/pytorch/pytorch/releases/tag/v2.6.0>`__

         .. tab-item:: PyTorch 2.7.1

            Tag
              `rocm/dgl:dgl-2.4.0.amd0_rocm7.0.0_ubuntu22.04_py3.10_pytorch_2.7.1 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4.0.amd0_rocm7.0.0_ubuntu22.04_py3.10_pytorch_2.7.1/images/sha256-d27aee16df922ccf0bcd9107bfcb6d20d34235445d456c637e33ca6f19d11a51>`_

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`__
              * `PyTorch 2.7.1 <https://github.com/pytorch/pytorch/releases/tag/v2.7.1>`__

   .. tab-item:: ROCm 6.4.3

      .. tab-set::

         .. tab-item:: PyTorch 2.6.0

            Tag
              `rocm/dgl:dgl-2.4.0.amd0_rocm6.4.3_ubuntu24.04_py3.12_pytorch_2.6.0 <https://hub.docker.com/layers/rocm/dgl/dgl-2.4.0.amd0_rocm6.4.3_ubuntu24.04_py3.12_pytorch_2.6.0/images/sha256-f3ba6a3c9ec9f6c1cde28449dc9780e0c4c16c4140f4b23f158565fbfd422d6b>`_

            Inventory
              * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__
              * `Python 3.12.9 <https://www.python.org/downloads/release/python-3129/>`__
              * `PyTorch 2.6.0 <https://github.com/ROCm/pytorch/tree/release/2.6>`__

.. _build-dgl-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------

1. Clone the `https://github.com/ROCm/dgl <https://github.com/ROCm/dgl>`_ repository 

   .. code-block:: bash

      git clone --recurse-submodules https://github.com/ROCm/dgl
      cd dgl

2. Build the Docker container

   .. tab-set::

      .. tab-item:: DGL on Ubuntu 24.04 + ROCm 7.0.0 + Py 3.12 + PyTorch 2.8.0

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 24.04 + ROCm 7.0.0 + Py 3.12 + PyTorch 2.8.0
            docker build \
               -t dgl:dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.8.0 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm7.0_ubuntu24.04_py3.12_pytorch_release_2.8.0 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               --build-arg ARG_DGL_ARTIFACTS_DIR="/artifacts" \
               -f docker/Dockerfile.ci_gpu_rocm \
               .

      .. tab-item:: DGL on Ubuntu 24.04 + ROCm 7.0.0 + Py 3.12 + PyTorch 2.6.0

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 24.04 + ROCm 7.0 + Py 3.12 + PyTorch 2.6.0
            docker build \
               -t dgl:dgl-2.4.0.amd0_rocm7.0.0_ubuntu24.04_py3.12_pytorch_2.6.0 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm7.0_ubuntu24.04_py3.12_pytorch_release_2.6.0 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               --build-arg ARG_DGL_ARTIFACTS_DIR="/artifacts" \
               -f docker/Dockerfile.ci_gpu_rocm \
               .

      .. tab-item:: DGL on Ubuntu 22.04 + ROCm 7.0.0 + Py 3.10 + PyTorch 2.7.1

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 22.04 + ROCm 7.0.0 + Py 3.10 + PyTorch 2.7.1
            docker build \
               -t dgl:dgl-2.4.0.amd0_rocm7.0.0_ubuntu22.04_py3.10_pytorch_2.7.1 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm7.0_ubuntu22.04_py3.10_pytorch_release_2.7.1 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               --build-arg ARG_DGL_ARTIFACTS_DIR="/artifacts" \
               -f docker/Dockerfile.ci_gpu_rocm \
               .

      .. tab-item:: DGL on Ubuntu 24.04 + ROCm 6.4.3 + Py 3.12 + PyTorch 2.6.0

         To build the Docker container, run the following command:

         .. code-block:: bash

            # DGL on Ubuntu 24.04 + ROCm 6.4.3 + Py 3.12 + PyTorch 2.6.0
            docker build \
               -t dgl:dgl-2.4.0.amd0_rocm6.4.3_ubuntu24.04_py3.12_pytorch_2.6.0 \
               --build-arg BASE_IMAGE=rocm/pytorch:rocm6.4.3_ubuntu24.04_py3.12_pytorch_release_2.6.0 \
               --build-arg ARG_CONDA_ENV=py_3.12 \
               --build-arg ARG_MAX_JOBS=8 \
               --build-arg ARG_GPU_BUILD_TARGETS="gfx90a,gfx942" \
               -f Dockerfile.rocm \
               .

.. _dgl-wheels-package:

Use a wheels package
--------------------------------------------------------------------------------

The DGL ``.whl`` packages are hosted on the AMD PyPI repository. Instead of manually downloading the files, 
you can simply install DGL using ``pip`` with the provided URL. 
This command will automatically download and install the appropriate ``.whl`` file.

.. tab-set::

   .. tab-item:: DGL on Ubuntu 24.04 + ROCm 7.0.0 + Py 3.12 + PyTorch 2.8.0

      To install using wheels, run the following command:

      .. code-block:: bash

         pip install https://pypi.amd.com/rocm-7.0.0/packages/amd-dgl/amd_dgl-2.4.0+amd0.torch2.8.0.rocm7.0.0.git64359f59.ubuntu24.4-cp312-cp312-linux_x86_64.whl

   .. tab-item:: DGL on Ubuntu 24.04 + ROCm 7.0.0 + Py 3.12 + PyTorch 2.6.0

      To install using wheels, run the following command:

      .. code-block:: bash

         pip install https://pypi.amd.com/rocm-7.0.0/packages/amd-dgl/amd_dgl-2.4.0+amd0.torch2.6.0.rocm7.0.0.git2e48b21f.ubuntu24.4-cp312-cp312-linux_x86_64.whl

   .. tab-item:: DGL on Ubuntu 22.04 + ROCm 7.0.0 + Py 3.10 + PyTorch 2.7.1
     
      To install using wheels, run the following command:

      .. code-block:: bash

         pip install https://pypi.amd.com/rocm-7.0.0/packages/amd-dgl/amd_dgl-2.4.0+amd0.torch2.7.1.rocm7.0.0.git698b58a9.ubuntu22.4-cp310-cp310-linux_x86_64.whl

   .. tab-item:: DGL on Ubuntu 24.04 + ROCm 6.4.3 + Py 3.12 + PyTorch 2.6.0
     
      To install using wheels, run the following command:

      .. code-block:: bash

         pip install https://pypi.amd.com/rocm-6.4.3/packages/amd-dgl/amd_dgl-2.4.0+amd0.torch2.6.0.gitdbfe118.ubuntu24.4-cp312-cp312-linux_x86_64.whl

After installing a ``.whl`` file, you can confirm that the package was installed successfully using:

.. code-block:: bash

   pip show amd_dgl


Test the DGL installation
================================================================================

To verify that DGL has been successfully installed, run the Docker container as described in the :ref:`Installing DGL section <using-docker-with-dgl-pre-installed>`. 
Once inside the container, ensure you have access to the Bash shell.

To check for a shared library:

.. code-block:: bash

   find / -name libdgl.so -print -quit 2>/dev/null && echo "libdgl.so found" || echo "libdgl.so NOT found"

To check for Python import:

.. code-block:: shell

   conda activate py_<python version> #You can check this with conda info --envs

   export DGLBACKEND=pytorch

   python -c "import dgl; print('dgl import successful, version:', dgl.__version__)" || echo "Failed to import DGL"

Run tests for DGL
--------------------------------------------------------------------------------

You can also run tests from the scripts folder at ``/src/dgl/``.
These tests are only viable if you are using the above Docker containers or building Docker containers from source.

To run Python tests:

.. code-block:: bash
      
   cd /src/dgl
   bash tests/scripts/task_unit_test_rocm.sh pytorch gpu

To run C++ tests:

.. code-block:: bash
   
   cd /src/dgl
   bash tests/scripts/task_cpp_unit_test.sh

Estimated time: the tests usually take 10-15 minutes to run.

Run a DGL example
================================================================================

Multiple use cases of DGL have been tested and verified. However, a recommended 
example follows a drug discovery pipeline using the ``SE3Transformer``.
For use cases and recommendations, refer to the `AMD ROCm blog <https://rocm.blogs.amd.com/>`__, 
where you can search for DGL examples and best practices to optimize your workloads on AMD GPUs.

Troubleshooting
================================================================================

- **Unable to access Docker or GPU in user accounts?** Ensure the user is added to ``docker``, ``video``, and ``render`` groups. See :ref:`group_permissions`.

- **Profiling DGL workloads?** Use the PyTorch Profiler, as explained in :ref:`mi300x-pytorch-profiler` to profile GPU kernels on ROCm.

Previous versions
===============================================================================
See :doc:`previous-versions/dgl-history` to find documentation for previous releases
of the ``ROCm/dgl`` Docker image.