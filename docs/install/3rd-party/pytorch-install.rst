.. meta::
  :description: Installing PyTorch for ROCm
  :keywords: installation instructions, PyTorch, AMD, ROCm

**********************************************************************************
Installing PyTorch for ROCm
**********************************************************************************

`PyTorch <https://pytorch.org/>`_ is an open-source tensor library designed for deep learning. PyTorch on
ROCm provides mixed-precision and large-scale training using our
`MIOpen <https://github.com/ROCm/MIOpen>`_ and
`RCCL <https://github.com/ROCm/rccl>`_ libraries.

To install PyTorch for ROCm, you have the following options:

* :ref:`using-docker-with-pytorch-pre-installed` (*recommended*)

  * :ref:`pytorch-docker-support`

* :ref:`using-wheels-package`

* :ref:`using-pytorch-rocm-docker-image`

* :ref:`using-pytorch-upstream-docker-image`

.. |br| raw:: html

   <br/>

For hardware, software, and third-party framework compatibility between ROCm and PyTorch, refer to:

* :ref:`system-requirements`
* :ref:`3rd-party-support-matrix`

.. _using-docker-with-pytorch-pre-installed:

Using a Docker image with PyTorch pre-installed
===============================================================

To install ROCm on bare metal, follow :doc:`/install/install-overview`. The recommended option to
get a PyTorch environment is through Docker.

Using Docker provides portability and access to a prebuilt Docker image that
has been rigorously tested within AMD. This can also save compilation time and
should perform as tested and mitigate potential installation issues. See
:ref:`pytorch-docker-support`

1. Download the latest public `PyTorch Docker image <https://hub.docker.com/r/rocm/pytorch>`_.

   .. code-block:: bash

      docker pull rocm/pytorch:latest

   You can also download a specific and supported configuration with different user-space ROCm
   versions, PyTorch versions, and operating systems by filtering through the `tags <https://hub.docker.com/r/rocm/pytorch/tags>`_.

   .. _pytorch-docker-latest-note:

   .. important::

      As of ROCm 6.2.1, ``rocm/pytorch:latest`` points to a docker image with the latest ROCm tested release version of PyTorch (for example, version 2.3), similar to ``rocm/pytorch:latest-release`` tag.
      Before ROCm 6.2.1, ``rocm/pytorch:latest`` pointed to a development version of PyTorch, which didn't correspond to a specific PyTorch release.

      .. csv-table::
        :header: "Description", "6.2.1 and later", "6.2.0 and earlier"

        "Latest PyTorch tested release", **rocm/pytorch:latest** |br| rocm/pytorch:latest-release, rocm/pytorch:latest-release
        "Latest PyTorch dev version", rocm/pytorch:latest-internal, **rocm/pytorch:latest**


2. Start a Docker container using the image.

   .. code-block:: bash

       docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
       --device=/dev/kfd --device=/dev/dri --group-add video \
       --ipc=host --shm-size 8G rocm/pytorch:latest

   .. note::

       This will automatically download the image if it does not exist on the host. You can also pass the ``-v`` argument to mount any data directories from the host onto the container.

.. _pytorch-docker-support:

Docker image support
--------------------

AMD validates and publishes ready-made `PyTorch <https://hub.docker.com/r/rocm/pytorch>`_ images
with ROCm backends on Docker Hub. The following Docker image tags and associated inventories are
validated for ROCm 6.2.

