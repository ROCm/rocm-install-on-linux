.. meta::
  :description: Frequently asked questions for install
  :keywords: Linux, install, FAQ, ubuntu, RHEL, SUSE, AMD, ROCm

************************************************************************************
Installation FAQ
************************************************************************************

Here are some of the frequently asked questions from some common issues people faced with ROCm.

**Q1: On installation, I'm getting "Problem: nothing provides 'perl-URI-Encode' needed to be installed by ..."** `#1827 <https://github.com/ROCm/ROCm/issues/1827>`_

A1: Ensure that the :doc:`../prerequisites` are installed.  There are prerequisite PERL packages required for SUSE.  RHEL also requires EPEL to be installed, which is also mentioned in prerequisites.  Be sure to install those first, then repeat your installation steps.


**Q2: When compiling HIP programs, I'm getting linking error for -lstdc++, or "fatal error: 'cmath' file not found"** `#2031 <https://github.com/ROCm/ROCm/issues/2031>`_

A2: You can install C++ libs by using your package manager.  Ubuntu example is below:

.. code-block:: bash

  sudo apt-get install libstdc++-12-dev


**Q3: The latest version of ROCm is 6.0.2, but the install instructions only install 6.0.0.** `#2422 <https://github.com/ROCm/ROCm/issues/2422>`_

A3: We have 3 install methods:

* Quick-start installation - Installs latest **major** release (i.e. 6.0.0)

* Native package manager install method - Provides latest **major and minor** release (i.e. 6.0.0, 6.0.2)

* ``amdgpu-install`` method - Provides latest **major and minor** release (i.e. 6.0.0, 6.0.2)

So if you installed with quick-start instructions, it may be expected that you only have the latest major release.  If you want to get the latest minor revisions, please follow the other two install methods.


**Q4: After successfully installing ROCm, when I run rocminfo, the command is not found.** `#1607 <https://github.com/ROCm/ROCm/issues/1607>`_

A4: You likely just need to update your ``PATH`` environment variable.  Follow the instructions in the :doc:`post-install` for updating your ``PATH``.





