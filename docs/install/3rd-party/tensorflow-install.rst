.. meta::
  :description: Install TensorFlow on ROCm
  :keywords: installation, docker, TensorFlow, deep learning, AMD, ROCm

.. raw:: html

   <meta http-equiv="refresh" content="0; url=https://rocm.docs.amd.com">

$$$$$$$$$$$$$$
Redirecting...
$$$$$$$$$$$$$$

.. important::

   This page has moved! Go to `<https://rocm.docs.amd.com>`__ for the latest documentation.

********************************************************************************
TensorFlow on ROCm installation
********************************************************************************

`TensorFlow <https://tensorflow.org>`__ is an open-source library for solving machine learning,
deep learning, and AI problems.

This topic covers setup instructions and the necessary files to build, test, and run
TensorFlow with ROCm support in a Docker environment. To learn more about TensorFlow
on ROCm, including its use cases, recommendations, as well as hardware and software compatibility,
see :doc:`rocm:compatibility/ml-compatibility/tensorflow-compatibility`.

.. note::

   As of ROCm 6.1.0, ``tensorflow-rocm`` packages are found at `<https://repo.radeon.com/rocm/manylinux>`__.
   Prior to ROCm 6.1.0, packages were found at `<https://pypi.org/project/tensorflow-rocm>`_.

.. _install-tensorflow-versions:

.. list-table::
    :header-rows: 1
    :widths: 1, 1

    * - ROCm version
      - TensorFlow version
    * - 7.2.x
      - 2.20.0, 2.19.1, 2.18.1
    * - 7.1.x
      - 2.20.0, 2.19.1, 2.18.1
    * - 7.0.x
      - 2.19.1, 2.18.1, 2.17.1
    * - 6.4.x
      - 2.18.1, 2.17.1, 2.16.2
    * - 6.3.x
      - 2.17.0, 2.16.2 2.15.1

.. _install-tensorflow-options:

Install TensorFlow
================================================================================

To install TensorFlow for ROCm, you have the following options:

* :ref:`install-tensorflow-prebuilt-docker` **(recommended)**

  * :ref:`tensorflow-docker-support`

* :ref:`install-tensorflow-wheels`

.. _install-tensorflow-prebuilt-docker:

Use a prebuilt Docker image with TensorFlow pre-installed
--------------------------------------------------------------------------------

The recommended setup to get a TensorFlow environment is through Docker, as it avoids potential installation issues.
The tested, prebuilt image includes TensorFlow, ROCm, and other dependencies. See :ref:`tensorflow-docker-support`.
To install ROCm on bare metal, follow :doc:`/install/install-overview`.

1. Download the latest public `TensorFlow Docker image <https://hub.docker.com/r/rocm/tensorflow>`__.

   .. code-block:: shell

       docker pull rocm/tensorflow:latest

2. Once you have pulled the image, run it by using the command below:

   .. code-block:: shell

       docker run -it \
           --network=host \
           --device=/dev/kfd \
           --device=/dev/dri \
           --ipc=host \
           --shm-size 16G \
           --group-add video \
           --cap-add=SYS_PTRACE \
           --security-opt seccomp=unconfined \
           rocm/tensorflow:latest \
           /bin/bash

.. _tensorflow-docker-support:

Docker image support
--------------------------------------------------------------------------------

AMD validates and publishes ready-made TensorFlow images with ROCm backends on
Docker Hub. The following Docker image tags and associated inventories are
validated for ROCm 7.2.4.

