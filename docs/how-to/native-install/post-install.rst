.. meta::
  :description: Post-installation instructions
  :keywords: ROCm install, installation instructions, AMD, ROCm

*************************************************************************
Post-installation instructions
*************************************************************************

1.  Configure the system linker.

    Instruct the system linker where to find shared objects (``.so``-files) for ROCm applications.

    .. code-block:: bash

        sudo tee --append /etc/ld.so.conf.d/rocm.conf <<EOF
        /opt/rocm/lib
        /opt/rocm/lib64
        EOF
        sudo ldconfig

2. Configure ``PATH``.

    Add binary paths to the ``PATH`` environment variable.

    .. code-block:: bash
        :substitutions:

        export PATH=$PATH:/opt/rocm-|rocm_directory_version|/bin

3. Verify kernel-mode driver installation.

    .. code-block:: bash

        dkms status

4. Verify ROCm installation.

    .. code-block:: bash
        :substitutions:

        /opt/rocm-|rocm_directory_version|/bin/rocminfo
        /opt/rocm-|rocm_directory_version|/bin/clinfo

5. Verify package installation.

    .. tab-set::

        .. tab-item:: Ubuntu

            .. code-block:: bash

                sudo apt list --installed

        .. tab-item:: RHEL

            .. code-block:: bash

                sudo yum list installed

        .. tab-item:: SLES

            .. code-block:: bash

                sudo zypper search --installed-only

         .. tab-item:: Ubuntu (WSL2 / Docker for Windows)

            .. code-block:: bash

                sudo apt list --installed
