.. meta::
  :description: JAX on ROCm
  :keywords: installation instructions, building, JAX, AMD, ROCm

***********
JAX on ROCm
***********

This directory provides setup instructions and necessary files to build, test, and run JAX with ROCm support in a Docker environment, suitable for both runtime and CI workflows. Explore the following methods to use or build JAX on ROCm.

For hardware, software, and third-party framework compatibility between ROCm and JAX, see the following resources:

* :ref:`system-requirements`

* :doc:`rocm:compatibility/ml-compatibility/jax-compatibility`

Using a prebuilt Docker image
===========================================

The ROCm JAX team provides prebuilt Docker images, which is the simplest way to use JAX on ROCm. These images are available on Docker Hub and come with JAX configured for ROCm.

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
--------------------

AMD validates and publishes ready-made JAX images with ROCm backends on Docker
Hub. The following Docker image tags and associated inventories are validated
for ROCm 7.0.2.
For ``jax-community`` images, see `rocm/jax-community <https://hub.docker.com/r/rocm/jax-community/tags>`__ on Docker Hub.

.. tab-set::

   .. tab-item:: JAX 0.6.0
      :selected:

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/jax:rocm7.0.2-jax0.6.0-py3.12-ubu24

            See
            ``rocm/jax:rocm7.0.2-jax0.6.0-py3.12-ubu24``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/jax/rocm7.0.2-jax0.6.0-py3.12-ubu24/images/sha256-8f82965b77f355ab39882033b7d1f4d06c9e3859c00e5004f46230f1a28bd0ea>`__.

         .. tab-item:: Python 3.10



            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/jax:rocm7.0.2-jax0.6.0-py3.10-ubu22

            See
            ``rocm/jax:rocm7.0.2-jax0.6.0-py3.10-ubu22``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/jax/rocm7.0.2-jax0.6.0-py3.10-ubu22/images/sha256-679228480d96a7297220f2fcaf2273816917232579f83e5f75398bd6e2f41653>`__.

Using a ROCm base Docker image and installing JAX
=================================================

If you prefer to use the ROCm Ubuntu image or already have a ROCm Ubuntu container, follow these steps to install JAX in the container.

1. Pull the ROCm Ubuntu Docker image. For example, use the following command to pull the ROCm Ubuntu image:

   .. code-block:: bash

      docker pull rocm/dev-ubuntu-22.04:7.0.2-complete

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
          rocm/dev-ubuntu-22.04:7.0.2-complete /bin/bash

3. Install the ``jaxlib`` v0.6.0 using ``pip`` install. Choose one of the following lines depending on your Python version:

   .. tab-set::

      .. tab-item:: Python 3.13
         :sync: python-3.13

         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp313-cp313-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.12
         :sync: python-3.12

         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp312-cp312-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.11
         :sync: python-3.11

         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp311-cp311-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.10
         :sync: python-3.10
         :selected:


         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp310-cp310-manylinux2014_x86_64.whl

4. Install JAX, ``jax-rocm7-pjrt``, and ``jax-rocm7-plugin`` from PyPI.
   
   .. code-block:: bash

      pip install jax==0.6.0 jax-rocm7-pjrt jax-rocm7-plugin

5. Verify the installed JAX version. Check whether the correct version of JAX and its ROCm plugins are installed.

   .. code-block:: bash

      pip freeze | grep jax

   Expected output:

   .. tab-set::

      .. tab-item:: Python 3.13
         :sync: python-3.13

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib @ https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp313-cp313-manylinux2014_x86_64.whl


      .. tab-item:: Python 3.12
         :sync: python-3.12

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib @ https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp312-cp312-manylinux2014_x86_64.whl


      .. tab-item:: Python 3.11
         :sync: python-3.11

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib @ https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp311-cp311-manylinux2014_x86_64.whl


      .. tab-item:: Python 3.10
         :sync: python-3.10
         :selected:


         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib @ https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp310-cp310-manylinux2014_x86_64.whl


6. Install ``libdw1`` if needed



   .. code-block:: bash

      apt update
      apt install libdw1

7. Verify the installation of ROCm JAX. See :ref:`jax-verify-installation`.

Install JAX on bare-metal or a custom container
===============================================

Follow these steps if you prefer to install ROCm manually on your host system or in a custom container.

1. Install ROCm. Follow the `ROCm installation guide <https://rocm.docs.amd.com/en/latest/deploy/linux/quick_start.html>`_ to install ROCm on your system.

   Once installed, verify your ROCm installation using:

   .. code-block:: bash

      rocm-smi

   Expected output:

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

