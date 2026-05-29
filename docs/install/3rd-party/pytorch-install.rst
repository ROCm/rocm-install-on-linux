.. meta::
  :description: Install PyTorch on ROCm
  :keywords: installation, docker, PyTorch, deep learning, AMD, ROCm

*************************************************************************************
PyTorch on ROCm installation
*************************************************************************************

`PyTorch <https://pytorch.org/>`__ is an open-source tensor library designed for deep learning.
PyTorch on ROCm provides mixed-precision and large-scale training using AMD `MIOpen <https://github.com/ROCm/MIOpen>`_
and `RCCL <https://github.com/ROCm/rccl>`_ libraries.

This topic covers setup instructions and the necessary files to build, test, and run
PyTorch with ROCm support in a Docker environment. To learn more about PyTorch on ROCm,
including its use cases, recommendations, as well as hardware and software compatibility,
see :doc:`rocm:compatibility/ml-compatibility/pytorch-compatibility`.

Install PyTorch
======================================================================================

To install PyTorch for ROCm, you have the following options:

* :ref:`using-docker-with-pytorch-pre-installed` **(recommended)**

  * :ref:`pytorch-docker-support`

* :ref:`using-wheels-package`

* :ref:`using-pytorch-upstream-docker-image`

.. _using-docker-with-pytorch-pre-installed:

Use a prebuilt Docker image with PyTorch pre-installed
--------------------------------------------------------------------------------------

The recommended setup to get a PyTorch environment is through Docker, as it avoids potential installation issues.
The tested, prebuilt image includes PyTorch, ROCm, and other dependencies. See :ref:`pytorch-docker-support`.
To install ROCm on bare metal, follow :doc:`/install/install-overview`.

1. Download the latest public `PyTorch Docker image <https://hub.docker.com/r/rocm/pytorch>`_.

   .. code-block:: bash

      docker pull rocm/pytorch:latest

   .. _pytorch-docker-latest-note:

   .. important::

      The ``rocm/pytorch:latest`` tag points to
      a Docker image with the latest ROCm-tested release of PyTorch.

   You can download Docker images with specific ROCm, PyTorch, and operating
   system versions. See the available tags on
   `Docker Hub <https://hub.docker.com/r/rocm/pytorch/tags>`_.

2. Start a Docker container using the image.

   .. code-block:: bash

       docker run -it \
           --cap-add=SYS_PTRACE \
           --security-opt seccomp=unconfined \
           --device=/dev/kfd \
           --device=/dev/dri \
           --group-add video \
           --ipc=host \
           --shm-size 8G \
           rocm/pytorch:latest

   .. note::

       This will automatically download the image if it does not exist on the host. You can also pass the ``-v`` argument to mount any data directories from the host onto the container.

.. _pytorch-docker-support:

Docker image support
--------------------------------------------------------------------------------------

AMD validates and publishes ready-made `PyTorch <https://hub.docker.com/r/rocm/pytorch>`_ images
with ROCm backends on Docker Hub. The following Docker image tags and associated inventories are
validated for ROCm 7.2.4.

