.. meta::
  :description: Install verl on ROCm
  :keywords: installation, docker, verl, AMD, ROCm

********************************************************************************
verl on ROCm
********************************************************************************

Volcano Engine Reinforcement Learning for LLMs (verl) is a reinforcement learning framework designed for large language models (LLMs). 
See the `verl documentation <https://verl.readthedocs.io/en/latest/>`_ for more information about verl.

For hardware, software, and third-party framework compatibility between ROCm and verl, 
see the following resources:

* :ref:`system-requirements`
* :doc:`rocm:compatibility/ml-compatibility/verl-compatibility`

.. note::

	verl is supported on ROCm 6.2.0.

Install verl
================================================================================

To install verl on ROCm, you have the following options:

- :ref:`Use the prebuilt Docker image <using-docker-with-verl-pre-installed>` **(recommended)**
- :ref:`Build your own Docker image <build-verl-rocm-docker-image>`
 
Running verl in a Docker environment is suitable for both runtime and CI workflows.

.. _using-docker-with-verl-pre-installed:

Use a prebuilt Docker image with verl pre-installed
--------------------------------------------------------------------------------

The recommended way to set up a verl environment and avoid potential installation issues is with Docker. 
The tested, prebuilt image includes verl, PyTorch, ROCm, and other dependencies.

Prebuilt Docker images with verl configured for ROCm 6.2.0 are available on `Docker Hub <https://hub.docker.com/r/rocm/verl/tags>`_.

1. Pull the Docker image

   .. code-block:: bash

      docker pull rocm/verl:verl-0.3.0.post0_rocm6.2_vllm0.6.3

2. Launch and connect to the Docker container

   .. code-block:: bash

      docker run --rm -it --device /dev/dri --device /dev/kfd -p 8265:8265 --group-add video \
      --cap-add SYS_PTRACE --security-opt seccomp=unconfined --privileged -v $HOME/.ssh:/root/.ssh \
      -v $HOME:$HOME --shm-size 128G -w $PWD --name rocm_verl \
      rocm/verl:verl-0.3.0.post0_rocm6.2_vllm0.6.3 /bin/bash


.. _build-verl-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------

1. Clone the `https://github.com/ROCm/verl <https://github.com/ROCm/verl>`_ repository

   .. code-block:: bash

      git clone https://github.com/volcengine/verl.git -b v0.3.0.post0

2. Build the Docker container using the Dockerfile in the ``verl/docker`` directory

   .. code-block:: bash

      cd verl
      docker build -f docker/Dockerfile.rocm -t my-rocm-verl .

3. Launch and connect to the container

   .. code-block:: bash

      docker run --rm -it --device /dev/dri --device /dev/kfd -p 8265:8265 --group-add video \
      --cap-add SYS_PTRACE --security-opt seccomp=unconfined --privileged -v $HOME/.ssh:/root/.ssh \
      -v $HOME:$HOME --shm-size 128G -w $PWD --name rocm_verl \
      my-rocm-verl /bin/bash

   .. note::

      The ``--shm-size`` parameter allocates shared memory for the container. It can be adjusted based on your system's resources.


Test the verl installation
================================================================================

Once connected to the Docker container, verify that verl is installed:

.. code-block:: bash 

   pip list | grep verl
   verl    0.3.0.post0        /app


Run a verl example
================================================================================

The ``/app/examples`` directory contains examples for using verl with ROCm. 
These examples are described in the `Reinforcement Learning from Human Feedback on AMD GPUs with verl and ROCm Integration <https://rocm.blogs.amd.com/artificial-intelligence/verl-large-scale/README.html>`_ blog.