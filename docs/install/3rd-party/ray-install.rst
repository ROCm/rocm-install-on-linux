.. meta::
  :description: Install Ray on ROCm
  :keywords: installation, docker, deep learning, Ray, AMD, ROCm

********************************************************************************
Ray on ROCm installation
********************************************************************************

Ray is a unified framework, consisting of `a core distributed 
runtime  <https://docs.ray.io/en/latest/ray-core/walkthrough.html>`_ and a set of 
`AI libraries <https://docs.ray.io/en/latest/ray-air/getting-started.html>`_ for 
simplifying machine learning computations.

This topic covers setup instructions and the necessary files to build, test, and run 
Ray with ROCm support in a Docker environment. To learn more about Ray on ROCm, 
including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/ray-compatibility`.

.. note::

   Ray is supported on ROCm 7.0.0 and 6.4.1. This topic provides installation
   instructions for ROCm 7.0.0. For ROCm 6.4.1, see :doc:`previous-versions/ray-history`.

Install Ray
======================================================================================

To install Ray on ROCm, you have the following options:

* :ref:`using-docker-with-ray-pre-installed` **(recommended)**
* :ref:`build-ray-rocm-docker-image`
* :ref:`install-rocm-ray-bare-metal`
* :ref:`build-rocm-ray-from-source`

.. _using-docker-with-ray-pre-installed:

Use a prebuilt Docker image with Ray pre-installed
--------------------------------------------------------------------------------------

The recommended way to set up a Ray environment and avoid potential installation issues is with Docker. 
The tested, prebuilt image includes Ray, PyTorch, ROCm, and other dependencies.

Prebuilt Docker images with Ray configured for ROCm are available on `Docker Hub <https://hub.docker.com/r/rocm/ray/tags>`_.

1. Pull the Docker image:

   .. code-block:: bash

      docker pull rocm/ray:ray-2.51.1_rocm7.0.0_ubuntu22.04_py3.12_pytorch2.9.0

2. Launch and connect to the Docker container:

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/host_dir \
      -w /app --name rocm_ray rocm/ray:ray-2.51.1_rocm7.0.0_ubuntu22.04_py3.12_pytorch2.9.0 /bin/bash

      docker attach rocm_ray

   .. tip::

      * The ``--shm-size`` parameter allocates shared memory for the container. Adjust it based on your system's resources if needed.
      * Replace ``$(pwd)`` with the absolute path to the directory you want to mount inside the container.

.. _build-ray-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------------

1. Clone the `https://github.com/ROCm/ray <https://github.com/ROCm/ray>`__ repository:

   .. code-block:: bash

      git clone https://github.com/ROCm/ray.git -b release/2.51.1 

2. Build the Docker container using the Dockerfile in the ``ray/docker`` directory:

   .. code-block:: bash

      cd ray
      docker build -f docker/Dockerfile.rocm -t my-rocm-ray .

3. Launch and connect to the container:

   .. code-block:: bash

      docker run --rm -it --device /dev/dri --device /dev/kfd -p 8265:8265 --group-add video \
      --cap-add SYS_PTRACE --security-opt seccomp=unconfined --privileged -v $HOME/.ssh:/root/.ssh \
      -v $HOME:$HOME --shm-size 128G -w $PWD --name rocm_verl \
      my-rocm-ray /bin/bash

   .. note::

      The ``--shm-size`` parameter allocates shared memory for the container. It can be adjusted based on your system's resources.

4. Verify the installed Ray version:

   .. code-block:: bash

      pip3 freeze | grep ray

   Expected output:

   .. code-block::

      memray==1.19.1
      ray==2.51.1

.. _install-rocm-ray-bare-metal:

Install Ray on bare metal or a custom container
--------------------------------------------------------------------------------------

Follow these steps if you prefer to install ROCm manually on your host system or in a custom container.

