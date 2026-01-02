.. meta::
  :description: Install JAX on ROCm
  :keywords: installation, docker, JAX, deep learning, AMD, ROCm

*************************************************************************************
JAX on ROCm installation
*************************************************************************************

`JAX <https://docs.jax.dev/en/latest/notebooks/thinking_in_jax.html>`__ is a library
for array-oriented numerical computation (similar to NumPy), with automatic differentiation
and just-in-time (JIT) compilation to enable high-performance machine learning research.

This topic covers setup instructions and the necessary files to build, test, and run
JAX with ROCm support in a Docker environment. To learn more about JAX on ROCm,
including its use cases, recommendations, as well as hardware and software compatibility,
see :doc:`rocm:compatibility/ml-compatibility/jax-compatibility`.

Install JAX on ROCm
======================================================================================

To install JAX on ROCm, you have the following options:

* :ref:`using-docker-with-jax-pre-installed` **(recommended)**
* :ref:`build-jax-rocm-docker-image`
* :ref:`install-jax-rocm-custom-container`
* :ref:`build-jax-from-source`

.. _using-docker-with-jax-pre-installed:

Use a prebuilt Docker image with JAX preinstalled
--------------------------------------------------------------------------------------
The ROCm JAX team provides prebuilt Docker images, which is the simplest way to use JAX on ROCm.
These images are available on Docker Hub and come with JAX configured for ROCm.

1. To pull the latest ROCm JAX Docker image, run:

   .. code-block:: bash

      docker pull rocm/jax:latest

   .. note::

      For specific versions of JAX, review the periodically pushed Docker images at `ROCm JAX on
      Docker Hub <https://hub.docker.com/r/rocm/jax/tags>`_.

2. Once the image is downloaded, launch a container using the following command:

   .. code-block:: bash

      docker run -it \
          --network=host \
          --device=/dev/kfd \
          --device=/dev/dri \
          --ipc=host \
          --shm-size 64G \
          --group-add video \
          --cap-add=SYS_PTRACE \
          --security-opt seccomp=unconfined \
          -v $(pwd):/jax_dir \
          --name rocm_jax \
          rocm/jax:latest /bin/bash

   .. tip::

      * The ``--shm-size`` parameter allocates shared memory for the container. Adjust it based on your system's resources if needed.
      * Replace ``$(pwd)`` with the absolute path to the directory you want to mount inside the container.

3. Verify the installation of ROCm JAX. See :ref:`jax-verify-installation`.

.. _jax-docker-support:

Docker image support
--------------------------------------------------------------------------------------

AMD validates and publishes ready-made JAX images with ROCm backends on Docker
Hub. The following Docker image tags and associated inventories are validated
for ROCm 7.0.0.
For ``jax-community`` images, see `rocm/jax-community <https://hub.docker.com/r/rocm/jax-community/tags>`__ on Docker Hub.

.. tab-set::

   .. tab-item:: JAX 0.7.1
      :selected:

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/jax:rocm7.1-jax0.7.1-py3.12

            See
            ``rocm/jax:rocm7.1-jax0.7.1-py3.12``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/jax/rocm7.1-jax0.7.1-py3.12/images/sha256-bc661fee582c591c4a9355e249afb912e8fd7dfe39f1fc02008821b1dc739bdf>`__.

         .. tab-item:: Python 3.11

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/jax:rocm7.1-jax0.7.1-py3.11

            See
            ``rocm/jax:rocm7.1-jax0.7.1-py3.11``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/jax/rocm7.1-jax0.7.1-py3.11/images/sha256-7e923ebfc117b2028c63991bfa1fbe274150ea94513c9530ece783f1a2f8a65e>`__.

.. _build-jax-rocm-docker-image:

Use a ROCm base Docker image to install JAX
--------------------------------------------------------------------------------------

If you prefer to use the ROCm Ubuntu image or already have a ROCm Ubuntu container, follow these steps to install JAX in the container.

1. Pull the ROCm Ubuntu Docker image. For example, use the following command to pull the ROCm Ubuntu image:

   .. code-block:: bash

      docker pull rocm/dev-ubuntu-22.04:7.0-complete

2. Launch the Docker container. After pulling the image, launch a container using this command:

   .. code-block:: bash

      docker run -it \
          --network=host \
          --device=/dev/kfd \
          --device=/dev/dri \
          --ipc=host \
          --shm-size 64G \
          --group-add video \
          --cap-add=SYS_PTRACE \
          --security-opt seccomp=unconfined \
          -v $(pwd):/jax_dir \
          --name rocm_jax \
          rocm/dev-ubuntu-22.04:7.0-complete /bin/bash

3. Install the latest version of JAX. Inside the running container, install the required version of JAX with ROCm support using pip:

   .. code-block:: bash

      pip3 install jax[rocm]