.. tab-set::

   .. tab-item:: tensorflow-rocm 2.20.0
      :selected:

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/tensorflow:rocm7.2.4-py3.12-tf2.20-dev

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Tensorboard

               * - 24.04
                 - `2.20.0 <https://github.com/tensorflow/tensorboard/tree/2.20.0>`__

            See
            ``rocm/tensorflow:rocm7.2.4-py3.12-tf2.20-dev``
            on `Docker Hub <https://hub.docker.com/layers/rocm/tensorflow/rocm7.2.4-py3.12-tf2.20-dev/images/sha256-3ed1ade56a3eb3645082933e293ade4c804adb92a206bea85e277b13a6edc5c2>`__.

         .. tab-item:: Python 3.10

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/tensorflow:rocm7.2.4-py3.10-tf2.20-dev

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Tensorboard

               * - 22.04
                 - `2.20.0 <https://github.com/tensorflow/tensorboard/tree/2.20.0>`__

            See
            ``rocm/tensorflow:rocm7.2.4-py3.10-tf2.20-dev``
            on `Docker Hub <https://hub.docker.com/layers/rocm/tensorflow/rocm7.2.4-py3.10-tf2.20-dev/images/sha256-9c2471145e4e5889ccfe074d1b34ac8e2a588dd58182dba1f029f10a205b1b9f>`__.

   .. tab-item:: tensorflow-rocm 2.19.1

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/tensorflow:rocm7.2.4-py3.12-tf2.19-dev

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Tensorboard

               * - 24.04
                 - `2.19.0 <https://github.com/tensorflow/tensorboard/tree/2.19.0>`__

            See
            ``rocm/tensorflow:rocm7.2.4-py3.12-tf2.19-dev``
            on `Docker Hub <https://hub.docker.com/layers/rocm/tensorflow/rocm7.2.4-py3.12-tf2.19-dev/images/sha256-582a72ebb67c9e86338ac291e22fa33dc7b7ef288e93cd7c65d75e3d781539e9>`__.

         .. tab-item:: Python 3.10

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/tensorflow:rocm7.2.4-py3.10-tf2.19-dev

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Tensorboard

               * - 22.04
                 - `2.19.0 <https://github.com/tensorflow/tensorboard/tree/2.19.0>`__

            See
            ``rocm/tensorflow:rocm7.2.4-py3.10-tf2.19-dev``
            on `Docker Hub <https://hub.docker.com/layers/rocm/tensorflow/rocm7.2.4-py3.10-tf2.19-dev/images/sha256-61c9f6a6eb70499fd41ec1fe03b9527e906fb6d9b47b5ee303eb95cc8ee36b1d>`__.

   .. tab-item:: tensorflow-rocm 2.18.1

      .. tab-set::

         .. tab-item:: Python 3.12

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/tensorflow:rocm7.2.4-py3.12-tf2.18-dev

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Tensorboard

               * - 24.04
                 - `2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`__

            See
            ``rocm/tensorflow:rocm7.2.4-py3.12-tf2.18-dev``
            on `Docker Hub <https://hub.docker.com/layers/rocm/tensorflow/rocm7.2.4-py3.12-tf2.18-dev/images/sha256-02c1bf7b28af9e8dfd2bd787017edf4c837562460658ed8a684ca91e1e6601f4>`__.

         .. tab-item:: Python 3.10

            .. rubric:: Docker pull tag

            .. code-block:: shell

               docker pull rocm/tensorflow:rocm7.2.4-py3.10-tf2.18-dev

            .. rubric:: Additional software components

            .. list-table::
               :header-rows: 1

               * - Ubuntu
                 - Tensorboard

               * - 22.04
                 - `2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`__

            See
            ``rocm/tensorflow:rocm7.2.4-py3.10-tf2.18-dev``
            on `Docker Hub <https://hub.docker.com/layers/rocm/tensorflow/rocm7.2.4-py3.10-tf2.18-dev/images/sha256-50d0ff5df65a94c3fc7618c863ffa1fef1838d8bc65d979f5b740cb6d9c8db00>`__.

.. _install-tensorflow-wheels:

Use a wheels package
--------------------------------------------------------------------------------

To install TensorFlow using the wheels package, use the following command.

.. code-block:: shell

   pip install --user tensorflow-rocm==[wheel-version] -f [repo] --upgrade

* ``[wheel-version]`` is the :ref:`TensorFlow version <install-tensorflow-versions>`.

* ``[repo]`` is ``https://repo.radeon.com/rocm/manylinux/rocm-rel-X.Y/`` for versions 6.1 and later,
  where ``X.Y`` indicates the :ref:`ROCm version <install-tensorflow-versions>`.

.. note::

   Prior to ROCm 6.1, ``[wheel-version]`` followed the ``<TensorFlowVersion>.<ROCmVersion>`` format.

.. _test-tensorflow-installation:

Test the TensorFlow installation
================================================================================

To test the installation of TensorFlow, run the container as specified in
:ref:`Installing TensorFlow <install-tensorflow-options>`. Ensure you have access to the Python
shell in the Docker container.

.. code-block:: shell

    python -c 'import tensorflow' 2> /dev/null && echo ‘Success’ || echo ‘Failure’

Run a TensorFlow example
================================================================================

To quickly validate your TensorFlow environment, run a basic TensorFlow example.

The MNIST dataset is a collection of handwritten digits that may be used to train a Convolutional Neural Network (CNN)
for handwriting recognition. This dataset is included with your TensorFlow installation.

Run the following sample code to load the MNIST dataset, then train and evaluate it.

.. code-block:: python

   import tensorflow as tf
   print("TensorFlow version:", tf.__version__)
   mnist = tf.keras.datasets.mnist

   (x_train, y_train), (x_test, y_test) = mnist.load_data()
   x_train, x_test = x_train / 255.0, x_test / 255.0
   model = tf.keras.models.Sequential([
     tf.keras.layers.Flatten(input_shape=(28, 28)),
     tf.keras.layers.Dense(128, activation='relu'),
     tf.keras.layers.Dropout(0.2),
     tf.keras.layers.Dense(10)
   ])
   predictions = model(x_train[:1]).numpy()
   tf.nn.softmax(predictions).numpy()
   loss_fn = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True)
   loss_fn(y_train[:1], predictions).numpy()
   model.compile(optimizer='adam',
                 loss=loss_fn,
                 metrics=['accuracy'])
   model.fit(x_train, y_train, epochs=5)
   model.evaluate(x_test,  y_test, verbose=2)

If successful, you should see the following output indicating the image classifier is now trained to around 98% accuracy
on this dataset.

.. image:: ../../data/install/tensorflow-install/tensorflow-test-output.png
   :alt: Example output of TensorFlow MNIST training example
   :align: center

