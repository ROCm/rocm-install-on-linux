.. meta::
  :description: Install ROCm Docker containers
  :keywords: installation instructions, Docker, AMD, ROCm

********************************************************************************
Running ROCm Docker containers
********************************************************************************

Using Docker to run your ROCm applications is one of the best ways to get consistent and reproducible environments.

Prerequisites
==========================================

* ``amdgpu-dkms`` : Docker containers share the kernel with the host OS, therefore, the ROCm kernel-mode driver (``amdgpu-dkms``) must be installed on the host.
  If you've already installed ROCm, you probably already have ``amdgpu-dkms``.

  * :ref:`Chedk for amdgpu-dkms<verify-dkms>`

  * If missing, you can follow the :ref:`standard install instructions<rocm-install-quick>` (which comes with amdgpu-dkms), or :ref:`install amdgpu-dkms only<amdgpu-install-dkms>`.

.. _docker-access-gpus-in-container:

Accessing GPUs in containers
==========================================

In order to grant access go GPUs from within a container, you should run your container with the following options:

.. code-block:: shell

    docker run --device /dev/kfd --device /dev/dri --security-opt seccomp=unconfined <image>

The purpose of each option is listed below:

* ``--device /dev/fdk``

  This is the main compute interface, shared by all GPUs.

* ``--device /dev/dri``

  This directory contains the Direct Rendering Interface (DRI) for each GPU. To restrict access to specific GPUs, see :ref:`docker-restrict-gpus`.

* ``--security-opt seccomp=unconfined`` (optional)

  This option enables memory mapping, and is recommended for containers running in HPC environments.

  The performance of an application can vary depending on the assignment of GPUs
  and CPUs to the task. Typically, ``numactl`` is installed as part of many HPC
  applications to provide GPU/CPU mappings. This Docker runtime option supports
  memory mapping and can improve performance.

Docker Compose
------------------------------

You can also use ``docker compose`` to launch your containers, even when launching a single container. This can be a convienent way to
run complex docker commands (like the one above) without having to remember all the CLI arguments Here is a docker-compose file which
is equivalent to the ``docker run`` command above:

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

You can then run this with ``docker compose run my-service``.

.. _docker-restrict-gpus:

Restricting GPU access
----------------------

By passing ``--device /dev/dri``, you are granting access to all GPUs on the system. In order to limit access to a subset of GPUs, you
can pass each device individually using one or more ``-device /dev/dri/renderD<node>``, where ``<node>`` is the card index, starting from 128.

For example, to expose the first and second GPU:

.. code-block:: shell

    docker run --device /dev/kfd --device /dev/dri/renderD128 --device /dev/dri/renderD129 ..


Docker images in the ROCm ecosystem
=======================================================

Base images
-------------------------------------------------------------------------------------------------

The `ROCm Docker repository <https://github.com/ROCm/ROCm-docker>`_ hosts images useful for users
wishing to build their own containers leveraging ROCm. The built images are
available from `Docker Hub <https://hub.docker.com/u/rocm>`_. In particular
``rocm/rocm-terminal`` is a small image with the prerequisites to build HIP
applications, but does not include any libraries.

Applications
-------------------------------------------------------------------------------------------------

AMD provides pre-built images for various GPU-ready applications through
`Infinity Hub <https://www.amd.com/en/technologies/infinity-hub>`_.
Examples for invoking each application and suggested parameters used for
benchmarking are also provided there.