2. Install the required version of JAX with ROCm support using ``pip``.


3. Install the ``jaxlib`` v0.6.0 using ``pip`` install. Choose one of the following lines depending on your Python version:

   .. tab-set::

      .. tab-item:: Python 3.13
         :sync: python-3.13

         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp313-cp313-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.12
         :sync: python-3.12

         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp312-cp312-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.11
         :sync: python-3.11

         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp311-cp311-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.10
         :sync: python-3.10
         :selected:


         .. code-block:: bash
         
               pip install https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp310-cp310-manylinux2014_x86_64.whl

4. Install JAX, ``jax-rocm7-pjrt``, and ``jax-rocm7-plugin`` from PyPI.
   
   .. code-block:: bash

      pip install jax==0.6.0 jax-rocm7-pjrt jax-rocm7-plugin

5. Verify the installed JAX version. Check whether the correct version of JAX and its ROCm plugins are installed.

   .. code-block:: bash

      pip freeze | grep jax

   Expected output:

   .. tab-set::

      .. tab-item:: Python 3.13
         :sync: python-3.13

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib==https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp313-cp313-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.12
         :sync: python-3.12

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib==https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp312-cp312-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.11
         :sync: python-3.11

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib==https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp311-cp311-manylinux2014_x86_64.whl

      .. tab-item:: Python 3.10
         :sync: python-3.10
         :selected:

         .. code-block::

            jax==0.6.0
            jax-rocm7-pjrt==0.6.0
            jax-rocm7-plugin==0.6.0
            jaxlib==https://github.com/ROCm/rocm-jax/releases/download/rocm-jax-v0.6.0/jaxlib-0.6.0-cp310-cp310-manylinux2014_x86_64.whl

6. Install ``libdw1`` if needed



   .. code-block:: bash

      apt update
      apt install libdw1

7. Verify the installation of ROCm JAX.

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

1. Clone the repository.


   .. code-block:: bash

    git clone https://github.com/ROCm/rocm-jax.git
    cd rocm-jax
    git checkout rocm-jaxlib-v0.6.0


2. Build ``manylinux`` wheels.


   .. code-block:: bash

    python3 build/ci_build --compiler=clang --python-versions="3.10, 3.11, 3.12, 3.13" --rocm-version=7.0.2 dist_wheels

3. Troubleshooting - If you have a ``BuildKit`` error:


   .. code-block:: bash

    sudo apt-get update
    sudo apt install docker-buildx
    export DOCKER_BUILDKIT=1

4. Move the created wheels to the wheelhouse directory.
   
   .. code-block:: bash

      mkdir -p wheelhouse && mv jax_rocm_plugin/wheelhouse/* ./wheelhouse/

5. Create Docker image.


   .. code-block:: bash
  
    python3 build/ci_build --rocm-version=7.0.2 build_dockers --filter=ubu22

6. Create a container with the image created in the previous step.


   .. code-block:: bash

    alias drun='sudo docker run --name <yourID>_rocm-jax -it --network=host  --device=/dev/infiniband --device=/dev/kfd --device=/dev/dri --ipc=host --shm-size 16G --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -w /root -v /home/<yourID>/rocm-jax:/rocm-jax'
    drun jax-ubu22.rocm700 #OR drun <docker image id or name of the image last step produced>


7. To perform unit tests:

   .. code-block:: bash

    apt-get install -y vim git
    cd /rocm-jax
    python stack.py develop
    
    cd jax
    pip install -r build/test-requirements.txt && pip install -r build/rocm-test-requirements.txt 
    python3 build/rocm/run_single_gpu.py -c 2>&1 | tee JAX_SG_0.6.0_ut.log
    python3 build/rocm/run_multi_gpu.py -c 2>&1 | tee JAX_MG_0.6.0_ut.log


For more build instructions or options, see: `<https://github.com/ROCm/rocm-jax/blob/rocm-jaxlib-v0.6.0/README.md>`__ 

.. _jax-verify-installation:

Test the JAX installation
======================================================================================

After launching the container, test whether JAX detects ROCm devices as expected:

.. code-block:: bash

   python3 -c "import jax; print(jax.devices())"
   python3 -c "import jax.numpy as jnp; x = jnp.arange(5); print(x)"

If the setup is successful, the output should list all available ROCm devices.

Expected output:

.. code-block:: shell-session

   [RocmDevice(id=0), RocmDevice(id=1), RocmDevice(id=2), RocmDevice(id=3)]

.. code-block::

   [0 1 2 3 4]

