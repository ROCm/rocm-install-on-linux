.. meta::
  :description: Quick start install guide
  :keywords: ROCm installation, AMD, ROCm, Package manager, AMDGPU

.. _rocm-install-quick:

*************************************************************
ROCm quick start install guide for Linux
*************************************************************

For a quick summary on installing ROCm on Linux, choose your preferred operating
system and install method and follow the steps listed in the table. If you want
more in-depth installation instructions, refer to :ref:`rocm-install-overview`.

.. note::

    If you're using RHEL or SLES, be sure to register with your distro before installation.  
    If you need guidance, get :ref:`help with registering your distro <troubleshooting-registering-license>`. 

.. caution::

    Docker images contain a bare minimum install so some important packages may need to be installed, prior 
    to installing ROCm. Get :ref:`help installing packages on your docker image <troubleshooting-install-missing-packages-for-dockers>`, before running the install.

.. datatemplate:nodata::

    .. tab-set::

        .. tab-item:: Ubuntu

            .. tab-set::

                {% for (os_version, os_release) in config.html_context['ubuntu_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                    .. tab-set::

                        .. tab-item:: Native package manager
                            :sync: native-package-manager

                            .. code-block:: bash
                                :substitutions:

                                sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"
                                sudo usermod -a -G render,video $LOGNAME # Adding current user to Video, Render groups. See prerequisites.
                                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                                sudo apt update
                                sudo apt install amdgpu-dkms
                                sudo apt install rocm
                                echo "Please reboot system for all settings to take effect."

                        .. tab-item:: AMDGPU installer
                            :sync: amdgpu-installer

                            .. code-block:: bash
                                :substitutions:

                                sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)"
                                sudo usermod -a -G render,video $LOGNAME # Adding current user to Video, Render groups. See prerequisites.
                                sudo apt update
                                wget https://repo.radeon.com/amdgpu-install/|amdgpu_version|/ubuntu/{{ os_release }}/amdgpu-install_|amdgpu_install_version|_all.deb
                                sudo apt install ./amdgpu-install_|amdgpu_install_version|_all.deb
                                sudo amdgpu-install --usecase=graphics,rocm
                {% endfor %}

        .. tab-item:: Red Hat Enterprise Linux

            .. tab-set::

                {% for os_version in config.html_context['rhel_version_numbers'] %}
                {% set os_major, _  = os_version.split('.') %}
                .. tab-item:: {{ os_version }}

                    .. tab-set::

                        .. tab-item:: Native package manager
                            :sync: native-package-manager

                            .. code-block:: bash
                                :substitutions:

                                wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                                sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                                sudo dnf install dnf-plugin-config-manager
                                sudo crb enable
                                sudo yum install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"
                                sudo usermod -a -G render,video $LOGNAME # Adding current user to Video, Render groups. See prerequisites.
                                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                                sudo yum clean all
                                sudo yum install amdgpu-dkms
                                sudo yum install rocm
                                echo "Please reboot system for all settings to take effect."

                        .. tab-item:: AMDGPU installer
                            :sync: amdgpu-installer

                            .. code-block:: bash
                                :substitutions:

                                wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-{{ os_major }}.noarch.rpm
                                sudo rpm -ivh epel-release-latest-{{ os_major }}.noarch.rpm
                                sudo dnf install dnf-plugin-config-manager
                                sudo crb enable
                                sudo yum install "kernel-headers-$(uname -r)" "kernel-devel-$(uname -r)"
                                sudo usermod -a -G render,video $LOGNAME # Adding current user to Video, Render groups. See prerequisites.
                                sudo yum install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/rhel/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.el{{ os_major }}.noarch.rpm
                                sudo amdgpu-install --usecase=graphics,rocm
                {% endfor %}


        .. tab-item:: SUSE Linux Enterprise Server

            .. tab-set::

                {% for os_version in config.html_context['sles_version_numbers'] %}
                .. tab-item:: {{ os_version }}

                    .. tab-set::

                        .. tab-item:: Native package manager
                            :sync: native-package-manager

                            .. code-block:: bash
                                :substitutions:

                {% if os_version == "15.4" %}
                                # Installing Perl module from SLES 15.5, as it was removed from 15.4
                                sudo zypper addrepo https://download.opensuse.org/repositories/devel:/languages:/perl/15.5/devel:languages:perl.repo
                {% else %}
                                sudo zypper addrepo https://download.opensuse.org/repositories/devel:languages:perl/{{ os_version}}/devel:languages:perl.repo
                {% endif %}
                                sudo zypper install kernel-default-devel
                                sudo usermod -a -G render,video $LOGNAME # Adding current user to Video, Render groups. See prerequisites.
                                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                                sudo zypper refresh
                                sudo zypper install amdgpu-dkms
                                sudo zypper install rocm
                                echo "Please reboot system for all settings to take effect."

                        .. tab-item:: AMDGPU installer
                            :sync: amdgpu-installer

                            .. code-block:: bash
                                :substitutions:

                {% if os_version == "15.4" %}
                                # Installing Perl module from SLES 15.5, as it was removed from 15.4
                                sudo zypper addrepo https://download.opensuse.org/repositories/devel:/languages:/perl/15.5/devel:languages:perl.repo
                {% else %}
                                sudo zypper addrepo https://download.opensuse.org/repositories/devel:languages:perl/{{ os_version}}/devel:languages:perl.repo
                {% endif %}
                                sudo zypper install kernel-default-devel
                                sudo usermod -a -G render,video $LOGNAME # Adding current user to Video, Render groups. See prerequisites.
                                sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/|amdgpu_version|/sle/{{ os_version }}/amdgpu-install-|amdgpu_install_version|.noarch.rpm
                                sudo amdgpu-install --usecase=graphics,rocm
                {% endfor %}


If you encounter install issues, you can refer to the :doc:`troubleshooting <../how-to/native-install/install-faq>` page.
