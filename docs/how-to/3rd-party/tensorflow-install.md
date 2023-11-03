# Installing TensorFlow for ROCm

## TensorFlow

TensorFlow is an open-source library for solving machine-learning,
deep-learning, and artificial-intelligence problems. It can be used to solve
many problems across different sectors and industries but primarily focuses on
training and inference in neural networks. It is one of the most popular and
in-demand frameworks and is very active in open source contribution and
development.

:::{warning}
ROCm 5.6 and 5.7 deviates from the standard practice of supporting the last three
TensorFlow versions. This is due to incompatibilities between earlier TensorFlow
versions and changes introduced in the ROCm 5.6 compiler. Refer to the following
version support matrix:

| ROCm  | TensorFlow |
|:-----:|:----------:|
| 5.6.x | 2.12       |
| 5.7.0 | 2.12, 2.13 |
| Post-5.7.0 | Last three versions at ROCm release. |
:::

### Installing TensorFlow

The following sections contain options for installing TensorFlow.

#### Option 1: using a Docker image

To install ROCm on bare metal, follow the section
[Linux installation guide](../install/linux/install.md). The recommended option to
get a TensorFlow environment is through Docker.

Using Docker provides portability and access to a prebuilt Docker container that
has been rigorously tested within AMD. This might also save compilation time and
should perform as tested without facing potential installation issues.
Follow these steps:

1. Pull the latest public TensorFlow Docker image.

   ```bash
   docker pull rocm/tensorflow:latest
   ```

2. Once you have pulled the image, run it by using the command below:

   ```bash
   docker run -it --network=host --device=/dev/kfd --device=/dev/dri \
   --ipc=host --shm-size 16G --group-add video --cap-add=SYS_PTRACE \
   --security-opt seccomp=unconfined rocm/tensorflow:latest
   ```

#### Option 2: using a wheels package

To install TensorFlow using the wheels package, follow these steps:

1. Check the Python version.

   ```bash
   python3 --version
   ```

   | If:                                 | Then:                            |
   |:-----------------------------------:|:--------------------------------:|
   | The Python version is less than 3.7 | Upgrade Python.                  |
   | The Python version is more than 3.7 | Skip this step and go to Step 3. |

   ```{note}
   The supported Python versions are:

   * 3.7
   * 3.8
   * 3.9
   * 3.10
   ```

   ```bash
   sudo apt-get install python3.7 # or python3.8 or python 3.9 or python 3.10
   ```

2. Set up multiple Python versions using update-alternatives.

   ```bash
   update-alternatives --query python3
   sudo update-alternatives --install
   /usr/bin/python3 python3 /usr/bin/python[version] [priority]
   ```

   ```{note}
   Follow the instruction in Step 2 for incompatible Python versions.
   ```

   ```bash
   sudo update-alternatives --config python3
   ```

3. Follow the screen prompts, and select the Python version installed in Step 2.

4. Install or upgrade PIP.

   ```bash
   sudo apt install python3-pip
   ```

   To install PIP, use the following:

   ```bash
   /usr/bin/python[version]  -m pip install --upgrade pip
   ```

   Upgrade PIP for Python version installed in step 2:

   ```bash
   sudo pip3 install --upgrade pip
   ```

5. Install TensorFlow for the Python version as indicated in Step 2.

   ```bash
   /usr/bin/python[version] -m pip install --user tensorflow-rocm==[wheel-version] --upgrade
   ```

   For a valid wheel version for a ROCm release, refer to the instruction below:

   ```bash
   sudo apt install rocm-libs rccl
   ```

6. Update `protobuf` to 3.19 or lower.

   ```bash
   /usr/bin/python3.7  -m pip install protobuf=3.19.0
   sudo pip3 install tensorflow
   ```

7. Set the environment variable `PYTHONPATH`.

   ```bash
   export PYTHONPATH="./.local/lib/python[version]/site-packages:$PYTHONPATH"  #Use same python version as in step 2
   ```

8. Install libraries.

   ```bash
   sudo apt install rocm-libs rccl
   ```

9. Test installation.

   ```bash
   python3 -c 'import tensorflow' 2> /dev/null && echo 'Success' || echo 'Failure'
   ```

   ```{note}
   For details on `tensorflow-rocm` wheels and ROCm version compatibility, see:
   [https://github.com/ROCmSoftwarePlatform/tensorflow-upstream/blob/develop-upstream/rocm_docs/tensorflow-rocm-release.md](https://github.com/ROCmSoftwarePlatform/tensorflow-upstream/blob/develop-upstream/rocm_docs/tensorflow-rocm-release.md)
   ```

### Test the TensorFlow installation

To test the installation of TensorFlow, run the container image as specified in
the previous section Installing TensorFlow. Ensure you have access to the Python
shell in the Docker container.

```bash
python3 -c 'import tensorflow' 2> /dev/null && echo ‘Success’ || echo ‘Failure’
```

### Run a basic TensorFlow example

The TensorFlow examples repository provides basic examples that exercise the
framework's functionality. The MNIST database is a collection of handwritten
digits that may be used to train a Convolutional Neural Network for handwriting
recognition.

Follow these steps:

1. Clone the TensorFlow example repository.

   ```bash
   cd ~
   git clone https://github.com/tensorflow/models.git
   ```

2. Install the dependencies of the code, and run the code.

   ```bash
   #pip3 install requirement.txt
   #python mnist_tf.py
   ```
