.. meta::
  :description: Troubleshooting installation issues
  :keywords: Linux, install, FAQ, ubuntu, RHEL, SUSE, AMD, ROCm

************************************************************************************
Troubleshooting installation issues
************************************************************************************

Here is a summary of common issues associated with ROCm installation.

`Issue #1827 <https://github.com/ROCm/ROCm/issues/1827>`_
================================================================

* **Problem**: When installing, I get
  `"Problem: nothing provides 'perl-URI-Encode' needed to be installed by ..."`.

* **Solution**: Ensure that the :doc:` prerequisites <../prerequisites>` are correctly installed.
  * There are prerequisite PERL packages required for SUSE.
  * RHEL requires that you install EPEL (also mentioned in prerequisites).

  Once you've successfully installed the prerequisites for your operating system, repeat the installation
  steps.

`Issue #2031 <https://github.com/ROCm/ROCm/issues/2031>`_
================================================================

* **Problem**: When compiling HIP programs, I get a linking error for ``-lstdc++``, or
  "fatal error: 'cmath' file not found".

* **Solution**:  You can install C++ libraries using your package manager. Here's an Ubuntu example:

  .. code-block:: bash

    sudo apt-get install libstdc++-12-dev

`Issue #2422 <https://github.com/ROCm/ROCm/issues/2422>`_
================================================================

* **Problem**: The latest version of ROCm is 6.0.2, but the install instructions install version 6.0.0.

* **Solution**: If you used the quick-start install, try another install method. The quick-start method installs only the latest major release.

  Here are the three installation methods you can choose from:

  * Quick-start: Installs the latest **major** release (i.e., 6.0.0)
  * Native package manager: Provides the latest **major and minor** release (i.e., 6.0.0, 6.0.2)
  * ``amdgpu-install``: Provides the latest **major and minor** release (i.e., 6.0.0 and 6.0.2)

`Issue #1607 <https://github.com/ROCm/ROCm/issues/1607>`_
================================================================

* **Problem**: When I run ``rocminfo`` after successfully installing ROCm, the command is not found

* **Solution**:  Update your ``PATH`` environment variable. Follow the instructions on the
  :doc:`post-install <post-install>` page,
