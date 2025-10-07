.. meta::
  :description: Install llama.cpp on ROCm
  :keywords: installation, llama.cpp, docker, deep learning, AMD, ROCm, GGML

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

  llama.cpp is supported on ROCm 7.0.0 and 6.4.x. This guide provides installation 
  instructions on ROCm 7.0.0, 6.4.3, 6.4.2 and 6.4.1. For ROCm 6.4.0, see :doc:`previous-versions/llama-cpp-history`.

Install llama.cpp
======================================================================================

To install llama.cpp for ROCm, you have the following options:

* :ref:`using-docker-with-llama-cpp-pre-installed` **(recommended)**
* :ref:`build-llama-cpp-docker-image`

.. _using-docker-with-llama-cpp-pre-installed:

Use a prebuilt Docker image with llama.cpp pre-installed
--------------------------------------------------------------------------------------

Docker is the recommended method to set up a llama.cpp environment, and it avoids 
potential installation issues. The tested, prebuilt image includes llama.cpp, ROCm, 
and other dependencies.

.. important::

   To follow these instructions, input your chosen tag into ``<TAG>``. Example: ``llama.cpp-b6356_rocm7.0.0_ubuntu24.04``.

   Tag endings of ``_full``, ``_server``, and ``_light`` serve different purposes for entrypoints as follows:

   - Full: This image includes both the main executable file and the tools to convert ``LLaMA`` models into ``ggml`` and convert into 4-bit quantization.
   - Server: This image only includes the server executable file.
   - Light: This image only includes the main executable file.

   You can download Docker images with specific ROCm, llama.cpp, and operating system versions. 
   See the available tags on `Docker Hub <https://hub.docker.com/r/rocm/llama.cpp/tags>`_ and see :ref:`docker image support <llama-cpp-docker-support>` below.

1. Download your required public `llama.cpp Docker image <https://hub.docker.com/r/rocm/llama.cpp/tags>`__:

   .. code-block:: bash

      docker pull rocm/llama.cpp:<TAG>_full
      docker pull rocm/llama.cpp:<TAG>_server
      docker pull rocm/llama.cpp:<TAG>_light

2. Launch and connect to the container with the respective entrypoints of your image:

   .. code-block:: bash

      export MODEL_PATH='<your_model_path>'

      # Multi-GPU Setup (e.g. 8-GPU) is required to load DeepSeek-V3-Q4_K_M model to avoid out-of-memory errors
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

AMD validates and publishes ready-made `llama.cpp <https://hub.docker.com/r/rocm/llama.cpp>`__ images
with ROCm backends on Docker Hub. The following Docker image tags and associated inventories are
validated for their respective ROCm version below. For `ROCm 6.4.0 
<https://repo.radeon.com/rocm/apt/6.4/>`__ support and Docker images, see :doc:`previous-versions/llama-cpp-history`.


