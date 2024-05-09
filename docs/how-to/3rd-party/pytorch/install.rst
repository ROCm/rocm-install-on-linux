.. meta::
  :description: PyTorch with ROCm
  :keywords: installation instructions, PyTorch, AMD, ROCm

**********************************************************************************
Installing PyTorch for ROCm
**********************************************************************************

`PyTorch <https://pytorch.org/>`_ is an open-source tensor library designed for deep learning. PyTorch on
ROCm provides mixed-precision and large-scale training using our
`MIOpen <https://github.com/ROCmSoftwarePlatform/MIOpen>`_ and
`RCCL <https://github.com/ROCmSoftwarePlatform/rccl>`_ libraries.

Install from pre-built wheels
=============================

PyTorch supports the ROCm platform by providing pre-built wheels packages for a variety of PyTorch and ROCm versions.

.. Warning::

  **Make sure the PyTorch version you install was compiled for your ROCm version!** If there is a mismatch, you may experience
  performace degredation or errors.

The Major and Minor versions must match, but different Patch versions are acceptable. For example, PyTorch 2.2.1+ROCm6.0 will work with ROCm 6.0.1, but not 6.1, or 5.7.

To check your rocm version:

.. code-block:: shell

                $ rocm-smi -V
                ROCM-SMI-LIB version: 5.7.0

Latest Stable
-------------

To install the latest version:

* Navigate to `pytorch.org/get-started/locally/ <https://pytorch.org/get-started/locally/>`_.
* Select ``Stable``, ``Linux``, ``Pip``, ``Python``, and ``ROCm``

  * The ``ROCm`` box will indicate which ROCm version these wheels were built for

You should see a ``pip3 install`` commmand:

.. code-block:: shell

    pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/rocm5.7


.. Note::

   **PyTorch typically only builds the latest stable builds against a single version of ROCm.** If this ROCm version
   does not match your needs, see :ref:`torch-nightly` or :ref:`torch-additional-versions` below.

.. Tip::

   You should use a virtual environment when installing python packages in order to separate dependencies
   from the system and other projects.

.. _torch-nightly:

Nightly
-------

In addition to stable wheels, PyTorch also publishes nightly builds, which *may* be against a newer version of ROCm. Nightly builds can be a great way
to get access to newer features.

To install from nightly:

* Navigate to `pytorch.org/get-started/locally/ <https://pytorch.org/get-started/locally/>`_.
* Select **``Nightly``**, ``Linux``, ``Pip``, ``Python``, and ``ROCm``

.. _torch-additional-versions:

Additional Versions
-------------------

In addition to the latest stable and nightly wheels, you can search for previous versions on `PyTorch's docs here <https://pytorch.org/get-started/previous-versions/>`_

**Make sure to search for the appropriate ROCm version**

Install From Source
===================

If a pre-built wheel is not available to match your specific Python, PyTorch, and ROCm versions,
you can build and install PyTorch from source. See the `official build instructions <https://github.com/pytorch/pytorch#from-source>`_ for details.

Other Package Managers
=======================

You can also use more sophisticated dependency management tools like PDM and Poetry. These tools provide several benefits over ``pip``, including
automatic creation of virtual environments, complex dependency resolution, lockfiles, and more.

`PDM <https://pdm-project.org/latest/>`_
-------------------------------------------

* Add the ``index-url`` from above as a `source <https://pdm-project.org/latest/usage/config/#configure-the-package-indexes>`_ by adding the following lines to your ``pyproject.toml`` file:

  .. code-block::

     [[tool.pdm.source]]
     name = "torch-index"       # You can give this any name
     url = "https://download.pytorch.org/whl/rocm5.7/"

* Add dependencies

  .. code-block:: shell

     pdm add torch ...

PDM will then first look in the proided source to install any package, before falling back to `pypi.org <pypi.org>`_.

`Poetry <https://python-poetry.org/docs/>`_
----------------------------------------------

* Add the ``index-url`` from above as a `source <https://python-poetry.org/docs/dependency-specification/#source-dependencies>`_:

  .. code-block::

     poetry source add torch-index https://download.pytorch.org/whl/rocm5.7

* Add dependencies, and specify the source:

  .. code-block::

     poetry add torch --source torch-index

[Optional] Installing pre-compiled MIOpen kernels
===================================================

PyTorch uses `MIOpen <https://github.com/ROCm/MIOpen>`_ for machine learning
primitives, which are compiled into kernels at runtime. Runtime compilation causes a small warm-up
phase when starting PyTorch, and MIOpen kdb files contain precompiled kernels that can speed up
application warm-up phases.

MIOpen kdb files can be used with ROCm PyTorch wheels. However, the kdb files need to be placed in
a specific location with respect to the PyTorch installation path. A helper script simplifies this task by
taking the ROCm version and GPU architecture as inputs. This works for Ubuntu and CentOS.

