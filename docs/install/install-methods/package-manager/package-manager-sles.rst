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

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `SUSE Linux Enterprise Server native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/detailed-install/package-manager/package-manager-sles.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper --gpg-auto-import-keys install rocm

Complete the :doc:`../../post-install`.

.. note::

    For information about the AMDGPU driver installation, see the `Install AMDGPU driver <https://instinct.docs.amd.com/projects/amdgpu-docs/en/latest/install/package-manager-index.html>`_ in the AMD Instinct Data Center GPU Documentation.

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

    sudo zypper remove rocm

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

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

