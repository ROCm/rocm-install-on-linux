.. meta::
  :description: SUSE Enterprise Linux AMDGPU installer installation
  :keywords: installation instructions, AMDGPU, AMDGPU installer, AMD, ROCm, SUSE Enterprise Linux, SUSE Enterprise Linux AMDGPU installer installation

*************************************************************************************
SUSE Enterprise Linux AMDGPU installer installation
*************************************************************************************

``amdgpu-install`` is a tool that helps you install and update AMDGPU, ROCm, and ROCm components.

.. note::

  ROCm doesn't support integrated graphics. If your system has an
  AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
  enumerate the IGP, the ROCm runtime might crash the system, even if told to omit
  it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.

.. _sles-amdgpu-install-installation:

Installation
=================================================

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. datatemplate:nodata::

  .. tab-set::
      {% for os_version in config.html_context['sles_version_numbers'] %}
      .. tab-item:: SLES {{ os_version }}

          .. code-block:: bash
              :substitutions:

              sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
      {% endfor %}

.. include:: ../includes/amdgpu-installer-common.rst


.. _sles-amdgpu-install-uninstall:

Uninstalling
=================================================

Uninstalling amdgpu-install
---------------------------------------------------------------------------

.. code-block:: bash

    sudo zypper remove amdgpu-install

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

Cache cleanup
---------------------------------------------------------------------------

.. code-block:: bash
    
    # Clear the cache and clean the system
    sudo zypper clean --all
    sudo zypper refresh
    
    # Restart the system
    sudo reboot

Additional options
=================================================

* Unattended installation.

  Adding ``-y`` as a parameter to ``amdgpu-install`` skips user prompts (for automation). For example:

  .. code-block:: bash

      amdgpu-install -y --usecase=rocm
