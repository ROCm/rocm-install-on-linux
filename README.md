# ROCm installation documentation (Linux)

This repository contains installation instructions for ROCm on Linux, along with installation-related information.

For Windows-related installation information (HIP SDK), refer to the [Windows installation GitHub repository](https://github.com/ROCm/rocm-install-on-windows) or the [ROCm docs Windows install page](https://rocm.docs.amd.com/projects/install-on-windows/en/latest/).

## Building our documentation

For a quick-start build, use the following code. For more options and detail, refer to
[Building documentation](https://rocm.docs.amd.com/en/latest/contribute/building.html).

```bash
cd docs

pip3 install -r sphinx/requirements.txt

python3 -m sphinx -T -E -b html -d _build/doctrees -D language=en . _build/html
```

## Build Using PDM

Alternatively, you can use [`pdm`] to manage the build environment.

Ensure [`pdm` is installed](https://pdm-project.org/latest/#installation)

* Create venv, install build requirements: `pdm install`
* Build the docs: `pdm run inv build`

Now you can open `docs/_build/html/index.html` in your browser