.. tab-set::

   .. tab-item:: PyTorch 2.9.1  

         .. tab-set::

            .. tab-item:: Python 3.12

               .. rubric:: Docker pull tag

               .. code-block:: shell

                  docker pull rocm/pytorch:rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.9.1

               .. rubric:: Additional software components

               .. list-table::
                  :header-rows: 1

                  * - Ubuntu
                    - Apex
                    - torchvision
                    - UCX
                    - Open MPI

                  * - 24.04
                    - `1.9.0+rocm7.2.4 <https://repo.radeon.com/rocm/manylinux/rocm-rel-7.2.4/>`__
                    - `0.24.0 <https://github.com/pytorch/vision/tree/v0.24.0>`__
                    - `1.16.0+ds-5ubuntu1 <http://archive.ubuntu.com/ubuntu/pool/universe/u/ucx/>`__
                    - `4.1.6-7ubuntu2 <http://archive.ubuntu.com/ubuntu/pool/universe/o/openmpi/>`__

               See
               ``rocm/pytorch:rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.9.1``
               on `Docker Hub
               <https://hub.docker.com/layers/rocm/pytorch/rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.9.1/images/sha256-7fe531fa185af260352fe7fbb3fa64ad749abe72adf0600a648c4692801b125a>`__.

            .. tab-item:: Python 3.10

               .. rubric:: Docker pull tag

               .. code-block:: shell

                  docker pull rocm/pytorch:rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.9.1
                  
               .. rubric:: Additional software components

               .. list-table::
                  :header-rows: 1

                  * - Ubuntu
                    - Apex
                    - torchvision
                    - UCX
                    - Open MPI

                  * - 22.04
                    - `1.9.0+rocm7.2.4 <https://repo.radeon.com/rocm/manylinux/rocm-rel-7.2.4/>`__
                    - `0.24.0 <https://github.com/pytorch/vision/tree/v0.24.0>`__
                    - `1.12.1~rc2-1 <http://archive.ubuntu.com/ubuntu/pool/universe/u/ucx/>`__
                    - `4.1.2-2ubuntu1 <http://archive.ubuntu.com/ubuntu/pool/universe/o/openmpi/>`__

               See
               ``rocm/pytorch:rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.9.1``
               on `Docker Hub
               <https://hub.docker.com/layers/rocm/pytorch/rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.9.1/images/sha256-9c9592175fece788d6c0b86059012f49b568dc95c98c13879dfdf89c30342559>`__.

   .. tab-item:: PyTorch 2.8.0

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/pytorch:rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.8.0

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Apex
                 - torchvision
                 - UCX
                 - Open MPI

               * - 24.04
                 - `1.8.0+rocm7.2.4 <https://repo.radeon.com/rocm/manylinux/rocm-rel-7.2.4/>`__
                 - `0.23.0 <https://github.com/pytorch/vision/tree/v0.23.0>`__
                 - `1.16.0+ds-5ubuntu1 <http://archive.ubuntu.com/ubuntu/pool/universe/u/ucx/>`__
                 - `4.1.6-7ubuntu2 <http://archive.ubuntu.com/ubuntu/pool/universe/o/openmpi/>`__

            See
            ``rocm/pytorch:rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.8.0``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/pytorch/rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.8.0/images/sha256-d909ec7b7251b2882340d66c0001e77f5e7c3848566d2cf81b4c08b34683cd31>`__.

         .. tab-item:: Python 3.10

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/pytorch:rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.8.0

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Apex
                 - torchvision
                 - UCX
                 - Open MPI

               * - 22.04
                 - `1.8.0+rocm7.2.4 <https://repo.radeon.com/rocm/manylinux/rocm-rel-7.2.4/>`__
                 - `0.23.0 <https://github.com/pytorch/vision/tree/v0.23.0>`__
                 - `1.12.1~rc2-1 <http://archive.ubuntu.com/ubuntu/pool/universe/u/ucx/>`__
                 - `4.1.2-2ubuntu1 <http://archive.ubuntu.com/ubuntu/pool/universe/o/openmpi/>`__

            See
            ``rocm/pytorch:rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.8.0``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/pytorch/rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.8.0/images/sha256-880e126d83370e3502b069a39f85cbd7b1f6f7dbfbceb00b6fefbac03c5da091>`__.

   .. tab-item:: PyTorch 2.7.1

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/pytorch:rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.7.1

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Apex
                 - torchvision
                 - UCX
                 - Open MPI

               * - 24.04
                 - `1.7.0+rocm7.2.4 <https://repo.radeon.com/rocm/manylinux/rocm-rel-7.2.4/>`__
                 - `0.22.1 <https://github.com/pytorch/vision/tree/v0.22.1>`__
                 - `1.16.0+ds-5ubuntu1 <http://archive.ubuntu.com/ubuntu/pool/universe/u/ucx/>`__
                 - `4.1.6-7ubuntu2 <http://archive.ubuntu.com/ubuntu/pool/universe/o/openmpi/>`__

            See
            ``rocm/pytorch:rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.7.1``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/pytorch/rocm7.2.4_ubuntu24.04_py3.12_pytorch_release_2.7.1/images/sha256-71c406685a88a0b50e03dcda2ea14f53630c69b6caeaee28f90ac7dd098cb928>`__.

         .. tab-item:: Python 3.10

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/pytorch:rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.7.1

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Apex
                 - torchvision
                 - UCX
                 - Open MPI

               * - 22.04
                 - `1.7.0+rocm7.2.4 <https://repo.radeon.com/rocm/manylinux/rocm-rel-7.2.4/>`__
                 - `0.22.1 <https://github.com/pytorch/vision/tree/v0.22.1>`__
                 - `1.12.1~rc2-1 <http://archive.ubuntu.com/ubuntu/pool/universe/u/ucx/>`__
                 - `4.1.2-2ubuntu1 <http://archive.ubuntu.com/ubuntu/pool/universe/o/openmpi/>`__

            See
            ``rocm/pytorch:rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.7.1``
            on `Docker Hub
            <https://hub.docker.com/layers/rocm/pytorch/rocm7.2.4_ubuntu22.04_py3.10_pytorch_release_2.7.1/images/sha256-dc29751681f2ed6c4f006de40e1c2ff7cc5a05dee3f5c4fe2898534771603bc5>`__.

