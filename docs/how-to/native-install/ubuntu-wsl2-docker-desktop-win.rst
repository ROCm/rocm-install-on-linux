.. meta::
  :description: Ubuntu (WSL2 / Docker for Windows) installation
  :keywords: ROCm install, installation instructions, Ubuntu,
             Ubuntu (WSL2 / Docker for Windows) installation, AMD, ROCm, WSL,
             Docker, Docker Desktop for Windows

****************************************************************************
Ubuntu (WSL2 / Docker for Windows) installation
****************************************************************************

.. _ubuntu-wsl2-docker-desktop-win-register-repo:

Registering repositories
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

.. _ubuntu-wsl2-docker-desktop-win-register-driver:

.. note::
    The GPG key may change; ensure it is updated when installing a new release.
    If the key signature verification fails while updating,
    re-add the key from the ROCm to the apt repository as mentioned above.
    The current ``rocm.gpg.key`` is not available in a standard key ring distribution
    but has the following SHA1 sum hash:
    ``73f5d8100de6048aa38a8b84cd9a87f05177d208 rocm.gpg.key``

Register ROCm packages
---------------------------------------------------------------------------

Add the ROCm repository.

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in config.html_context['ubuntu_wsl2_docker_desktop_win_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: ubuntu-wsl2-docker-desktop-win-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/|rocm_version| {{ os_release }} main" \
                    | sudo tee --append /etc/apt/sources.list.d/rocm.list
                echo -e 'Package: *\nPin: release o=repo.radeon.com\nPin-Priority: 600' \
                    | sudo tee /etc/apt/preferences.d/rocm-pin-600
        {% endfor %}

.. _ubuntu-wsl2-docker-desktop-win-install:

Installing
================================================

Install override packages
---------------------------------------------------------------------------

Linux Docker containers running on Windows do not make use of ``amdgpu-dkms``,
but instead use an alternative user-space ROCm Runtime (ROCr) relaying to the
host driver.

The following packages override the native packages.

.. code-block:: bash

    sudo apt install hsa-runtime-rocr4wsl-amdgpu rocminfo4wsl-amdgpu
    sudo reboot

Install ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash

    sudo apt install rocm

Complete the :doc:`post-install`.

.. _ubuntu-wsl2-docker-desktop-win-upgrade:

Upgrading
================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`ubuntu-register-repo` and :ref:`ubuntu-install`. 

.. note::

    Upgrading the kernel driver may also upgrade the GPU firmware, which requires a
    system reboot to take effect.

.. _ubuntu-wsl2-docker-desktop-win-uninstall:

Uninstalling
================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # sudo apt autoremove <package-name>
    # For example:
    sudo apt autoremove rocm
    # Or for version specific packages:
    sudo apt autoremove rocm|rocm_version|

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo apt autoremove rocm-core
    # Or for version specific packages:
    sudo apt autoremove rocm-core|rocm_version|

Uninstall override packages
---------------------------------------------------------------------------

Although WSL2 and Docker Desktop for Windows installs don't need to uninstall
the DKMS driver, the override packages were manually installed and won't be
removed by uninstalling ``rocm-core``.

.. code-block:: bash

    sudo apt autoremove hsa-runtime-rocr4wsl-amdgpu rocminfo4wsl-amdgpu

Remove ROCm and AMDGPU repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories.
    sudo rm /etc/apt/sources.list.d/rocm.list

    # Clear the cache and clean the system.
    sudo rm -rf /var/cache/apt/*
    sudo apt-get clean all

    # Restart the system.
    sudo reboot
