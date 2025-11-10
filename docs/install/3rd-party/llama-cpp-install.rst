.. meta::
  :description: Install llama.cpp on ROCm
  :keywords: installation, llama.cpp, docker, deep learning framework, AMD, ROCm, GGML

********************************************************************************
llama.cpp on ROCm installation
********************************************************************************

`llama.cpp <https://github.com/ggml-org/llama.cpp>`__ is an open-source framework 
for Large Language Model (LLM) inference that runs on both central processing units 
(CPUs) and graphics processing units (GPUs). 

This topic covers setup instructions and the necessary files to build, test, and run 
llama.cpp with ROCm support in a Docker environment. To learn more about llama.cpp on ROCm, 
including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/llama-cpp-compatibility`.

.. note::

   llama.cpp is supported on ROCm 7.0.0 and 6.4.x. This topic provides the latest installation 
   instructions for ROCm 7.0.0. For previous versions, see :doc:`previous-versions/llama-cpp-history`.

Install llama.cpp
======================================================================================

To install llama.cpp for ROCm, you have the following options:

* :ref:`using-docker-with-llama-cpp-pre-installed` **(recommended)**
* :ref:`build-llama-cpp-docker-image`

.. note::

   Release ``b6652.amd0`` includes specific optimizations for AMD Instinct™ MI300X and ROCm 7.0.0. 
   Refer to the `AMD ROCm blog <https://rocm.blogs.amd.com/>`__, to search for llama.cpp examples 
   and best practices to optimize your workloads on AMD GPUs.

.. _using-docker-with-llama-cpp-pre-installed:

Use a prebuilt Docker image with llama.cpp pre-installed
--------------------------------------------------------------------------------------

Docker is the recommended method to set up a llama.cpp environment, and it avoids 
potential installation issues. The tested, prebuilt image includes llama.cpp, ROCm, 
and other dependencies.

.. important::

   To follow these instructions, input your chosen tag into ``<TAG>``. Example: ``llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04``.

   Tag endings of ``_full``, ``_server``, and ``_light`` serve different purposes for entrypoints as follows:

   - Full: This image includes both the main executable file and the tools to convert ``LLaMA`` models into ``ggml`` and apply 4-bit quantization.
   - Server: This image only includes the server executable file.
   - Light: This image only includes the main executable file.

   You can download Docker images with specific ROCm, llama.cpp, and operating system versions. 
   See the available tags on `Docker Hub <https://hub.docker.com/r/rocm/llama.cpp/tags>`_ and see :ref:`Docker image support <llama-cpp-docker-support>` below.

1. Download your required public `llama.cpp Docker image <https://hub.docker.com/r/rocm/llama.cpp/tags>`__:

   .. code-block:: bash

      docker pull rocm/llama.cpp:<TAG>_full
      docker pull rocm/llama.cpp:<TAG>_server
      docker pull rocm/llama.cpp:<TAG>_light

