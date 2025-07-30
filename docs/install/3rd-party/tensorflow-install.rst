.. meta::
  :description: Installing TensorFlow for ROCm
  :keywords: installation instructions, TensorFlow, AMD, ROCm

******************
TensorFlow on ROCm
******************

`TensorFlow <https://tensorflow.org>`__ is an open-source library for solving machine learning,
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

       docker run -it 
           --network=host \
           --device=/dev/kfd \
           --device=/dev/dri \
           --ipc=host \
           --shm-size 16G \
           --group-add video \
           --cap-add=SYS_PTRACE \
           --security-opt seccomp=unconfined \
           rocm/tensorflow:latest

.. |hr| raw:: html

   <hr>

.. _tensorflow-docker-support:

Docker image support
--------------------

AMD validates and publishes ready-made TensorFlow images with ROCm backends on
Docker Hub. The following Docker image tags and associated inventories are
validated for ROCm 6.4.2.

.. tab-set::

   .. tab-item:: TensorFlow 2.18.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.2-py3.12-tf2.18-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.2-py3.12-tf2.18-dev/images/sha256-96754ce2d30f729e19b497279915b5212ba33d5e408e7e5dd3f2304d87e3441e>`__

            Inventory
              * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`__
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.2/tensorflow_rocm-2.18.1-cp312-cp312-manylinux_2_28_x86_64.whl>`__
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`__

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.2-py3.10-tf2.18-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.2-py3.10-tf2.18-dev/images/sha256-fa741508d383858e86985a9efac85174529127408102558ae2e3a4ac894eea1e>`_

            Inventory
              * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__
              * `Python 3.10 <https://www.python.org/downloads/release/python-31017/>`__
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.2/tensorflow_rocm-2.18.1-cp310-cp310-manylinux_2_28_x86_64.whl>`__
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`__

   .. tab-item:: TensorFlow 2.17.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.2-py3.12-tf2.17-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.2-py3.12-tf2.17-dev/images/sha256-3a0aef09f2a8833c2b64b85874dd9449ffc2ad257351857338ff5b706c03a418>`_

            Inventory
              * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`__
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.2/tensorflow_rocm-2.17.1-cp312-cp312-manylinux_2_28_x86_64.whl>`__
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`__

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.2-py3.10-tf2.17-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.2-py3.10-tf2.17-dev/images/sha256-bc7341a41ebe7ab261aa100732874507c452421ef733e408ac4f05ed453b0bc5>`_

            Inventory
              * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__
              * `Python 3.10 <https://www.python.org/downloads/release/python-31017/>`__
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.2/tensorflow_rocm-2.17.1-cp310-cp310-manylinux_2_28_x86_64.whl>`__
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`__

   .. tab-item:: TensorFlow 2.16.2

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.2-py3.12-tf2.16-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.2-py3.12-tf2.16-dev/images/sha256-4841a8df7c340dab79bf9362dad687797649a00d594e0832eb83ea6880a40d3b>`_

            Inventory
              * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`__
              * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.2/tensorflow_rocm-2.16.2-cp312-cp312-manylinux_2_28_x86_64.whl>`__
              * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`__

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.2-py3.10-tf2.16-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.2-py3.10-tf2.16-dev/images/sha256-883fa95aba960c58a3e46fceaa18f03ede2c7df89b8e9fd603ab2d47e0852897>`_

            Inventory
              * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__
              * `Python 3.10 <https://www.python.org/downloads/release/python-31017/>`__
              * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.2/tensorflow_rocm-2.16.2-cp310-cp310-manylinux_2_28_x86_64.whl>`__
              * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`__

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
