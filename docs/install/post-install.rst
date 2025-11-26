.. meta::
  :description: Post-installation instructions
  :keywords: ROCm install, installation instructions, AMD, ROCm

*************************************************************************
Post-installation instructions
*************************************************************************

After installing ROCm, follow these steps to finalize and validate the installation.

Environment Configuration
=====================================================

1. Configure ROCm shared objects
-----------------------------------------------------

Configure the system linker by specifying where to find the shared objects (``.so`` files) for ROCm applications.

.. code-block:: bash

   sudo tee --append /etc/ld.so.conf.d/rocm.conf <<EOF
   /opt/rocm/lib
   /opt/rocm/lib64
   EOF
   sudo ldconfig

.. _config_rocm_path:

2. Configure ROCm ``PATH``
-----------------------------------------------------

Configure the path to the ROCm binary using one of the following Linux utilities or manually update the ``PATH`` variable. 
The ROCm installation process adds the ROCm executables to these systems, provided they are installed on the system.

**Option A:**  ``update-alternatives``

The ``update-alternatives`` utility is available on most Linux distributions. It helps 
manage multiple versions of a command or program.
For more information about ``update-alternatives``, see 
`Linux man <https://man7.org/linux/man-pages/man1/update-alternatives.1.html>`_.

To use ``update-alternatives``, follow these steps:

#. Display a list of all ROCm versions available:

   .. code-block:: bash

      sudo update-alternatives --display rocm

#. If multiple ROCm versions are installed, switch between them using this command and selecting the ROCm version:

   .. code-block:: bash

      sudo update-alternatives --config rocm

**Option B:**  ``environment-modules``

The ``environment-modules`` tool simplifies shell initialization. It lets you modify 
your session environment using module files. For more information, see 
`Environment Modules <https://modules.readthedocs.io/en/latest/>`_.

.. note::

   The ``environment-modules`` package should be installed on the system before ROCm can be configured using modules. For more information, see :ref:`prerequisites <additional_dev_packages>`.

To use ``environment-modules``, follow these instructions:

#. Enable ``environment-modules``:

   .. code-block:: bash

      source /etc/profile.d/modules.sh

#. Display a list of all available modules (including ROCm modules):

   .. code-block:: bash

      module avail

#. Display a list of all currently loaded modules:

   .. code-block:: bash

      module list

#. If multiple ROCm versions are installed, and no other ROCm modules are currently loaded, set ROCm by version:

   .. code-block:: bash
      :substitutions:

      module load rocm/|rocm_directory_version|

#. If multiple ROCm versions are installed with a current ROCm module in use, switch to another ROCm version as follows:

   .. code-block:: bash
      :substitutions:

      module switch rocm/|rocm_directory_version|

.. note::

   If modules are used for ROCm, any ``update-alternatives`` ROCm setting will be overwritten for the terminal session.

**Option C:**  ``PATH``

If ``update-alternatives`` or ``environment-modules`` are not available on the system, configure the ROCm path by setting the ``PATH`` variable to ``/opt/rocm-<version>/bin``.

.. code-block:: bash
   :substitutions:

   export PATH=$PATH:/opt/rocm-|rocm_directory_version|/bin

3. Configure ``LD_LIBRARY_PATH``
-----------------------------------------------------

.. important::

   This step is required for version-specific or :doc:`multi-version installations <./install-methods/multi-version-install-index>`. 

.. code-block:: shell
   :substitutions:

   export LD_LIBRARY_PATH=/opt/rocm-|rocm_directory_version|/lib

Install verification
=====================================================

Once ROCm has been configured, validate the installation.

1. Verify the package installation
-----------------------------------------------------

Use the package manager to validate the list of ROCm component packages installed on the system. 
If package installation was successful, the list will contain ``rocm*`` and ``hip*`` packages currently installed on the system.

.. tab-set::

   .. tab-item:: Ubuntu
      :sync: ubuntu-tab

      .. code-block:: bash

         apt list --installed

   .. tab-item:: Debian
      :sync: debian-tab

      .. code-block:: bash

         apt list --installed

   .. tab-item:: RHEL
      :sync: rhel-tab

      .. code-block:: bash

         dnf list installed
   
   .. tab-item:: OL
      :sync: ol-tab

      .. code-block:: bash

         dnf list installed

   .. tab-item:: Rocky
      :sync: rl-tab

      .. code-block:: bash

         dnf list installed

   .. tab-item:: SLES
      :sync: sle-tab

      .. code-block:: bash

         zypper search --installed-only

2. Verify the ROCm installation
-----------------------------------------------------

Use the following ROCm tools to verify that installation was successful:

.. tab-set::

   .. tab-item:: rocminfo

      .. code-block:: bash

         rocminfo | grep -i "Marketing Name:"

      **Example output:**

      .. code-block:: bash

            Marketing Name:          AMD EPYC 9654 96-Core Processor    
            Marketing Name:          AMD EPYC 9654 96-Core Processor    
            Marketing Name:          AMD Instinct MI300X

   .. tab-item:: clinfo

      .. code-block:: bash

         clinfo | grep -i "Board name:"

      **Example output:**

      .. code-block:: bash

            Board name:                                    AMD Instinct MI300X

   .. tab-item:: amd-smi

      .. code-block:: bash

          amd-smi version

      **Example output:**

      .. code-block:: bash

          AMDSMI Tool: 26.2.0+021c61fc | AMDSMI Library version: 26.2.0 | ROCm version: 7.1.1 | amdgpu version: 6.16.6 | amd_hsmp version: N/A

Troubleshooting
=====================================================

#. **What if environment-modules is not installed before installing ROCm?**

   You can still install ``environment-modules`` package after installing ROCm. However, no ROCm modules will be listed for the ``module avail`` command.
   As an alternative to the standard method of loading the ROCm modules, you can load each version-specific module directly from the ``/opt/rocm-<version>`` directory:

   .. code-block:: bash
      :substitutions:

      module load /opt/rocm-|rocm_directory_version|/lib/rocmmod

#. **Will the ROCm path configuration persist once I set it?**

   - If you are using update-alternatives to configure ROCm, then yes, the currently set configuration will persist even after a system reboot.

   - If you are using environment-modules to configure ROCm, then no, the current set configuration will only last for the current terminal session.