.. tab-set::

   .. tab-item:: ROCm 6.2.1

      .. tab-set::

         .. tab-item:: PyTorch 2.3.0

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_2.3.0 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_2.3.0/images/sha256-8ffc2fcde77c54800057b385bc95f1481fc5300dccff192afa865b29a5d00201>`_ (`latest <https://hub.docker.com/layers/rocm/pytorch/latest/images/sha256-63f46c1bd0db29c74238efa72778b4fabc614e180b8e9e3bcf8d457d9b34b610>`_)

                    .. note::

                       As of ROCm 6.2.1, ``rocm/pytorch:latest`` points to a Docker image with the latest ROCm tested
                       release version of PyTorch (for example, version 2.3), similar to ``rocm/pytorch:latest-release`` tag. See
                       :ref:`Using a Docker image with PyTorch pre-installed <pytorch-docker-latest-note>` for more information.

                  Inventory
                    * `ROCm 6.2.1 <https://repo.radeon.com/rocm/apt/6.2.1/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 2.3.0 <https://github.com/ROCm/pytorch/tree/release/2.3>`_
                    * `Apex 1.3.0 <https://github.com/ROCm/apex/tree/release/1.3.0>`_
                    * `torchvision 0.18.0 <https://github.com/pytorch/vision/tree/v0.18.0>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.1 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

         .. tab-item:: PyTorch 2.2.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_2.2.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_2.2.1/images/sha256-b655f032e13fa05051b7e447b83735be88dd8286888d7d242d0337106bae1547>`_

                  Inventory
                    * `ROCm 6.2.1 <https://repo.radeon.com/rocm/apt/6.2.1/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 2.2.1 <https://github.com/ROCm/pytorch/tree/release/2.3>`_
                    * `Apex 1.2.0 <https://github.com/ROCm/apex/tree/release/1.2.0>`_
                    * `torchvision 0.17.1 <https://github.com/pytorch/vision/tree/v0.17.1>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.1 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

         .. tab-item:: PyTorch 2.1.2

            .. tab-set::

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/pytorch:rocm6.2.1_ubuntu22.04_py3.10_pytorch_release_2.1.2 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2.1_ubuntu22.04_py3.10_pytorch_release_2.1.2/images/sha256-1a497364d1541ca4ff97dcd69ffb49b3ad0d82d73bba90095089002e3a8a64a2>`_

                  Inventory
                    * `ROCm 6.2.1 <https://repo.radeon.com/rocm/apt/6.2.1/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                    * `PyTorch 2.1.2 <https://github.com/ROCm/pytorch/tree/release/2.1>`_
                    * `Apex 1.1.0 <https://github.com/ROCm/apex/tree/release/1.1.0>`_
                    * `torchvision 0.16.1 <https://github.com/pytorch/vision/tree/release/0.16>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.14.1 <https://github.com/openucx/ucx/tree/v1.14.1>`_
                    * `OMPI 4.1.5 <https://github.com/open-mpi/ompi/tree/v4.1.5>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

         .. tab-item:: PyTorch 1.13.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_1.13.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_1.13.1/images/sha256-eed24dd5534d996155e646f69e61181c8f63ecf02d100a98c657936849756c6b>`_

                  Inventory
                    * `ROCm 6.2.1 <https://repo.radeon.com/rocm/apt/6.2.1/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 1.13.1 <https://github.com/ROCm/pytorch/tree/release/1.13>`_
                    * `Apex 1.0.0 <https://github.com/ROCm/apex/tree/release/1.0.0>`_
                    * `torchvision 0.14.0 <https://github.com/pytorch/vision/tree/v0.14.0>`_
                    * `TensorBoard 2.17.0 <https://github.com/tensorflow/tensorboard/tree/2.17.0>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_


   .. tab-item:: ROCm 6.2.0

      .. tab-set::

         .. tab-item:: PyTorch 2.3.0

            .. tab-set::

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu22.04_py3.10_pytorch_release_2.3.0 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu22.04_py3.10_pytorch_release_2.3.0/images/sha256-931d3e3dcebe6c6fab84adf16cfca3e1d1449100df7c881a46fccd06f6c9bc1c>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                    * `PyTorch 2.3.0 <https://github.com/ROCm/pytorch/tree/release/2.3>`_
                    * `Apex 1.3.0 <https://github.com/ROCm/apex/tree/release/1.3.0>`_
                    * `torchvision 0.18.0 <https://github.com/pytorch/vision/tree/v0.18.0>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.14.1 <https://github.com/openucx/ucx/tree/v1.14.1>`_
                    * `OMPI 4.1.5 <https://github.com/open-mpi/ompi/tree/v4.1.5>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_release_2.3.0 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu20.04_py3.9_pytorch_release_2.3.0/images/sha256-a1b2be0e705b02c25a3cf7fdaa991afea68deaebcafa58ef1872ce961713617c>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 2.3.0 <https://github.com/ROCm/pytorch/tree/release/2.3>`_
                    * `Apex 1.3.0 <https://github.com/ROCm/apex/tree/release/1.3.0>`_
                    * `torchvision 0.18.0 <https://github.com/pytorch/vision/tree/v0.18.0>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.1 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

         .. tab-item:: PyTorch 2.2.1

            .. tab-set::

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu22.04_py3.9_pytorch_release_2.2.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu22.04_py3.9_pytorch_release_2.2.1/images/sha256-86b214d2e4b380c3a6fdc8e161d5cc0a154a567880a2377f636ebf80611dfff7>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 2.2.1 <https://github.com/ROCm/pytorch/tree/release/2.2>`_
                    * `Apex 1.2.0 <https://github.com/ROCm/apex/tree/release/1.2.0>`_
                    * `torchvision 0.17.1 <https://github.com/pytorch/vision/tree/v0.17.1>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.14.1 <https://github.com/openucx/ucx/tree/v1.14.1>`_
                    * `OMPI 4.1.5 <https://github.com/open-mpi/ompi/tree/v4.1.5>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_2.2.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu20.04_py3.9_pytorch_release_2.2.1/images/sha256-83ee72d83356c36df640133d088189f16c8f119ec9c6569a873dfaa8de161f01>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 2.2.1 <https://github.com/ROCm/pytorch/tree/release/2.2>`_
                    * `Apex 1.2.0 <https://github.com/ROCm/apex/tree/release/1.2.0>`_
                    * `torchvision 0.17.1 <https://github.com/pytorch/vision/tree/v0.17.1>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

         .. tab-item:: PyTorch 2.1.2

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_release_2.1.2 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu20.04_py3.9_pytorch_release_2.1.2/images/sha256-58186da550e3d83c5b598ce0c1f581206eabd82c85bd77d22b34f5695d749762>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 2.1.2 <https://github.com/ROCm/pytorch/tree/release/2.1>`_
                    * `Apex 1.1.0 <https://github.com/ROCm/apex/tree/release/1.1.0>`_
                    * `torchvision 0.16.1 <https://github.com/pytorch/vision/tree/release/0.16>`_
                    * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

         .. tab-item:: PyTorch 1.13.1

            .. tab-set::

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu22.04_py3.9_pytorch_1.13.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu22.04_py3.9_pytorch_release_1.13.1/images/sha256-fe417e67704625038ed782bf48ac892a1451721d86eef5f8b28b5fe16d320e0d>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 1.13.1 <https://github.com/ROCm/pytorch/tree/release/1.13>`_
                    * `Apex 1.0.0 <https://github.com/ROCm/apex/tree/release/1.0.0>`_
                    * `torchvision 0.14.0 <https://github.com/pytorch/vision/tree/v0.14.0>`_
                    * `TensorBoard 2.17.0 <https://github.com/tensorflow/tensorboard/tree/2.17>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.14.1 <https://github.com/openucx/ucx/tree/v1.14.1>`_
                    * `OMPI 4.1.5 <https://github.com/open-mpi/ompi/tree/v4.1.5>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_


               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_1.13.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2_ubuntu20.04_py3.9_pytorch_release_1.13.1/images/sha256-9338a4fb9cac31fa25f1c7c8907e6ab1bbf8b57f4e04b7af2ae4dbf7c7d36dae>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `PyTorch 1.13.1 <https://github.com/ROCm/pytorch/tree/release/1.13>`_
                    * `Apex 1.0.0 <https://github.com/ROCm/apex/tree/release/1.0.0>`_
                    * `torchvision 0.14.0 <https://github.com/pytorch/vision/tree/v0.14.0>`_
                    * `TensorBoard 2.17.0 <https://github.com/tensorflow/tensorboard/tree/2.17.0>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

.. _install_pytorch_wheels:
.. _using-wheels-package:

Using a wheels package
======================

PyTorch supports the ROCm platform by providing tested wheels packages. To access this feature, go
to `pytorch.org/get-started/locally/ <https://pytorch.org/get-started/locally/>`_. For the correct
wheels command, you must select **Linux**, **Python**, **pip**, and **ROCm** in the matrix.

