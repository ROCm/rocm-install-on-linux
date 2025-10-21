.. meta::
  :description: Install Megablocks on ROCm
  :keywords: installation, docker, Megablocks, deep learning, AMD, ROCm

********************************************************************************
Megablocks on ROCm installation
********************************************************************************

`Megablocks <https://github.com/databricks/megablocks>`__ is a lightweight library 
for mixture-of-experts `(MoE) <https://huggingface.co/blog/moe>`__ training. 

This topic covers setup instructions and the necessary files to build, test, and run 
Megablocks with ROCm support in a Docker environment. To learn more about Megablocks on ROCm, 
including its use cases, recommendations, as well as hardware and software compatibility, 
see :doc:`rocm:compatibility/ml-compatibility/megablocks-compatibility`.

.. note::

	Megablocks is supported on ROCm 6.3.0.

Install Megablocks
======================================================================================

To install Megablocks on ROCm, you have the following options:

* :ref:`using-docker-with-megablocks-pre-installed` **(recommended)**
* :ref:`build-megablocks-rocm-docker-image`

.. _using-docker-with-megablocks-pre-installed:

Use a prebuilt Docker image with Megablocks pre-installed
--------------------------------------------------------------------------------------

Docker is the recommended method to set up a Megablocks environment, as it avoids potential installation issues.  
The tested, prebuilt image includes Megablocks, PyTorch, ROCm, and other dependencies.

1. Pull the Docker image

   .. code-block:: bash

      docker pull rocm/megablocks:megablocks-0.7.0_rocm6.3.0_ubuntu24.04_py3.12_pytorch2.4.0


2. Launch and connect to the container

   .. code-block:: bash

      docker run -it --rm \
      --privileged -v ./:/app \
      --network=host --device=/dev/kfd \
      --device=/dev/dri --group-add video \
      --name=my_megablocks --cap-add=SYS_PTRACE \
      --security-opt seccomp=unconfined \
      --ipc=host --shm-size 16G \
      rocm/megablocks:megablocks-0.7.0_rocm6.3.0_ubuntu24.04_py3.12_pytorch2.4.0

.. _build-megablocks-rocm-docker-image:

Build your own Docker image
--------------------------------------------------------------------------------------

Megablocks supports the ROCm platform and can be run directly by setting up a Docker container from scratch. 
A Dockerfile is provided in the `https://github.com/ROCm/megablocks <https://github.com/ROCm/megablocks>`_ repository to help you get started.

1. Clone the `https://github.com/ROCm/megablocks <https://github.com/ROCm/megablocks>`_ repository

   .. code-block:: bash
      
      git clone https://github.com/ROCm/megablocks.git

2. Enter the directory and build the docker file

   .. code-block:: bash
      
      cd megablocks
      docker build -t rocm/megablocks:megablocks-0.7.0_rocm6.3.0_ubuntu24.04_py3.12_pytorch2.4.0

3. Run the docker container

   .. code-block:: bash
      
      docker run -it --device=/dev/kfd --device=/dev/dri --group-add video rocm/megablocks:megablocks-0.7.0_rocm6.3.0_ubuntu24.04_py3.12_pytorch2.4.0

Set up your datasets
======================================================================================

You can use the `gpt2_125m_8gpu.sh script <https://github.com/ROCm/megablocks/blob/main/exp/gpt2/gpt2_125m_8gpu.sh>`_ to run the Megablocks training process.
If you are working with other model sizes, the process is similar, but you will need to use a different script.

1. Once you are inside the Megablocks Directory, you can download the BooksCorpus dataset or Oscar dataset by utilizing the helper scripts stored in the dataset directory:
   
   * Oscar dataset
   * gpt2-vocab.json
   * gpt2-merges.txt

   .. code-block:: bash

      cd third_party/Stanford-Megatron-LM/tools
      wget https://huggingface.co/bigscience/misc-test-data/resolve/main/stas/oscar-1GB.jsonl.xz
      xz -d oscar-1GB.jsonl.xz
      wget -O gpt2-vocab.json https://huggingface.co/openai-community/gpt2/resolve/main/vocab.json
      wget -O gpt2-merges.txt https://huggingface.co/mkhalifa/gpt2-biographies/resolve/main/merges.txt


2. Pre-process the datasets 

   .. code-block:: bash

      export BASE_SRC_PATH=$(dirname $(pwd))
      export BASE_DATA_PATH=${BASE_SRC_PATH}/tools
      python preprocess_data.py \
      --input ${BASE_DATA_PATH}/oscar-1GB.jsonl \
      --output-prefix ${BASE_DATA_PATH}/my-gpt2 \
      --vocab-file ${BASE_DATA_PATH}/gpt2-vocab.json \
      --dataset-impl mmap \
      --tokenizer-type GPT2BPETokenizer \
      --merge-file ${BASE_DATA_PATH}/gpt2-merges.txt \
      --append-eod \
      --workers 8 \
      --chunk-size 10

3. Set up the pre-training script

   Edit the ``exp/gpt2/gpt2_125m_8gpu.sh`` script inside the project root directory: 

   .. code-block:: bash

      DATA_PATH=${BASE_DATA_PATH}/my-gpt2_text_document
      CHECKPOINT_PATH=${BASE_DATA_PATH}/checkpoints
      VOCAB_FILE=${BASE_DATA_PATH}/gpt2-vocab.json
      MERGE_FILE=${BASE_DATA_PATH}/gpt2-merges.txt

4. Run the pre-training script

   From the project root directory, execute the following command:

   .. code-block:: bash

      ./exp/gpt2/gpt2_125m_8gpu.sh | tee train.log


Test the Megablocks installation
======================================================================================

Megablocks unit tests are optional for validating your installation if you used a
prebuilt Docker image from AMD ROCm Docker Hub.

To run unit tests manually and validate your installation fully, follow these steps:

.. note::

   Run the following from the Stanford Megatron-LM root. Running the unit tests requires 8 GPUs as they test for distributed functionality. 

.. code-block:: bash
   
   pytest -m gpu /root/megablocks/tests/ 2>&1 | tee "megablocks_test.log"


Run a Megablocks example
======================================================================================

Recommended example: ``pretraining_gpt.sh``.
For detailed steps, refer to the `Efficient MoE training on AMD ROCm: How-to use Megablocks on AMD GPUs blog <https://rocm.blogs.amd.com/artificial-intelligence/megablocks/README.html>`_.
