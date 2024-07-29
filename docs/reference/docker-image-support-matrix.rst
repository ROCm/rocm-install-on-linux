.. meta::
  :description: Docker image support matrix
  :keywords: ROCm installation, AMD, ROCm, Docker, Docker image

.. _docker-support-matrix:

******************************************************************
Docker image support matrix
******************************************************************

AMD validates and publishes ready-made `PyTorch <https://hub.docker.com/r/rocm/pytorch>`_ and
`TensorFlow <https://hub.docker.com/r/rocm/tensorflow>`_ images with ROCm backends on Docker Hub.
The following Docker image tags and associated inventories are validated for ROCm 6.2.

.. tab-set::

    .. tab-item:: PyTorch

        .. tab-set::

            .. tab-item:: Ubuntu 22.04

               Tag
                 `rocm/pytorch:rocm6.2_ubuntu22.04_py3.10_pytorch_2.3.0 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                 * `PyTorch 2.3 <https://github.com/ROCm/pytorch/tree/release/2.3>`_
                 * `Apex 1.3.0 <https://github.com/ROCm/apex/tree/release/1.3.0>`_
                 * `torchvision 0.18.0 <https://github.com/pytorch/vision/tree/v0.18.0>`_
                 * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.14.1 <https://github.com/openucx/ucx/tree/v1.14.1>`_
                 * `OMPI 4.1.5 <https://github.com/open-mpi/ompi/tree/v4.1.5>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/pytorch:rocm6.2_ubuntu22.04_py3.10_pytorch_2.1.2 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                 * `PyTorch 2.1.2 <https://github.com/ROCm/pytorch/tree/release/2.1>`_
                 * `Apex 1.1.0 <https://github.com/ROCm/apex/tree/release/1.1.0>`_
                 * `torchvision 0.16.1 <https://github.com/pytorch/vision/tree/v0.16.1>`_
                 * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.14.1 <https://github.com/openucx/ucx/tree/v1.14.1>`_
                 * `OMPI 4.1.5 <https://github.com/open-mpi/ompi/tree/v4.1.5>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

            .. tab-item:: Ubuntu 20.04

               Tag
                 `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_2.3.0 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.3.0 <https://github.com/ROCm/pytorch/tree/release/2.3>`_
                 * `Apex 1.3.0 <https://github.com/ROCm/apex/tree/1.3.0>`_
                 * `torchvision 0.18.0 <https://github.com/pytorch/vision/tree/release/v0.18.0>`_
                 * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13.0>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_2.2.1 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.2.1 <https://github.com/ROCm/pytorch/tree/release/2.2>`_
                 * `Apex 1.2.0 <https://github.com/ROCm/apex/tree/1.2.0>`_
                 * `torchvision 0.17.1 <https://github.com/pytorch/vision/tree/v0.17>`_
                 * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/pytorch:rocm6.2_ubuntu20.04_py3.9_pytorch_2.1.2 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.1.2 <https://github.com/ROCm/pytorch/tree/release/2.1>`_
                 * `Apex 1.0.0 <https://github.com/ROCm/apex/tree/1.0.0>`_
                 * `torchvision 0.16.1 <https://github.com/pytorch/vision/tree/release/0.16>`_
                 * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/pytorch:rocm6.1_ubuntu20.04_py3.9_pytorch_1.13.1 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 1.13.1 <https://github.com/ROCm/pytorch/tree/release/1.13.1>`_
                 * `Apex 1.0.0 <https://github.com/ROCm/apex/tree/1.0.0>`_
                 * `torchvision 0.14.0 <https://github.com/pytorch/vision/tree/release/0.14.0>`_
                 * `TensorBoard 2.17.0 <https://github.com/tensorflow/tensorboard/tree/2.17.0>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

    .. tab-item:: TensorFlow

        .. tab-set::

            .. tab-item:: Ubuntu 20.04

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.17-dev <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.17.0 <>`_
                 * `TensorBoard 2.17.0 <https://github.com/tensorflow/tensorboard/tree/2.17.0>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/tensorflow:rocm6.2-py3.10-tf2.15 <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                 * `tensorflow-rocm 2.15.1 <>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/tensorflow:rocm6.2-py3.10-tf2.15-dev <>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                 * `tensorflow-rocm 2.15.1 <>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_
