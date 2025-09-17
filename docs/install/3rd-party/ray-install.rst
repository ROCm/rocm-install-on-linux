.. meta::
  :description: Ray on ROCm
  :keywords: installation instructions, building, Ray, AMD, ROCm

********************************************************************************
Ray on ROCm installation
********************************************************************************

Ray is a unified framework for scaling AI and Python applications from your laptop 
to a full cluster, without changing your code. Ray consists of `a core distributed 
runtime  <https://docs.ray.io/en/latest/ray-core/walkthrough.html>`_ and a set of 
`AI libraries <https://docs.ray.io/en/latest/ray-air/getting-started.html>`_ for 
simplifying machine learning computations.

Ray is a general-purpose framework that runs many types of workloads efficiently. 
Any Python application can be scaled with Ray, without extra infrastructure.

For hardware, software, and third-party framework compatibility between ROCm and Ray, 
see the following resources:

* :ref:`system-requirements`
* :doc:`rocm:compatibility/ml-compatibility/ray-compatibility`

.. note::

	Ray is supported on ROCm 6.4.1.

Install Ray
======================================================================================

To install Ray on ROCm, you have the following options:

* :ref:`using-docker-with-ray-pre-installed` **(recommended)**
* :ref:`build-ray-rocm-docker-image`
* :ref:`install-rocm-ray-bare-metal`
* :ref:`build-rocm-ray-from-source`

.. _using-docker-with-ray-pre-installed:

Using a prebuilt Docker image with Ray pre-installed
--------------------------------------------------------------------------------------

Docker is the recommended method to set up a Ray environment, and it avoids potential installation issues.  
The tested, prebuilt image includes Ray, ROCm, and other dependencies.


1. Pull the Docker image

   .. code-block:: bash

      docker pull rocm/ray:ray-2.48.0.post0_rocm6.4.1_ubuntu24.04_py3.12_pytorch2.6.0

   .. note::

      For specific versions of Ray, review the periodically pushed Docker images at `ROCm Ray on
      Docker Hub <https://hub.docker.com/r/rocm/ray/tags>`_.

      Additional Docker images are available at `ROCm Ray on Docker Hub <https://hub.docker.com/r/rocm/ray/tags>`_.
      These contain the latest ROCm version but might use an older version of Ray.

2. Launch and connect to the container

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/host_dir \
      -w /app --name rocm_ray rocm/ray:ray-2.48.0.post0_rocm6.4.1_ubuntu24.04_py3.12_pytorch2.6.0 /bin/bash

      docker attach rocm_ray

   .. tip::

      * The ``--shm-size`` parameter allocates shared memory for the container. Adjust it based on your system's resources if needed.
      * Replace ``$(pwd)`` with the absolute path to the directory you want to mount inside the container.

.. _build-ray-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------------

If you prefer to use the ROCm Ubuntu image or already have a ROCm Ubuntu container, follow these steps to install Ray in the container.

1. Pull the ROCm Ubuntu Docker image. For example, use the following command to pull the ROCm Ubuntu image:

   .. code-block:: bash

      docker pull rocm/pytorch:rocm6.4.1_ubuntu24.04_py3.12_pytorch_release_2.6.0

2. Launch the Docker container. After pulling the image, launch a container using this command:

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/host_dir \
      --name rocm_ray rocm/pytorch:rocm6.4.1_ubuntu24.04_py3.12_pytorch_release_2.6.0 /bin/bash
      docker attach rocm_ray

3. Activate the conda environment
   
   .. code-block:: bash

      conda init
      source ~/.bashrc
      conda activate py_3.12

4. Install from Ray nightly wheels. Inside the running container, install the required version of Ray with ROCm support using pip:

   .. code-block:: bash

      pip install -U "ray[all] @ https://s3-us-west-2.amazonaws.com/ray-wheels/master/005c372262e050d5745f475e22e64305fa07f8b8/ray-3.0.0.dev0-cp312-cp312-manylinux2014_x86_64.whl" 