.. note::

   Installing pre-compiled MIOpen kernels can speed up warm-up, but will not affect performance after the
   initial warm-up. Additionally, as MIOpen caches kernels, this warm-up cost is only paid once.

To install MIOpen kbd files for pytorch, run:

.. code-block:: shell

                wget https://raw.githubusercontent.com/wiki/ROCmSoftwarePlatform/pytorch/files/install_kdb_files_for_pytorch_wheels.sh

                #Optional; replace 'gfx90a' with your architecture and 5.6 with your preferred ROCm version
                export GFX_ARCH=gfx90a
                export ROCM_VERSION=5.6

                ./install_kdb_files_for_pytorch_wheels.sh

Further reading:

* `MIOpen Docs <https://docs.amd.com/projects/MIOpen/en/latest/>`_
* `MIOpen repo <https://github.com/ROCm/MIOpen>`_
* `Installing pre-compiled MIOpen kernels <https://docs.amd.com/projects/MIOpen/en/latest/cache.html#installing-pre-compiled-kernels>`_
* `Using MIOpen kbd files with PyTorch Wheels <https://github.com/ROCm/pytorch/wiki/Using-MIOpen-kdb-files-with-ROCm-PyTorch-wheels>`_

Testing the PyTorch installation
=================================

You can use PyTorch unit tests to validate your PyTorch installation.

If you want to manually run unit tests to validate your PyTorch installation fully, follow these steps:

1. Import the torch package in Python to test if PyTorch is installed and accessible.

   .. note::

       Do not run the following command in the PyTorch git folder.

   .. code-block:: bash

       python3 -c 'import torch' 2> /dev/null && echo 'Success' || echo 'Failure'

2. Check if the GPU is accessible from PyTorch. In the PyTorch framework, ``torch.cuda`` is a generic way
   to access the GPU. This can only access an AMD GPU if one is available.

   .. code-block:: bash

       python3 -c 'import torch; print(torch.cuda.is_available())'


3. Run unit tests to validate the PyTorch installation fully.

   .. note::

       You must run the following command from the PyTorch home directory.

   .. code-block:: bash

       PYTORCH_TEST_WITH_ROCM=1 python3 test/run_test.py --verbose \
       --include test_nn test_torch test_cuda test_ops \
       test_unary_ufuncs test_binary_ufuncs test_autograd

   This command ensures that the required environment variable is set to skip certain unit tests for
   ROCm. This also applies to wheel installs in a non-controlled environment.

   .. note::

       Make sure your PyTorch source code corresponds to the PyTorch wheel or the installation in the
       Docker image. Incompatible PyTorch source code can give errors when running unit tests.

   Some tests may be skipped, as appropriate, based on your system configuration. ROCm doesn't
   support all PyTorch features; tests that evaluate unsupported features are skipped. Other tests might
   be skipped, depending on the host or GPU memory and the number of available GPUs.

   If the compilation and installation are correct, all tests will pass.

4. Run individual unit tests.

   .. code-block:: bash

       PYTORCH_TEST_WITH_ROCM=1 python3 test/test_nn.py --verbose

   You can replace ``test_nn.py`` with any other test set.

Running a basic PyTorch example
================================

The PyTorch examples repository provides basic examples that exercise the functionality of your
framework.

Two of our favorite testing databases are:

* **MNIST** (Modified National Institute of Standards and Technology): A database of handwritten
  digits that can be used to train a Convolutional Neural Network for **handwriting recognition**.
* **ImageNet**: A database of images that can be used to train a network for
  **visual object recognition**.

MNIST PyTorch example
------------------------

1. Clone the PyTorch examples repository.

   .. code-block:: bash

       git clone https://github.com/pytorch/examples.git

2. Go to the MNIST example folder.

   .. code-block:: bash

       cd examples/mnist

3. Follow the instructions in the ``README.md`` file in this folder to install the requirements. Then run:

   .. code-block:: bash

       python3 main.py

   This generates the following output:

   .. code-block::

       ...
       Train Epoch: 14 [58240/60000 (97%)]     Loss: 0.010128
       Train Epoch: 14 [58880/60000 (98%)]     Loss: 0.001348
       Train Epoch: 14 [59520/60000 (99%)]     Loss: 0.005261

       Test set: Average loss: 0.0252, Accuracy: 9921/10000 (99%)

ImageNet PyTorch example
----------------------------

1. Clone the PyTorch examples repository (if you didn't already do this in the preceding MNIST
   example).

   .. code-block:: bash

       git clone https://github.com/pytorch/examples.git

2. Go to the ImageNet example folder.

   .. code-block:: bash

       cd examples/imagenet

3. Follow the instructions in the ``README.md`` file in this folder to install the Requirements. Then run:

   .. code-block:: bash

       python3 main.py