.. tab-set::

   .. tab-item:: ROCm 7.0.0

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm7.0.0_ubuntu24.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm7.0.0_ubuntu24.04_full/images/sha256-a2ecd635eaa65bb289a9041330128677f3ae88bee6fee0597424b17e38d4903c>`__

                  Inventory
                    * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm7.0.0_ubuntu24.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm7.0.0_ubuntu24.04_server/images/sha256-cb46b47df415addb5ceb6e6fdf0be70bf9d7f6863bbe6e10c2441ecb84246d52>`__

                  Inventory
                    * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm7.0.0_ubuntu24.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm7.0.0_ubuntu24.04_light/images/sha256-8f8536eec4b05c0ff1c022f9fc6c527ad1c89e6c1ca0906e4d39e4de73edbde9>`__

                  Inventory
                    * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

         .. tab-item:: Ubuntu 22.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm7.0.0_ubuntu22.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm7.0.0_ubuntu22.04_full/images/sha256-f36de2a3b03ae53e81c85422cb3780368c9891e1ac7884b04403a921fe2ea45d>`__

                  Inventory
                    * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm7.0.0_ubuntu22.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm7.0.0_ubuntu22.04_server/images/sha256-df15e8ab11a6837cd3736644fec1e047465d49e37d610ab0b79df000371327df>`__

                  Inventory
                    * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm7.0.0_ubuntu22.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm7.0.0_ubuntu22.04_light/images/sha256-4ea2d5bb7964f0ee3ea9b30ba7f343edd6ddfab1b1037669ca7eafad2e3c2bd7>`__

                  Inventory
                    * `ROCm 7.0.0 <https://repo.radeon.com/rocm/apt/7.0/>`__

   .. tab-item:: ROCm 6.4.3

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.3_ubuntu24.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.3_ubuntu24.04_full/images/sha256-5960fc850024a8a76451f9eaadd89b7e59981ae9f393b407310c1ddf18892577>`__

                  Inventory
                    * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.3_ubuntu24.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.3_ubuntu24.04_server/images/sha256-1b79775d9f546065a6aaf9ca426e1dd4ed4de0b8f6ee83687758cc05af6538e6>`__

                  Inventory
                    * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.3_ubuntu24.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.3_ubuntu24.04_light/images/sha256-8f863c4c2857ae42bebd64e4f1a0a1e7cc3ec4503f243e32b4a4dcad070ec361>`__

                  Inventory
                    * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__

         .. tab-item:: Ubuntu 22.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.3_ubuntu22.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.3_ubuntu22.04_full/images/sha256-888879b3ee208f9247076d7984524b8d1701ac72611689e89854a1588bec9867>`__

                  Inventory
                    * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.3_ubuntu22.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.3_ubuntu22.04_server/images/sha256-90e4ff99a66743e33fd00728cd71a768588e5f5ef355aaa196669fe65ac70672>`__

                  Inventory
                    * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.3_ubuntu22.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.3_ubuntu22.04_light/images/sha256-bd447a049939cb99054f8fbf3f2352870fe906a75e2dc3339c845c08b9c53f9b>`__

                  Inventory
                    * `ROCm 6.4.3 <https://repo.radeon.com/rocm/apt/6.4.3/>`__

   .. tab-item:: ROCm 6.4.2

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.2_ubuntu24.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.2_ubuntu24.04_full/images/sha256-5b3a1bc4889c1fcade434b937fbf9cc1c22ff7dc0317c130339b0c9238bc88c4>`__

                  Inventory
                    * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.2_ubuntu24.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.2_ubuntu24.04_server/images/sha256-5228ff99d0f627a9032d668f4381b2e80dc1e301adc3e0821f26d8354b175271>`__

                  Inventory
                    * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.2_ubuntu24.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.2_ubuntu24.04_light/images/sha256-b12723b332a826a89b7252dddf868cbe4d1a869562fc4aa4032f59e1a683b968>`__

                  Inventory
                    * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__

         .. tab-item:: Ubuntu 22.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.2_ubuntu22.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.2_ubuntu22.04_full/images/sha256-cd6e21a6a73f59b35dd5309b09dd77654a94d783bf13a55c14eb8dbf8e9c2615>`__

                  Inventory
                    * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.2_ubuntu22.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.2_ubuntu22.04_server/images/sha256-c2b4689ab2c47e6626e8fea22d7a63eb03d47c0fde9f5ef8c9f158d15c423e58>`__

                  Inventory
                    * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.2_ubuntu22.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.2_ubuntu22.04_light/images/sha256-1acc28f29ed87db9cbda629cb29e1989b8219884afe05f9105522be929e94da4>`__

                  Inventory
                    * `ROCm 6.4.2 <https://repo.radeon.com/rocm/apt/6.4.2/>`__

   .. tab-item:: ROCm 6.4.1

      .. tab-set::

         .. tab-item:: Ubuntu 24.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.1_ubuntu24.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.1_ubuntu24.04_full/images/sha256-2f8ae8a44510d96d52dea6cb398b224f7edeb7802df7ec488c6f63d206b3cdc9>`__

                  Inventory
                    * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.1_ubuntu24.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.1_ubuntu24.04_server/images/sha256-fece497ff9f4a28b12f645de52766941da8ead8471aa1ea84b61d4b4568e51f2>`__

                  Inventory
                    * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.1_ubuntu24.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.1_ubuntu24.04_light/images/sha256-3e14352fa6f8c6128b23cf9342531c20dbfb522550b626e09d83b260a1947022>`__

                  Inventory
                    * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`__

         .. tab-item:: Ubuntu 22.04

            .. tab-set::

               .. tab-item:: Full Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.1_ubuntu22.04_full <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.1_ubuntu22.04_full/images/sha256-80763062ef0bec15038c35fd01267f1fc99a5dd171d4b48583cc668b15efad69>`__

                  Inventory
                    * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`__

               .. tab-item:: Server Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.1_ubuntu22.04_server <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.1_ubuntu22.04_server/images/sha256-db2a6c957555ed83b819bbc54aea884a93192da0fb512dae63d32e0dc4e8ab8f>`__

                  Inventory
                    * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`__

               .. tab-item:: Light Docker

                  Tag
                    `rocm/llama.cpp:llama.cpp-b6356_rocm6.4.1_ubuntu22.04_light <https://hub.docker.com/layers/rocm/llama.cpp/llama.cpp-b6356_rocm6.4.1_ubuntu22.04_light/images/sha256-c6dbb07cc655fb079d5216e4b77451cb64a9daa0585d23b6fb8b32cb22021197>`__

                  Inventory
                    * `ROCm 6.4.1 <https://repo.radeon.com/rocm/apt/6.4.1/>`__


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
| 24.04          | 6.4.3        | ``rocm/dev-ubuntu-24.04:6.4.3-complete``     |
+----------------+--------------+----------------------------------------------+
| 22.04          | 6.4.3        | ``rocm/dev-ubuntu-22.04:6.4.3-complete``     |
+----------------+--------------+----------------------------------------------+
| 24.04          | 6.4.2        | ``rocm/dev-ubuntu-24.04:6.4.2-complete``     |
+----------------+--------------+----------------------------------------------+
| 22.04          | 6.4.2        | ``rocm/dev-ubuntu-22.04:6.4.2-complete``     |
+----------------+--------------+----------------------------------------------+
| 24.04          | 6.4.1        | ``rocm/dev-ubuntu-24.04:6.4.1-complete``     |
+----------------+--------------+----------------------------------------------+
| 22.04          | 6.4.1        | ``rocm/dev-ubuntu-22.04:6.4.1-complete``     |
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
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp16 |         47.71 ± 1.50 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp32 |         72.22 ± 0.76 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp64 |        111.48 ± 2.64 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            pp96 |        148.84 ± 1.22 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           pp128 |        180.11 ± 1.54 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           pp256 |        290.04 ± 1.37 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           pp512 |        439.14 ± 1.68 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |          pp1024 |        439.02 ± 1.61 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |          pp2048 |        432.00 ± 2.87 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |          pp4096 |        420.19 ± 0.62 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |            tg64 |         37.36 ± 0.03 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           tg128 |         37.04 ± 0.02 |
      | deepseek2 671B Q4_K - Medium   | 376.65 GiB |   671.03 B | ROCm       | 999 |           tg256 |         36.53 ± 0.01 |

      build: 66906cd8 (5997)

Previous versions
===============================================================================
See :doc:`previous-versions/llama-cpp-history` to find documentation for previous releases
of the ``ROCm/llama.cpp`` Docker image.