//
// auto-generated by op2.py
//

void update_omp4_kernel(
  double *data0,
  int dat0size,
  int *arg1,
  int count,
  int num_teams,
  int nthread){

  int arg1_l = *arg1;
  #pragma omp target teams num_teams(num_teams) thread_limit(nthread) map(to:data0[0:dat0size])\
    map(tofrom: arg1_l) reduction(+:arg1_l)
  #pragma omp distribute parallel for schedule(static,1) reduction(+:arg1_l)
  for ( int n_op=0; n_op<count; n_op++ ){
    //variable mapping
    double *data = &data0[4*n_op];
    int *count = &arg1_l;

    //inline function
    
    data[0] = 0.0;
    (*count)++;
    //end inline func
  }

  *arg1 = arg1_l;
}
