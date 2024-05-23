.. meta::
  :description: Installing TensorFlow for ROCm
  :keywords: installation instructions, TensorFlow, AMD, ROCm

****************************************************************************************
Installing TensorFlow for ROCm
****************************************************************************************

TensorFlow is an open-source library for solving machine learning,
deep learning, and AI problems. It can solve many
problems across different sectors and industries, but primarily focuses on
neural network training and inference. It is one of the most popular and
in-demand frameworks and is very active in open-source contribution and
development.

.. warning::

   As of ROCm 6.1, ``tensorflow-rocm`` packages are found at `<https://repo.radeon.com/rocm/manylinux>`__.
   Prior to ROCm 6.1, packages were found at `<https://pypi.org/project/tensorflow-rocm>`_.

.. _install-tensorflow-versions:

.. list-table::
    :header-rows: 1
    :widths: 1, 1

    * - ROCm version
      - TensorFlow version
    * - 6.1.x
      - 2.13.1, 2.14.0, 2.15.0
    * - 6.0.x
      - 2.12.1, 2.13.1, 2.14.0

.. _install-tensorflow-options:

Installing TensorFlow
===============================================

The following section describes TensorFlow installation options.

.. _install-tensorflow-prebuilt-docker:

Using a prebuilt Docker image
-------------------------------------------------------------------------------

To install ROCm on bare metal, follow
:doc:`/tutorial/install-overview`. The recommended option to
get a TensorFlow environment is through Docker.

Using Docker provides portability and access to a prebuilt Docker image that
has been rigorously tested within AMD. This can also save compilation time and
should perform as tested and mitigate potential installation issues.

Follow these steps:

1. Pull the latest public TensorFlow Docker image.

   .. code-block:: shell

       docker pull rocm/tensorflow:latest

2. Once you have pulled the image, run it by using the command below:

   .. code-block:: shell

       docker run -it --network=host --device=/dev/kfd --device=/dev/dri \
       --ipc=host --shm-size 16G --group-add video --cap-add=SYS_PTRACE \
       --security-opt seccomp=unconfined rocm/tensorflow:latest

.. _install-tensorflow-wheels:

Using a wheels package
-------------------------------------------------------------------------------

To install TensorFlow using the wheels package, use the following command.

.. code-block:: shell

   /usr/bin/python[version] -m pip install --user tensorflow-rocm==[wheel-version] -f [repo] --upgrade

* The optional ``[version]`` parameter is the Python version.

* ``[wheel-version]`` is the :ref:`TensorFlow version <install-tensorflow-versions>`.

* ``[repo]`` is ``https://repo.radeon.com/rocm/manylinux/rocm-rel-X.Y/`` for versions 6.1 and later,
  where ``X.Y`` indicates the :ref:`ROCm version <install-tensorflow-versions>`.

.. note::

   For details on ``tensorflow-rocm`` wheels and ROCm version compatibility, refer to
   `<https://github.com/ROCm/tensorflow-upstream/blob/develop-upstream/rocm_docs/tensorflow-rocm-release.md>`__.

.. _test-tensorflow-installation:

Testing the TensorFlow installation
=======================================

To test the installation of TensorFlow, run the container as specified in
:ref:`Installing TensorFlow <install-tensorflow-options>`. Ensure you have access to the Python
shell in the Docker container.

.. code-block:: shell

    python[version] -c 'import tensorflow' 2> /dev/null && echo ‘Success’ || echo ‘Failure’

Running a basic TensorFlow example
======================================

The TensorFlow examples repository provides basic examples that exercise the
framework's functionality. The MNIST database is a collection of handwritten
digits that may be used to train a Convolutional Neural Network for handwriting
recognition.

Follow these steps:

1. Clone the TensorFlow example repository.

   .. code-block:: shell

       cd ~
       git clone https://github.com/tensorflow/models.git

2. Install the dependencies of the code, and run the code.

   .. code-block:: shell

      pip3 install -r requirement.txt
      python[version] mnist_tf.py
