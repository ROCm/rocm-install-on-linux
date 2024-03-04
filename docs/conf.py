# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# ROCm version numbers
rocm_version = '6.0.2'
rocm_latest_versions = '6.0.1 6.0.2'
rocm_directory_version = '6.0.2' # in 6.0 rocm was located in /opt/rocm-6.0.0
amdgpu_version = '6.0.2' # directory in https://repo.radeon.com/rocm/apt/ and https://repo.radeon.com/amdgpu-install/
amdgpu_install_version = '6.0.60002-1' # version in https://repo.radeon.com/amdgpu-install/6.0.2/ubuntu/jammy/

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
version = "6.0.2"
release = "6.0.2"
setting_all_article_info = True
all_article_info_os = ["linux"]
all_article_info_author = ""

# Supported linux version numbers
ubuntu_version_numbers = [('22.04', 'jammy'), ('20.04', 'focal')]
rhel_release_version_numbers = ['9', '8']
rhel_version_numbers = [('9', '9.3'), ('9', '9.2'), ('8', '8.9'), ('8', '8.8')]
sles_version_numbers = ['15.5', '15.4']
ol_release_version_numbers = ['8']
ol_version_numbers = [('8', '8.8')]

# pages with specific settings
article_pages = [
    {
        "file":"release",
        "os":["linux"],
        "date":"2023-12-15"
    }
]

exclude_patterns = [
    'temp', 
    'how-to/native-install/install-rocm-template.rst', 
    'how-to/native-install/uninstall-rocm-template.rst'
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
