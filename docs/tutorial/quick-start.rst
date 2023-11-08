Quick Start
###########

AMDGPU Installer
****************

Ubuntu
======

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in [('22.04', 'jammy'), ('20.04', 'focal')] %}
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
                sudo apt install rocm-hip-libraries 
                echo Please reboot system for all settings to take effect.
        {% endfor %}

Red Hat Enterprise Linux
========================

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in [('8', '8.8'), ('8', '8.7'), ('9', '9.2'), ('9', '9.1')] %}
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
                sudo yum install rocm-hip-libraries 
                echo Please reboot system for all settings to take effect.
        {% endfor %}

SUSE Linux Enterprise Server
============================

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in ['15.5', '15.4'] %}
        {% set os_release, os_sp  = os_version.split('.') %}
        .. tab-item:: {{ os_version }}
            :sync: sle-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo zypper addrepo https://download.opensuse.org/repositories/devel:languages:perl/SLE_{{ os_release }}_SP{{ os_sp }}/devel:languages:perl.repo 
                sudo zypper install kernel-default-devel 
                # See prerequisites. Adding current user to Video and Render groups 
                sudo usermod -a -G render,video $LOGNAME 
                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                sudo zypper refresh 
                sudo zypper install amdgpu-dkms 
                sudo zypper install rocm-hip-libraries 
                echo Please reboot system for all settings to take effect.
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}

Native Package Manager
**********************

Ubuntu
======

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_version, os_release) in [('22.04', 'jammy'), ('20.04', 'focal')] %}
        .. tab-item:: {{ os_version }}
            :sync: ubuntu-{{ os_version}}

            .. code-block:: bash
                :substitutions:

                sudo apt update 
                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb 
                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb 
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}

Red Hat Enterprise Linux
========================

.. datatemplate:nodata::

    .. tab-set::
        {% for (os_release, os_version) in [('8', '8.8'), ('8', '8.7'), ('9', '9.2'), ('9', '9.1')] %}
        .. tab-item:: {{ os_version }}
            :sync: rhel-{{ os_version }} rhel-{{ os_release }}

            .. code-block:: bash
                :substitutions:

                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_release }}.noarch.rpm 
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}

SUSE Linux Enterprise Server
============================

.. datatemplate:nodata::

    .. tab-set::
        {% for os_version in ['15.5', '15.4'] %}
        .. tab-item:: {{ os_version }}
            :sync: sle-{{ os_version }}

            .. code-block:: bash
                :substitutions:

                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                sudo amdgpu-install --usecase=graphics,rocm
        {% endfor %}
