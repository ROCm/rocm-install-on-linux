
<!-- markdownlint-disable no-duplicate-header blanks-around-headings no-multiple-blanks -->
# Quick Start (Linux)


::::::::::::{tab-set}



:::::::::::{tab-item} Instinct
:sync: instinct
    




::::::::::{tab-set}



:::::::::{tab-item} Ubuntu
:sync: ubuntu

                    


::::::::{tab-set}


:::::::{tab-item} 22.04
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)" 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
wget https://repo.radeon.com/amdgpu-install/latest/ubuntu/jammy/amdgpu-install_5.7.50700-1_all.deb 
sudo apt install ./amdgpu-install_5.7.50700-1_all.deb 
sudo apt update 
sudo apt install amdgpu-dkms 
sudo apt install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo apt update 
wget https://repo.radeon.com/amdgpu-install/5.7/ubuntu/jammy/amdgpu-install_5.7.50700-1_all.deb 
sudo apt install ./amdgpu-install_5.7.50700-1_all.deb 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

:::::::{tab-item} 20.04
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
sudo apt install "linux-headers-$(uname -r)" "linux-modules-extra-$(uname -r)" 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
wget https://repo.radeon.com/amdgpu-install/latest/ubuntu/focal/amdgpu-install_5.7.50700-1_all.deb 
sudo apt install ./amdgpu-install_5.7.50700-1_all.deb 
sudo apt update 
sudo apt install amdgpu-dkms 
sudo apt install rocm-hip-libraries 
echo Please reboot system for all settings to take effect
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo apt update 
wget https://repo.radeon.com/amdgpu-install/5.7/ubuntu/focal/amdgpu-install_5.7.50700-1_all.deb 
sudo apt install ./amdgpu-install_5.7.50700-1_all.deb 
sudo amdgpu-install --usecase=graphics,rocm 
```
:::::
::::::
                         


                                                                   


:::::::

::::::::
                                                                   


:::::::::



:::::::::{tab-item} Red Hat Enterprise Linux
:sync: rhel

                    


::::::::{tab-set}


:::::::{tab-item} 9.2
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-9.noarch.rpm 
sudo rpm -ivh epel-release-latest-9.noarch.rpm 
sudo crb enable 
sudo yum install kernel-headers kernel-devel 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
sudo yum install https://repo.radeon.com/amdgpu-install/latest/rhel/9.2/amdgpu-install-5.7.50700-1.el9.noarch.rpm 
sudo yum clean all 
sudo yum install amdgpu-dkms 
sudo yum install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo yum install https://repo.radeon.com/amdgpu-install/5.7/rhel/9.2/amdgpu-install-5.7.50700-1.el9.noarch.rpm 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

:::::::{tab-item} 9.1
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-9.noarch.rpm 
sudo rpm -ivh epel-release-latest-9.noarch.rpm 
sudo crb enable 
sudo yum install kernel-headers kernel-devel 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
sudo yum install https://repo.radeon.com/amdgpu-install/latest/rhel/9.1/amdgpu-install-5.7.50700-1.el9.noarch.rpm 
sudo yum clean all 
sudo yum install amdgpu-dkms 
sudo yum install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo yum install https://repo.radeon.com/amdgpu-install/5.7/rhel/9.1/amdgpu-install-5.7.50700-1.el9.noarch.rpm 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

:::::::{tab-item} 8.8
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm 
sudo rpm -ivh epel-release-latest-8.noarch.rpm 
sudo crb enable 
sudo yum install kernel-headers kernel-devel 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
sudo yum install https://repo.radeon.com/amdgpu-install/latest/rhel/8.8/amdgpu-install-5.7.50700-1.el8.noarch.rpm 
sudo yum clean all 
sudo yum install amdgpu-dkms 
sudo yum install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo yum install https://repo.radeon.com/amdgpu-install/5.7/rhel/8.8/amdgpu-install-5.7.50700-1.el8.noarch.rpm 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

:::::::{tab-item} 8.7
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm 
sudo rpm -ivh epel-release-latest-8.noarch.rpm 
sudo crb enable 
sudo yum install kernel-headers kernel-devel 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
sudo yum install https://repo.radeon.com/amdgpu-install/latest/rhel/8.7/amdgpu-install-5.7.50700-1.el8.noarch.rpm 
sudo yum clean all 
sudo yum install amdgpu-dkms 
sudo yum install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo yum install https://repo.radeon.com/amdgpu-install/5.7/rhel/8.7/amdgpu-install-5.7.50700-1.el8.noarch.rpm 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

::::::::
                                                                   


:::::::::



:::::::::{tab-item} SUSE Linux Enterprise Server
:sync: sle

                    


::::::::{tab-set}


:::::::{tab-item} 15.5
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
wget https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm 
sudo rpm -ivh epel-release-latest-8.noarch.rpm 
sudo crb enable 
sudo yum install kernel-headers kernel-devel 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
sudo yum install https://repo.radeon.com/amdgpu-install/latest/rhel/8.7/amdgpu-install-5.7.50700-1.el8.noarch.rpm 
sudo yum clean all 
sudo yum install amdgpu-dkms 
sudo yum install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/5.7/sle/15.5/amdgpu-install-5.7.50700-1.noarch.rpm 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

:::::::{tab-item} 15.4
 


::::::{tab-set}

:::::{tab-item} Installation via Package Manager
```shell
sudo zypper addrepo https://download.opensuse.org/repositories/devel:languages:perl/SLE_15_SP4/devel:languages:perl.repo 
sudo zypper install kernel-default-devel 
# See prerequisites. Adding current user to Video and Render groups 
sudo usermod -a -G render,video $LOGNAME 
sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/latest/sle/15.4/amdgpu-install-5.7.50700-1.noarch.rpm 
sudo zypper refresh 
sudo zypper install amdgpu-dkms 
sudo zypper install rocm-hip-libraries 
echo Please reboot system for all settings to take effect.
```
:::::

:::::{tab-item} Installation via AMDGPU Script
```shell
sudo zypper --no-gpg-checks install https://repo.radeon.com/amdgpu-install/5.7/sle/15.4/amdgpu-install-5.7.50700-1.noarch.rpm 
sudo amdgpu-install --usecase=graphics,rocm
```
:::::
::::::
                         


                                                                   


:::::::

::::::::
                                                                   


:::::::::


::::::::::

                                                                   




:::::::::::



:::::::::::{tab-item} Radeon
:sync: radeon
    


See {doc}`Radeon Installation instructions <radeon:install/install-radeon>`
for those using the Radeon GPU with graphical applications.
    



:::::::::::


::::::::::::

                                                                   