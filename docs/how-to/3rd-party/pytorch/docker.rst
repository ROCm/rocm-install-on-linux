PyTorch+ROCm in Docker
=======================

Using Docker to run your PyTorch + ROCm application is one of the best ways to get consistent and reproducible environments.

Additional PyTorch Docker arguments
-------------------------------

Regardless of which image you use or build, running PyTorch docker images requires several arguments in addition to those discussed in :ref:`docker-access-gpus-in-container`.

* ``--ipc=host`` OR ``--shm-size=Xg``

  PyTorch uses shared memory to share data between processes (such as multi-threaded data loaders). As such, you must increase the shared memory size, which defaults to 64M. This can be done in two ways:

  * ``--ipc=host`` shares the IPC directly from the host, which will allow the container access to all resources on the host. For most applications, this is sufficient.

  * ``--shm-size`` allows more granular control over resourcing for a container. In applications with multiple containers running simultaneously, setting this value appropriately can help prevent memory errors.

  See the `PyTorch docs on using docker images <https://github.com/pytorch/pytorch?tab=readme-ov-file#using-pre-built-images>`_ for information on these options.

.. code-block:: bash

                docker run -it --device=/dev/fkd --device=/dev/dri \
                  --security-opt seccomp=unconfined --ipc=host \
                  <image>

Alternatively, you can use the equivalent ``docker-compose.yaml``:

.. code-block:: yaml

    version: "3.7"
    services:
      my-service:
        image: <image>
        device:
          - /dev/fdk
          - /dev/dri
        security_opt:
          - seccomp:unconfined
        ipc: host


Pre-built PyTorch+ROCm Docker images
--------------------------------------

The easiest method to run PyTorch+ROCm is to use a pre-built image from `AMD ROCm on docker hub <https://hub.docker.com/u/rocm>`_, which contain ROCm as well as PyTorch. You can select an image from either of the following sources, with your desired OS, ROCm, Python, and PyTorch versions.

* `rocm/pytorch <https://hub.docker.com/r/rocm/pytorch>`_ - latest stable builds
* `rocm/pytorch-nightly <https://hub.docker.com/r/rocm/pytorch-nightly>`_ - latest nightly builds

For example, to run the latest rocm/pytorch image, run:

.. code-block:: bash

                docker run -it --device=/dev/fkd --device=/dev/dri \
                  --security-opt seccomp=unconfined --ipc=host \
                  rocm/pytorch:rocm6.0.2_ubuntu22.04_py3.10_pytorch_2.1.2

.. Tip::

   Always use a specific tag (e.g. ``rocm6.0.2_ubuntu22.04_py3.10_pytorch_2.1.2``) over ``latest``! Otherwise, the image may change without your knowledge.

Custom Docker Images
--------------------

As is often the case, your specific requirements may not be met by one of the pre-built PyTorch+ROCm images. For example, you may need additional Python dependencies, a different version of PyTorch, or even a completely different combination of OS, ROCm, Python, and PyTorch.

To meet these needs, you can build your own ROCm docker images.

From ROCm dev container
.......................

We provide several dev containers, which contain just the base OS + ROCm. These containers are a great place to start when building custom images, as you don't have to install ROCm into the image yourself.

* Select a base image that meets your needs. To find a list of base images, `search rocm/dev <https://hub.docker.com/search?q=rocm%2Fdev>`_ on Docker Hub.
* Build your ``dockerfile``

  * Install required python version
  * Install PyTorch, and other python dependencies

Below is an example ``dockerfile`` based on ``rocm/dev-ubuntu-22.04:5.7``

.. literalinclude:: ../../../docker_examples/torch/dockerfile_from_dev_ubuntu
                    :language: dockerfile

.. tip::

   * Using ARGs can help simplify your dockerfiles, and prevent version mismatches
   * Use specific versions, rather than ``latest``, to help keep builds reproducible. This also applies to python packages.
   * It is always a good idea to use virtual environments, *even inside docker*!
