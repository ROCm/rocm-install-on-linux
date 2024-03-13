PyTorch+ROCm in Docker
=======================

Using Docker to run your PyTorch + ROCm application is one of the best ways to get consistent and reproducible environemnts.

Additional PyTorch Docker Args
-------------------------------

Regardless of which image you use or build, running PyTorch docker images requires several arguments in addition to those discussed in :ref:`docker-access-gpus-in-container`.

* ``--ipc=host`` OR ``--shm-size=Xg``

  PyTorch uses shared memory to share data betwee processes (such as multithreaded data loaders). As such, you must increase the shared memory size, which defaults to 64M. This can be done in two ways:

  * ``--ipc=host`` shares the IPC directly from the host, which will allow the container access to all resources on the host. For most applications, this is sufficient.

  * ``--shm-size`` allows more granular control over resourcing for a container. In applications with multiple containers running simultaneously, setting this value appropriately can help prevent memory errors.

  See the `PyTorch docs on using docker images <https://github.com/pytorch/pytorch?tab=readme-ov-file#using-pre-built-images>`_ for information on these options.

.. code-block:: bash

                docker run -it --device=/dev/fkd --device=/dev/dri --security-opt seccomp=unconfined --ipc=host <image>


Pre-Built PyTorch+ROCm Docker Images
--------------------------------------

The easiest method to run PyTorch+ROCm is to use a pre-built image from `AMD ROCm on docker hub <https://hub.docker.com/u/rocm>`_, which contain ROCm as well as PyTorch. You can select an image from either of the following sources, with your desired OS, ROCm, Python, and PyTorch versions.

* `rocm/pytorch <https://hub.docker.com/r/rocm/pytorch>`_ - latest stable builds
* `rocm/pytorch-nightly <https://hub.docker.com/r/rocm/pytorch-nightly>`_ - latest nightly builds

For example, to run the latest rocm/pytorch image, run:

.. code-block:: bash

                docker run -it --device=/dev/fkd --device=/dev/dri --security-opt seccomp=unconfined --ipc=host rocm/pytorch:latest


Custom Docker Images
--------------------

As is often the case, your specific requirements may not be met by one of the pre-built PyTorch+ROCm images. For example, you may need additional pythond dependencies, a different version of PyTorch, or even a completely different combination of OS, ROCm, Python, and PyTorch.

To meet these needs, you can build your own ROCm docker images.

From ROCm dev container
.......................

We provide several dev containers, which contain just the base OS + ROCm. These containers are a great place to start when building custom images, as you don't have to install ROCm into the image yourself.

* Select a base image that neets your needs. To find a list of base images, `search rocm/dev <https://hub.docker.com/search?q=rocm%2Fdev>`_ on Docker Hub.
* Build your ``dockerfile``

  * Install required python version
  * Install PyTorch, and other python dependencies

Below is an example ``dockerfile`` based on ``rocm/dev-ubuntu-22.04:5.7``

.. literalinclude:: ../../docker_examples/torch/dockerfile_from_dev_ubuntu
                    :language: dockerfile

.. tip::

   * Using ARGs can help simplify your dockerfiles, and prevent version mismatches
   * Use specific versions, rather than ``latest``, to help keep builds reproducible. This also applies to python packages.
   * It is always a good idea to use virtual environments, *even inside docker*!

Building PyTorch from source
............................

You may need to install a version of pytorch which is not available as a pre-built binary. In this case,  you can build and install PyTorch from source.

For details, see :ref:`building pytorch from source <https://github.com/pytorch/pytorch#from-source>`_.

.. literalinclude:: ../../docker_examples/torch/dockerfile_from_base
                    :language: dockerfile


From scratch
............

Using Dependency Managers (PDM)
...............................

Using Pre-Compiled MIOpen KDB Files
===================================

<MOVE TO INSTALL_TORCH SECTION?>

PyTorch uses MIOpen for machine learning primitives, which are compiled into kernels at runtime. Runtime compilation causes a small warm-up phase when starting PyTorch, and MIOpen kdb files contain precompiled kernels that can speed up application warm-up phases.

.. tip::

   The MIOpen installation script takes time.

MIOpen kdb files can be used with ROCm PyTorch wheels. However, the kdb files need to be placed in a specific location with respect to the PyTorch installation path. A helper script simplifies this task by taking the ROCm version and GPU architecture as inputs. This works for Ubuntu and CentOS.

You can download the helper script here: install_kdb_files_for_pytorch_wheels.sh, or use:

.. code-block:: bash

                wget https://raw.githubusercontent.com/wiki/ROCmSoftwarePlatform/pytorch/files/install_kdb_files_for_pytorch_wheels.sh

                #Optional; replace 'gfx90a' with your architecture and 5.6 with your preferred ROCm version
                export GFX_ARCH=gfx90a     # Limiting architectures can greatly speed up install time
                export ROCM_VERSION=5.6

                ./install_kdb_files_for_pytorch_wheels.sh

LINKS:

* https://github.com/ROCm/pytorch/wiki/Using-MIOpen-kdb-files-with-ROCm-PyTorch-wheels
* https://docs.amd.com/projects/MIOpen/en/latest/#installing-miopen-kernels-package
* https://docs.amd.com/projects/MIOpen/en/latest/cache.html#installing-pre-compiled-kernels
* https://github.com/ROCm/MIOpen
