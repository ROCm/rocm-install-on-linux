*************************************************************************
Post-installation instructions
*************************************************************************

1.  Configure system linker.

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

        export PATH=$PATH:/opt/rocm-|rocm_version|/bin

3. Verify kernel-mode driver installation.

    .. code-block:: bash

        dkms status

4. Verify ROCm installation.

    .. code-block:: bash
        :substitutions:

        /opt/rocm-|rocm_version|/bin/rocminfo
        /opt/rocm-|rocm_version|/bin/clinfo

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
