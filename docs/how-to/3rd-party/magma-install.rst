*******************************************************************************************
MAGMA installation for ROCm
*******************************************************************************************

Matrix Algebra on GPU and Multicore Architectures (MAGMA) is a
collection of next-generation dense linear algebra libraries that is designed
for heterogeneous architectures, such as multiple GPUs and multi- or many-core
CPUs.

MAGMA provides implementations for CUDA, HIP, Intel Xeon Phi, and OpenCL™. For
more information, refer to
`https://icl.utk.edu/magma/index.html <https://icl.utk.edu/magma/index.html>`_.

Using MAGMA for PyTorch
======================================

Tensor is fundamental to deep-learning techniques because it provides extensive
representational functionalities and math operations. This data structure is
represented as a multidimensional matrix. MAGMA accelerates tensor operations
with a variety of solutions including driver routines, computational routines,
BLAS routines, auxiliary routines, and utility routines.

Building MAGMA from source
========================================

To build MAGMA from the source, follow these steps:

1. In the event you want to compile only for your uarch, use:

   .. code-block:: shell

       export PYTORCH_ROCM_ARCH=<uarch>

   ``<uarch>`` is the architecture reported by the ``rocminfo`` command.

2. Use the following:

   .. code-block:: shell

       export PYTORCH_ROCM_ARCH=<uarch>

       # "install" hipMAGMA into /opt/rocm/magma by copying after build
       git clone https://bitbucket.org/icl/magma.git
       pushd magma
       # Fixes memory leaks of MAGMA found while executing linalg UTs
       git checkout 5959b8783e45f1809812ed96ae762f38ee701972
       cp make.inc-examples/make.inc.hip-gcc-mkl make.inc
       echo 'LIBDIR += -L$(MKLROOT)/lib' >> make.inc
       echo 'LIB += -Wl,--enable-new-dtags -Wl,--rpath,/opt/rocm/lib -Wl,--rpath,$(MKLROOT)/lib -Wl,--rpath,/opt/rocm/magma/lib' >> make.inc
       echo 'DEVCCFLAGS += --gpu-max-threads-per-block=256' >> make.inc
       export PATH="${PATH}:/opt/rocm/bin"
       if [[ -n "$PYTORCH_ROCM_ARCH" ]]; then
         amdgpu_targets=`echo $PYTORCH_ROCM_ARCH | sed 's/;/ /g'`
       else
         amdgpu_targets=`rocm_agent_enumerator | grep -v gfx000 | sort -u | xargs`
       fi
       for arch in $amdgpu_targets; do
         echo "DEVCCFLAGS += --amdgpu-target=$arch" >> make.inc
       done
       # hipcc with openmp flag may cause isnan() on __device__ not to be found; depending on context, compiler may attempt to match with host definition
       sed -i 's/^FOPENMP/#FOPENMP/g' make.inc
       make -f make.gen.hipMAGMA -j $(nproc)
       LANG=C.UTF-8 make lib/libmagma.so -j $(nproc) MKLROOT=/opt/conda
       make testing/testing_dgemm -j $(nproc) MKLROOT=/opt/conda
       popd
       mv magma /opt/rocm
