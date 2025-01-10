# Change Log

[ROCm Offline Installer Creator Documentation](https://rocm.docs.amd.com/projects/install-on-linux/en/latest/install/rocm-offline-installer.html)

All notable changes to this project will be documented in this file.

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

