.. meta::
  :description: Answers to frequently asked questions about installing ROCm on the Linux platform
  :keywords: Linux, install, FAQ, answers, Ubuntu, RHEL, SUSE, AMD, ROCm

************************************************************************************
Frequently asked questions
************************************************************************************

This document provides answers to common installation and ROCm questions.
For troubleshooting tips and suggestions, see the :doc:`install-faq` guide.

.. _faq-install-options:

Installation options
======================

**Is it possible to install multiple ROCm and AMDGPU use cases at the same time using the installer script?**

Yes. Provide the use case names using the ``--usecase`` parameter. Separate each option with a comma,
as shown in this example:

.. code-block:: shell

   sudo amdgpu-install --usecase=hiplibsdk,rocm 

**Is it possible to list the valid options for the --usecase parameter in the amdgpu-install script?**

To list all the ``–-usecase`` options, use this command:

.. code-block:: shell

   amdgpu-install --list-usecase

**What other options are available in the amdgpu-install script?**

The ``--help`` parameter lists all available options for the ``amdgpu-install`` script. Run
the command that follows to see the application help. For more details about the AMDGPU installer,
see :doc:`../install/amdgpu-install`.

.. code-block:: shell

   sudo amdgpu-install --help

**Can a single-version ROCm package be installed alongside a multiversion packages?**

Installing single-version and multiversion ROCm packages together on the same machine is not supported. 
The conflicting package versions can result in unpredictable behavior. For more information on
multiversion installation and a comparison between single-version and multiversion install,
see :doc:`../install/native-install/multi-version-install`.

**Which GPUs and AMD Instinct accelerators does ROCm support?**

For a list of the supported GPUs and accelerators, see :doc:`system-requirements`.

.. _faq-install-verification:

Installation verification
=========================

**How can the kernel module installation be verified?**

To verify the kernel installation, use this command:

.. code-block:: shell

   sudo dkms status

If the installation of the kernel module was successful, the command displays the output
in the following format:

.. code-block:: shell

   amdgpu, 4.3-52.el7, 3.10.0-1160.11.1.el7.x86_64, x86_64: installed (original_module exists)

**What are the next steps to take if the AMDGPU driver is not loaded after ROCm installation?**

Ensure that the AMDGPU driver is not on a denylist such as
``/etc/modprobe.d/blacklist-amdgpu.conf`` or a similar file. To verify whether it is on a denylist,
use the following command:

.. code-block:: shell

   grep amdgpu /etc/modprobe.d/*

.. _faq-application-options:

Application options and support
===============================

**Is membership in the video or rende` group mandatory?**

Yes, you must be part of the ``video`` or ``render`` group to access the AMD GPU or accelerator.
To add a user to these groups, use this command:

.. code-block:: shell

   sudo usermod -a -G render,video $LOGNAME # Add the current user to the render and video groups

**Which kernels does ROCm support?**

For a list of supported kernels that have been tested and validated, see :doc:`user-kernel-space-compat-matrix`.

**Does ROCm support upgrades?**

Yes, ROCm can be upgraded. To upgrade ROCm, use the install script.
For more information, see :ref:`amdgpu-install-installation`.

**Does ROCm support applications that use a GUI?**

Yes, ROCm supports GUI-based applications.

.. _faq-platform-support:

Platform support
=========================

**Does ROCm support non-LTS OS versions?**

No, ROCm does not support non-LTS versions. 

**Is ROCm supported on MacOS?**

No, MacOS does not support ROCm.

**What Linux distributions does ROCm support?**

ROCm currently supports Ubuntu, Red Hat Enterprise Linux (RHEL),
and SUSE Linux Enterprise Server (SLES). For a full list of supported distributions and versions,
see :ref:`supported_distributions`.

.. _faq-application-testing:

Application testing
=========================

**Is there any utility for stress testing?**

The AMD ROCm team recommends using the :doc:`ROCm Validation Suite<rocmvalidationsuite:index>` (RVS) for stress tests. To use
RVS, follow these steps:

#. To install the ROCm Validation Suite, use the relevant command for your Linux distribution:

   .. tab-set::

       .. tab-item:: Ubuntu

           .. code-block:: bash

               sudo apt-get install rocm-validation-suite

       .. tab-item:: Red Hat Enterprise Linux

           .. code-block:: bash

               sudo yum install rocm-validation-suite

       .. tab-item:: SUSE Linux Enterprise Server

           .. code-block:: bash

               sudo zypper install rocm-validation-suite

#. To run the script, use the following commands:

   .. code-block:: shell

      cd /opt/rocm/share/rocm-validation-suite/testscripts
      sudo ./rvs-stress-long.sh