1. Install ROCm. Follow the `ROCm installation guide <https://rocm.docs.amd.com/en/latest/deploy/linux/quick_start.html>`_ to install ROCm on your system.

   Once installed, verify your ROCm installation using:

   .. code-block:: bash

      amd-smi

   Expected output:

   .. code-block:: bash

      +------------------------------------------------------------------------------+
      | AMD-SMI 26.0.0+37d158ab      amdgpu version: 6.14.14  ROCm version: 7.0.0    |
      | Platform: Linux Baremetal                                                    |
      |-------------------------------------+----------------------------------------|
      | BDF                        GPU-Name | Mem-Uti   Temp   UEC       Power-Usage |
      | GPU  HIP-ID  OAM-ID  Partition-Mode | GFX-Uti    Fan               Mem-Usage |
      |=====================================+========================================|
      | 0000:05:00.0 ...Instinct MI300X OAM | 0 %      38 °C   0           141/750 W |
      |   0       0       7        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:26:00.0 ...Instinct MI300X OAM | 0 %      38 °C   0           135/750 W |
      |   1       1       6        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:46:00.0 ...Instinct MI300X OAM | 0 %      42 °C   0           139/750 W |
      |   2       2       4        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:65:00.0 ...Instinct MI300X OAM | 0 %      37 °C   0           136/750 W |
      |   3       3       5        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:85:00.0 ...Instinct MI300X OAM | 0 %      41 °C   0           139/750 W |
      |   4       4       3        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:a6:00.0 ...Instinct MI300X OAM | 0 %      38 °C   0           140/750 W |
      |   5       5       2        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:c6:00.0 ...Instinct MI300X OAM | 0 %      38 °C   0           138/750 W |
      |   6       6       0        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      |-------------------------------------+----------------------------------------|
      | 0000:e5:00.0 ...Instinct MI300X OAM | 0 %      37 °C   0           139/750 W |
      |   7       7       1        SPX/NPS1 | 0 %        N/A           283/196592 MB |
      +-------------------------------------+----------------------------------------+
      +------------------------------------------------------------------------------+
      | Processes:                                                                   |
      |  GPU        PID  Process Name          GTT_MEM  VRAM_MEM  MEM_USAGE     CU % |
      |==============================================================================|
      |  No running processes found                                                  |
      +------------------------------------------------------------------------------+

2. Install the required version of Ray with ROCm support using pip:

   .. code-block:: bash

      pip install -U ray[all]==2.51.1

3. Verify the installed Ray version:

   .. code-block:: bash

      pip3 freeze | grep ray
   
   Expected output:

   .. code-block::

      memray==1.19.1
      ray==2.51.1

.. _build-rocm-ray-from-source:

Build Ray from source
--------------------------------------------------------------------------------------

Follow the `Building Ray from source guide <https://docs.ray.io/en/latest/ray-contribute/development.html>`__ 
to build Ray with ROCm support from source.

.. _ray-verify-installation:

Test the Ray installation
======================================================================================

Ray unit tests are optional for validating your installation if you used a
prebuilt Docker image from AMD ROCm Docker Hub. To run unit tests manually and
validate your installation fully, follow these steps:

1. After launching the container, test whether Ray detects ROCm devices as expected.

   .. code-block:: bash
   
      python3 -c "import ray; ray.init(); print(ray.cluster_resources())"

2. If the setup is successful, the output should list all available ROCm devices.

   Expected output (for example, on the MI300X node):

   .. code-block:: shell-session

      {'memory': 1420360912896.0, 'GPU': 8.0, 'accelerator_type:AMD-Instinct-MI300X-OAM': 1.0, 'node:10.7.39.110': 1.0, 'CPU': 384.0, 'node:__internal_head__': 1.0, 'object_store_memory': 200000000000.0}

Previous versions
===============================================================================
See :doc:`previous-versions/ray-history` to find documentation for previous releases
of the ``ROCm/ray`` Docker image.
