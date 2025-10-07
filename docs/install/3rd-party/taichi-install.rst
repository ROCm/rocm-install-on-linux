.. meta::
  :description: Install Taichi on ROCm
  :keywords: installation, docker, Taichi, deep learning, AMD, ROCm

********************************************************************************
Taichi on ROCm installation
********************************************************************************

`Taichi <https://www.taichi-lang.org/>`_ is an open-source, imperative, and parallel 
programming language designed for high-performance numerical computation. 

This topic covers setup instructions and the necessary files to build, test, and run 
Taichi with ROCm support in a Docker environment. To learn more about Taichi
on ROCm, including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/taichi-compatibility`.

.. note::

	Taichi is supported on ROCm 6.3.2.

Install Taichi
================================================================================

To install Taichi on ROCm, you have the following options:

- :ref:`Use the prebuilt Docker image <using-docker-with-taichi-pre-installed>` **(recommended)**
- :ref:`Use a wheels package <taichi-wheels-package>`
- :ref:`Build your own docker image <build-taichi-rocm-docker-image>`

.. _using-docker-with-taichi-pre-installed:

Use a prebuilt Docker image with Taichi pre-installed
--------------------------------------------------------------------------------

Docker is the recommended method to set up a Taichi environment, and it avoids potential installation issues. 
The tested, prebuilt image includes Taichi, Python, ROCm, and other dependencies.

1. Pull the Docker image

   .. code-block:: bash

      docker pull rocm/taichi:taichi-1.8.0b1_rocm6.3.2_ubuntu22.04_py3.10.12

2. Launch and connect to the container

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/taichi_dir \
      --name rocm_taichi rocm/taichi:taichi-1.8.0b1_rocm6.3.2_ubuntu22.04_py3.10.12

.. _taichi-wheels-package:

Use a wheels package
--------------------------------------------------------------------------------

The Taichi ``.whl`` packages are hosted on the AMD PyPI repository. 
Instead of manually downloading the files, you can simply install Taichi using ``pip`` with the provided URL. 
This command will automatically download and install the appropriate ``.whl`` file.

.. code-block:: bash

   pip install amd-taichi==1.8.0b1 --extra-index-url=https://pypi.amd.com/simple
   sudo apt-get update
   sudo apt-get install -y lld

.. _build-taichi-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------

If you prefer to use the ROCm Ubuntu image, or already have a ROCm Ubuntu container, follow these steps to install Taichi in the container.

1. Pull the ROCm Ubuntu Docker image

   .. code-block:: bash

      docker pull rocm/dev-ubuntu-22.04:6.3.2

2. Launch the Docker container

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/taichi_dir \
      --name rocm_taichi rocm/dev-ubuntu-22.04:6.3.2 /bin/bash

3. Inside the running container, install build dependencies

   .. code-block:: bash

      sudo apt-get update && apt-get install -y --no-install-recommends \
      git wget vim \
      freeglut3-dev libglfw3-dev libglm-dev libglu1-mesa-dev \
      libjpeg-dev liblz4-dev libpng-dev libssl-dev \
      libwayland-dev libx11-xcb-dev libxcb-dri3-dev libxcb-ewmh-dev \
      libxcb-keysyms1-dev libxcb-randr0-dev libxcursor-dev libxi-dev \
      libxinerama-dev libxrandr-dev libzstd-dev \
      python3-pip cmake pybind11-dev ca-certificates \
      llvm-15 clang-15 lld-15 \
      && apt-get clean && rm -rf /var/lib/apt/lists/*

4. Add LLVM 15 to PATH

   .. code-block:: bash
      
      export LLVM_DIR=/usr/lib/llvm-15
      export PATH=${LLVM_DIR}/bin:$PATH

5. Clone the `https://github.com/ROCm/taichi <https://github.com/ROCm/taichi>`_ repository with the desired branch

   .. code-block:: bash
      
      cd <working-directory>
      git clone --recursive https://github.com/ROCm/taichi -b amd-release/v1.8.0b1
      cd taichi

6. Build the Taichi wheel

   .. code-block:: bash

      export GPU_TARGETS=gfx90a
      export TAICHI_CMAKE_ARGS="-DTI_WITH_VULKAN=OFF -DTI_WITH_OPENGL=OFF -DTI_BUILD_TESTS=ON -DTI_BUILD_EXAMPLES=OFF -DCMAKE_PREFIX_PATH=${LLVM_DIR}/lib/cmake -DCMAKE_CXX_COMPILER=${LLVM_DIR}/bin/clang++ -DTI_WITH_AMDGPU=ON -DTI_WITH_CUDA=OFF -DTI_AMDGPU_ARCHS=${GPU_TARGETS}"

      ./build.py

7. Install the Taichi ``.whl`` file

   .. code-block:: bash

      pip3 install <taichi-src-dir>/dist/taichi*.whl


.. _build-taichi-docker-from-source:

Test the Taichi installation
================================================================================

Clone the `https://github.com/ROCm/taichi <https://github.com/ROCm/taichi>`_ repository

   .. code-block:: bash

      sudo apt-get update
      sudo apt-get install -y git
      git clone --recursive https://github.com/ROCm/taichi -b amd-release/v1.8.0b1

To test the Taichi installation, run the ``laplace`` example in the source code: 

.. code-block:: bash

   python3 taichi/python/taichi/examples/algorithm/laplace.py


``laplace`` example output:

.. code-block:: bash

   [Taichi] version 1.8.0, llvm 15.0.0, commit f7911653, linux, python 3.10.12
   [Taichi] Starting on arch=amdgpu
   0.0
   4.0
   0.0
   0.0
   4.0
   0.0
   0.0
   4.0
   0.0
   0.0


Run a Taichi example
================================================================================

Several examples have been collected in the `https://github.com/ROCm/taichi_examples <https://github.com/ROCm/taichi_examples>`_ repository.
This repository contains a Dockerfile for building a container and installing Taichi. It contains a ``README.md`` file that guides the building of the container using the Dockerfile and running the examples.

1. Clone the repository: 

   .. code-block:: bash

      git clone https://github.com/ROCm/taichi_examples.git

2. If you have Taichi installed in your environment, you do not need to build an additional container. Simply install the example dependencies:

   .. code-block:: bash

      pip3 install pillow
      pip3 install --no-cache-dir torch --index-url https://download.pytorch.org/whl/nightly/rocm6.3/

3. Run the examples scripts from the ``taichi_examples`` directory:

   .. code-block:: bash

      cd taichi_examples
      ./run_demos.sh
      ./run_algorithm_graph_examples.sh

Refer to the `AMD ROCm blog <https://rocm.blogs.amd.com/>`_ to search for Taichi examples and best practices to optimize your workflows on AMD GPUs.