.. _install_pytorch_wheels:
.. _using-wheels-package:

Use a wheels package
--------------------------------------------------------------------------------------

PyTorch supports the ROCm platform by providing tested wheels packages. To access this feature, go
to `pytorch.org/get-started/locally/ <https://pytorch.org/get-started/locally/>`_. For the correct
wheels command, you must select **Linux**, **Python**, **pip**, and **ROCm** in the matrix.

.. note::

   The available ROCm release varies between the **PyTorch Build** of ``Stable`` or ``Nightly``.
   More recent releases are generally available through the Nightly builds.

.. dropdown:: Setting up the environment for the wheel installation

  1. Choose one of the following three options:
  
     **Option 1:**
  
     a. Download a base Docker image with the correct ROCm version.
  
        .. list-table::
            :header-rows: 1
  
            * - Base OS
              - Docker Image
            * - Ubuntu 22.04
              - `rocm/dev-ubuntu-22.04 <https://hub.docker.com/r/rocm/dev-ubuntu-22.04>`_
            * - Ubuntu 24.04
              - `rocm/dev-ubuntu-24.04 <https://hub.docker.com/r/rocm/dev-ubuntu-24.04>`_
  
     b. Pull the selected image.
  
        .. code-block:: bash
  
            docker pull rocm/dev-ubuntu-22.04:latest
  
     c. Start a Docker container using the downloaded image.
  
        .. code-block:: bash
  
            docker run -it --device=/dev/kfd --device=/dev/dri --group-add video rocm/dev-ubuntu-22.04:latest
  
     **Option 2:**
  
     a. Select a base OS Docker image. Check :ref:`system-requirements`.
  
     b. Pull selected base OS image (Ubuntu 22.04, for example).
  
        .. code-block:: bash
  
            docker pull ubuntu:22.04
  
     c. Start a Docker container using the downloaded image.
  
        .. code-block:: bash
  
            docker run -it --device=/dev/kfd --device=/dev/dri --group-add video ubuntu:22.04
  
     d. Install ROCm using the directions in the :ref:`rocm-install-overview` section.
  
     **Option 3:**
  
     Install on bare-metal. Check :ref:`system-requirements` and install ROCm using the
     instructions in the :ref:`rocm-install-overview` section.

  2. Install the required dependencies for the wheels package.
  
     .. code-block:: bash
  
         sudo apt update
         sudo apt install libjpeg-dev python3-dev python3-pip
         pip3 install wheel setuptools

* Install ``torch``, ``torchvision``, and ``torchaudio``, as specified in the `installation matrix <https://pytorch.org/get-started/locally/>`_.

  .. code-block:: bash

      pip3 install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/rocm7.2      

  .. note::

      The above command uses the ROCm 7.2 PyTorch wheel. If you want a different version of ROCm, modify the command accordingly.


.. _using-pytorch-rocm-docker-image:
.. _building-pytorch-from-source:

Build PyTorch from source
--------------------------------------------------------------------------------------

Use the ``rocm/pytorch:latest`` image, uninstall the preinstalled PyTorch
package, and rebuild PyTorch from source. This ensures compatibility with your
specific ROCm version, GPU architecture, and project requirements.

1. Download the latest PyTorch Docker image.

   .. code-block:: bash

       docker pull rocm/pytorch:latest

2. Start a Docker container using the downloaded image.

   .. code-block:: bash

       docker run -it \
           --cap-add=SYS_PTRACE \
           --security-opt seccomp=unconfined \
           --device=/dev/kfd \
           --device=/dev/dri \
           --group-add video \
           --ipc=host \
           --shm-size 8G \
           rocm/pytorch:latest

3. Uninstall the pre-installed PyTorch inside the container. Otherwise, the prebuilt ROCm PyTorch from the
   container might conflict with your source build.

   .. code-block:: bash

       pip3 uninstall -y torch torchvision torchaudio

4. Clone the PyTorch repository.

   .. code-block:: bash

       cd ~
       git clone https://github.com/pytorch/pytorch.git
       cd pytorch
       git submodule update --init --recursive

