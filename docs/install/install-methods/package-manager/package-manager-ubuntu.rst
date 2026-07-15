.. meta::
  :description: Ubuntu native installation
  :keywords: ROCm install, installation instructions, Ubuntu, Ubuntu native installation, AMD, ROCm

.. raw:: html

   <meta http-equiv="refresh" content="0; url=https://rocm.docs.amd.com/en/latest/install/rocm.html">

$$$$$$$$$$$$$$
Redirecting...
$$$$$$$$$$$$$$

.. important::

   This page has moved! Go to `<https://rocm.docs.amd.com/en/latest/install/rocm.html>`__ for the latest instructions on installing ROCm.

****************************************************************************
Ubuntu native installation
****************************************************************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.

.. Note::

    The following installation steps also apply when upgrading from a previous ROCm version.

.. _ubuntu-register-repo:

Registering ROCm repositories
=================================================

.. _ubuntu-package-key:

Package signing key
---------------------------------------------------------------------------

Download and convert the package signing key.

.. code-block:: bash

    # Make the directory if it doesn't exist yet.
    # This location is recommended by the distribution maintainers.
    sudo mkdir --parents --mode=0755 /etc/apt/keyrings

    # Download the key, convert the signing-key to a full
    # keyring required by apt and store in the keyring directory
    wget https://repo.radeon.com/rocm/rocm.gpg.key -O - | \
        gpg --dearmor | sudo tee /etc/apt/keyrings/rocm.gpg > /dev/null

.. note::

    The GPG key may change; ensure it is updated when installing a new release.
    If the key signature verification fails while updating,
    re-add the key from the ROCm to the apt repository as mentioned above.

.. _ubuntu-register-rocm:

Register packages
---------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
        .. tab-item:: Ubuntu {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                sudo tee /etc/apt/sources.list.d/rocm.list << EOF
                deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/|rocm_version| {{ os_release }} main
                deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/graphics/|rocm_version|/ubuntu {{ os_release }} main
                EOF

                sudo tee /etc/apt/preferences.d/rocm-pin-600 << EOF
                Package: *
                Pin: release o=repo.radeon.com
                Pin-Priority: 600
                EOF

                sudo apt update

        {% endfor %}

.. _ubuntu-install:

Installing
================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Ubuntu native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-30.30.4/install/detailed-install/package-manager/package-manager-ubuntu.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

.. code-block:: bash

    sudo apt install rocm

.. include:: ../includes/meta-package-table.rst

.. _ubuntu-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. _ubuntu-package-manager-uninstall:

Uninstalling
================================================

Uninstall ROCm meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo apt autoremove rocm
    sudo apt autoremove rocm-core

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories
    sudo rm /etc/apt/sources.list.d/rocm.list

    # Clear the cache and clean the system
    sudo rm -rf /var/cache/apt/*
    sudo apt clean all
    sudo apt update

.. Important::

    To apply all settings, reboot your system.
