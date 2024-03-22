.. meta::
  :description: ROCm installation for Linux
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU

.. _rocm-install-home:

****************************************************************
ROCm installation for Linux
****************************************************************

If you're new to ROCm, we recommend using the :ref:`rocm-install-quick`. If you want more
complete instructions, refer to the following sections.

.. grid:: 2
    :gutter: 1

    .. grid-item-card:: Quick-start
        :link: tutorial/quick-start
        :link-type: doc

        ROCm quick-start installation guide.

    .. grid-item-card:: Prerequisites
        :link: how-to/prerequisites
        :link-type: doc

        Steps required before installation.

    .. grid-item-card:: Install overview
        :link: tutorial/install-overview
        :link-type: doc

        * Package manager vs AMDGPU installer
        * Single-version vs multi-version

Choose your install method
========================================

.. grid:: 2
    :gutter: 1

    .. grid-item-card:: Package manager
        :link: how-to/native-install/index
        :link-type: doc

        Directly use your distribution's package manager to install ROCm.

    .. grid-item-card:: AMDGPU installer
        :link: how-to/amdgpu-install
        :link-type: doc

        Use an installer tool that orchestrates changes via the package manager.

Additional resources
========================================

.. grid:: 2
    :gutter: 1

    .. grid-item-card:: Reference

        * :doc:`reference/system-requirements`
        * :doc:`reference/docker-image-support-matrix`
        * :doc:`reference/3rd-party-support-matrix`

    .. grid-item-card:: Tutorials

        * :doc:`how-to/3rd-party/magma-install`
        * :doc:`how-to/3rd-party/pytorch-install`
        * :doc:`how-to/3rd-party/tensorflow-install`

    .. grid-item-card:: How to

        * :doc:`Run Docker containers <how-to/docker>`
        * :doc:`Use Spack <how-to/spack>`