5. (Optional) Set your ROCm architecture.

   By default, PyTorch builds for a broad set of AMD architectures. To speed
   up compilation, you can target only your GPU architecture.

   To determine your architecture:

   .. code-block:: bash

       rocminfo | grep gfx

   Then set the ``PYTORCH_ROCM_ARCH`` environment variable:

   .. code-block:: bash

       export PYTORCH_ROCM_ARCH=<uarch>

   Replace ``<uarch>`` with the result from ``rocminfo`` (for example, ``gfx90a``, ``gfx1030``). See :ref:`system-requirements`
   for the list of AMD GPU architectures.

6. Build and install PyTorch following the instructions in
   `<https://github.com/pytorch/pytorch?tab=readme-ov-file#install-pytorch>`__.

.. _using-pytorch-upstream-docker-image:

Use the PyTorch upstream Dockerfile
--------------------------------------------------------------------------------------

If you don't want to use a prebuilt base Docker image, you can build a custom base Docker image
using scripts from the PyTorch repository. This uses a standard Docker image from operating system
maintainers and installs all the required dependencies, including:

* ROCm
* torchvision
* Conda packages
* The compiler toolchain

1. Clone the PyTorch repository.

   .. code-block:: bash

       cd ~
       git clone https://github.com/pytorch/pytorch.git
       cd pytorch
       git submodule update --init --recursive

2. Build the PyTorch Docker image.

   .. code-block:: bash

       cd .ci/docker
       ./build.sh pytorch-linux-<os-version>-rocm<rocm-version>-py<python-version> -t rocm/pytorch:build_from_dockerfile

   Where:

   * ``<os-version>`` = ``ubuntu20.04`` (or ``focal``), ``ubuntu22.04`` (or ``jammy``)
   * ``<rocm-version>`` = ``6.0``, ``6.1``, ``6.2``
   * ``<python-version>`` = ``3.8`` - ``3.11``

   To verify that your image was successfully created, run:

   .. code-block:: bash

       docker image ls rocm/pytorch:build_from_dockerfile

   If successful, the output looks like this:

   .. code-block:: bash

       REPOSITORY    TAG                       IMAGE ID         CREATED           SIZE
       rocm/pytorch  build_from_dockerfile     17071499be47     2 minutes ago     32.8GB

3. Start a Docker container using the image with the mounted PyTorch folder.

   .. code-block:: bash

       docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
       --user root --device=/dev/kfd --device=/dev/dri \
       --group-add video --ipc=host --shm-size 8G \
       -v ~/pytorch:/pytorch rocm/pytorch:build_from_dockerfile

   You can also pass the ``-v`` argument to mount any data directories from the host onto the container.

4. Go to the PyTorch directory.

   .. code-block:: bash

       cd /pytorch

5. Set ROCm architecture.

   To determine your AMD architecture, run:

   .. code-block:: bash

       rocminfo | grep gfx

   The result looks like this (for ``gfx1030`` architecture):

   .. code-block:: bash

       Name:                    gfx1030
       Name:                    amdgcn-amd-amdhsa--gfx1030

   Set the ``PYTORCH_ROCM_ARCH`` environment variable to specify the architectures you want to
   build PyTorch for.

   .. code-block:: bash

       export PYTORCH_ROCM_ARCH=<uarch>

   where ``<uarch>`` is the architecture reported by the ``rocminfo`` command.

6. Build PyTorch.

   .. code-block:: bash

       .ci/pytorch/build.sh

   This converts PyTorch CUDA sources to :doc:`HIP <hip:index>` and builds the
   PyTorch framework.

   To check if your build is successful, run:

   .. code-block:: bash

       echo $? # should return 0 if success

.. _test-pytorch-installation:

Test the PyTorch installation
======================================================================================

You can use PyTorch unit tests to validate your PyTorch installation. If you used a
**prebuilt PyTorch Docker image from AMD ROCm Docker Hub** or installed an
**official wheels package**, validation tests are not necessary.

If you want to manually run unit tests to validate your PyTorch installation fully, follow these steps:

1. Import the torch package in Python to test if PyTorch is installed and accessible.

   .. note::

       Do not run the following command from the PyTorch home directory.

   .. code-block:: bash

       python3 -c 'import torch' 2> /dev/null && echo 'Success' || echo 'Failure'

2. Check if the GPU is accessible from PyTorch. In the PyTorch framework, ``torch.cuda`` is a generic way
   to access the GPU. This can only access an AMD GPU if one is available.

   .. code-block:: bash

       python3 -c 'import torch; print(torch.cuda.is_available())'


