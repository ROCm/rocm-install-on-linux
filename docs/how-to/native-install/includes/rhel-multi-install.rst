.. _rhel-multi-install:

1. Register the kernel-mode driver.

   .. datatemplate:nodata::

      .. tab-set::
          {% for os_version in config.html_context['rhel_version_numbers'] %}
          {% set os_major, _  = os_version.split('.') %}
          .. tab-item:: RHEL {{ os_version }}
              :sync: rhel-{{ os_version }} rhel-{{ os_major }}

              .. code-block:: bash
                  :substitutions:

                  for ver in |rocm_multi_versions|; do
                  sudo tee /etc/yum.repos.d/amdgpu.repo <<EOF
                  [amdgpu]
                  name=amdgpu
                  baseurl=https://repo.radeon.com/amdgpu/$ver/rhel/{{ os_version }}/main/x86_64/
                  enabled=1
                  priority=50
                  gpgcheck=1
                  gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                  EOF
                  done
                  sudo yum clean all
          {% endfor %}

.. _rhel-multi-register-rocm:

2. Register ROCm packages.

   .. datatemplate:nodata::

      .. tab-set::
         {% for os_release in config.html_context['rhel_release_version_numbers']  %}
         .. tab-item:: RHEL {{ os_release }}
             :sync: rhel-{{ os_release }}

             .. code-block:: bash
                 :substitutions:

                 for ver in |rocm_multi_versions|; do
                 sudo tee --append /etc/yum.repos.d/rocm.repo <<EOF
                 [ROCm-$ver]
                 name=ROCm|rocm_version|
                 baseurl=https://repo.radeon.com/rocm/rhel{{ os_release }}/$ver/main
                 enabled=1
                 priority=50
                 gpgcheck=1
                 gpgkey=https://repo.radeon.com/rocm/rocm.gpg.key
                 EOF
                 done

                 sudo yum clean all
         {% endfor %}

3. Install ROCm.

   Install kernel driver.

   .. code-block:: bash

      sudo yum install amdgpu-dkms
      sudo reboot

   Install the registered ROCm packages.

   .. code-block:: bash
      :substitutions:

      for ver in |rocm_multi_versions|; do
          sudo yum install rocm$ver
      done

4. Complete the :doc:`post-install`.

.. tip::

   For a single-version installation of the latest ROCm version on RHEL,
   use the steps in :ref:`rhel-register-repo` and :ref:`rhel-install`.
