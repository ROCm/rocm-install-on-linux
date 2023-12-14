****************************************************************************
Ubuntu native installation
****************************************************************************

.. _ubuntu-register-repo:

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

.. _ubuntu-register-driver:

.. note::
    The GPG key may change; ensure it is updated when installing a new release.
    If the key signature verification fails while updating,
    re-add the key from the ROCm to the apt repository as mentioned above.
    The current ``rocm.gpg.key`` is not available in a standard key ring distribution
    but has the following SHA1 sum hash:
    ``73f5d8100de6048aa38a8b84cd9a87f05177d208 rocm.gpg.key``

Register kernel-mode driver
---------------------------------------------------------------------------

Add the AMDGPU repository for the driver.

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in [('22.04', 'jammy'), ('20.04', 'focal')] %}
        .. tab-item:: Ubuntu {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/amdgpu/|rocm_version|/ubuntu {{ os_release }} main" \
                    | sudo tee /etc/apt/sources.list.d/amdgpu.list
                sudo apt update 
        {% endfor %}

.. _ubuntu-register-rocm:

Register ROCm packages
---------------------------------------------------------------------------

Add the ROCm repository.

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in [('22.04', 'jammy'), ('20.04', 'focal')] %}
        .. tab-item:: Ubuntu {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/rocm.gpg] https://repo.radeon.com/rocm/apt/|rocm_version| {{ os_release }} main" \
                    | sudo tee --append /etc/apt/sources.list.d/rocm.list
                done
                echo -e 'Package: *\nPin: release o=repo.radeon.com\nPin-Priority: 600' \
                    | sudo tee /etc/apt/preferences.d/rocm-pin-600
        {% endfor %}

.. _ubuntu-install:

Installing
================================================

Install kernel driver
---------------------------------------------------------------------------

.. code-block:: bash

    sudo apt install amdgpu-dkms
    sudo reboot

Install ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash

    sudo apt install rocm-hip-sdk

Perform :doc:`post-install`.

.. _ubuntu-upgrade:

Upgrading
================================================

To upgrade an existing ROCm installation to a newer version, follow the steps in
:ref:`ubuntu-register-repo` and :ref:`ubuntu-install`. After upgrading the kernel
driver, it may also upgrade the GPU firmware which requires a system reboot to
take effect.

.. _ubuntu-uninstall:

Uninstalling
================================================

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    # sudo apt autoremove <package-name>
    # For example:
    sudo apt autoremove rocm-hip-sdk
    # Or for version specific packages:
    sudo apt autoremove rocm-hip-sdk|rocm_version|

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo apt autoremove rocm-core
    # Or for version specific packages:
    sudo apt autoremove rocm-core|rocm_version|

Uninstall kernel-mode driver
---------------------------------------------------------------------------

.. code-block:: bash

    sudo apt autoremove amdgpu-dkms

Remove ROCm and AMDGPU repositories
---------------------------------------------------------------------------

.. code-block:: bash

    # Remove the repositories.
    sudo rm /etc/apt/sources.list.d/rocm.list
    sudo rm /etc/apt/sources.list.d/amdgpu.list

    # Clear the cache and clean the system.
    sudo rm -rf /var/cache/apt/*
    sudo apt-get clean all

    # Restart the system.
    sudo reboot
