.. meta::
  :description: Docker image support matrix
  :keywords: ROCm installation, AMD, ROCm, Docker, Docker image

.. _docker-support-matrix:

******************************************************************
Docker image support matrix
******************************************************************

AMD validates and publishes `PyTorch <https://hub.docker.com/r/rocm/pytorch>`_ and
`TensorFlow <https://hub.docker.com/r/rocm/tensorflow>`_ containers on Docker Hub. The following
tags, and associated inventories, are validated with ROCm 5.7.

.. tab-set::

    .. tab-item:: PyTorch

        .. tab-set::

            .. tab-item:: Ubuntu 22.04

               Tag
                 `rocm/pytorch:rocm6.1_ubuntu22.04_py3.10_pytorch_2.1.2 <https://hub.docker.com/layers/rocm/pytorch/rocm6.1_ubuntu22.04_py3.10_pytorch_2.1.2/images/sha256-f6ea7cee8aae299c7f6368187df7beed29928850c3929c81e6f24b34271d652b>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
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
                 `rocm/pytorch:rocm6.1_ubuntu20.04_py3.9_pytorch_2.1.2 <https://hub.docker.com/layers/rocm/pytorch/rocm6.1_ubuntu20.04_py3.9_pytorch_2.1.2/images/sha256-96ba7b33bc7fa37b88c5ed550488960dd1dcedabaa8a9c17a4fd62e6c50e7574>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.1.2 <https://github.com/ROCm/pytorch/tree/release/2.1>`_
                 * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                 * `torchvision 0.16.0 <https://github.com/pytorch/vision/tree/release/0.16>`_
                 * `TensorBoard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/pytorch:rocm6.1_ubuntu20.04_py3.9_pytorch_2.0.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.1_ubuntu20.04_py3.9_pytorch_2.0.1/images/sha256-77656adb5e8254053ef05879bfb0e62076172d0b3e89d06e18cc6b7071fdfd03>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.0.1 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/release/2.0>`_
                 * `Apex 1.0.0 <https://github.com/ROCm/apex/tree/release/1.0.0>`_
                 * `torchvision 0.15.2 <https://github.com/pytorch/vision/tree/release/0.15>`_
                 * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>


               Tag
                 `rocm/pytorch:rocm6.1_ubuntu20.04_py3.9_pytorch_1.13.1 <https://hub.docker.com/layers/rocm/pytorch/rocm6.1_ubuntu20.04_py3.9_pytorch_1.13.1/images/sha256-9a01c527a05c53fb9966159650a30b10c134c987825dce0646fbf36a24bfba7c>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.0.1 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/release/2.0>`_
                 * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                 * `torchvision 0.15.2 <https://github.com/pytorch/vision/tree/release/0.15>`_
                 * `TensorBoard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                 * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                 * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                 * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

               .. raw:: html

                  <hr>

            .. tab-item:: CentOS 7

               Tag 
                 `rocm6.1_centos7_py3.9_pytorch_staging <https://hub.docker.com/layers/rocm/pytorch/rocm6.1_centos7_py3.9_pytorch_staging/images/sha256-b4311bc0c6221ffc388f678a0654f64919a3ecd46024ecf67b09fb494d6d192d>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/yum/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `PyTorch 2.3.0 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/rocm6.1_internal_testing>`_
                 * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                 * `torchvision 0.18.0 <https://github.com/pytorch/vision/tree/release/0.18>`_
                 * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_

    .. tab-item:: TensorFlow

        .. tab-set::

            .. tab-item:: Ubuntu 20.04

               Tag
                 `rocm/tensorflow:rocm6.1-py3.10-tf2.15-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.1-py3.10-tf2.15-dev/images/sha256-5bb6212c86376d3333be0fc170fef785d8a13a2dc2a3e33649c9a4d86ec38d70>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-31013/>`_
                 * `tensorflow-rocm 2.15.0 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.1/tensorflow_rocm-2.15.0-cp310-cp310-manylinux2014_x86_64.whl>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/tensorflow:rocm6.1-py3.9-tf2.15-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.1-py3.9-tf2.15-dev/images/sha256-1435fe5c762ae1a331b9c210c48553787c05f12145d7eeb3e140b98467d04911>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.15.0 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.1/tensorflow_rocm-2.15.0-cp310-cp310-manylinux2014_x86_64.whl>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/tensorflow:rocm6.1-py3.9-tf2.14-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.1-py3.9-tf2.14-dev/images/sha256-e871c1cbe9150787395d103c05bf8c923c8457ded13dbfc2f479ecab9c4661d8>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.14.0 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.1/tensorflow_rocm-2.14.0-cp39-cp39-manylinux2014_x86_64.whl>`_
                 * `TensorBoard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14.0>`_

               .. raw:: html

                  <hr>

               Tag
                 `rocm/tensorflow:rocm6.1-py3.9-tf2.13-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.1-py3.9-tf2.13-dev/images/sha256-f221f0838f5c2320052bd54de640494e578fb860afac07144e91c8a730304e8f>`_

               Inventory
                 * `ROCm 6.1 <https://repo.radeon.com/rocm/apt/6.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.13.0 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.1/tensorflow_rocm-2.13.1-cp39-cp39-manylinux2014_x86_64.whl>`_
                 * `TensorBoard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13.0>`_
