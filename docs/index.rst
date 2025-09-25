.. meta::
  :description: ROCm installation for Linux
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU

.. _rocm-install-home:

****************************************************************
ROCm installation for Linux
****************************************************************

This section describes the ROCm for Linux installation options.

.. note::

    * If you’re using ROCm with AMD Radeon GPUs or Ryzen APUs for graphics workloads, see the `Use ROCm on Radeon and Ryzen <https://rocm.docs.amd.com/projects/radeon-ryzen/en/latest/index.html>`_ documentation for installation instructions. 
    * The AMDGPU installer documentation has been removed to encourage the use of the package manager for ROCm installation. While the package manager is the recommended method, you can still install ROCm using the AMDGPU installer by following the `legacy process <https://rocm.docs.amd.com/projects/install-on-linux/en/docs-6.4.1/install/install-methods/amdgpu-installer-index.html>`_. Ensure to update the command with the intended ROCm version before running it.


.. grid:: 2
    :gutter: 3

    .. grid-item-card:: Install ROCm
      
       * :doc:`Quick start <install/quick-start>` - recommended for new users
       * :doc:`Detailed install <install/detailed-install>` - includes explanations

    .. grid-item-card:: Install deep learning frameworks

       * :doc:`PyTorch <install/3rd-party/pytorch-install>`
       * :doc:`TensorFlow <install/3rd-party/tensorflow-install>`
       * :doc:`JAX <install/3rd-party/jax-install>`
       * :doc:`verl <install/3rd-party/verl-install>`
       * :doc:`Stanford Megatron-LM <install/3rd-party/stanford-megatron-lm-install>`
       * :doc:`DGL <install/3rd-party/dgl-install>`
       * :doc:`Megablocks <install/3rd-party/megablocks-install>`
       * :doc:`Taichi <install/3rd-party/taichi-install>`
       * :doc:`Ray <install/3rd-party/ray-install>`
       * :doc:`Taichi <install/3rd-party/llama-cpp-install>`


.. grid:: 2
    :gutter: 3

    .. grid-item-card:: How to

        * :doc:`Run Docker containers <how-to/docker>`
        * :doc:`Use Spack <how-to/spack>`

    .. grid-item-card:: Reference

        * :doc:`reference/package-manager-integration`
        * :doc:`reference/system-requirements`
        * :doc:`Troubleshooting <reference/install-faq>`
        * :doc:`reference/user-kernel-space-compat-matrix`
