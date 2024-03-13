.. meta::
  :description: Post-installation instructions
  :keywords: ROCm install, installation instructions, AMD, ROCm

*************************************************************************
Post-installation instructions
*************************************************************************

#. Configure the system linker.

   Instruct the system linker where to find shared objects (``.so``-files) for ROCm applications.

   .. code-block:: bash

       sudo tee --append /etc/ld.so.conf.d/rocm.conf <<EOF
       /opt/rocm/lib
       /opt/rocm/lib64
       EOF
       sudo ldconfig

#. Configure ``PATH``.

   Add binary paths to the ``PATH`` environment variable.

   .. code-block:: bash
       :substitutions:

       export PATH=$PATH:/opt/rocm-|rocm_directory_version|/bin

.. _verify-dkms:

#. Verify kernel-mode driver installation.

   .. code-block:: bash

       dkms status

#. Verify ROCm installation.

   .. code-block:: bash
       :substitutions:

       /opt/rocm-|rocm_directory_version|/bin/rocminfo
       /opt/rocm-|rocm_directory_version|/bin/clinfo

#. Verify package installation.

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
