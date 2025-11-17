.. meta::
  :description: Install ROCm Docker containers
  :keywords: installation instructions, Docker, AMD, ROCm

********************************************************************************
Running ROCm Docker containers
********************************************************************************

Using Docker to run your ROCm applications is one of the best ways to get consistent and
reproducible environments.

Prerequisites
==========================================

* ``amdgpu-dkms``: Docker containers share the kernel with the host OS. Therefore, the ROCm
  kernel-mode driver (``amdgpu-dkms``) must be installed on the host. If you've already installed
  ROCm, you probably already have ``amdgpu-dkms``.

  * `Check for amdgpu-dkms <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/post-install.html#verify-kernel-mode-driver-installation>`_

  * If you don't have ``amdgpu-dkms``, follow the :ref:`standard ROCm installation instructions <rocm-install-quick>`
    (which comes with ``amdgpu-dkms``) or `install amdgpu-dkms separately <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/package-manager-index.html>`__.

.. seealso::

   For instructions on installing Docker, see the `official Docker installation
   documentation <https://docs.docker.com/engine/install/>`_.

.. _docker-access-gpus-in-container:

Accessing GPUs in containers
==========================================

To grant a Docker container access to the host's AMD GPUs, run your container with the following options.
See the `Docker documentation <https://docs.docker.com/reference/cli/docker/container/run/>`_ to learn
more about the ``docker run`` command and its options.

.. code-block:: shell

    docker run --device /dev/kfd --device /dev/dri --security-opt seccomp=unconfined <image>

The purpose of each option is as follows:

* ``--device /dev/kfd``

  This is the main compute interface, shared by all GPUs.
  The Docker CLI's ``--device`` option enables directly exposing host devices
  to a container. See `Add host device to container (--device)
  <https://docs.docker.com/reference/cli/docker/container/run/#device>`_ for
  more information.

* ``--device /dev/dri``

  This directory contains the Direct Rendering Interface (DRI) for each GPU. To restrict access to specific
  GPUs, see :ref:`docker-restrict-gpus`.

* ``--security-opt seccomp=unconfined`` (optional)

  This option enables memory mapping, and is recommended for containers running in HPC
  environments.
  See `Optional security options (--security-opt)
  <https://docs.docker.com/reference/cli/docker/container/run/#security-opt>`_.

  The performance of an application can vary depending on the assignment of GPUs and CPUs to the
  task. Typically, ``numactl`` is installed as part of many HPC applications to provide GPU/CPU
  mappings. This Docker runtime option supports memory mapping and can improve performance.

Docker compose
--------------------------------------------------------------------

You can also use ``docker compose`` to launch your containers, even when launching a single
container. This can be a convenient way to run complex Docker commands without having to
remember all the CLI arguments.
The following snippet is an example ``compose.yaml`` file, which is equivalent to
the preceding ``docker run`` command:

.. code-block:: yaml

    services:
      my-service:
        image: <image>
        devices:
          - /dev/kfd
          - /dev/dri
        security_opt:
          - seccomp=unconfined

You can then run this using ``docker compose run my-service``.

.. _docker-restrict-gpus:

Restricting GPU access
--------------------------------------------------------------------

By default, passing ``--device /dev/dri`` grants access to all GPUs on the system. To limit a container to a
specific subset of GPUs, you can instead pass in their individual device nodes.

GPU device nodes are located in ``/dev/dri/`` and are typically named ``renderD128``, ``renderD129``, and so on.
You can list the available GPUs on your host system with the following command:

.. code-block:: shell

   ls /dev/dri/render*

To expose only the first two GPUs to the container, specify them directly in the run command.
Note that ``/dev/kfd`` is always required for the compute interface.

For example, to expose the first and second GPU:

.. code-block:: shell

    docker run --device /dev/kfd --device /dev/dri/renderD128 --device /dev/dri/renderD129 ..

Verifying the amdgpu driver has been loaded on GPUs
--------------------------------------------------------------------

``rocminfo`` is an application for reporting information about the HSA system attributes and agents.
``amd-smi`` is a tool that acts as a command line interface for manipulating and monitoring the amdgpu kernel.

Running ``rocminfo`` and ``amd-smi list`` inside the container will only enumerate the GPUs passed into the docker container.
Running ``rocminfo`` and ``amd-smi list`` on bare metal will enumerate all ROCm-capable GPUs on the machine.

.. _docker-rocm-images:

Docker images in the ROCm ecosystem
=======================================================

The `ROCm Docker repository <https://github.com/ROCm/ROCm-docker>`_ hosts Dockerfiles useful for
building your own ROCm-capable containers. The built images are available on
`Docker Hub <https://hub.docker.com/u/rocm>`_. In particular:

* ``rocm/rocm-terminal`` is a small image with the prerequisites to build HIP applications, but does not
  include any libraries.

* `ROCm dev images <https://hub.docker.com/search?q=rocm%2Fdev>`_ provide a variety of OS +
  ROCm versions, and are a great starting place for building applications.

Applications
-------------------------------------------------------------------------------------------------

AMD provides pre-built images for various GPU-ready AI and HPC applications through
`Infinity Hub <https://www.amd.com/en/developer/resources/infinity-hub.html>`_. There, you'll also find examples
for invoking each application and suggested parameters used for benchmarking.
