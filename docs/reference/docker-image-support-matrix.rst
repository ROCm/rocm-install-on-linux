.. _docker-support-matrix:

******************************************************************
Docker image support matrix
******************************************************************

AMD validates and publishes `PyTorch <https://hub.docker.com/r/rocm/pytorch>`_ and
`TensorFlow <https://hub.docker.com/r/rocm/tensorflow>`_ containers on dockerhub. The following
tags, and associated inventories, are validated with ROCm 5.7.

.. tab-set::

    .. tab-item:: PyTorch

        .. tab-set::

            .. tab-item:: Ubuntu 22.04

                Tag: `rocm/pytorch:rocm5.7_ubuntu22.04_py3.10_pytorch_2.0.1 <https://hub.docker.com/layers/rocm/pytorch/rocm5.7_ubuntu22.04_py3.10_pytorch_2.0.1/images/sha256-21df283b1712f3d73884b9bc4733919374344ceacb694e8fbc2c50bdd3e767ee>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31013/>`_
                    * `Torch 2.0.1 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/release/2.0>`_
                    * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                    * `Torchvision 0.15.0 <https://github.com/pytorch/vision/tree/release/0.15>`_
                    * `Tensorboard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

            .. tab-item:: Ubuntu 20.04

                Tag: `rocm/pytorch:rocm5.7_ubuntu20.04_py3.9_pytorch_staging <https://hub.docker.com/layers/rocm/pytorch/rocm5.7_ubuntu20.04_py3.9_pytorch_2.0.1/images/sha256-4dd86046e5f777f53ae40a75ecfc76a5e819f01f3b2d40eacbb2db95c2f971d4)>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `Torch 2.1.0 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/rocm5.7_internal_testing>`_
                    * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                    * `Torchvision 0.16.0 <https://github.com/pytorch/vision/tree/release/0.16>`_
                    * `Tensorboard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_


                Tag: `Ubuntu rocm/pytorch:rocm5.7_ubuntu20.04_py3.9_pytorch_1.12.1 <https://hub.docker.com/layers/rocm/pytorch/rocm5.7_ubuntu20.04_py3.9_pytorch_1.12.1/images/sha256-e67db9373c045a7b6defd43cc3d067e7d49fd5d380f3f8582d2fb219c1756e1f>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `Torch 1.12.1 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/release/1.12>`_
                    * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                    * `Torchvision 0.13.1 <https://github.com/pytorch/vision/tree/v0.13.1>`_
                    * `Tensorboard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

                Tag: `Ubuntu rocm/pytorch:rocm5.7_ubuntu20.04_py3.9_pytorch_1.13.1 <https://hub.docker.com/layers/rocm/pytorch/rocm5.7_ubuntu20.04_py3.9_pytorch_1.13.1/images/sha256-ed99d159026093d2aaf5c48c1e4b0911508773430377051372733f75c340a4c1>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `Torch 1.13.1 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/release/1.13>`_
                    * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                    * `Torchvision 0.14.0 <https://github.com/pytorch/vision/tree/v0.14.0>`_
                    * `Tensorboard 2.12.0 <https://github.com/tensorflow/tensorboard/tree/2.12.0>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

                Tag: `Ubuntu rocm/pytorch:rocm5.7_ubuntu20.04_py3.9_pytorch_2.0.1 <https://hub.docker.com/layers/rocm/pytorch/rocm5.7_ubuntu20.04_py3.9_pytorch_2.0.1/images/sha256-4dd86046e5f777f53ae40a75ecfc76a5e819f01f3b2d40eacbb2db95c2f971d4>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `Torch 2.0.1 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/release/2.0>`_
                    * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                    * `Torchvision 0.15.2 <https://github.com/pytorch/vision/tree/release/0.15>`_
                    * `Tensorboard 2.14.0 <https://github.com/tensorflow/tensorboard/tree/2.14>`_
                    * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_
                    * `UCX 1.10.0 <https://github.com/openucx/ucx/tree/v1.10.0>`_
                    * `OMPI 4.0.3 <https://github.com/open-mpi/ompi/tree/v4.0.3>`_
                    * `OFED 5.4.3 <https://content.mellanox.com/ofed/MLNX_OFED-5.3-1.0.5.0/MLNX_OFED_LINUX-5.3-1.0.5.0-ubuntu20.04-x86_64.tgz>`_

            .. tab-item:: CentOS 7

                Tag: `rocm/pytorch:rocm5.7_centos7_py3.9_pytorch_staging <https://hub.docker.com/layers/rocm/pytorch/rocm5.7_centos7_py3.9_pytorch_staging/images/sha256-92240cdf0b4aa7afa76fc78be995caa19ee9c54b5c9f1683bdcac28cedb58d2b>`_

                * Inventory:

                * `ROCm 5.7 (yum) <https://repo.radeon.com/rocm/yum/5.7/>`_
                * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                * `Torch 2.1.0 <https://github.com/ROCmSoftwarePlatform/pytorch/tree/rocm5.7_internal_testing>`_
                * `Apex 0.1 <https://github.com/ROCmSoftwarePlatform/apex/tree/v0.1>`_
                * `Torchvision 0.16.0 <https://github.com/pytorch/vision/tree/release/0.16>`_
                * `MAGMA <https://bitbucket.org/icl/magma/src/master/>`_

    .. tab-item:: TensorFlow

        .. tab-set::

            .. tab-item:: Ubuntu 20.04

                Tag: `rocm5.7-tf2.12-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm5.7-tf2.12-dev/images/sha256-e0ac4d49122702e5167175acaeb98a79b9500f585d5e74df18facf6b52ce3e59>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `tensorflow-rocm 2.12.1 <https://pypi.org/project/tensorflow-rocm/2.12.1.570/>`_
                    * `Tensorboard 2.12.3 <https://github.com/tensorflow/tensorboard/tree/2.12>`_

                Tag: `rocm5.7-tf2.13-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm5.7-tf2.13-dev/images/sha256-6f995539eebc062aac2b53db40e2b545192d8b032d0deada8c24c6651a7ac332>`_

                * Inventory:

                    * `ROCm 5.7 <https://repo.radeon.com/rocm/apt/5.7/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `tensorflow-rocm 2.13.0 <https://pypi.org/project/tensorflow-rocm/2.13.0.570/>`_
                    * `Tensorboard 2.13.0 <https://github.com/tensorflow/tensorboard/tree/2.13>`_