4. Verify the installed JAX version. Check whether the correct version of JAX and its ROCm plugins are installed.

   .. code-block:: bash

      pip3 freeze | grep jax

   Expected output:

   .. code-block::

      jax==0.4.35
      jax-rocm60-pjrt==0.4.35
      jax-rocm60-plugin==0.4.35
      jaxlib==0.4.35

5. Explicitly set the ``LLVM_PATH`` environment variable. This helps XLA find ``ld.lld`` in the PATH at runtime.

   .. code-block:: bash

      export LLVM_PATH=/opt/rocm/llvm

6. Verify the installation of ROCm JAX. See :ref:`jax-verify-installation`.

.. _install-jax-rocm-custom-container:

Install JAX on bare-metal or a custom container
--------------------------------------------------------------------------------------

Follow these steps if you prefer to install ROCm manually on your host system or in a custom container.

1. Install ROCm. Follow the `ROCm installation guide <https://rocm.docs.amd.com/en/latest/deploy/linux/quick_start.html>`_ to install ROCm on your system.

   Once installed, verify your ROCm installation using:

   .. code-block:: bash

      amd-smi

   .. code-block:: bash

      +------------------------------------------------------------------------------+
      | AMD-SMI 26.0.0+37d158ab      amdgpu version: 6.14.14  ROCm version: 7.0.1    |
      | Platform: Linux Baremetal                                                    |
      |-------------------------------------+----------------------------------------|
      | BDF                        GPU-Name | Mem-Uti   Temp   UEC       Power-Usage |
      | GPU  HIP-ID  OAM-ID  Partition-Mode | GFX-Uti    Fan               Mem-Usage |
      |=====================================+========================================|
      | 0000:09:00.0    AMD Instinct MI325X | 0 %      49 °C   0          144/1000 W |
      |   0       0       3        SPX/NPS1 | 0 %        N/A           283/262128 MB |
      +-------------------------------------+----------------------------------------+
      +------------------------------------------------------------------------------+
      | Processes:                                                                   |
      |  GPU        PID  Process Name          GTT_MEM  VRAM_MEM  MEM_USAGE     CU % |
      |==============================================================================|
      |  No running processes found                                                  |
      +------------------------------------------------------------------------------+

2. Install the required version of JAX with ROCm support using pip:

   .. code-block:: bash

      pip3 install jax[rocm]

3. Verify the installed JAX version. Check whether the correct version of JAX and its ROCm plugins are installed.

   .. code-block:: bash

      pip3 freeze | grep jax

4. Explicitly set the ``LLVM_PATH`` environment variable.

   .. code-block:: bash

      export LLVM_PATH=/opt/rocm/llvm

5. Apply the namespace patch:

   .. code-block:: bash

      patch -p1 \
          -d "$(python3 -c \"import sysconfig; print(sysconfig.get_paths()['purelib'])\")" \
          < jax_rocm_plugin/third_party/jax/namespace.patch

6. Verify the installation of ROCm JAX.

   Run the following commands to verify that ROCm JAX is installed correctly:

   .. code-block:: bash

      python3 -c "import jax; print(jax.devices())"
      python3 -c "import jax.numpy as jnp; x = jnp.arange(5); print(x)"

   Expected output:

   .. code-block::

      [RocmDevice(id=0), RocmDevice(id=1), RocmDevice(id=2), RocmDevice(id=3)]

   .. code-block::

      [0 1 2 3 4]

.. _build-jax-from-source:
.. _build-jax-wheels:

Build JAX from source
--------------------------------------------------------------------------------------

The `<https://github.com/ROCm/rocm-jax>`__ repository contains sources for the ROCm
plugin for JAX as well as Dockerfiles used to build the AMD ``rocm/jax`` images.
For the most up-to-date instructions, refer directly to the instructions in the repository:

- See `Quick build <https://github.com/ROCm/ROCm-jax?tab=readme-ov-file#quickbuild>`__ for concise high-level steps.

- See `Building <https://github.com/ROCm/rocm-jax/blob/master/BUILDING.md#building>`__ for more in-depth build instructions and troubleshooting suggestions.

.. _jax-verify-installation:

Test the JAX installation
======================================================================================

After launching the container, test whether JAX detects ROCm devices as expected:

.. code-block:: bash

   python -c "import jax; print(jax.devices())"
   python3 -c "import jax.numpy as jnp; x = jnp.arange(5); print(x)"

If the setup is successful, the output should list all available ROCm devices.

Expected output:

.. code-block:: shell-session

   [RocmDevice(id=0), RocmDevice(id=1), RocmDevice(id=2), RocmDevice(id=3)]

.. code-block::

   [0 1 2 3 4]
