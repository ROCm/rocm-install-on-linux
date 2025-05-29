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
validated for ROCm 6.4.1.

.. tab-set::

   .. tab-item:: TensorFlow 2.18.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.12-tf2.18-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.12-tf2.18-dev/images/sha256-b91a554a68ec1246c7f5c779c95764be78c5bf3e2fca10ddeecd90c91625d31f>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.18.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.12-tf2.18-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.12-tf2.18-runtime/images/sha256-d14d8c4989e7c9a60f4e72461b9e349de72347c6162dcd6897e6f4f80ffbb440>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.18.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.10-tf2.18-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.10-tf2.18-dev/images/sha256-081e5bd6615a5dc17247ebd2ccc26895c3feeff086720400fa39b477e60a77c0>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.18.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.10-tf2.18-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.10-tf2.18-runtime/images/sha256-bf369637378264f4af6ddad5ca8b8611d3e372ffbea9ab7a06f1e122f0a0867b>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1>`_
              * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.18.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.18.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.18.0 <https://github.com/tensorflow/tensorboard/tree/2.18.0>`_

   .. tab-item:: TensorFlow 2.17.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.12-tf2.17-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.12-tf2.17-dev/images/sha256-5a502008c50d0b6508e6027f911bdff070a7493700ae064bed74e1d22b91ed50>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.17.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.12-tf2.17-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.12-tf2.17-runtime/images/sha256-1ee5dfffceb71ac66617ada33de3a10de0cb74199cc4b82441192e5e92fa2ddf>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.17.1-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.10-tf2.17-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.10-tf2.17-dev/images/sha256-109218ad92bfae83bbd2710475f7502166e1ed54ca0b9748a9cbc3f5a1d75af1>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.17.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.10-tf2.17-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.10-tf2.17-runtime/images/sha256-5d78bd5918d394f92263daa2990e88d695d27200dd90ed83ec64d20c7661c9c1>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.10 <https://www.python.org/downloads/release/python-31016/>`_
              * `tensorflow-rocm 2.17.1 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.17.1-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.17.1 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

   .. tab-item:: TensorFlow 2.16.2

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.12-tf2.16-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.12-tf2.16-dev/images/sha256-b09b1ad921c09c687b7c916141051e9fcf15539a5686e5aa67c689195a522719>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.16.2-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.17.1>`_

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.12-tf2.16-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.12-tf2.16-runtime/images/sha256-20dbd824e85558abfe33fc9283cc547d88cde3c623fe95322743a5082f883a64>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.12 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.16.2-cp312-cp312-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

         .. tab-item:: Ubuntu 22.04

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.10-tf2.16-dev <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.10-tf2.16-dev/images/sha256-36c4fa047c86e2470ac473ec1429aea6d4b8934b90ffeb34d1afab40e7e5b377>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.10 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.16.2-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

            Tag
              `rocm/tensorflow:rocm6.4.1-py3.10-tf2.16-runtime <https://hub.docker.com/layers/rocm/tensorflow/rocm6.4.1-py3.10-tf2.16-runtime/images/sha256-a94150ffb81365234ebfa34e764db5474bc6ab7d141b56495eac349778dafcf3>`_

            Inventory
              * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`_
              * `Python 3.10 <https://www.python.org/downloads/release/python-31210/>`_
              * `tensorflow-rocm 2.16.2 <https://repo.radeon.com/rocm/manylinux/rocm-rel-6.4.1/tensorflow_rocm-2.16.2-cp310-cp310-manylinux_2_28_x86_64.whl>`_
              * `TensorBoard 2.16.2 <https://github.com/tensorflow/tensorboard/tree/2.16.2>`_

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
