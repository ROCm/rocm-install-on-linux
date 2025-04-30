.. meta::
  :description: Installing TensorFlow for ROCm
  :keywords: installation instructions, TensorFlow, AMD, ROCm

******************
TensorFlow on ROCm
******************

`TensorFlow <https://tensorflow.org>`_ is an open-source library for solving machine learning,
deep learning, and AI problems. It can solve many
problems across different sectors and industries, but primarily focuses on
neural network training and inference. It is one of the most popular and
in-demand frameworks and is very active in open-source contribution and
development.

To install TensorFlow for ROCm, you have the following options:

* :ref:`install-tensorflow-prebuilt-docker` (recommended)

  * :ref:`tensorflow-docker-support`

* :ref:`install-tensorflow-wheels`

For hardware, software, and third-party framework compatibility between ROCm and TensorFlow, see the following resources:

* :ref:`system-requirements`

* :doc:`rocm:compatibility/ml-compatibility/tensorflow-compatibility`

.. note::

   As of ROCm 6.1, ``tensorflow-rocm`` packages are found at `<https://repo.radeon.com/rocm/manylinux>`__.
   Prior to ROCm 6.1, packages were found at `<https://pypi.org/project/tensorflow-rocm>`_.

.. _install-tensorflow-versions:

.. list-table::
    :header-rows: 1
    :widths: 1, 1

    * - ROCm version
      - TensorFlow version
    * - 6.4.x
      - 2.18.1, 2.17.1, 2.16.2
    * - 6.3.x
      - 2.17.0, 2.16.2 2.15.1
    * - 6.2.x
      - 2.16.1, 2.15.1, 2.14.1
    * - 6.1.x
      - 2.15.0, 2.14.0, 2.13.1
    * - 6.0.x
      - 2.14.0, 2.13.1 2.12.1

.. _install-tensorflow-prebuilt-docker:

.. _install-tensorflow-options:

Using a Docker image with TensorFlow pre-installed
==================================================

To install ROCm on bare metal, follow
:doc:`/install/install-overview`. The recommended option to
get a TensorFlow environment is through Docker.

Using Docker provides portability and access to a prebuilt Docker image that
has been rigorously tested within AMD. This can also save compilation time and
should perform as tested and mitigate potential installation issues. See
:ref:`tensorflow-docker-support`

Follow these steps:

1. Pull the latest public TensorFlow Docker image.

   .. code-block:: shell

       docker pull rocm/tensorflow:latest

2. Once you have pulled the image, run it by using the command below:

   .. code-block:: shell

       docker run -it --network=host --device=/dev/kfd --device=/dev/dri \
       --ipc=host --shm-size 16G --group-add video --cap-add=SYS_PTRACE \
       --security-opt seccomp=unconfined rocm/tensorflow:latest

.. |hr| raw:: html

   <hr>

.. _tensorflow-docker-support:

Docker image support
--------------------

AMD validates and publishes ready-made `TensorFlow <https://hub.docker.com/r/rocm/pytorch>`_ images
with ROCm backends on Docker Hub. The following Docker image tags and associated inventories are
validated for ROCm 6.4.

.. tab-set::

   .. tab-item:: TensorFlow 2.18.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.12-tf2.18-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.12-tf2.18-dev/images/sha256-fa9cf5fa6c6079a7118727531ccd0056c6e3224a42c3d6e78a49e7781daafff4>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.4 <https://www.python.org/downloads/release/python-3124/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.18.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.12-tf2.18-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.12-tf2.18-runtime/images/sha256-14addca4b92a47c806b83ebaeed593fc6672cd99f0017ed8dad759fe72ed0309>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.4 <https://www.python.org/downloads/release/python-3124/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.18.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.10-tf2.18-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.10-tf2.18-dev/images/sha256-f5e151060df04ff5fb59f5604b49cd371931bbe75b06aec9fe7781397c4be0ce>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.18.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.10-tf2.18-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.10-tf2.18-runtime/images/sha256-5cd4c03fdb1036570c0d4929da60a65c4466998dc80f1dc8a5a0b173eae017fb>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.18.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

   .. tab-item:: TensorFlow 2.17.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.12-tf2.17-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.12-tf2.17-dev/images/sha256-b3add80e374a2db2d1088d746e740afa89d439aca02cacba959ad298f5cd2b3f>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.4 <https://www.python.org/downloads/release/python-3124/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.17.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.12-tf2.17-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.12-tf2.17-runtime/images/sha256-3a244f026c32177eff7958ffbad390de85b438b2b48b455cc39f15d70fa1270d>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.12.4 <https://www.python.org/downloads/release/python-3124/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.17.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.10-tf2.17-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.10-tf2.17-dev/images/sha256-e0cecdfacb59169335049983cdab6da578c209bb9f4d08aad97e184ae59171a6>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.17.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

            Tag
              `rocm/tensorflow:rocm6.4.0-py3.10-tf2.17-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4-py3.10-tf2.17-runtime/images/sha256-6f43de12f7eb202791b698ac51d28b72098de90034dbcd48486629b0125f7707>`_

            Inventory
              * `ROCm 6.4.0 <https://repo.radeon.com/rocm/apt/6.4/>`_
              * `Python 3.10.16 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4/tensorflow_rocm-2.17.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

.. _install-tensorflow-wheels:

Using a wheels package
======================

To install TensorFlow using the wheels package, use the following command.

.. code-block:: shell

   pip install --user tensorflow-rocm==[wheel-version] -f [repo] --upgrade

* ``[wheel-version]`` is the :ref:`TensorFlow version <install-tensorflow-versions>`.

* ``[repo]`` is ``https://repo.radeon.com/rocm/manylinux/rocm-rel-X.Y/`` for versions 6.1 and later,
  where ``X.Y`` indicates the :ref:`ROCm version <install-tensorflow-versions>`.

.. note::

   Prior to ROCm 6.1, ``[wheel-version]`` followed the ``<TensorFlowVersion>.<ROCmVersion>`` format.

.. _test-tensorflow-installation:

Testing the TensorFlow installation
===================================

To test the installation of TensorFlow, run the container as specified in
:ref:`Installing TensorFlow <install-tensorflow-options>`. Ensure you have access to the Python
shell in the Docker container.

.. code-block:: shell

    python -c 'import tensorflow' 2> /dev/null && echo ‘Success’ || echo ‘Failure’

Running a basic TensorFlow example
==================================

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
