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

* :ref:`install-tensorflow-prebuilt-docker` (*recommended*)

  * :ref:`tensorflow-docker-support`

* :ref:`install-tensorflow-wheels`

.. note::

   As of ROCm 6.1, ``tensorflow-rocm`` packages are found at `<https://repo.radeon.com/rocm/manylinux>`__.
   Prior to ROCm 6.1, packages were found at `<https://pypi.org/project/tensorflow-rocm>`_.

.. _install-tensorflow-versions:

.. list-table::
    :header-rows: 1
    :widths: 1, 1

    * - ROCm version
      - TensorFlow version
    * - 6.3.x
      - 2.15.1, 2.16.2, 2.17.0
    * - 6.2.x
      - 2.14.1, 2.15.1, 2.16.1
    * - 6.1.x
      - 2.13.1, 2.14.0, 2.15.0
    * - 6.0.x
      - 2.12.1, 2.13.1, 2.14.0

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
validated for ROCm 6.3.

.. tab-set::

   .. tab-item:: ROCm 6.3.1

      .. tab-set::

         .. tab-item:: TensorFlow 2.17.0

            .. tab-set::

               .. tab-item:: Ubuntu 24.04

                  Tag
                    `rocm/tensorflow:rocm6.3.1-py3.12-tf2.17.0-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3.1-py3.12-tf2.17.0-dev/images/sha256-804121ee4985718277ba7dcec53c57bdade130a1ef42f544b6c48090ad379c17>`_

                  Inventory
                    * `ROCm 6.3.1 <https://repo.radeon.com/rocm/apt/6.3.1/>`_
                    * `Python 3.12 <https://www.python.org/downloads/release/python-3124/>`_
                    * `tensorflow-rocm 2.17.0 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.17.0-cp312-cp312-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/tensorflow:rocm6.3.1-py3.10-tf2.17.0-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3.1-py3.10-tf2.17.0-dev/images/sha256-776837ffa945913f6c466bfe477810a11453d21d5b6afb200be1c36e48fbc08e>`_

                  Inventory
                    * `ROCm 6.3.1 <https://repo.radeon.com/rocm/apt/6.3.1/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31012/>`_
                    * `tensorflow-rocm 2.17.0 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.17.0-cp310-cp310-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.17.0 <https://github.com/tensorflow/tensorboard/tree/2.17.0>`_

         .. tab-item:: TensorFlow 2.16.2

            .. tab-set::

               .. tab-item:: Ubuntu 24.04

                  Tag
                    `rocm/tensorflow:rocm6.3.1-py3.12-tf2.16.2-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3.1-py3.12-tf2.16.2-dev/images/sha256-c793e1483e30809c3c28fc5d7805bedc033c73da224f839fff370717cb100944>`_

                  Inventory
                    * `ROCm 6.3.1 <https://repo.radeon.com/rocm/apt/6.3.1/>`_
                    * `Python 3.12 <https://www.python.org/downloads/release/python-3124/>`_
                    * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.16.2-cp310-cp310-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/tensorflow:rocm6.3.1-py3.10-tf2.16.0-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3.1-py3.10-tf2.16.0-dev/images/sha256-263e78414ae85d7bcd52a025a94131d0a279872a45ed632b9165336dfdcd4443>`_

                  Inventory
                    * `ROCm 6.3.1 <https://repo.radeon.com/rocm/apt/6.3.1/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
                    * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.16.2-cp310-cp310-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

         .. tab-item:: TensorFlow 2.15.1

            .. tab-set::

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/tensorflow:rocm6.3.1-py3.10-tf2.15.0-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3.1-py3.10-tf2.15.0-dev/images/sha256-479046a8477ca701a9494a813ab17e8ab4f6baa54641e65dc8d07629f1e6a880>`_

                  Inventory
                    * `ROCm 6.3.1 <https://repo.radeon.com/rocm/apt/6.3.1/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
                    * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.15.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

   .. tab-item:: ROCm 6.3.0

      .. tab-set::

         .. tab-item:: TensorFlow 2.15.1

            .. tab-set::

               .. tab-item:: Ubuntu 22.04

                  Tag
                    `rocm/tensorflow:6.3_ubuntu22_runtime_py3.10_tf-manylinux_r2.15-rocm-enhanced_f059d40 <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3-py3.10-tf2.15.0-runtime/images/sha256-37e0ab694ac0c65afbf34e32e115122d1c2af37e8095740ac1c951e48faed4e7?context=explore>`_

                  Inventory
                    * `ROCm 6.3.0 <https://repo.radeon.com/rocm/apt/6.3/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
                    * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.15.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

                  |hr|

                  Tag
                    `rocm/tensorflow:6.3_ubuntu22_dev_py3.10_tf-manylinux_r2.15-rocm-enhanced_f059d40 <https://hub.docker.com/layers/rocm/tensorflow/rocm6.3-py3.10-tf2.15.0-dev/images/sha256-f1c633cbcebb9e34660c06bff5aa22dee82a9e2a4919ba923deb32216edce5db?context=explore>`_

                  Inventory
                    * `ROCm 6.3.0 <https://repo.radeon.com/rocm/apt/6.3/>`_
                    * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
                    * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.3/tensorflow_rocm-2.15.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
                    * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

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