3. Run unit tests to validate the PyTorch installation fully.

   .. note::

       You must run the following command from the PyTorch home directory.

   .. code-block:: bash

       PYTORCH_TEST_WITH_ROCM=1 python3 test/run_test.py --verbose \
       --include test_nn test_torch test_cuda test_ops \
       test_unary_ufuncs test_binary_ufuncs test_autograd

   This command ensures that the required environment variable is set to skip certain unit tests for
   ROCm. This also applies to wheel installs in a non-controlled environment.

   .. note::

       Make sure your PyTorch source code corresponds to the PyTorch wheel or the installation in the
       Docker image. Incompatible PyTorch source code can give errors when running unit tests.

   Some tests may be skipped, as appropriate, based on your system configuration. ROCm doesn't
   support all PyTorch features; tests that evaluate unsupported features are skipped. Other tests might
   be skipped, depending on the host or GPU memory and the number of available GPUs.

   If the compilation and installation are correct, all tests will pass.

4. (Optional) Run individual unit tests.

   .. code-block:: bash

       PYTORCH_TEST_WITH_ROCM=1 python3 test/test_nn.py --verbose

   You can replace ``test_nn.py`` with any other test set.

Run a PyTorch example
======================================================================================

The PyTorch examples repository provides basic examples that exercise the functionality of your
framework.

Two of our favorite testing databases are:

* **MNIST** (Modified National Institute of Standards and Technology): A database of handwritten
  digits that can be used to train a Convolutional Neural Network for **handwriting recognition**.
* **ImageNet**: A database of images that can be used to train a network for
  **visual object recognition**.

MNIST PyTorch example
--------------------------------------------------------------------------------------

1. Clone the PyTorch examples repository.

   .. code-block:: bash

       git clone https://github.com/pytorch/examples.git

2. Go to the MNIST example folder.

   .. code-block:: bash

       cd examples/mnist

3. Follow the instructions in the ``README.md`` file in this folder to install the requirements. Then run:

   .. code-block:: bash

       python3 main.py

   This generates the following output:

   .. code-block::

       ...
       Train Epoch: 14 [58240/60000 (97%)]     Loss: 0.010128
       Train Epoch: 14 [58880/60000 (98%)]     Loss: 0.001348
       Train Epoch: 14 [59520/60000 (99%)]     Loss: 0.005261

       Test set: Average loss: 0.0252, Accuracy: 9921/10000 (99%)

ImageNet PyTorch example
-----------------------------------------------------------------------------------------

1. Clone the PyTorch examples repository (if you didn't already do this in the preceding MNIST
   example).

   .. code-block:: bash

       git clone https://github.com/pytorch/examples.git

2. Go to the ImageNet example folder.

   .. code-block:: bash

       cd examples/imagenet

3. Follow the instructions in the ``README.md`` file in this folder to install the Requirements. Then run:

   .. code-block:: bash

       python3 main.py

.. _troubleshooting-pytorch:

Troubleshooting
======================================================================================

* What to do if you get the following error when trying to run PyTorch:

  .. code-block:: shell

     hipErrorNoBinaryForGPU: Unable to find code object for all current devices!

  The error denotes that the installation of PyTorch and/or other dependencies or libraries do not support the current GPU. To workaround this issue, use the following steps:

  1. Confirm that the hardware supports the ROCm stack. Refer to :ref:`system-requirements` and :ref:`rocm-install-on-windows:system-requirements-win`.

  2. Determine the gfx target.

     .. code-block:: shell

        rocminfo | grep gfx

  3. Check if PyTorch is compiled with the correct gfx target.

     .. code-block:: shell

        TORCHDIR=$( dirname $( python3 -c 'import torch; print(torch.__file__)' ) )
        llvm-readobj --offloading $TORCHDIR/lib/libtorch_hip.so # check for gfx target

     .. note::

        Recompile PyTorch with the right gfx target if compiling from the source if
        the hardware is not supported.

* What if you are unable to access Docker or GPU in user accounts?

  Ensure that the user is added to docker, video, and render Linux groups as described in :ref:`group_permissions`.

* Can you install PyTorch directly on bare metal?

  Bare-metal installation of PyTorch is supported through wheels. For more information, see :ref:`using-wheels-package`.

* How do you profile PyTorch workloads?

  Use the PyTorch Profiler as described in :ref:`mi300x-pytorch-profiler` to profile GPU kernels on ROCm.
