.. meta::
  :description: Install FlashInfer on ROCm
  :keywords: installation, docker, FlashInfer, deep learning, AMD, ROCm

********************************************************************************
FlashInfer on ROCm installation
********************************************************************************

.. caution::

	This topic does not reflect the latest version of FlashInfer on ROCm documentation. See :doc:`../flashinfer-install` for the latest version.

`FlashInfer <https://docs.flashinfer.ai/index.html>`__ is a library and kernel generator 
for Large Language Models (LLMs) that provides a high-performance implementation of graphics 
processing units (GPUs) kernels. 

This topic covers setup instructions and the necessary files to build, test, and run 
FlashInfer with ROCm support in a Docker environment. To learn more about FlashInfer on ROCm, 
including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/flashinfer-compatibility`.

.. note::

	FlashInfer is supported on ROCm 6.4.1.

Install FlashInfer on ROCm
======================================================================================

To install FlashInfer on ROCm, you have the following options:

* :ref:`using-docker-with-flashinfer-pre-installed-v259` **(recommended)**
* :ref:`build-flashinfer-rocm-docker-image-v259`
* :ref:`flashinfer-pip-install-v259`

.. _using-docker-with-flashinfer-pre-installed-v259:

Use a prebuilt Docker image with FlashInfer pre-installed
--------------------------------------------------------------------------------------

Docker is the recommended method to set up a FlashInfer environment, as it avoids 
potential installation issues.  The tested, prebuilt image includes FlashInfer, PyTorch, 
ROCm, and other dependencies.

1. Pull the Docker image:

   .. code-block:: bash

      docker pull rocm/flashinfer:flashinfer-0.2.5_rocm6.4_ubuntu24.04_py3.12_pytorch2.7


2. Launch and connect to the container:

   .. code-block:: bash

      docker run -it --rm \
      --privileged -v ./:/app \
      --network=host --device=/dev/kfd \
      --device=/dev/dri --group-add video \
      --name=my_flashinfer --cap-add=SYS_PTRACE \
      --security-opt seccomp=unconfined \
      --ipc=host --shm-size 16G \
      rocm/flashinfer:flashinfer-0.2.5_rocm6.4_ubuntu24.04_py3.12_pytorch2.7


.. _build-flashinfer-rocm-docker-image-v259:

Build your own Docker image
--------------------------------------------------------------------------------------

FlashInfer supports the ROCm platform and can be run directly by setting up a Docker container from scratch. 
A Dockerfile is provided in the `https://github.com/ROCm/flashinfer <https://github.com/ROCm/flashinfer>`__ repository to help you get started.

1. Clone the `https://github.com/ROCm/flashinfer <https://github.com/ROCm/flashinfer>`__ repository:

   .. code-block:: bash
      
      git clone https://github.com/ROCm/flashinfer.git

2. Enter the directory and build the Dockerfile:
   
   .. code-block:: bash
      
      cd flashinfer
      docker build -t rocm/flashinfer:flashinfer-0.2.5_rocm6.4_ubuntu24.04_py3.12_pytorch2.7

3. Run the Docker container:

   .. code-block:: bash
      
      docker run -it --device=/dev/kfd --device=/dev/dri --group-add video rocm/flashinfer:flashinfer-0.2.5_rocm6.4_ubuntu24.04_py3.12_pytorch2.7

4. The above step will create a Docker container with FlashInfer pre-installed. During this process, the Dockerfile will have pre-installed and setup a micromamba environment named ``flashinfer-py3.12-torch2.7.1-rocm6.4.1``.

.. _flashinfer-pip-install-v259:

Install FlashInfer using pip
--------------------------------------------------------------------------------------

Use a base PyTorch Docker image and follow these steps to install FlashInfer using pip.  

1. Pull the base ROCm PyTorch Docker image:

   .. code-block:: bash

      docker pull rocm/pytorch:rocm6.4.1_ubuntu24.04_py3.12_pytorch_release_2.7.1
   
2. Change the ``<container name>`` and then use the following command:

   .. code-block:: bash
      
      docker run -it --privileged --network=host --device=/dev/kfd --device=/dev/dri --group-add video --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --ipc=host --shm-size 128G --name=<container name> rocm/pytorch:rocm6.4.1_ubuntu24.04_py3.12_pytorch_release_2.7.1

3. After setting up the container, install FlashInfer from the AMD-hosted `PyPI repository <https://pypi.amd.com/simple/>`__.

   .. code-block:: bash

      pip install flashinfer==0.2.5.post10 --extra-index-url=https://pypi.amd.com/simple


Test the FlashInfer installation
======================================================================================

Once you have the Docker container running, start using FlashInfer by following these steps:

1. Activate the micromamba environment:

   .. note::

      If you followed :ref:`flashinfer-pip-install`, you do not need to activate the micromamba environment.
      If you followed :ref:`using-docker-with-flashinfer-pre-installed` or :ref:`build-flashinfer-rocm-docker-image`, don't forget this step.

   .. code-block:: bash
      
      micromamba activate flashinfer-py3.12-torch2.7.1-rocm6.4.1

2. Enter the FlashInfer directory:

   .. note::

      If you followed :ref:`flashinfer-pip-install`, ensure you git clone the repository first.

      .. code-block:: bash
         
         git clone https://github.com/ROCm/flashinfer.git 

   .. code-block:: bash
      
      cd flashinfer/
   
3. Run the example provided in the ``flashinfer/examples`` directory. This example runs ``Batch Decode`` and then verifies the output. 

   .. code-block:: bash

      python examples/test_batch_decode_example.py

3. If FlashInfer was installed correctly, you should see the following output:
   
   .. code-block:: bash

      PASS

4. The above output indicates that FlashInfer is installed correctly. You can now use FlashInfer in your projects.


Run a FlashInfer example
======================================================================================

The `https://github.com/ROCm/flashinfer <https://github.com/ROCm/flashinfer>`__ repository has example code that you can run FlashInfer with.
You can save the following code snippet to a Python script once you have FlashInfer installed and run the script to try it out.

1. Save the following code snippet:

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

2. Save it to a Python script by renaming ``<example_name>``:

   .. code-block:: bash

      python <example_name>.py

3. Run the script to use FlashInfer.

