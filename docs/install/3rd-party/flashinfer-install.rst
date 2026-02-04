.. meta::
  :description: Install FlashInfer on ROCm
  :keywords: installation, docker, FlashInfer, deep learning, AMD, ROCm

********************************************************************************
FlashInfer on ROCm installation
********************************************************************************

`FlashInfer <https://docs.flashinfer.ai/index.html>`__ is a library and kernel generator 
for Large Language Models (LLMs) that provides a high-performance implementation of graphics 
processing units (GPUs) kernels. 

This topic covers setup instructions and the necessary files to build, test, and run 
FlashInfer with ROCm support in a Docker environment. To learn more about FlashInfer on ROCm, 
including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/flashinfer-compatibility`.

.. note::

   FlashInfer is supported on ROCm 7.1.1 and 6.4.1. This topic provides the latest installation 
   instructions for ROCm 7.1.1. For 6.4.1, see :doc:`previous-versions/flashinfer-history`.

Install FlashInfer on ROCm
======================================================================================

To install FlashInfer on ROCm, you have the following options:

* :ref:`using-docker-with-flashinfer-pre-installed` **(recommended)**
* :ref:`flashinfer-pip-install`
* :ref:`build-flashinfer-rocm-docker-image`

.. _using-docker-with-flashinfer-pre-installed:

Use a prebuilt Docker image with FlashInfer pre-installed
--------------------------------------------------------------------------------------

Docker is the recommended method to set up a FlashInfer environment, as it avoids 
potential installation issues.  The tested, prebuilt image includes FlashInfer, PyTorch, 
ROCm, and other dependencies.

1. Pull the Docker image.

   .. code-block:: bash

      docker pull rocm/flashinfer:flashinfer-0.2.5.amd2_rocm7.1.1_ubuntu24.04_py3.12_pytorch2.8

2. Start a Docker container using the image.

   .. code-block:: bash

      docker run -it --rm \
      --privileged \
      --network=host --device=/dev/kfd \
      --device=/dev/dri --group-add video \
      --name=my_flashinfer --cap-add=SYS_PTRACE \
      --security-opt seccomp=unconfined \
      --ipc=host --shm-size 16G \
      rocm/flashinfer:flashinfer-0.2.5.amd2_rocm7.1.1_ubuntu24.04_py3.12_pytorch2.8

3. The above step will create a Docker container with FlashInfer pre-installed. During this process, the Dockerfile will have a pre-installed and setup micromamba environment with FlashInfer available inside. To use FlashInfer, activate the micromamba environment.

   .. code-block:: bash

      micromamba activate base


.. _flashinfer-pip-install:

Install FlashInfer using pip
--------------------------------------------------------------------------------------

Use a base PyTorch Docker image and follow these steps to install FlashInfer using pip.  

1. Pull the base ROCm PyTorch Docker image.

   .. code-block:: bash

      docker pull rocm/pytorch:rocm7.1.1_ubuntu24.04_py3.12_pytorch_release_2.8.0

2. Start a Docker container using the image.

   .. code-block:: bash

      docker run -it --rm \
      --privileged \
      --network=host --device=/dev/kfd \
      --device=/dev/dri --group-add video \
      --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
      --ipc=host --shm-size 128G \
      rocm/pytorch:rocm7.1.1_ubuntu24.04_py3.12_pytorch_release_2.8.0

3. After setting up the container, install FlashInfer from the AMD-hosted `PyPI repository <https://pypi.amd.com/rocm-7.1.1/simple/amd-flashinfer/>`__.

   .. code-block:: bash

      pip install amd-flashinfer --extra-index-url https://pypi.amd.com/rocm-7.1.1/simple

.. _build-flashinfer-rocm-docker-image:

Build from source
--------------------------------------------------------------------------------------

FlashInfer supports the ROCm platform and can be run directly by setting up a Docker container from scratch. 
A Dockerfile is provided in the `https://github.com/ROCm/flashinfer <https://github.com/ROCm/flashinfer/blob/amd-integration/.devcontainer/rocm/Dockerfile>`__ repository to help you get started.

1. Clone the `https://github.com/ROCm/flashinfer <https://github.com/ROCm/flashinfer>`__ repository.

   .. code-block:: bash
      
      git clone https://github.com/ROCm/flashinfer.git

2. Enter the directory and build the Dockerfile to create a Docker image.
   
   .. code-block:: bash
      
      cd flashinfer
      docker build \
      --build-arg USERNAME=$USER \
      --build-arg USER_UID=$(id -u) \
      --build-arg USER_GID=$(id -g) \
      -f .devcontainer/rocm/Dockerfile \
      -t rocm-flashinfer-dev .

3. Start a Docker container using the image.

   .. code-block:: bash
      
      docker run -it --rm \
      --privileged --network=host --device=/dev/kfd \
      --device=/dev/dri --group-add video \
      --cap-add=SYS_PTRACE \
      --security-opt seccomp=unconfined \
      --ipc=host --shm-size 16G \
      -v $PWD:/workspace \
      rocm-flashinfer-dev

4. Once you are inside the container, the micromamba environment is automatically activated. You can now install FlashInfer inside it.

   .. code-block:: bash

      cd /workspace
      FLASHINFER_HIP_ARCHITECTURES=gfx942 python -m pip wheel . --wheel-dir=./dist/ --no-deps --no-build-isolation -v
      cd dist && pip install amd_flashinfer-*.whl


Test the FlashInfer installation
======================================================================================

Once you have installed FlashInfer, run the following command. If it outputs ``0.2.5+amd.2``, then FlashInfer is installed correctly. You can now use FlashInfer in your projects.

.. code-block:: bash

   python -c "import flashinfer; print(flashinfer.__version__)"

Run a FlashInfer example
======================================================================================

The `https://github.com/ROCm/flashinfer <https://github.com/ROCm/flashinfer/tree/amd-integration/examples>`_ repository has example code that you can run FlashInfer with.
You can save the following code snippet to a Python script once you have FlashInfer installed and run the script to try it out.

1. Save the following code snippet to a Python script named ``flashinfer_example.py``.

   .. code-block:: bash

      import torch
      import flashinfer

      kv_len = 2048
      num_kv_heads = 32
      head_dim = 128

      k = torch.randn(kv_len, num_kv_heads, head_dim).half().to(0)
      v = torch.randn(kv_len, num_kv_heads, head_dim).half().to(0)

      # decode attention

      num_qo_heads = 32
      q = torch.randn(num_qo_heads, head_dim).half().to(0)

      o = flashinfer.single_decode_with_kv_cache(q, k, v) # decode attention without RoPE on-the-fly
      o_rope_on_the_fly = flashinfer.single_decode_with_kv_cache(q, k, v, pos_encoding_mode="ROPE_LLAMA") # decode with LLaMA style RoPE on-the-fly

2. Run the script to use FlashInfer.

   .. code-block:: bash

      python flashinfer_example.py

Previous versions
===============================================================================
See :doc:`previous-versions/flashinfer-history` to find documentation for previous releases
of the ``ROCm/flashinfer`` Docker image.
