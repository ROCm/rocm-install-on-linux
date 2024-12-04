.. meta::
  :description: Installing TensorFlow for ROCm
  :keywords: installation instructions, TensorFlow, AMD, ROCm

****************************************************************************************
Installing TensorFlow for ROCm
****************************************************************************************

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
validated for ROCm 6.2.

.. tab-set::

   .. tab-item:: ROCm 6.2.1

      .. tab-set::

         .. tab-item:: TensorFlow 2.16.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/tensorflow:rocm6.2.1-py3.9-tf2.16.1-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2.1-py3.9-tf2.16.1-dev/images/sha256-55b5f75180cc8be17d6d5d4fab0f35f2f20d240ca9c4c6828af18cf81bba68c6>`_ (`latest <https://hub.docker.com/layers/rocm/tensorflow/latest/images/sha256-3d5ba86a2cc3b6a4c2e160f6bffc7c5503e14e2fbb8d9712bc70ec8708f72d8c>`_)

                  Inventory
                    * `ROCm 6.2.1 <https://repo.radeon.com/rocm/apt/6.2.1/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `tensorflow-rocm 2.16.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                    * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

         .. tab-item:: TensorFlow 2.15.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/tensorflow:rocm6.2.1-py3.9-tf2.15.1-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2.1-py3.9-tf2.15.1-dev/images/sha256-c2feef869374f8eccfad77d210457160a3019df6b15ffc226c27acddb5d03462>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `tensorflow-rocm 2.15.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                    * `TensorBoard 2.15.2 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

         .. tab-item:: TensorFlow 2.14.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

                  Tag
                    `rocm/tensorflow:rocm6.2.1-py3.9-tf2.14.1-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.2.1-py3.9-tf2.14.1-dev/images/sha256-99f8560aea6d4cd7bc030c0f7e32651abbaf5f118e1aa119288b3eace1421659>`_

                  Inventory
                    * `ROCm 6.2 <https://repo.radeon.com/rocm/apt/6.2/>`_
                    * `Python 3.9 <https://www.python.org/downloads/release/python-3918/>`_
                    * `tensorflow-rocm 2.14.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.2/>`_
                    * `TensorBoard 2.14.1 <https://github.com/tensorflow/tensorboard/tree/2.15.2>`_

   .. tab-item:: ROCm 6.2.0

      .. tab-set::

         .. tab-item:: TensorFlow 2.16.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

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

         .. tab-item:: TensorFlow 2.15.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

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

         .. tab-item:: TensorFlow 2.14.1

            .. tab-set::

               .. tab-item:: Ubuntu 20.04

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