.. note::

   The available ROCm release varies between the **PyTorch Build** of ``Stable`` or ``Nightly``.
   More recent releases are generally available through the Nightly builds.

1. Choose one of the following three options:

   **Option 1:**

   a. Download a base Docker image with the correct user-space ROCm version.

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

   Install on bare metal. Check :ref:`system-requirements` and install ROCm using the
   directions in the  :ref:`rocm-install-overview` section.

2. Install the required dependencies for the wheels package.

   .. code-block:: bash

       sudo apt update
       sudo apt install libjpeg-dev python3-dev python3-pip
       pip3 install wheel setuptools

3. Install ``torch``, ``torchvision``, and ``torchaudio``, as specified in the
   `installation matrix <https://pytorch.org/get-started/locally/>`_.

   .. note::

       The following command uses the ROCm 6.2 PyTorch wheel. If you want a different version of ROCm,
       modify the command accordingly.

   .. code-block:: bash

       pip3 install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/rocm6.2/

4. (Optional) Use MIOpen kdb files with ROCm PyTorch wheels.

   PyTorch uses `MIOpen <https://github.com/ROCm/MIOpen>`_ for machine learning
   primitives, which are compiled into kernels at runtime. Runtime compilation causes a small warm-up
   phase when starting PyTorch, and MIOpen kdb files contain precompiled kernels that can speed up
   application warm-up phases.

   MIOpen kdb files can be used with ROCm PyTorch wheels. However, the kdb files need to be placed in
   a specific location with respect to the PyTorch installation path. A helper script simplifies this task by
   taking the ROCm version and GPU architecture as inputs. This works for Ubuntu.

   You can download the helper script here:
   `install_kdb_files_for_pytorch_wheels.sh <https://raw.githubusercontent.com/wiki/ROCm/pytorch/files/install_kdb_files_for_pytorch_wheels.sh>`_, or use:

   .. code-block:: bash

       wget https://raw.githubusercontent.com/wiki/ROCm/pytorch/files/install_kdb_files_for_pytorch_wheels.sh

   After installing ROCm PyTorch wheels, run the following code:

   .. code-block:: bash

       #Optional: replace 'gfx90a' with your architecture and 6.2 with your preferred ROCm version
       export GFX_ARCH=gfx90a

       #Optional
       export ROCM_VERSION=6.2

       ./install_kdb_files_for_pytorch_wheels.sh

