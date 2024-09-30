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

.. |hr| raw:: html

   <hr>

.. tab-set::

    .. tab-item:: PyTorch

        .. tab-set::

            .. tab-item:: Ubuntu 22.04

               Tag
                 `rocm/pytorch:rocm6.2.1_ubuntu22.04_py3.10_pytorch_release_2.1.2 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2.1_ubuntu22.04_py3.10_pytorch_release_2.1.2/images/sha256-1a497364d1541ca4ff97dcd69ffb49b3ad0d82d73bba90095089002e3a8a64a2>`_ (latest)

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

               |hr|

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

               |hr|

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

               |hr|

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
                 `rocm/pytorch:rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_2.3.0 <https://hub.docker.com/layers/rocm/pytorch/rocm6.2.1_ubuntu20.04_py3.9_pytorch_release_2.3.0/images/sha256-8ffc2fcde77c54800057b385bc95f1481fc5300dccff192afa865b29a5d00201>`_

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

               |hr|

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

               |hr|

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

               |hr|

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

               |hr|

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

               |hr|

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

               |hr|

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

    .. tab-item:: TensorFlow

        .. tab-set::

            .. tab-item:: Ubuntu 20.04

               Tag
                 `rocm/tensorflow:rocm6.2.1-py3.9-tf2.16.1-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2.1-py3.9-tf2.16.1-dev/images/sha256-55b5f75180cc8be17d6d5d4fab0f35f2f20d240ca9c4c6828af18cf81bba68c6>`_ (latest)

               Inventory
                 * `ROCm 6.2.1 <https://repo.radeon.com/rocm/apt/6.2.1/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.16.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2.1-py3.9-tf2.15.1-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2.1-py3.9-tf2.15.1-dev/images/sha256-c2feef869374f8eccfad77d210457160a3019df6b15ffc226c27acddb5d03462>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2.1-py3.9-tf2.14.1-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2.1-py3.9-tf2.14.1-dev/images/sha256-99f8560aea6d4cd7bc030c0f7e32651abbaf5f118e1aa119288b3eace1421659>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.14.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.14.1 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.16-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2-py3.9-tf2.16-dev/images/sha256-dcdeafe0dcb5b5160c7ab7ef860dc29a95f2d2dd691946497ab6fb549cde8497>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.16.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.16-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2-py3.9-tf2.16-runtime/images/sha256-ea1f05be5f618111ad0edbf25458fc96e02bc596859cf8c7ddbbf7c797fa22b3>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.16.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.15-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2-py3.9-tf2.15-dev/images/sha256-1a28f5735a719e2a6ef076523ce76fa308663ad12f0b5530666468a2b775666f>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.15-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2-py3.9-tf2.15-runtime/images/sha256-81ef38ce067666ab2a4ba3cff8f5803f8596b4d7395169b4f0e2946ba2a403f6>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.14-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2-py3.9-tf2.14-dev/images/sha256-ad1fbaed5b9f2085d2716468147aca8d390e0e99470960e7b8f7e11d0286e80f>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.14.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.14.1 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

               |hr|

               Tag
                 `rocm/tensorflow:rocm6.2-py3.9-tf2.14-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2-py3.9-tf2.14-runtime/images/sha256-ed0ca0548ba140253e23ef683440e144e90e309e26d208ad2a84b5d6d5ddd95a>`_

               Inventory
                 * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                 * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                 * `tensorflow-rocm 2.14.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                 * `TensorBoard 2.14.1 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_
