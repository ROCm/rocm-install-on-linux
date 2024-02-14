Uninstall
=====================================================

Uninstall specific meta packages
----------------------------------------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # sudo apt autoremove <package-name>
    # For example:
    sudo yum remove rocm
    # Or for version specific packages:
    sudo yum remove rocm|rocm_version|

Uninstall ROCm packages
----------------------------------------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo yum remove rocm-core
    # Or for version specific packages:
    sudo yum remove rocm-core|rocm_version|

Uninstall kernel-mode driver
----------------------------------------------------------------------------------------------------------

.. code-block:: bash

    sudo yum remove  amdgpu-dkms

Remove ROCm and AMDGPU repositories
----------------------------------------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories.
    sudo rm /etc/yum.repos.d/rocm.list
    sudo rm /etc/yum.repos.d/amdgpu.list

    # Clear the cache and clean the system.
    sudo rm -rf /var/cache/yum
    sudo yum clean all

    # Restart the system.
    sudo reboot