2. Launch and connect to the container with the respective entrypoints of your image:

   .. code-block:: bash

      export MODEL_PATH='<your_model_path>'

      # Multi-GPU Setup (for example, an 8-GPU configuration) is required to load DeepSeek-V3-Q4_K_M model and prevent out-of-memory errors
      # Loading the model may take several minutes depending on the hardware configuration

      # To run the 'full' docker image with main executable (--run) and other options
      docker run --privileged \
                 --network=host \
                 --device=/dev/kfd \
                 --device=/dev/dri \
                 --group-add video \
                 --cap-add=SYS_PTRACE \
                 --security-opt seccomp=unconfined \
                 --ipc=host \
                 --shm-size 16G \
                 -v $MODEL_PATH:/data \
                 rocm/llama.cpp:<TAG>_full \
                   --run -m /data/DeepSeek-V3-Q4_K_M-00001-of-00009.gguf \
                   -p "Building a website can be done in 10 simple steps:" -n 512 --n-gpu-layers 999

      # To run the 'server' docker image with the server executable
      docker run --privileged \
                 --network=host \
                 --device=/dev/kfd \
                 --device=/dev/dri \
                 --group-add video \
                 --cap-add=SYS_PTRACE \
                 --security-opt seccomp=unconfined \
                 --ipc=host \
                 --shm-size 16G \
                 -v $MODEL_PATH:/data \
                 rocm/llama.cpp:<TAG>_server \
                   -m /data/DeepSeek-V3-Q4_K_M-00001-of-00009.gguf \
                   --port 8000 --host 0.0.0.0 -n 512 --n-gpu-layers 999

      # To run the 'light' docker image with only the main executable
      docker run --privileged \
                 --network=host \
                 --device=/dev/kfd \
                 --device=/dev/dri \
                 --group-add video \
                 --cap-add=SYS_PTRACE \
                 --security-opt seccomp=unconfined \
                 --ipc=host \
                 --shm-size 16G \
                 -v $MODEL_PATH:/data \
                 rocm/llama.cpp:<TAG>_light \
                   -m /data/DeepSeek-V3-Q4_K_M-00001-of-00009.gguf \
                   -p "Building a website can be done in 10 simple steps:" -n 512 --n-gpu-layers 999

   .. note::

       This will automatically download the image if it does not exist on the host. You can
       also pass the ``-v`` argument to mount any data directories from the host onto the container.

.. _llama-cpp-docker-support:

Docker image support
--------------------------------------------------------------------------------------

AMD validates and publishes ready-made `llama.cpp <https://hub.docker.com/r/rocm/llama.cpp/tags>`__ 
images with ROCm backends on Docker Hub. The following Docker image tags and associated inventories 
are validated for their respective ROCm versions listed below. For ROCm 6.4.x support and version history, 
see :doc:`previous-versions/llama-cpp-history`.

.. tab-set::

   .. tab-item:: ROCm 7.0.0 - Ubuntu 24.04

      .. tab-set::

         .. tab-item:: Full Docker

            Tag
              `rocm/llama.cpp:llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04_full/images/sha256-a94f0c7a598cc6504ff9e8371c016d7a2f93e69bf54a36c870f9522567201f10>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

         .. tab-item:: Server Docker

            Tag
              `rocm/llama.cpp:llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04_server/images/sha256-be175932c3c96e882dfbc7e20e0e834f58c89c2925f48b222837ee929dfc47ee>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

         .. tab-item:: Light Docker

            Tag
              `rocm/llama.cpp:llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6652.amd0_rocm7.0.0_ubuntu24.04_light/images/sha256-d8ba0c70603da502c879b1f8010b439c8e7fa9f6cbdac8bbbbbba97cb41ebc9e>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

   .. tab-item:: ROCm 7.0.0 - Ubuntu 22.04

      .. tab-set::

         .. tab-item:: Full Docker

            Tag
              `rocm/llama.cpp:llama.cpp-b6652.amd0_rocm7.0.0_ubuntu22.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6652.amd0_rocm7.0.0_ubuntu22.04_full/images/sha256-37582168984f25dce636cc7288298e06d94472ea35f65346b3541e6422b678ee>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

         .. tab-item:: Server Docker

            Tag
              `rocm/llama.cpp:llama.cpp-b6652.amd0_rocm7.0.0_ubuntu22.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6652.amd0_rocm7.0.0_ubuntu22.04_server/images/sha256-7e70578e6c3530c6591cc2c26da24a9ee68a20d318e12241de93c83224f83720>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

         .. tab-item:: Light Docker

            Tag
              `rocm/llama.cpp:llama.cpp-b6652.amd0_rocm7.0.0_ubuntu22.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6652.amd0_rocm7.0.0_ubuntu22.04_light/images/sha256-9a5231acf88b4a229677bc2c636ea3fe78a7a80f558bd80910b919855de93ad5>`__

            Inventory
              * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__


.. _build-llama-cpp-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------------

If you want to explore llama.cpp capabilities without being limited to the entrypoints
from the prebuilt Docker images, you have the option to build directly from source inside a
ROCm Ubuntu base Docker image.

The prebuilt base Docker image has all dependencies installed, including:

* ROCm
* hipBlas
* hipBlasLt
* rocWMMA

1. Choose your base Ubuntu Docker image with the correct ROCm version.

+----------------+--------------+----------------------------------------------+
| Ubuntu Version | ROCm Version | Base Image                                   |
+================+==============+==============================================+
| 24.04          | 7.0.0        | ``rocm/dev-ubuntu-24.04:7.0-complete``       |
+----------------+--------------+----------------------------------------------+
| 22.04          | 7.0.0        | ``rocm/dev-ubuntu-22.04:7.0-complete``       |
+----------------+--------------+----------------------------------------------+

2. Start your local container from the base image. The following example uses ``rocm/dev-ubuntu-24.04:7.0-complete``:

   .. code-block:: bash

      export MODEL_PATH='./models'

      docker run -it \
            --name=$(whoami)_llamacpp \
            --privileged --network=host \
            --device=/dev/kfd --device=/dev/dri \
            --group-add video --cap-add=SYS_PTRACE \
            --security-opt seccomp=unconfined \
            --ipc=host --shm-size 16G \
            -v $MODEL_PATH:/data
            rocm/dev-ubuntu-24.04:7.0-complete

Once inside the docker container, run the following steps:

3. Setup your workspace:

   .. code-block:: bash

      apt-get update && apt-get install -y nano libcurl4-openssl-dev cmake git
      mkdir -p /workspace && cd /workspace

4. Clone the `https://github.com/ROCm/llama.cpp <https://github.com/ROCm/llama.cpp>`__ repository:

   .. code-block:: bash

      git clone https://github.com/ROCm/llama.cpp
      cd llama.cpp

