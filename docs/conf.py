# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# ROCm version numbers
rocm_version = '7.0.0'
rocm_major_version = '7.0'
rocm_multi_versions = '7.0 6.4.3' # in 6.3, the folder names on repo.radeon.com use 6.3 for minor releases
rocm_multi_versions_package_versions = '7.0.0 6.4.3' # however, in multi, the packages use 6.3.0
rocm_directory_version = '7.0.0' # in 6.0 rocm was located in /opt/rocm-6.0.0
amdgpu_version = '7.0' # directory in https://repo.radeon.com/rocm/apt/ and https://repo.radeon.com/amdgpu-install/
amdgpu_install_version = '7.0.70000-1' # version in https://repo.radeon.com/amdgpu-install/6.0.2/ubuntu/jammy/


latex_engine = "xelatex"
latex_elements = {
    "fontpkg": r"""
\usepackage{tgtermes}
\usepackage{tgheros}
\renewcommand\ttdefault{txtt}
"""
}

# configurations for PDF output by Read the Docs
project = "ROCm installation on Linux"
author = "Advanced Micro Devices, Inc."
copyright = "Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved."
version = "7.0.0"
release = "7.0.0"
setting_all_article_info = True
all_article_info_os = ["linux"]
all_article_info_author = ""

# Supported linux version numbers
ubuntu_version_numbers = [('24.04', 'noble'), ('22.04', 'jammy')]
debian_version_numbers = [('12', 'jammy')]
rhel_release_version_numbers = ['9', '8']
rhel_version_numbers = ['9.6', '9.4', '8.10']
rhel_multi_versions = ['9.6', '9.4', '8.10']
sles_version_numbers = ['15.7']
ol_release_version_numbers = ['9', '8']
ol_version_numbers = ['9.6', '8.10']
ol_multi_versions = ['9.6', '8.10']
azl_version_numbers = ['3.0']
rl_version_numbers = ['9.6']

exclude_patterns = [
    'temp', 
    'install/install-methods/includes/rhel-multi-install.rst',
    'install/install-methods/includes/sles-multi-install.rst',
    'install/install-methods/includes/ubuntu-multi-install.rst',
    'install/install-methods/includes/debian-multi-install.rst',
    'install/install-methods/includes/ol-multi-install.rst',
    'install/install-methods/includes/azl-multi-install.rst',
    'install/install-methods/includes/amdgpu-installer-common.rst',
    'install/install-methods/includes/meta-package-table.rst',
    'install/amdgpu-install.rst'
]

external_toc_path = "./sphinx/_toc.yml"

html_theme = "rocm_docs_theme"
html_theme_options = {"flavor": "rocm-docs-home"}

extensions = [
    "rocm_docs",
    "sphinxcontrib.datatemplates",
    "sphinx_substitution_extensions",
]

html_title = "ROCm installation (Linux)"

external_projects_current_project = "rocm"

# Add the following replacements to every RST file.
rst_prolog = f"""
.. |rocm_version| replace:: {rocm_version}
.. |rocm_major_version| replace:: {rocm_major_version}
.. |rocm_multi_versions| replace:: {rocm_multi_versions}
.. |rocm_multi_versions_package_versions| replace:: {rocm_multi_versions_package_versions}
.. |amdgpu_version| replace:: {amdgpu_version}
.. |rocm_directory_version| replace:: {rocm_directory_version}
.. |amdgpu_install_version| replace:: {amdgpu_install_version}
"""

html_theme_options = {
    "link_main_doc": True
}

html_context = {
    "ubuntu_version_numbers" : ubuntu_version_numbers,
    "debian_version_numbers" : debian_version_numbers,
    "sles_version_numbers" : sles_version_numbers,
    "rhel_release_version_numbers" : rhel_release_version_numbers,
    "rhel_version_numbers" : rhel_version_numbers,
    "ol_release_version_numbers" : ol_release_version_numbers,
    "ol_version_numbers" : ol_version_numbers,
    "azl_version_numbers": azl_version_numbers,
    "rl_version_numbers" : rl_version_numbers,
    "rhel_multi_versions" : rhel_multi_versions,
    "ol_multi_versions" : ol_multi_versions
}

footnote_backlinks = False
