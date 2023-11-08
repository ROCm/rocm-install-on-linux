# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import shutil
import os

from rocm_docs import ROCmDocs

# ROCm version numbers
rocm_version = '6.0.0' 
amdgpu_version = '6.0.0' # directory in # directory in https://repo.radeon.com/rocm/apt/https://repo.radeon.com/amdgpu-install/
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
        "date":"2023-07-27"
    }
]

exclude_patterns = ['temp']

external_toc_path = "./sphinx/_toc.yml"

docs_core = ROCmDocs("Linux Installation")
docs_core.setup()

external_projects_current_project = "rocm"

docs_core.extensions += [
    'sphinxcontrib.datatemplates',
    'sphinx_substitution_extensions'
]

# Add the following replacements to every RST file.
rst_prolog = f"""
.. |rocm_version| replace:: {rocm_version}
.. |amdgpu_version| replace:: {amdgpu_version}
.. |amdgpu_install_version| replace:: {amdgpu_install_version}
"""

for sphinx_var in ROCmDocs.SPHINX_VARS:
    globals()[sphinx_var] = getattr(docs_core, sphinx_var)
html_theme_options = {
    "link_main_doc": True
}
