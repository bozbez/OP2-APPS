//
// auto-generated by op2.py
//

//user function
//user function
//#pragma acc routine
inline void res_openacc( const float *A, const float *u, float *du, const float *beta) {
  *du += (*beta) * (*A) * (*u);
}

// host stub function
void op_par_loop_res(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3){

  float*arg3h = (float *)arg3.data;
  int nargs = 4;
  op_arg args[4];

  args[0] = arg0;
  args[1] = arg1;
  args[2] = arg2;
  args[3] = arg3;

  // initialise timers
  double cpu_t1, cpu_t2, wall_t1, wall_t2;
  op_timing_realloc(0);
  op_timers_core(&cpu_t1, &wall_t1);
  OP_kernels[0].name      = name;
  OP_kernels[0].count    += 1;

  int  ninds   = 2;
  int  inds[4] = {-1,0,1,-1};

  if (OP_diags>2) {
    printf(" kernel routine with indirection: res\n");
  }

  // get plan
  #ifdef OP_PART_SIZE_0
    int part_size = OP_PART_SIZE_0;
  #else
    int part_size = OP_part_size;
  #endif

  int set_size = op_mpi_halo_exchanges_cuda(set, nargs, args);

  float arg3_l = arg3h[0];

  int ncolors = 0;

  if (set_size >0) {


    //Set up typed device pointers for OpenACC
    int *map1 = arg1.map_data_d;

    float* data0 = (float*)arg0.data_d;
    float *data1 = (float *)arg1.data_d;
    float *data2 = (float *)arg2.data_d;

    op_plan *Plan = op_plan_get_stage(name,set,part_size,nargs,args,ninds,inds,OP_COLOR2);
    ncolors = Plan->ncolors;
    int *col_reord = Plan->col_reord;
    int set_size1 = set->size + set->exec_size;

    // execute plan
    for ( int col=0; col<Plan->ncolors; col++ ){
      if (col==1) {
        op_mpi_wait_all_cuda(nargs, args);
      }
      int start = Plan->col_offsets[0][col];
      int end = Plan->col_offsets[0][col+1];

      #pragma acc parallel loop independent deviceptr(col_reord,map1,data0,data1,data2)
      for ( int e=start; e<end; e++ ){
        int n = col_reord[e];
        int map1idx;
        int map2idx;
        map1idx = map1[n + set_size1 * 1];
        map2idx = map1[n + set_size1 * 0];


        res_openacc(
          &data0[1 * n],
          &data1[1 * map1idx],
          &data2[1 * map2idx],
          &arg3_l);
      }

    }
    OP_kernels[0].transfer  += Plan->transfer;
    OP_kernels[0].transfer2 += Plan->transfer2;
  }

  if (set_size == 0 || set_size == set->core_size || ncolors == 1) {
    op_mpi_wait_all_cuda(nargs, args);
  }
  // combine reduction data
  op_mpi_set_dirtybit_cuda(nargs, args);

  // update kernel record
  op_timers_core(&cpu_t2, &wall_t2);
  OP_kernels[0].time     += wall_t2 - wall_t1;
}
