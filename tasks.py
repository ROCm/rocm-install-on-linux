#!/usr/bin/env python3

from invoke import task
from pathlib import Path

SOURCE_DIR = Path(__file__).parent / "docs"
BUILD_DIR = SOURCE_DIR / "_build"


@task
def clean(c):
    import shutil

    print(f"Removing build dir: {BUILD_DIR}")
    if BUILD_DIR.exists():
        shutil.rmtree(BUILD_DIR)


@task
def build(c):
    from sphinx.application import Sphinx

    build_dir_html = BUILD_DIR / "html"
    build_dir_doctree = BUILD_DIR / "doctrees"

    conf_overrides = {"language": "en"}

    app = Sphinx(
        str(SOURCE_DIR),
        str(SOURCE_DIR),  # Directory containing conf.py, typically the same as SOURCE_DIR
        str(build_dir_html),  # Output directory
        str(build_dir_doctree),  # Doctree directory
        "html",  # Builder name
        conf_overrides,  # Configuration overrides
        freshenv=True,  # Equivalent to -E option
        warningiserror=False,  # You can change this as needed
        tags=[],  # Tags can be used to conditionally include/exclude content
        verbosity=0,  # Increase verbosity (0 by default, increase for more messages)
    )

    # Build the project
    app.build(force_all=True)  # force_all is like the -a option, rebuild everything
