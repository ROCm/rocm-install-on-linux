.. meta::
  :description: Third-party support matrix
  :keywords: ROCm installation, AMD, ROCm, third-party support matrix

.. _3rd-party-support-matrix:

***************************************************************************
Third-party support matrix
***************************************************************************

ROCm™ supports various third-party libraries and frameworks. We've tested our supported versions, so
you can be assured that they work. Non-supported third-party versions may also work, but we haven't
tested these for functionality.

Deep learning
================================================

ROCm releases support the most recent and two prior releases of PyTorch and
TensorFlow.

.. list-table::
    :header-rows: 1

    * - ROCm
      - `Pytorch <https://github.com/pytorch/pytorch/releases/>`_
      - `TensorFlow <https://github.com/tensorflow/tensorflow/releases/>`_

    * - 5.0.2
      - 1.8, 1.9, 1.10
      - 2.6, 2.7, 2.8

    * - 5.1.3
      - 1.9,  1.10, 1.11
      - 2.7, 2.8, 2.9

    * - 5.2.x
      - 1.10, 1.11, 1.12
      - 2.8, 2.9, 2.9

    * - 5.3.x
      - 1.10.1, 1.11, 1.12.1, 1.13
      - 2.8, 2.9, 2.10

    * - 5.4.x
      - 1.10.1, 1.11, 1.12.1, 1.13
      - 2.8, 2.9, 2.10, 2.11

    * - 5.5.x
      - 1.10.1, 1.11, 1.12.1, 1.13
      - 2.10, 2.11, 2.13

    * - 5.6.x
      - 1.12.1, 1.13, 2.0
      - 2.12, 2.1

    * - 5.7.x
      - 1.12.1, 1.13, 2.0
      - 2.12, 2.13

    * - 6.0.x
      - 1.13, 2.0, 2.1
      - 2.12, 2.13, 2.14

.. _communication-libraries:

Communication libraries
================================================

ROCm supports `OpenUCX <https://openucx.org/>`_, an open-source, production-grade
communication framework for data-centric and high performance applications.


.. list-table::
    :header-rows: 1

    * - UCX version
      - ROCm 5.4 and older
      - ROCm 5.5 and newer

    * - -1.14.0
      - COMPATIBLE
      - INCOMPATIBLE

    * - 1.14.1+
      - COMPATIBLE
      - COMPATIBLE

The `Unified Collective Communication (UCC) <https://github.com/openucx/ucc>`_ library also has
support for ROCm devices.

.. list-table::
    :header-rows: 1

    * - UCC version
      - ROCm 5.5 and older
      - ROCm 5.6 and newer

    * - -1.1.0
      - COMPATIBLE
      - INCOMPATIBLE

    * - 1.2.0+
      - COMPATIBLE
      - COMPATIBLE

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

    * - 5.0.2
      - 1.14
      - 21.9

    * - 5.1.3
      - 1.15
      - 22.1

    * - 5.2.x
      - 1.15
      - 22.2, 22.3

    * - 5.3.x
      - 1.16
      - 22.7

    * - 5.4.x
      - 1.16
      - 22.9

    * - 5.5.x
      - 1.17
      - 22.9

    * - 5.6.x
      - 1.17.2
      - 22.9

    * - 5.7.x
      - 1.17.2
      - 22.9

    * - 6.0.x
      - 2.0.1
      - 22.9

For the latest documentation of these libraries, refer to the
`ROCm API libraries <https://rocm.docs.amd.com/en/latest/reference/library-index.html>`_.
