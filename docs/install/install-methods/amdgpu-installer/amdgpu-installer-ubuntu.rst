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

Uninstalling
=================================================

Uninstalling amdgpu-install
---------------------------------------------------------------------------

.. code-block:: bash

    sudo apt purge amdgpu-install
    sudo apt autoremove

Uninstall specific meta packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo apt autoremove rocm

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo apt autoremove rocm-core

Cache cleanup
---------------------------------------------------------------------------

.. code-block:: bash

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
