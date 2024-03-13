.. meta::
  :description: PyTorch with ROCm
  :keywords: installation instructions, PyTorch, AMD, ROCm

**********************************************************************************
PyTorch for ROCm
**********************************************************************************

`PyTorch <https://pytorch.org/>`_ is an open-source tensor library designed for deep learning. PyTorch on
ROCm provides mixed-precision and large-scale training using our
`MIOpen <https://github.com/ROCmSoftwarePlatform/MIOpen>`_ and
`RCCL <https://github.com/ROCmSoftwarePlatform/rccl>`_ libraries.



Installation (Pip)
------------------

PyTorch supports the ROCm platform by providing pre-built wheels packages for a variety of PyTorch and ROCm versions. To install the
latest version:

* Navigate to `pytorch.org/get-started/locally/ <https://pytorch.org/get-started/locally/>`_.
* Select ``Stable``, ``Linux``, ``Pip``, ``Python``, and ``ROCm``

You should see ``pip3 install`` commmand

.. code-block:: shell

    pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/rocm5.7

.. Note::

   You should use a virtual environment when installing python packages in order to separate dependencies
   from the system and other projects.

Additional Versions
...................

In addition to the latest stable version, you can also install new, preview versions, as well as older versions.

* Preview (Nightly): Select ``Preview (Nightly)`` from the `installation matrix <https://pytorch.org/get-started/locally/>`_

* Previous versions: You can search for previous versions on `PyTorch's docs here <https://pytorch.org/get-started/previous-versions/>`_

  Make sure to search for the appropriate ROCm version

Other Package Managers
......................

You can also use more sophisticated dependency management tools like PDM and Poetry. These tools provide several benefits over ``pip``, including
automatic creation of virtual environments, complex dependency resolution, lockfiles, and more.

`PDM <https://pdm-project.org/latest/>`_
++++++++++++++++++++++++++++++++++++++++++++++

* Add the ``index-url`` from above as a `source <https://pdm-project.org/latest/usage/config/#configure-the-package-indexes>`_ by adding the following lines to your ``pyproject.toml`` file:

  .. code-block::

     [[tool.pdm.source]]
     name = "torch-index"       # You can give this any name
     url = "https://download.pytorch.org/whl/rocm5.7/"

* Add dependencies

  .. code-block:: shell

     pdm add torch ...

PDM will then first look in the proided source to install any package, before falling back to `pypi.org <pypi.org>`_.

`Poetry <https://python-poetry.org/docs/>`_
++++++++++++++++++++++++++++++++++++++++++++


* Add the ``index-url`` from above as a `source <https://python-poetry.org/docs/dependency-specification/#source-dependencies>`_:

  .. code-block::

     poetry source add torch-index https://download.pytorch.org/whl/rocm5.7

* Add dependencies, and specify the source:

  .. code-block::

     poetry add torch --source torch-index

Install From Source
--------------------

If a pre-built wheel is not available to match your specific Python, PyTorch, and ROCm versions,
you can build and install PyTorch from source. See the `official build instructions <https://github.com/pytorch/pytorch#from-source>`_ for details.