5. Set your ROCm architecture:

   To compile for supported microarchitectures, run:
   
   .. code-block:: bash

      export LLAMACPP_ROCM_ARCH=gfx942,gfx90a

   .. note::
   
      To compile for a wide range of microarchitectures, run:

      .. code-block:: bash

         export LLAMACPP_ROCM_ARCH=gfx803,gfx900,gfx906,gfx908,gfx90a,gfx942,gfx1010,gfx1030,gfx1032,gfx1100,gfx1101,gfx1102

6. Build and install llama.cpp:

   .. code-block:: bash

      HIPCXX="$(hipconfig -l)/clang" HIP_PATH="$(hipconfig -R)" \
      cmake -S . -B build -DGGML_HIP=ON -DAMDGPU_TARGETS=$LLAMACPP_ROCM_ARCH \
      -DCMAKE_BUILD_TYPE=Release -DLLAMA_CURL=ON \
      && cmake --build build --config Release -j$(nproc)

Test the llama.cpp installation
================================================================================

llama.cpp unit tests are optional for validating your installation if you used a
prebuilt Docker image from AMD ROCm Docker Hub.

To run unit tests manually and validate your installation fully, follow these steps:

1. To verify that llama.cpp has been successfully installed, run the Docker container as described in :ref:`build-llama-cpp-docker-image`. 

2. Once inside the container, ensure you have access to the Bash shell.

   .. code-block:: bash
   
      cd /workspace/llama.cpp
      ./build/bin/test-backend-ops

.. note::

   Running unit tests requires at least one AMD GPU.

Run a llama.cpp example
================================================================================

The `https://github.com/ROCm/llama.cpp <https://github.com/ROCm/llama.cpp>`__ repository provides the necessary examples that exercise the functionality of your
framework.

You can also search for llama.cpp examples on the `AMD ROCm blog <https://rocm.blogs.amd.com/>`_, 
to find instructions to prepare your model and test the containers.

