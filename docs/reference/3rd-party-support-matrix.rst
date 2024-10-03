.. meta::
  :description: Third-party support matrix
  :keywords: ROCm installation, AMD, ROCm, third-party support matrix

.. _3rd-party-support-matrix:

***************************************************************************
Third-party support matrix
***************************************************************************

ROCm™ supports a variety of third-party libraries and frameworks. The supported versions have been tested so you can be assured that they function as expected. Non-supported third-party versions might work but haven’t been tested.

Deep learning
================================================

ROCm releases support the most recent and two prior releases of PyTorch and TensorFlow.

.. list-table::
    :header-rows: 1

    * - ROCm
      - `PyTorch <https://github.com/pytorch/pytorch/releases/>`_
      - `TensorFlow <https://github.com/tensorflow/tensorflow/releases/>`_

    * - 6.2.x
      - 1.13, 2.0, 2.1, 2.2, 2.3
      - 2.14.1, 2.15.1, 2.16.1

    * - 6.1.x
      - 1.13, 2.0, 2.1
      - 2.13.1, 2.14.0, 2.15.0

    * - 6.0.x
      - 1.13, 2.0, 2.1
      - 2.12.1, 2.13.1, 2.14.0

    * - 5.7.x
      - 1.12.1, 1.13, 2.0, 2.1
      - 2.12, 2.13, 2.14

    * - 5.6.x
      - 1.12.1, 1.13, 2.0, 2.1
      - 2.12, 2.13, 2.14

    * - 5.5.x
      - 1.11, 1.12.1, 1.13, 2.0
      - 2.10, 2.11, 2.12

    * - 5.4.x
      - 1.10.1, 1.11, 1.12.1, 1.13
      - 2.8, 2.9, 2.10, 2.11

    * - 5.3.x
      - 1.10.1, 1.11, 1.12.1, 1.13
      - 2.8, 2.9, 2.10

    * - 5.2.x
      - 1.10, 1.11, 1.12
      - 2.7, 2.8, 2.9

    * - 5.1.3
      - 1.9,  1.10, 1.11
      - 2.7, 2.8, 2.9

    * - 5.0.2
      - 1.8, 1.9, 1.10
      - 2.6, 2.7, 2.8

.. note::

   See the :ref:`Compatibility matrix <rocm:framework-support-compatibility-matrix>` for an overview
   of deep learning framework support across ROCm releases.

.. _communication-libraries:

Communication libraries
================================================

ROCm supports `OpenUCX <https://openucx.org/>`_, an open-source, production-grade
communication framework for data-centric and high performance applications.


.. list-table::
    :header-rows: 1

    * - ROCm version
      - UCX version

    * - >= 6.1.1
      - >= 1.15.0

    * - <= 6.1.0, >= 5.5.0
      - >= 1.14.1

    * - <= 5.4.x
      - >= 1.14.0

The `Unified Collective Communication (UCC) <https://github.com/openucx/ucc>`_ library also has
support for ROCm devices.

.. list-table::
    :header-rows: 1

    * - ROCm version
      - UCC version

    * - >= 6.1.0
      - >= 1.3.0

    * - >= 5.6.0
      - >= 1.2.0

    * - <= 5.5.x
      - >= 1.1.0

.. note::

   See the :ref:`Compatibility matrix <rocm:thirdpartycomms-support-compatibility-matrix>` for an overview
   of support for third-party communication libraries across ROCm releases.

Algorithm libraries
================================================

ROCm releases provide algorithm libraries with interfaces compatible with contemporary
CUDA/NVIDIA HPC SDK alternatives.

* Thrust → rocThrust
* CUB → hipCUB

.. list-table::
    :header-rows: 1

    * - ROCm
      - Thrust / CUB
      - HPC SDK

    * - 6.2.x
      - 2.2.0
      - 22.9
    
    * - 6.1.x
      - 2.1.0
      - 22.9

    * - 6.0.x
      - 2.0.1
      - 22.9

    * - 5.7.x
      - 1.17.2
      - 22.9

    * - 5.6.x
      - 1.17.2
      - 22.9

    * - 5.5.x
      - 1.17
      - 22.9

    * - 5.4.x
      - 1.16
      - 22.9

    * - 5.3.x
      - 1.16
      - 22.7

    * - 5.2.x
      - 1.15
      - 22.2, 22.3

    * - 5.1.3
      - 1.15
      - 22.1

    * - 5.0.2
      - 1.14
      - 21.9

For the latest documentation of these libraries, refer to the ROCm
:doc:`API libraries <rocm:reference/api-libraries>`.

.. note::

   See the :ref:`Compatibility matrix <rocm:thirdpartyalgorithm-support-compatibility-matrix>` for an overview
   of algorithm library support across ROCm releases.