4. Verify the installed Ray version. Check whether the correct version of Ray is installed.

   .. code-block:: bash

      pip3 freeze | grep ray

   Expected output:

   .. code-block::

      memray==1.17.2
      ray @ https://s3-us-west-2.amazonaws.com/ray-wheels/master/005c372262e050d5745f475e22e64305fa07f8b8/ray-3.0.0.dev0-cp312-cp312-manylinux2014_x86_64.whl#sha256=e8f457f1bb8009b1e2744733c269fc54f3ec78e3705e16a2f88a8305720efe1b

6. Verify the installation of ROCm Ray. See :ref:`ray-verify-installation`.

.. _install-rocm-ray-bare-metal:

Install Ray on bare metal or a custom container
--------------------------------------------------------------------------------------

Follow these steps if you prefer to install ROCm manually on your host system or in a custom container.

1. Install ROCm. Follow the `ROCm installation guide <https://rocm.docs.amd.com/en/latest/deploy/linux/quick_start.html>`_ to install ROCm on your system.

   Once installed, verify your ROCm installation using:

   .. code-block:: bash

      rocm-smi

   .. code-block:: bash

      ========================================== ROCm System Management Interface ==========================================
      ==================================================== Concise Info ====================================================
     Device  [Model : Revision]    Temp        Power     Partitions      SCLK     MCLK     Fan  Perf  PwrCap  VRAM%  GPU%
               Name (20 chars)       (Junction)  (Socket)  (Mem, Compute)
       ======================================================================================================================
       0       [0x74a1 : 0x00]       50.0°C      170.0W    NPS1, SPX       131Mhz   900Mhz   0%   auto  750.0W    0%   0%
               AMD Instinct MI300X
       1       [0x74a1 : 0x00]       51.0°C      176.0W    NPS1, SPX       132Mhz   900Mhz   0%   auto  750.0W    0%   0%
               AMD Instinct MI300X
       2       [0x74a1 : 0x00]       50.0°C      177.0W    NPS1, SPX       132Mhz   900Mhz   0%   auto  750.0W    0%   0%
               AMD Instinct MI300X
       3       [0x74a1 : 0x00]       53.0°C      176.0W    NPS1, SPX       132Mhz   900Mhz   0%   auto  750.0W    0%   0%
               AMD Instinct MI300X
       ======================================================================================================================
       ================================================ End of ROCm SMI Log =================================================

2. Install the required version of Ray with ROCm support using pip:

   .. code-block:: bash

      pip install -U "ray[all] @ https://s3-us-west-2.amazonaws.com/ray-wheels/master/005c372262e050d5745f475e22e64305fa07f8b8/ray-3.0.0.dev0-cp312-cp312-manylinux2014_x86_64.whl"

3. Verify the installed Ray version. Check whether the correct version of Ray and its ROCm plugins are installed.

   .. code-block:: bash

      pip3 freeze | grep ray

.. _build-rocm-ray-from-source:

Build Ray from source
--------------------------------------------------------------------------------------

Follow the `Building Ray from Source guide <https://docs.ray.io/en/latest/ray-contribute/development.html>`__ 
to build Ray with ROCm support from source.

.. _ray-verify-installation:

Test the Ray installation
======================================================================================

Ray unit tests are optional for validating your installation if you used a
prebuilt Docker image from AMD ROCm Docker Hub.

To run unit tests manually and validate your installation fully, follow these steps:

1. After launching the container, test whether Ray detects ROCm devices as expected.

.. code-block:: bash
   
   python3 -c "import ray; ray.init(); print(ray.cluster_resources())"

2. If the setup is successful, the output should list all available ROCm devices.

Expected output (e.g. on MI300x node):

.. code-block:: shell-session

   {'memory': 1420360912896.0, 'GPU': 8.0, 'accelerator_type:AMD-Instinct-MI300X-OAM': 1.0, 'node:10.7.39.110': 1.0, 'CPU': 384.0, 'node:__internal_head__': 1.0, 'object_store_memory': 200000000000.0}

