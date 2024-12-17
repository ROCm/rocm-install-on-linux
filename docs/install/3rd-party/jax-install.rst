.. meta::
  :description: JAX on ROCm
  :keywords: installation instructions, building, JAX, AMD, ROCm

***********
JAX on ROCm
***********

This directory provides setup instructions and necessary files to build, test, and run JAX with ROCm support in a Docker environment, suitable for both runtime and CI workflows. Explore the following methods to use or build JAX on ROCm.

Using a prebuilt Docker image
===========================================

The ROCm JAX team provides prebuilt Docker images, which is the simplest way to use JAX on ROCm. These images are available on Docker Hub and come with JAX configured for ROCm.

1. To pull the latest ROCm JAX Docker image, run:

   .. code-block:: bash

      docker pull rocm/jax-community:latest

   .. note::

      For older versions, review the periodically pushed Docker images at:
      `ROCm JAX Community on Docker Hub <https://hub.docker.com/r/rocm/jax-community/tags>`_.

2. Once the image is downloaded, launch a container using the following command:

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/jax_dir \
      --name rocm_jax rocm/jax-community:latest /bin/bash

      docker attach rocm_jax

   .. tip::

      * The ``--shm-size`` parameter allocates shared memory for the container. Adjust it based on your system's resources if needed.
      * Replace ``$(pwd)`` with the absolute path to the directory you want to mount inside the container.

3. Verify the installation of ROCm JAX. See :ref:`jax-verify-installation`.

Using a ROCm base Docker image and installing JAX
=================================================

If you prefer to use the ROCm Ubuntu image or already have a ROCm Ubuntu container, follow these steps to install JAX in the container.

1. Pull the ROCm Ubuntu Docker image. For example, use the following command to pull the ROCm Ubuntu image:

   .. code-block:: bash

      docker pull rocm/dev-ubuntu-22.04:6.3-complete

2. Launch the Docker container. After pulling the image, launch a container using this command:

   .. code-block:: bash

      docker run -it -d --network=host --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 64G \
      --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -v $(pwd):/jax_dir \
      --name rocm_jax rocm/dev-ubuntu-22.04:6.3-complete /bin/bash
      docker attach rocm_jax

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

Install JAX on bare-metal or a custom container
===============================================

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

2. Install the required version of JAX with ROCm support using pip:

   .. code-block:: bash

      pip3 install jax[rocm]

3. Verify the installed JAX version. Check whether the correct version of JAX and its ROCm plugins are installed.

   .. code-block:: bash

      pip3 freeze | grep jax

4. Explicitly set the ``LLVM_PATH`` environment variable.

   .. code-block:: bash

      export LLVM_PATH=/opt/rocm/llvm

5. Verify the installation of ROCm JAX.

   Run the following commands to verify that ROCm JAX is installed correctly:

   .. code-block:: bash

      python3 -c "import jax; print(jax.devices())"
      python3 -c "import jax.numpy as jnp; x = jnp.arange(5); print(x)"

   Expected output:

   .. code-block::

      [RocmDevice(id=0), RocmDevice(id=1), RocmDevice(id=2), RocmDevice(id=3)]

   .. code-block::

      [0 1 2 3 4]

Build ROCm JAX from source
==========================

Follow these steps to build JAX with ROCm support from source.

1. Clone the ROCm-specific fork of JAX with the desired branch:

   .. code-block:: bash

      git clone https://github.com/ROCm/jax -b <branch_name>
      cd jax

.. _build-jax-wheels:

2. Run the following command to build the necessary wheels:

   .. code-block:: bash

      python3 ./build/build.py build --wheels=jaxlib,jax-rocm-plugin,jax-rocm-pjrt \
          --rocm_version=60 --rocm_path=/opt/rocm-[version]

   This will generate three wheels in the ``dist/`` directory:

   - ``jaxlib`` (generic, device agnostic library)
   - ``jax-rocm-plugin`` (ROCm-specific plugin)
   - ``jax-rocm-pjrt`` (ROCm-specific runtime)

3. Install the custom JAX wheels.

   .. code-block:: bash

      python3 setup.py develop --user && pip3 -m pip install dist/*.whl

Simplified build script
-----------------------

For a streamlined build process, consider using the ``jax/build/rocm/dev_build_rocm.py`` script. See
`<https://github.com/rocm/jax/tree/main/build/rocm>`__ for more information.

.. _jax-verify-installation:

Testing your JAX installation with ROCm
=======================================

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
