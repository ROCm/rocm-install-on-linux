# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# ROCm version numbers
rocm_version = '6.2.1'
rocm_multi_versions = '6.2.1 6.2' # in 6.2, the folder names on repo.radeon.com use 6.2 for minor releases
rocm_multi_versions_package_versions = '6.2.1 6.2.0' # however, in multi, the packages use 6.2.0
rocm_directory_version = '6.2.1' # in 6.0 rocm was located in /opt/rocm-6.0.0
amdgpu_version = '6.2.1' # directory in https://repo.radeon.com/rocm/apt/ and https://repo.radeon.com/amdgpu-install/
amdgpu_install_version = '6.2.60201-1' # version in https://repo.radeon.com/amdgpu-install/6.0.2/ubuntu/jammy/


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
copyright = "Copyright (c) 2024 Advanced Micro Devices, Inc. All rights reserved."
version = "6.2.1"
release = "6.2.1"
setting_all_article_info = True
all_article_info_os = ["linux"]
all_article_info_author = ""

# Supported linux version numbers
ubuntu_version_numbers = [('24.04', 'noble'), ('22.04', 'jammy')]
rhel_release_version_numbers = ['9', '8']
rhel_version_numbers = ['9.4', '9.3', '8.10', '8.9']
sles_version_numbers = ['15.6', '15.5']
ol_release_version_numbers = ['8']
ol_version_numbers = [('8', '8.8')]

exclude_patterns = [
    'temp', 
    'install/native-install/uninstall-rocm-template.rst',
    'install/native-install/includes/rhel-multi-install.rst',
    'install/native-install/includes/sles-multi-install.rst',
    'install/native-install/includes/ubuntu-multi-install.rst'
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
    "sles_version_numbers" : sles_version_numbers,
    "rhel_release_version_numbers" : rhel_release_version_numbers,
    "rhel_version_numbers" : rhel_version_numbers,
    "ol_release_version_numbers" : ol_release_version_numbers,
    "ol_version_numbers" : ol_version_numbers
}