Two most popular use-cases are:

* **llama-cli**: The main executable to run the model interactively or get a response to a prompt.
* **llama-bench**: Run a benchmark of your model with different configurations.

Main Application: ``llama-cli`` 
--------------------------------------------------------------------------------------

1. Use the CLI tool to start the client:

   .. code-block:: bash

      ./build/bin/llama-cli -m /data/DeepSeek-V3-Q4_K_M/DeepSeek-V3-Q4_K_M-00001-of-00009.gguf -ngl 999

2. A prompt will appear when the client is ready, and you can start interacting with the model using the client:

   .. code-block::

      > hi, who are you?
      Hi! I’m an AI assistant here to help answer your questions, provide information, or just chat with you.
      How can I assist you today? 😊

      > What are the main causes of heart failure?
      Heart failure is a condition in which the heart cannot pump blood effectively to meet the body's needs.
      It can result from various underlying causes or contributing factors.
      The **main causes of heart failure** include:

      ---

      ### 1. **Coronary Artery Disease (CAD)**
         - Narrowing or blockage of the coronary arteries reduces blood flow to the heart muscle, weakening it over time.
         - A heart attack (myocardial infarction) can cause significant damage to the heart muscle, leading to heart failure.

      ---

      ### 2. **High Blood Pressure (Hypertension)**
         - Chronic high blood pressure forces the heart to work harder to pump blood, eventually causing the heart muscle to thicken or weaken.

      ---

      ### 3. **Cardiomyopathy**
         - Diseases of the heart muscle, such as dilated cardiomyopathy, hypertrophic cardiomyopathy, or restrictive cardiomyopathy, can impair the heart's ability to pump effectively.
      ...
      ### 11. **Other Conditions**
         - Thyroid disorders, severe anemia, or infections like myocarditis can also lead to heart failure.

      ---

      ### Prevention and Management

Benchmark Application: ``llama-bench``
--------------------------------------------------------------------------------------

1. Use the CLI tool to start the application:

   .. code-block:: bash

      ./build/bin/llama-bench \
      -m /data/DeepSeek-V3-Q4_K_M/DeepSeek-V3-Q4_K_M-00001-of-00009.gguf \
      -p 16,32,64,96,128,256,512,1024,2048,4096 \
      -n 64,128,256 \
      -ngl 999

2. The result of the command above should be similar to the following when running on a MI300X system:

   .. code-block::

      ggml_cuda_init: GGML_CUDA_FORCE_MMQ:    no
      ggml_cuda_init: GGML_CUDA_FORCE_CUBLAS: no
      ggml_cuda_init: found 8 ROCm devices:
      Device 0: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 1: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 2: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 3: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 4: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 5: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 6: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      Device 7: AMD Instinct MI300X, gfx942:sramecc+:xnack- (0x942), VMM: no, Wave Size: 64
      | model                          |       size |     params | backend    | ngl |            test |                  t/s |
      | ------------------------------ | ---------: | ---------: | ---------- | --: | --------------: | -------------------: |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp16 |        118.10 ± 4.78 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp32 |        153.70 ± 3.11 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp64 |        191.69 ± 1.95 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp96 |        180.58 ± 2.99 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           pp128 |        192.25 ± 3.14 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           pp256 |        318.73 ± 3.79 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           pp512 |        513.29 ± 4.07 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |          pp1024 |        880.58 ± 5.17 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |          pp2048 |       1358.24 ± 2.49 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |          pp4096 |       1650.81 ± 4.47 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            tg64 |         42.94 ± 0.08 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           tg128 |         42.24 ± 0.04 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           tg256 |         41.82 ± 0.10 |

      build: 071e9e45 (6662)

Previous versions
===============================================================================
See :doc:`previous-versions/llama-cpp-history` to find documentation for previous releases
of the ``ROCm/llama.cpp`` Docker image.