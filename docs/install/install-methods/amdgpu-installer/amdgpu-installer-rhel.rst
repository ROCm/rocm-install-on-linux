.. meta::
  :description: Red Hat Enterprise Linux AMDGPU installer installation
  :keywords: installation instructions, AMDGPU, AMDGPU installer, AMD, ROCm, Red Hat Enterprise Linux, Red Hat Enterprise Linux AMDGPU installer installation

*************************************************************************************
Red Hat Enterprise Linux AMDGPU installer installation
*************************************************************************************

``amdgpu-install`` is a tool that helps you install and update AMDGPU, ROCm, and ROCm components.

.. note::

  ROCm doesn't support integrated graphics. If your system has an
  AMD IGP installed, disable it in the BIOS prior to using ROCm. If the driver can
  enumerate the IGP, the ROCm runtime might crash the system, even if told to omit
  it via `HIP_VISIBLE_DEVICES <https://rocm.docs.amd.com/en/latest/conceptual/gpu-isolation.html#hip-visible-devices>`_.

.. _rhel-amdgpu-install-installation:

Installation
=================================================

.. caution::

    Ensure that the :doc:`/install/prerequisites` are met before installing.

.. datatemplate:nodata::

  .. tab-set::
      {% for os_version in config.html_context['rhel_version_numbers'] %}
      {% set os_major, _  = os_version.split('.') %}
      .. tab-item:: RHEL {{ os_version }}

          .. code-block:: bash
              :substitutions:

              sudo dnf install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
      {% endfor %}

.. include:: ../includes/amdgpu-installer-common.rst

.. _rhel-amdgpu-install-uninstall:

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

    sudo dnf remove amdgpu-install

Remove ROCm and AMDGPU repositories
=================================================

.. code-block:: bash

    # Remove the repositories
    sudo rm /etc/yum.repos.d/rocm.repo*
    sudo rm /etc/yum.repos.d/amdgpu.repo*
    
    # Clear the cache and clean the system
    sudo rm -rf /var/cache/dnf
    sudo dnf clean all

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
