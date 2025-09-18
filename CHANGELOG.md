# Change Log

[ROCm Offline Installer Creator Documentation](https://rocm.docs.amd.com/projects/install-on-linux/en/latest/install/rocm-offline-installer.html)

All notable changes to this project will be documented in this file.

## Offline Installer Creator v1.0.12

### Added

- Add ROCm 7.0 support for Debian 12, Ubuntu 22.04, 24.04, SUSE 15.7, RHEL 8.10, 9.4, 9.6, Oracle Linux 8.10, 9.6 and Rocky 9.6 and their ctests.
- Add support for Rocky 9.6
- On Ubuntu, let users select kernel version when creating an offline installer package for driver installation.

### Changed

- Try to download kernel headers for currently installed kernel when running the creator on Debian.
- Remove ctest `rocm-only-6.4.2` from the `ci` suite of tests and replace it with `rocm-only-6.4.3`. This creates the ROCm 6.4.3 installer package that the test `rocm-only-6.4.3-install` uses.

### Fixed

- Fix bug where file /etc/apt/preferences.d/rocm-pin-600 wasn't being deleted on Ubuntu and Debian during cleanup after running the creator.
- Fix bug where selecting extra packages with driver install didn't actually download the extra packages during package creation because `EXTRA_PACKAGES` variable wasn't being populated.
- Download kernel headers for the RHCK kernel installed on Oracle Linux during driver creation to prevent RHCK kernel from being updated during driver install. 
- Delete any UEK headers that aren't for the UEK kernel installed on Oracle Linux during creation if user enables driver install.
- Check to see if ROCm is installed before running the installer package in RHEL, Rocky, Oracle Linux and SUSE. If it's installed, then tell user to uninstall it before running the pacakge. Same behaviour as Ubuntu and Debian.

## Offline Installer Creator v1.0.11

### Added

- Add ROCm 6.4.3 support for Debian 12, Ubuntu 20.04, 22.04, 24.04, SUSE 15.6, RHEL 8.10, 9.4, 9.6, Oracle Linux 8.10 and 9.6 and their ctests.

### Changed

- Remove ctest `rocm-only-6.4.1` from the `ci` suite of tests and replace it with `rocm-only-6.4.2`. This creates the ROCm 6.4.2 installer package that the test `rocm-only-6.4.2-install` uses.
- Remove ROCm 6.0 support.

## Offline Installer Creator v1.0.10

### Added

- Add ROCm 6.4.2 support for Debian 12, Ubuntu 20.04, 22.04, 24.04, SUSE 15.6, RHEL 8.10, 9.4, 9.6, Oracle Linux 8.10 and 9.6 and their ctests.
- Add packages `amd-smi`, `rocdecode`, `rocjpeg` and `rdc` to the Extra Packages menu.
- Add support for new dynamic usecase/component UI menus that use new Meta-package naming convention.  Meta-package use begins for ROCm 6.4.2 and up.
- Add RHEL SUSE 15.7 support for ROCm 6.4.2+.

### Changed

- Remove ROCm support for 6.4.x for Ubuntu 20.04
- Remove RHEL 9.5 and OL 9.5 from our CI/CD builds.
- Remove ROCm 5.7.3 support.
- Remove 6.3.0, 6.4.0 and 6.4.1 tests from the `ci` suite of tests.
- Disable all 5.7.3 ctests by default.

### Fixed

- Don't download kernel headers during creation if user isn't installing the driver and don't download rocm dependencies if user is doing a driver only install.

## Offline Installer Creator v1.0.9

### Added

- Add ROCm 6.4.1 support for Ubuntu 20.04, 22.04, 24.04, SUSE 15.6, RHEL 8.10, 9.4, 9.5, Oracle Linux 8.10 and 9.4 and their ctests.
- Add Debian 12 support for offline creator, enabling installations of ROCm versions starting from 6.3.1.
- Add Debian 12 naming convention for build files.
- Add RHEL 9.6 and Oracle Linux 9.6 support for ROCm 6.4.1+.

### Changed

- Enable 'full' mode for RHEL and Oracle Linux.
- Let user select rocm version and rocm components in their respective menus via the Enter key.
- Remove ctest `rocm-only-6.4`  from the `ci` suite of tests and replace it with `rocm-only-6.4.1`. This creates the ROCm 6.4.1 installer package that the test `rocm-only-6.4.1-install` uses.
- Update our installer test to `rocm-only-6.4.1-install`.
- Changed naming conventions of build files to be more consistent across distros.
- Add RHEL 9.5 support for ROCm 6.4.1.

## Fixed

- Fix bug in RHEL 9.4 where gdm package was being uninstalled for ROCm 6.3.x in 'full mode'.
- Fix bug where enabling RVS in 'Extra Packages' menu doesn't persist when user enables it and then exits the menu. SWDEV-531130.

## Offline Installer Creator v1.0.8

### Added

- Add ROCm 6.4 support for Ubuntu 20.04, 22.04, 24.04, SUSE 15.6, RHEL 8.10, 9.4, 9.5, Oracle Linux 8.10 and 9.4 and their ctests.
- Add the uninstall feature for RHEL, Oracle Linux and SUSE.
- Add a `debug` command line argument for creation and/or installation of packages. It runs the creation and installation scripts with the -x flag, which shows the commands being run as the script is running.

### Changed

- Remove ctest `rocm-only-6.3.2` from the `ci` suite of tests and replace it with `rocm-only-6.3.3`. This creates the ROCm 6.3.3 installer package that the test `rocm-only-6.3.3-install` uses.
- Update our installer test to `rocm-only-6.3.3-install`.


### Fixed

- Fix bug where we write Post-Install Options twice in the config file that's created when user clicks <ACCEPT> in the GUI. It is now only written once.
- Pass in --no-dkms flag when doing the --dryrun for amdgpu-install for EL. This is done due to a parsing bug within amdgpu-install that gives you an incorrect output when user selects rocm, graphics and driver usecases.

## Offline Installer Creator v1.0.7

### Added

- Use a help header to display the help message when running the offline creator run file and the install package run file. This displays the help message immediately instead of waiting to untar the run file to display the header message.
- Add new menu `Post-Install Options` that contains the option for user to let all users access the GPU via udev or to only let the current user access the GPU by adding them to the video and render groups.
- Add ROCm 6.3.3 support for Ubuntu 20.04, 22.04, 24.04, SUSE 15.5, 15.6, RHEL 8.10, 9.4, 9.5 and Oracle Linux 8.10 and their ctests.

### Changed

- Moved the option to add current user to video and render groups from `Driver Options` to newly created menu `Post-Install Options`.
- Updated the summary menu pages to ensure we show the summary of all options users selected in the same order as the menus as displayed in.
- Update all the .config files in src/offline-installer/tests/ to add the `Post-Install Options` fields and remove `AMDGPU_POST_INSTALL_VIDEO_RENDER_GRP`.

### Fixed

- Fix bug in Oracle Linux 8.10 so that we download the exact gcc version that was used to build the kernel by looking at the full version (eg 11.5.0-2.0.1) instead of the partial version (11.5.0) provided in the variable CONFIG_CC_VERSION_TEXT in the kernel's config file that is located in /boot/config-$(uname -r).

## Offline Installer Creator v1.0.6

### Added

- Add ROCm 6.3.2 support for Ubuntu 20.04, 22.04, 24.04, SUSE 15.5, 15.6, RHEL 8.10, 9.4, 9.5 and Oracle Linux 8.10 and their ctests.

### Changed

- Change existing uninstall command for uninstalling ROCm on Ubuntu from using purge to autoremove to align with existing [docs](https://rocm.docs.amd.com/projects/install-on-linux/en/latest/install/native-install/ubuntu.html#uninstalling).
- Remove ctest `rocm-only-6.3` from the `ci` suite of tests and replace it with `rocm-only-6.3.1`. This creates the ROCm 6.3.1 installer package that the test `rocm-only-6.3.1-install` uses.
- Update our installer test to `rocm-only-6.3.1-install`.

## Offline Installer Creator v1.0.5

### Added

- Add ROCm 6.3.1 support for Ubuntu 20.04, 22.04, 24.04, SUSE 15.5, 15.6, RHEL 8.10, 9.4, 9.5 and Oracle Linux 8.10 and their ctests.
- Add RHEL 9.5 support.
- Added prerequisite installation step to install `python3-setuptools python3-wheel` for Ubuntu, RHEL, SLES and Oracle Linux adding `libpython3.x` for Ubuntu.
- Package specific version of `gcc-toolset-11` tied to the UEK when user sets Install Driver to yes for Oracle Linux.

### Changed

- Add ctest `rocm-only-6.3` to the `ci` suite of tests. This creates the ROCm 6.3 installer package that the test `rocm-only-6.3-install` uses.
- Add ROCm 6.3.1 tests to the `ci` suite of tests.
- Change our installation test from `rocm-only-6.3-install` to `rocm-only-6.3-install` as we only want to test the installation of the latest version of ROCm.


## Offline Installer Creator v1.0.4

### Added

- Add ROCm 6.3 support for all Ubuntu 20.04, 22.04, 24.04, SUSE 15.6, RHEL 8.10, 9.4 and Oracle Linux 8.10 and their ctests.
- Added RVS (rocm-validation-suite) as a selectable 'extra' package for installer creation.
- Add uninstall feature for ubuntu only.

### Changed

- Add ctest `rocm-only-6.2.4` to the `ci` suite of tests. This creates the ROCm 6.2.4 installer package that the test `rocm-only-6.2.4-install` uses.
- Reduce test coverage of `ci` suite of tests from 5.7.3, 6.0.2, 6.1,6.1.1, 6.1.2, 6.1.3, 6.2, 6.2.1, 6.2.2, 6.2.4 to only test 5.7.3, 6.0.2, 6.1.3, 6.2.4, 6.3. Our new policy is to simply test the latest patch version of each version of ROCm and all the patch versions of the latest ROCm version.
- Update our ctest tests to set FAIL_REGULAR_EXPRESSION for all creation installer tests to the regex `FAIL_CREATE_REGEX_ALL`. This will help us capture more failed tests.
- Change our installation test from `rocm-only-6.2.2-install` to `rocm-only-6.2.4-install` as we only want to test the installation of the latest version of ROCm.
- Update all the create-offline.sh scripts to create the create logs directly from the scripts instead of from rocm_offline_ui.c.

### Fixed

- Fix bug where we displayed wrong list of eligible ROCm versions in the offline installer GUI for SUSE 15.5 and 15.6.
- Remove support for ROCm 6.2+ for RHEL 9.2

