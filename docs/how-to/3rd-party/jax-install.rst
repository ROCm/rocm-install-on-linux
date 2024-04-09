.. meta::
  :description: Installing JAX for ROCm
  :keywords: installation instructions, JAX, AMD, ROCm

*******************************************************************************************
Installing JAX for ROCm
*******************************************************************************************

JAX provides a NumPy-like API, which combines automatic differentiation and the Accelerated Linear
Algebra (XLA) compiler to achieve high-performance machine learning at scale.

JAX uses composable transformations of Python+Numpy through just-in-time (JIT) compilation,
automatic vectorization, and parallelization.

To learn about JAX, including profiling and optimizations, refer to the
`JAX documentation <https://jax.readthedocs.io/en/latest/notebooks/quickstart.html>`_.

Compatibility
======================================

You can currently use JAX with the following hardware and software:

* GPUs: MI250 and MI300
* OS: Ubuntu 20.04
* Python: 3.9, 3.10, 3.11
* ROCm: 5.7.0, 6.0.0

Installing JAX
========================================

JAX wheels and Docker images are released through the GitHub
`ROCm JAX fork <https://github.com/ROCm/jax/releases>`_.

.. tip::

  To build JAX from source files, refer to the `JAX developer documentation <https://jax.readthedocs.io/en/latest/developer.html>`_ 
or use the `ROCm build script <https://github.com/google/jax/blob/main/build/rocm/build_rocm.sh>`_.

1.  Pull the latest public JAX Docker image.

    .. code-block:: shell
      docker pull rocm/jax:latest
2.  Start Docker container.

    .. code-block:: shell
      docker run -it -w /workspace --device=/dev/kfd --device=/dev/dri --group-add video \
      --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --shm-size 16G rocm/jax:latest
3.  Verify the installation.

    .. code-block:: shell
      python3 -c 'import jax' 2> /dev/null && echo 'Success' || echo 'Failure'
4.  Verify that the GPU is accessible from JAX.

    .. code-block:: shell
      python3 -c 'import jax; print(jax.devices())'
5.  Run a basic example to ensure installation is successful.

    .. code-block:: shell
      git clone https://github.com/google/jax.git jax

      cd jax

      export PYTHONPATH=/workspace/jax/examples/:$PYTHONPATH

      python3 examples/mnist_classifier.py

    Your output should look similar to this:

    .. code-block:: text

      Starting training...
      Epoch 0 in 10.97 sec
      Training set accuracy 0.871916651725769
      Test set accuracy 0.880299985408783
      Epoch 1 in 0.34 sec
      Training set accuracy 0.8979166746139526
      Test set accuracy 0.9030999541282654
      Epoch 2 in 0.33 sec
      Training set accuracy 0.9092333316802979
      Test set accuracy 0.9142999649047852
      Epoch 3 in 0.33 sec
      Training set accuracy 0.9170833230018616
      Test set accuracy 0.9220999479293823
      Epoch 4 in 0.33 sec
      Training set accuracy 0.9226333498954773
      Test set accuracy 0.9279999732971191
      Epoch 5 in 0.33 sec
      Training set accuracy 0.9271667003631592
      Test set accuracy 0.9297999739646912
      Epoch 6 in 0.34 sec
      Training set accuracy 0.9323500394821167
      Test set accuracy 0.9328999519348145
      Epoch 7 in 0.34 sec
      Training set accuracy 0.935699999332428
      Test set accuracy 0.9364999532699585
      Epoch 8 in 0.33 sec
      Training set accuracy 0.938800036907196
      Test set accuracy 0.9393999576568604
      Epoch 9 in 0.33 sec
      Training set accuracy 0.9425833225250244
      Test set accuracy 0.9418999552726746