.. _using-pytorch-rocm-docker-image:

Using the PyTorch ROCm base Docker image
========================================

The pre-built base Docker image has all dependencies installed, including:

* ROCm
* torchvision
* Conda packages
* The compiler toolchain

Additionally, a particular environment flag (``BUILD_ENVIRONMENT``) is set, which is used by the build
scripts to determine the configuration of the build environment.

1. Download the Docker image. This is the base image, which does not contain PyTorch.

   .. code-block:: bash

       docker pull rocm/pytorch:latest-base

2. Start a Docker container using the downloaded image.

   .. code-block:: bash

       docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --device=/dev/kfd --device=/dev/dri --group-add video --ipc=host --shm-size 8G rocm/pytorch:latest-base

   You can also pass the ``-v`` argument to mount any data directories from the host onto the container.

Inside the docker container, run the following steps:

3. Clone the PyTorch repository.

   .. code-block:: bash

       cd ~
       git clone https://github.com/pytorch/pytorch.git
       cd pytorch
       git submodule update --init --recursive

4. Set ROCm architecture (optional).

   .. note::

       By default in the ``rocm/pytorch:latest-base`` image, PyTorch builds simultaneously for the following
       architectures:

       * gfx900
       * gfx906
       * gfx908
       * gfx90a
       * gfx1030
       * gfx1100
       * gfx1101
       * gfx940
       * gfx941
       * gfx942

   If you want to compile *only* for your microarchitecture (uarch), run:

   .. code-block:: bash

       export PYTORCH_ROCM_ARCH=<uarch>

   Where ``<uarch>`` is the architecture reported by the ``rocminfo`` command.

   To find your uarch, run:

   .. code-block:: bash

       rocminfo | grep gfx

5. Build PyTorch.

   .. code-block:: bash

       .ci/pytorch/build.sh

   This converts PyTorch sources for HIP compatibility and builds the PyTorch framework.

   To check if your build is successful, run:

   .. code-block:: bash

       echo $? # should return 0 if success

.. _using-pytorch-upstream-docker-image:

Using the PyTorch upstream Dockerfile
=====================================

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

   This converts PyTorch sources for
   `HIP compatibility <https://www.amd.com/en/developer/rocm-hub/hip-sdk.html>`_ and builds the
   PyTorch framework.

   To check if your build is successful, run:

   .. code-block:: bash

       echo $? # should return 0 if success

.. _test-pytorch-installation:

Testing the PyTorch installation
================================

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

Running a basic PyTorch example
===============================

The PyTorch examples repository provides basic examples that exercise the functionality of your
framework.

Two of our favorite testing databases are:

* **MNIST** (Modified National Institute of Standards and Technology): A database of handwritten
  digits that can be used to train a Convolutional Neural Network for **handwriting recognition**.
* **ImageNet**: A database of images that can be used to train a network for
  **visual object recognition**.

MNIST PyTorch example
---------------------

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
---------------------------------------------------------------------------------------------------------

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
===============

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
        roc-obj-ls -v $TORCHDIR/lib/libtorch_hip.so # check for gfx target

     .. note:: 

        Recompile PyTorch with the right gfx target if compiling from the source if
        the hardware is not supported. 

* What if you are unable to access Docker or GPU in user accounts?

  Ensure that the user is added to docker, video, and render Linux groups as described in :ref:`group_permissions`.

* Can you install PyTorch directly on bare metal?

  Bare-metal installation of PyTorch is supported through wheels. For more information, see :ref:`using-wheels-package`. 

* How do you profile PyTorch workloads?

  Use the PyTorch Profiler as described in :ref:`mi300x-pytorch-profiler` to profile GPU kernels on ROCm. 
