.. _sles-multi-install:

1. Register the kernel-mode driver following the steps in :ref:`sles-register-driver`.

2. Register ROCm packages.

   .. code-block:: bash
      :substitutions:

      for ver in |rocm_multi_versions|; do
      sudo tee --append /etc/zypp/repos.d/rocm.repo <<EOF
      [ROCm-$ver]
      name=ROCm$ver
      baseurl=https://repo.radeon.com/rocm/zyp/$ver/main
      enabled=1
      gpgcheck=1
      gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
      EOF
      done

      sudo zypper ref

3. Install ROCm.

   a. Install kernel driver.

      .. code-block:: bash

         sudo zypper --gpg-auto-import-keys install amdgpu-dkms
         sudo reboot

   b. Install the registered ROCm packages.

      .. code-block:: bash
         :substitutions:

         for ver in |rocm_multi_versions|; do
             sudo zypper --gpg-auto-import-keys install rocm$ver
         done

4. Complete the :doc:`post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on SLES,
   use the steps in :ref:`sles-register-rocm` and :ref:`sles-install`.

