.. meta::
  :description: SUSE Enterprise Linux native installation
  :keywords: ROCm install, installation instructions, SUSE, SUSE Linux Enterprise native installation,
    AMD, ROCm

*********************************************************************************************
SUSE Linux Enterprise native installation
*********************************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. Note::

    The following installation steps also apply when upgrading from a previous ROCm version.

.. _sles-register-repo:

Registering ROCm repositories
===============================================

.. code-block:: bash
    :substitutions:

    sudo tee /etc/zypp/repos.d/rocm.repo <<EOF
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

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install rocm

.. include:: ../includes/meta-package-table.rst

.. _sles-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. _sles-package-manager-uninstall:

Uninstalling
================================================

Uninstall ROCm meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo zypper remove rocm
    sudo zypper remove rocm-core amdgpu-core

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

.. note::

    For information about the AMDGPU driver installation, see the `SUSE Linux Enterprise native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-sles.html>`_ in the AMD Instinct Data Center GPU Documentation.