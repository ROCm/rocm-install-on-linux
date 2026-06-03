.. meta::
  :description: Install multiple ROCm versions
  :keywords: installation instructions, AMD, ROCm, multiple versions, Debian

.. _debian-multi-version_install:

*********************************
Debian multi-version installation
*********************************

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met.


.. _debian-multi-register-rocm:

Registering ROCm repositories
=================================================

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

Register packages
---------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in config.html_context['debian_version_numbers'] %}
        .. tab-item:: Debian {{ os_version }}
            :sync: debian-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                # Note: There is NO trailing .0 in the patch version for repositories
                for ver in |rocm_multi_versions_new|; do
                sudo tee --append /etc/apt/sources.list.d/rocm.list << EOF
                deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/$ver {{ os_release }} main
                EOF
                done

                sudo tee /etc/apt/preferences.d/rocm-pin-600 << EOF
                Package: *
                Pin: release o=repo.radeon.com
                Pin-Priority: 600
                EOF
                sudo apt update
        {% endfor %}

.. _debian-multi-install:

Installing
=================================================

Install kernel driver
--------------------------------------------------------------------------

For information about the AMDGPU driver installation, see the `Debian native installation <https://instinct.docs.amd.com/projects/amdgpu-docs/en/docs-|amdgpu_version|/install/detailed-install/package-manager/package-manager-debian.html>`_ in the AMD Instinct Data Center GPU Documentation.

For information about driver compatibility, see :doc:`../../../reference/user-kernel-space-compat-matrix`.

Install ROCm
--------------------------------------------------------------------------

Before proceeding with a multi-version ROCm installation, you must remove
ROCm packages that were previously installed from a single-version
installation to avoid conflicts.

.. code-block:: bash
    :substitutions:

    # Note: There IS a trailing .0 in the patch version for packages
    for ver in |rocm_multi_versions_package_versions_new|; do
        sudo apt install rocm$ver
    done

.. note::

    For versions earlier than ROCm 6.0.0, use ``rocm-hip-sdk`` instead of ``rocm`` (for example, ``rocm-hip-sdk5.7.1``).

.. _debian-multi-post-install:

Post-installation
=====================================================

Complete the :doc:`../../post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on Debian,
   follow the steps in :doc:`../package-manager/package-manager-debian` in the ROCm documentation.

.. _debian-multi-uninstall:

Uninstalling
================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # Note: There IS a trailing .0 in the patch version for packages
    for ver in |rocm_multi_versions_package_versions_new|; do
        sudo apt autoremove rocm$ver
    done

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # Note: There IS a trailing .0 in the patch version for packages
    for ver in |rocm_multi_versions_package_versions_new|; do
        sudo apt autoremove rocm-core$ver
    done

Remove ROCm repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove ROCm repositories
    sudo rm /etc/apt/sources.list.d/rocm.list

    # Clear the cache and clean the system
    sudo rm -rf /var/cache/apt/*
    sudo apt clean all
    sudo apt update

.. Important::

    To apply all settings, reboot your system.
