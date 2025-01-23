.. meta::
  :description: Ubuntu AMDGPU installer installation
  :keywords: installation instructions, AMDGPU, AMDGPU installer, AMD, ROCm, Ubuntu, Ubuntu AMDGPU installer installation

*************************************************************************************
Ubuntu AMDGPU installer installation
*************************************************************************************

``amdgpu-install`` is a tool that helps you install and update AMDGPU, ROCm, and ROCm components.

.. note::

  ROCm doesn't support integrated graphics. If your system has an
  AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
  enumerate the IGP, the ROCm runtime might crash the system, even if told to omit
  it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.

.. _ubuntu-amdgpu-install-installation:

Installation
=================================================

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. datatemplate:nodata::

  .. tab-set::
      {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
      .. tab-item:: Ubuntu {{ os_version }}

          .. code-block:: bash
              :substitutions:

              sudo apt update
              wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
              sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
              sudo apt update
      {% endfor %}

.. include:: ../includes/amdgpu-installer-common.rst


.. _ubuntu-amdgpu-install-uninstall:

Uninstalling ROCm
=================================================

To uninstall all ROCm packages and the kernel-mode driver, use the following commands.

* Uninstalling single-version install

  .. code-block:: bash

    sudo amdgpu-install --uninstall

* Uninstalling a specific ROCm release

  .. code-block:: bash

    sudo amdgpu-install --uninstall --rocmrelease=<release-number>


* Uninstalling all ROCm releases

  .. code-block:: bash

    sudo amdgpu-install --uninstall --rocmrelease=all

Uninstalling amdgpu-install
=================================================

After uninstalling ROCm, remove the amdgpu-install package from system.

.. code-block:: bash

    sudo apt purge amdgpu-install
    sudo apt autoremove

Remove ROCm and AMDGPU repositories
=================================================

.. code-block:: bash

    # Remove the repositories
    sudo rm /etc/apt/sources.list.d/amdgpu.list
    sudo rm /etc/apt/sources.list.d/rocm.list
    
    # Clear the cache and clean the system
    sudo rm -rf /var/cache/apt/*
    sudo apt clean all
    sudo apt update
    
    # Restart the system
    sudo reboot

Additional options
=================================================

* Unattended installation.

  Adding ``-y`` as a parameter to ``amdgpu-install`` skips user prompts (for automation). For example:

  .. code-block:: bash

      amdgpu-install -y --usecase=rocm

* Skipping kernel mode driver installation.

  The installer script tries to install the kernel mode driver and the requested use cases. This
  might be unnecessary (as in the case of Docker containers). You might want to keep a specific version
  when using multi-version installation, and not have the last installed version overwrite the kernel
  mode driver.

  To skip the installation of the kernel-mode driver, add the ``--no-dkms`` option when calling the
  installer script.
