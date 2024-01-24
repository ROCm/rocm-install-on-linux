# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# ROCm version numbers
rocm_version = '6.0'
rocm_directory_version = '6.0.0' # in 6.0 rcom was located in /opt/rocm-6.0.0
amdgpu_version = '6.0' # directory in https://repo.radeon.com/rocm/apt/ and https://repo.radeon.com/amdgpu-install/
amdgpu_install_version = '6.0.60000-1' # version in https://repo.radeon.com/amdgpu-install/5.7.1/ubuntu/focal/

latex_engine = "xelatex"
latex_elements = {
    "fontpkg": r"""
\usepackage{tgtermes}
\usepackage{tgheros}
\renewcommand\ttdefault{txtt}
"""
}

# configurations for PDF output by Read the Docs
project = "ROCm Installation on Linux"
author = "Advanced Micro Devices, Inc."
copyright = "Copyright (c) 2023 Advanced Micro Devices, Inc. All rights reserved."
version = "6.0.0"
release = "6.0.0"
setting_all_article_info = True
all_article_info_os = ["linux"]
all_article_info_author = ""

# pages with specific settings
article_pages = [
    {
        "file":"release",
        "os":["linux"],
        "date":"2023-12-15"
    }
]

exclude_patterns = ['temp']

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
.. |amdgpu_install_version| replace:: {amdgpu_install_version}
"""

html_theme_options = {
    "link_main_doc": True
}
