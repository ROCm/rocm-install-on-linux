.. meta::
  :description: Post-installation instructions
  :keywords: ROCm install, installation instructions, AMD, ROCm

*************************************************************************
Post-installation instructions
*************************************************************************

After installing ROCm, follow these steps to finalize and validate the installation.

1. Configure the system linker by indicating where to find the shared objects (``.so`` files) for the ROCm applications.

   .. code-block:: bash

       sudo tee --append /etc/ld.so.conf.d/rocm.conf <<EOF
       /opt/rocm/lib
       /opt/rocm/lib64
       EOF
       sudo ldconfig

2. Configure the path to the ROCm binary using either the ``update-alternatives`` or ``environment-modules`` Linux utilities.
   The ROCm installation process adds the ROCm executables to these systems, provided they are
   installed on the system.

   *  ``update-alternatives``:

      The ``update-alternatives`` utility is available on most Linux distributions. It helps 
      manage multiple versions of a command or program.
      For more information about ``update-alternatives``, see 
      `the Linux man page <https://man7.org/linux/man-pages/man1/update-alternatives.1.html>`_.
      
      To use ``update-alternatives``, follow these steps:

      #. List all the ROCm commands that are supported:

         .. code-block:: shell

            update-alternatives --list rocm

      #. If you have installed multiple ROCm versions, ``update-alternatives`` is automatically configured to use the
         latest version. To switch between installed versions, use this command:

         .. code-block:: shell

            update-alternatives --config rocm

   *  ``environment-modules``:

      The ``environment-modules`` tool simplifies shell initialization. It lets you modify 
      your session environment using module files. For more information, see the 
      `Environment Modules documentation <https://modules.readthedocs.io/en/latest/>`_.

      To use ``environment-modules``, follow these instructions:

      #. List the ROCm versions that are available:

         .. code-block:: shell

            module avail

      #. If multiple ROCm versions are installed, switch between them using this command:

         .. code-block:: shell

            module load rocm/<version>

   .. note::

      The ROCm module file is located at ``/opt/rocm-<ver>/lib/rocmmod``.

      If ``update-alternatives`` isn't available on the system, set the ``PATH`` variable to ``/opt/rocm-<ver>/bin``.

      .. code-block:: bash
         :substitutions:

         export PATH=$PATH:/opt/rocm-|rocm_directory_version|/bin

.. _verify-dkms:

3. Verify the kernel-mode driver installation.

   .. code-block:: bash

       dkms status

4. Export LD_LIBRARY_PATH as needed

   .. important::

      This step is required for version specific or :doc:`multi-version installations <./native-install/multi-version-install>`. 

   .. code-block:: shell
      :substitutions:

      export LD_LIBRARY_PATH=/opt/rocm-|rocm_directory_version|/lib

5. Verify the ROCm installation.

   .. code-block:: bash

       rocminfo
       clinfo

6. Verify the package installation.

   .. tab-set::

       .. tab-item:: Ubuntu

           .. code-block:: bash

               apt list --installed

       .. tab-item:: Debian

           .. code-block:: bash

               apt list --installed

       .. tab-item:: RHEL

           .. code-block:: bash

               dnf list installed
      
       .. tab-item:: OL

           .. code-block:: bash

               dnf list installed

       .. tab-item:: SLES

           .. code-block:: bash

               zypper search --installed-only
