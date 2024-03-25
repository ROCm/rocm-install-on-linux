.. meta::
  :description: Quick-start install guide
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU

.. _rocm-install-quick:

*************************************************************
Quick-start install guide
*************************************************************

For a quick summary on installing ROCm on Linux, follow the steps listed on this page. If you want
more in-depth installation instructions, refer to :ref:`rocm-install-overview`.

To start, choose your preferred install method and operating system:


.. grid:: 2
    :gutter: 1

    .. grid-item-card:: :ref:`rocm-package-man-quick`

        * :ref:`package-man-ubuntu`
        * :ref:`package-man-rhel`
        * :ref:`package-man-suse`

    .. grid-item-card:: :ref:`rocm-amdgpu-quick`

        * :ref:`amdgpu-ubuntu`
        * :ref:`amdgpu-rhel`
        * :ref:`amdgpu-suse`

.. _rocm-package-man-quick:

Native package manager
==========================================

.. _package-man-ubuntu:

Ubuntu
------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"
                # See prerequisites. Adding current user to Video and Render groups
                sudo usermod -a -G render,video $LOGNAME
                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                sudo apt update
                sudo apt install amdgpu-dkms
                sudo apt install rocm
                echo "Please reboot system for all settings to take effect."
        {% endfor %}

.. _package-man-rhel:

Red Hat Enterprise Linux
------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in config.html_context['rhel_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_release }}.noarch.rpm
                sudo rpm -ivh epel-release-latest-{{ os_release }}.noarch.rpm
                sudo crb enable
                sudo yum install kernel-headers kernel-devel
                # See prerequisites. Adding current user to Video and Render groups
                sudo usermod -a -G render,video $LOGNAME
                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_release }}.noarch.rpm 
                sudo yum clean all
                sudo yum install amdgpu-dkms
                sudo yum install rocm
                echo "Please reboot system for all settings to take effect."
        {% endfor %}

.. _package-man-suse:

SUSE Linux Enterprise Server
------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in config.html_context['sles_version_numbers'] %}
        {% set os_release, os_sp  = os_version.split('.') %}
        .. tab-item:: {{ os_version }}
            :sync: sle-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                # Currently installing Perl module from SLES 15.5
                sudo zypper addrepo https://download.opensuse.org/repositories/devel:/languages:/perl/15.5/devel:languages:perl.repo
                sudo zypper install kernel-default-devel
                # See prerequisites. Adding current user to Video and Render groups
                sudo usermod -a -G render,video $LOGNAME
                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                sudo zypper refresh
                sudo zypper install amdgpu-dkms
                sudo zypper install rocm
                echo "Please reboot system for all settings to take effect."
        {% endfor %}

.. _rocm-amdgpu-quick:

AMDGPU installer
=================================================

.. _amdgpu-ubuntu:

Ubuntu
------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                sudo apt update
                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}

.. _amdgpu-rhel:

Red Hat Enterprise Linux
------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in config.html_context['rhel_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_release }}.noarch.rpm 
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}

.. _amdgpu-suse:

SUSE Linux Enterprise Server
------------------------------------------------------------------------------------

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in config.html_context['sles_version_numbers'] %}
        .. tab-item:: {{ os_version }}
            :sync: sle-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}
