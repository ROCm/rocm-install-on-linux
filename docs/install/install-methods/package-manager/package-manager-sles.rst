.. meta::
  :description: SUSE Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, SUSE, SUSE Linux Enterprise native installation,
    AMD, ROCm

*********************************************************************************************
SUSE Linux Enterprise native installation
*********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. _sles-register-repo:

Registering ROCm repositories
===============================================

.. _sles-register-rocm:

Register ROCm packages
--------------------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo tee --append /etc/zypp/repos.d/rocm.repo <<EOF
    [ROCm-|rocm_version|]
    name=ROCm|rocm_version|
    baseurl=https://repo.radeon.com/rocm/zyp/|rocm_version|/main
    enabled=1
    gpgcheck=1
    gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
    EOF

    sudo zypper refresh


.. _sles-install:

Installing
===============================================


Install ROCm packages
--------------------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install rocm

Complete the :doc:`../../post-install`.

.. note::

    For information about the AMDGPU driver installation, see the `Install AMDGPU driver <https://advanced-micro-devices-dcgpu-documentation--16.com.readthedocs.build/projects/amdgpu-docs/en/16/install/package-manager-index.html>`_ in the AMD Instinct Data Center GPU Documentation.

.. _sles-upgrade:

Upgrading
================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`sles-register-rocm` and :ref:`sles-install`.

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _sles-package-manager-uninstall:

Uninstalling
================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # sudo zypper remove <package-name>
    # For example:
    sudo zypper remove rocm
    # Or, for version specific packages:
    sudo zypper remove rocm|rocm_version|

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo zypper remove rocm-core
    # Or for version specific packages:
    sudo zypper remove rocm-core|rocm_version|

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # Remove the repositories
    sudo zypper removerepo "ROCm-|rocm_version|"
    
    # Clear cache and clean system
    sudo zypper clean --all
    sudo zypper refresh
    
    # Restart the system
    sudo reboot

