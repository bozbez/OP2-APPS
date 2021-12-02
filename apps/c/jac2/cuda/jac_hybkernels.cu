//
// auto-generated by op2.py
//

//header
#ifdef GPUPASS
#define op_par_loop_res op_par_loop_res_gpu
#define op_par_loop_update op_par_loop_update_gpu
#include "jac_kernels.cu"
#undef op_par_loop_res
#undef op_par_loop_update
#else
#define op_par_loop_res op_par_loop_res_cpu
#define op_par_loop_update op_par_loop_update_cpu
#include "../openmp/jac_kernels.cpp"
#undef op_par_loop_res
#undef op_par_loop_update

//user kernel files

void op_par_loop_res_gpu(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3);

//GPU host stub function
#if OP_HYBRID_GPU
void op_par_loop_res(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3){

  if (OP_hybrid_gpu) {
    op_par_loop_res_gpu(name, set,
      arg0,
      arg1,
      arg2,
      arg3);

    }else{
    op_par_loop_res_cpu(name, set,
      arg0,
      arg1,
      arg2,
      arg3);

  }
}
#else
void op_par_loop_res(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3){

  op_par_loop_res_gpu(name, set,
    arg0,
    arg1,
    arg2,
    arg3);

  }
#endif //OP_HYBRID_GPU

void op_par_loop_update_gpu(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3,
  op_arg arg4);

//GPU host stub function
#if OP_HYBRID_GPU
void op_par_loop_update(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3,
  op_arg arg4){

  if (OP_hybrid_gpu) {
    op_par_loop_update_gpu(name, set,
      arg0,
      arg1,
      arg2,
      arg3,
      arg4);

    }else{
    op_par_loop_update_cpu(name, set,
      arg0,
      arg1,
      arg2,
      arg3,
      arg4);

  }
}
#else
void op_par_loop_update(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3,
  op_arg arg4){

  op_par_loop_update_gpu(name, set,
    arg0,
    arg1,
    arg2,
    arg3,
    arg4);

  }
#endif //OP_HYBRID_GPU
#endif
