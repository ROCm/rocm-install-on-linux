.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions

.. _multi-version_install:

*********************************
Installing multiple ROCm versions
*********************************

A multi-version ROCm installation covers situations where you need multiple
versions of ROCm on the same machine--for compatibility with different
applications and hardware, testing, and other use cases.

.. _installation-types:

A multi-version ROCm installation involves the following:

* Installing multiple instances of the ROCm stack on a system.

* Using versioned ROCm meta-packages. ROCm packages are versioned with both
  a ROCm release version and package-specific semantic versioning. Extending a
  package name and its dependencies with the release version adds the ability to
  support multiple versions of packages simultaneously.

A single-version ROCm installation involves the following.

* Installing a single instance of the ROCm release on a system.

* Using non-versioned ROCm meta-packages.

See :doc:`../../install/quick-start` or :doc:`../../install/detailed-install` for
a standard single-version installation.

.. caution::

   You cannot install single-version and multi-version ROCm packages together on the same machine.
   The conflicting package versions might result in unpredictable behavior.

The following illustrations shows the difference between single-version and
multi-version ROCm installations.

.. image:: /data/install/linux/linux001.png
    :alt: ROCm Installation Types

Select the install and uninstall instructions for your operating system

.. grid:: 2
    :gutter: 3

    .. grid-item-card:: Install

        * :doc:`Ubuntu <./multi-version-install/multi-version-install-ubuntu>`
        * :doc:`Debian <./multi-version-install/multi-version-install-debian>`
        * :doc:`Red Hat Enterprise Linux <./multi-version-install/multi-version-install-rhel>`
        * :doc:`Oracle Linux <./multi-version-install/multi-version-install-ol>`
        * :doc:`SUSE Linux Enterprise Server <./multi-version-install/multi-version-install-sles>`
        * :doc:`Azure Linux <./multi-version-install/multi-version-install-azl>`

    .. grid-item-card:: Uninstall

        * :ref:`Ubuntu <ubuntu-multi-uninstall>`
        * :ref:`Debian <debian-multi-uninstall>`
        * :ref:`Red Hat Enterprise Linux <rhel-multi-uninstall>`
        * :ref:`Oracle Linux <ol-multi-uninstall>`
        * :ref:`SUSE Linux Enterprise Server <sles-multi-uninstall>`
        * :ref:`Azure Linux <azl-multi-uninstall>`


See also: :doc:`/reference/system-requirements`. If you encounter install issues, you can refer to the
:doc:`troubleshooting </reference/install-faq>` page.