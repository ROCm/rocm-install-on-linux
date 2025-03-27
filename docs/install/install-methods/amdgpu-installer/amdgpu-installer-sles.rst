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

    # sudo zypper remove <package-name>
    # For example:
    sudo zypper remove rocm
    # Or, for version specific packages:
    sudo zypper remove rocm|rocm_version|

Uninstall ROCm packages
---------------------------------------------------------------------------

.. code-block:: bash
    :substitutions:

    sudo zypper remove rocm-core amdgpu-core
    # Or for version specific packages:
    sudo zypper remove rocm-core|rocm_version| amdgpu-core

Remove ROCm repositories
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

* Skipping kernel mode driver installation.

  The installer script tries to install the kernel mode driver and the requested use cases. This
  might be unnecessary (as in the case of Docker containers). You might want to keep a specific version
  when using multi-version installation, and not have the last installed version overwrite the kernel
  mode driver.

  To skip the installation of the kernel-mode driver, add the ``--no-dkms`` option when calling the
  installer script.
