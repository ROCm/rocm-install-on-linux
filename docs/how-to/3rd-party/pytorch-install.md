# Installing PyTorch for ROCm

[PyTorch](https://pytorch.org/) is an open-source tensor library designed for deep learning. PyTorch on
ROCm provides mixed-precision and large-scale training using our
[MIOpen](https://github.com/ROCmSoftwarePlatform/MIOpen) and
[RCCL](https://github.com/ROCmSoftwarePlatform/rccl) libraries.

To install [PyTorch for ROCm](https://pytorch.org/blog/pytorch-for-amd-rocm-platform-now-available-as-python-package/), you have the following options:

* [Use a Docker image with PyTorch pre-installed](#using-a-docker-image-with-pytorch-pre-installed)
  (recommended)
* [Use a wheels package](#using-a-wheels-package)
* [Use the PyTorch ROCm base Docker image](#using-the-pytorch-rocm-base-docker-image)
* [Use the PyTorch upstream Docker file](#using-the-pytorch-upstream-docker-file)

For hardware, software, and third-party framework compatibility between ROCm and PyTorch, refer to:

* [GPU and OS support (Linux)](../about/compatibility/linux-support.md)
* [Compatibility](../about/compatibility/3rd-party-support-matrix.md)

## Using a Docker image with PyTorch pre-installed

1. Download the latest public PyTorch Docker image
   ([https://hub.docker.com/r/rocm/pytorch](https://hub.docker.com/r/rocm/pytorch)).

   ```bash
   docker pull rocm/pytorch:latest
   ```

   You can also download a specific and supported configuration with different user-space ROCm
   versions, PyTorch versions, and operating systems.

2. Start a Docker container using the image.

   ```bash
   docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
   --device=/dev/kfd --device=/dev/dri --group-add video \
   --ipc=host --shm-size 8G rocm/pytorch:latest
   ```

   :::{note}
   This will automatically download the image if it does not exist on the host. You can also pass the `-v`
   argument to mount any data directories from the host onto the container.
   :::

(install_pytorch_wheels)=

## Using a wheels package

PyTorch supports the ROCm platform by providing tested wheels packages. To access this feature, go
to [https://pytorch.org/get-started/locally/](https://pytorch.org/get-started/locally/). For the correct
wheels command, you must select 'Linux', 'Python', 'pip', and 'ROCm' in the matrix.

1. Choose one of the following three options:

   **Option 1:**

   a. Download a base Docker image with the correct user-space ROCm version.
   | Base OS         | Docker image                   | Link to Docker image|
   |----------------|-----------------------------|----------------|
   | Ubuntu 20.04 | `rocm/dev-ubuntu-20.04` | [https://hub.docker.com/r/rocm/dev-ubuntu-20.04](https://hub.docker.com/r/rocm/dev-ubuntu-20.04)
   | Ubuntu 22.04 | `rocm/dev-ubuntu-22.04` | [https://hub.docker.com/r/rocm/dev-ubuntu-22.04](https://hub.docker.com/r/rocm/dev-ubuntu-22.04)
   | CentOS 7        | `rocm/dev-centos-7` | [https://hub.docker.com/r/rocm/dev-centos-7](https://hub.docker.com/r/rocm/dev-centos-7)

   b. Pull the selected image.

   ```bash
   docker pull rocm/dev-ubuntu-20.04:latest
   ```

   c. Start a Docker container using the downloaded image.

   ```bash
   docker run -it --device=/dev/kfd --device=/dev/dri --group-add video rocm/dev-ubuntu-20.04:latest
   ```

   **Option 2:**

   Select a base OS Docker image (Check [OS compatibility](../about/compatibility/linux-support.md))

   Pull selected base OS image (Ubuntu 20.04 for example)

   ```docker
   docker pull ubuntu:20.04
   ```

   Start a Docker container using the downloaded image

   ```docker
   docker run -it --device=/dev/kfd --device=/dev/dri --group-add video ubuntu:20.04
   ```

   Install ROCm using the directions in the [Installation section](./linux/install.md).

   **Option 3:**

   Install on bare metal. Check [OS compatibility](../about/compatibility/linux-support.md) and install ROCm using the
   directions in the [Installation section](./linux/install.md).

2. Install the required dependencies for the wheels package.

   ```bash
   sudo apt update
   sudo apt install libjpeg-dev python3-dev python3-pip
   pip3 install wheel setuptools
   ```

3. Install `torch`, `torchvision`, and `torchaudio`, as specified in the
   [installation matrix](https://pytorch.org/get-started/locally/).

   :::{note}
   The following command uses the ROCm 5.6 PyTorch wheel. If you want a different version of ROCm,
   modify the command accordingly.
   :::

   ```bash
   pip3 install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/rocm5.6/
   ```

4. (Optional) Use MIOpen kdb files with ROCm PyTorch wheels.

   PyTorch uses [MIOpen](https://github.com/ROCmSoftwarePlatform/MIOpen) for machine learning
   primitives, which are compiled into kernels at runtime. Runtime compilation causes a small warm-up
   phase when starting PyTorch, and MIOpen kdb files contain precompiled kernels that can speed up
   application warm-up phases. For more information, refer to the
   {doc}`MIOpen installation page <miopen:install>`.

   MIOpen kdb files can be used with ROCm PyTorch wheels. However, the kdb files need to be placed in
   a specific location with respect to the PyTorch installation path. A helper script simplifies this task by
   taking the ROCm version and GPU architecture as inputs. This works for Ubuntu and CentOS.

   You can download the helper script here:
   [install_kdb_files_for_pytorch_wheels.sh](https://raw.githubusercontent.com/wiki/ROCmSoftwarePlatform/pytorch/files/    install_kdb_files_for_pytorch_wheels.sh), or use:

   `wget https://raw.githubusercontent.com/wiki/ROCmSoftwarePlatform/pytorch/files/install_kdb_files_for_pytorch_wheels.sh`

   After installing ROCm PyTorch wheels, run the following code:

   ```bash
   #Optional; replace 'gfx90a' with your architecture and 5.6 with your preferred ROCm version
   export GFX_ARCH=gfx90a

   #Optional
   export ROCM_VERSION=5.6

   ./install_kdb_files_for_pytorch_wheels.sh
   ```

## Using the PyTorch ROCm base Docker image

The pre-built base Docker image has all dependencies installed, including:

* ROCm
* Torchvision
* Conda packages
* The compiler toolchain

Additionally, a particular environment flag (`BUILD_ENVIRONMENT`) is set, which is used by the build
scripts to determine the configuration of the build environment.

1. Download the Docker image. This is the base image, which does not contain PyTorch.

   ```bash
   docker pull rocm/pytorch:latest-base
   ```

2. Start a Docker container using the downloaded image.

   ```bash
   docker run -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --device=/dev/kfd --device=/dev/dri --group-add video --ipc=host --shm-size 8G rocm/pytorch:latest-base
   ```

   You can also pass the `-v` argument to mount any data directories from the host onto the container.

3. Clone the PyTorch repository.

   ```bash
   cd ~
   git clone https://github.com/pytorch/pytorch.git
   cd /pytorch
   git submodule update --init --recursive
   ```

4. Set ROCm architecture (optional). The Docker image tag is `rocm/pytorch:latest-base`.

   :::{note}
   By default in the `rocm/pytorch:latest-base` image, PyTorch builds simultaneously for the following
   architectures:
   * gfx900
   * gfx906
   * gfx908
   * gfx90a
   * gfx1030
   :::

   If you want to compile _only_ for your microarchitecture (uarch), run:

   ```bash
   export PYTORCH_ROCM_ARCH=<uarch>
   ```

   Where `<uarch>` is the architecture reported by the `rocminfo` command.

   To find your uarch, run:

   ```bash
   rocminfo | grep gfx
   ```

5. Build PyTorch.

   ```bash
   ./.ci/pytorch/build.sh
   ```

   This converts PyTorch sources for
   [HIP compatibility](https://www.amd.com/en/developer/rocm-hub/hip-sdk.html) and builds the
   PyTorch framework.

   To check if your build is successful, run:

   ```bash
   echo $? # should return 0 if success
   ```

## Using the PyTorch upstream Docker file

If you don't want to use a prebuilt base Docker image, you can build a custom base Docker image
using scripts from the PyTorch repository. This uses a standard Docker image from operating system
maintainers and installs all the required dependencies, including:

* ROCm
* Torchvision
* Conda packages
* The compiler toolchain

1. Clone the PyTorch repository.

   ```bash
   cd ~
   git clone https://github.com/pytorch/pytorch.git
   cd /pytorch
   git submodule update --init --recursive
   ```

2. Build the PyTorch Docker image.

   ```bash
   cd .ci/docker
   ./build.sh pytorch-linux-<os-version>-rocm<rocm-version>-py<python-version> -t rocm/pytorch:build_from_dockerfile
   ```

   Where:
   * `<os-version>`: `ubuntu20.04` (or `focal`), `ubuntu22.04` (or `jammy`), `centos7.5`, or `centos9`
   * `<rocm-version>`: `5.4`, `5.5`, or `5.6`
   * `<python-version>`: `3.8`-`3.11`

   To verify that your image was successfully created, run:

   `docker image ls rocm/pytorch:build_from_dockerfile`

   If successful, the output looks like this:

   ```bash
   REPOSITORY    TAG                       IMAGE ID         CREATED           SIZE
   rocm/pytorch  build_from_dockerfile     17071499be47     2 minutes ago     32.8GB
   ```

3. Start a Docker container using the image with the mounted PyTorch folder.

   ```bash
   docker run -it --cap-add=SYS_PTRACE --security-opt --user root \
   seccomp=unconfined --device=/dev/kfd --device=/dev/dri \
   --group-add video --ipc=host --shm-size 8G \
   -v ~/pytorch:/pytorch rocm/pytorch:build_from_dockerfile
   ```

   You can also pass the `-v` argument to mount any data directories from the host onto the container.

4. Go to the PyTorch directory.

   ```bash
   cd pytorch
   ```

5. Set ROCm architecture.

   To determine your AMD architecture, run:

   ```bash
   rocminfo | grep gfx
   ```

   The result looks like this (for `gfx1030` architecture):

   ```bash
   Name:                    gfx1030
   Name:                    amdgcn-amd-amdhsa--gfx1030
   ```

   Set the `PYTORCH_ROCM_ARCH` environment variable to specify the architectures you want to
   build PyTorch for.

   ```bash
   export PYTORCH_ROCM_ARCH=<uarch>
   ```

   where `<uarch>` is the architecture reported by the `rocminfo` command.

6. Build PyTorch.

   ```bash
   ./.ci/pytorch/build.sh
   ```

   This converts PyTorch sources for
   [HIP compatibility](https://www.amd.com/en/developer/rocm-hub/hip-sdk.html) and builds the
   PyTorch framework.

   To check if your build is successful, run:

   ```bash
   echo $? # should return 0 if success
   ```

## Testing the PyTorch installation

You can use PyTorch unit tests to validate your PyTorch installation. If you used a
**prebuilt PyTorch Docker image from AMD ROCm DockerHub** or installed an
**official wheels package**, validation tests are not necessary.

If you want to manually run unit tests to validate your PyTorch installation fully, follow these steps:

1. Import the torch package in Python to test if PyTorch is installed and accessible.

   :::{note}
   Do not run the following command in the PyTorch git folder.
   :::

   ```bash
   python3 -c 'import torch' 2> /dev/null && echo 'Success' || echo 'Failure'
   ```

2. Check if the GPU is accessible from PyTorch. In the PyTorch framework, `torch.cuda` is a generic way
   to access the GPU. This can only access an AMD GPU if one is available.

   ```bash
   python3 -c 'import torch; print(torch.cuda.is_available())'
   ```

3. Run unit tests to validate the PyTorch installation fully.

   :::{note}
   You must run the following command from the PyTorch home directory.
   :::

   ```bash
   PYTORCH_TEST_WITH_ROCM=1 python3 test/run_test.py --verbose \
   --include test_nn test_torch test_cuda test_ops \
   test_unary_ufuncs test_binary_ufuncs test_autograd
   ```

   This command ensures that the required environment variable is set to skip certain unit tests for
   ROCm. This also applies to wheel installs in a non-controlled environment.

   :::{note}
   Make sure your PyTorch source code corresponds to the PyTorch wheel or the installation in the
   Docker image. Incompatible PyTorch source code can give errors when running unit tests.
   :::

   Some tests may be skipped, as appropriate, based on your system configuration. ROCm doesn't
   support all PyTorch features; tests that evaluate unsupported features are skipped. Other tests might
   be skipped, depending on the host or GPU memory and the number of available GPUs.

   If the compilation and installation are correct, all tests will pass.

4. Run individual unit tests.

   ```bash
   PYTORCH_TEST_WITH_ROCM=1 python3 test/test_nn.py --verbose
   ```

   You can replace `test_nn.py` with any other test set.

## Running a basic PyTorch example

The PyTorch examples repository provides basic examples that exercise the functionality of your
framework.

Two of our favorite testing databases are:

* **MNIST** (Modified National Institute of Standards and Technology): A database of handwritten
  digits that can be used to train a Convolutional Neural Network for **handwriting recognition**.
* **ImageNet**: A database of images that can be used to train a network for
  **visual object recognition**.

### MNIST PyTorch example

1. Clone the PyTorch examples repository.

   ```bash
   git clone https://github.com/pytorch/examples.git
   ```

2. Go to the MNIST example folder.

   ```bash
   cd examples/mnist
   ```

3. Follow the instructions in the `README.md`` file in this folder to install the requirements. Then run:

   ```bash
   python3 main.py
   ```

   This generates the following output:

   ```bash
   ...
   Train Epoch: 14 [58240/60000 (97%)]     Loss: 0.010128
   Train Epoch: 14 [58880/60000 (98%)]     Loss: 0.001348
   Train Epoch: 14 [59520/60000 (99%)]     Loss: 0.005261

   Test set: Average loss: 0.0252, Accuracy: 9921/10000 (99%)
   ```

### ImageNet PyTorch example

1. Clone the PyTorch examples repository (if you didn't already do this step in the preceding MNIST example).

   ```bash
   git clone https://github.com/pytorch/examples.git
   ```

2. Go to the ImageNet example folder.

   ```bash
   cd examples/imagenet
   ```

3. Follow the instructions in the `README.md` file in this folder to install the Requirements. Then run:

   ```bash
   python3 main.py
   ```
