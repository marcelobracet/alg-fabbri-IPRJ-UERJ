/* R. Fabbri, 2024 */
#include "sorted_merge_3way.h"
#include <climits>

static bool is_sorted(const int *arr, int n) {
  if (n <= 1) {
    return true;
  }
  
  for(int i = 1; i < n; i++) {
    if(arr[i] < arr[i - 1]) {
      return false;
    }
  }
  return true;
}

bool
sorted_merge_3way(
    const int *list_a, int na,
    const int *list_b, int nb,
    const int *list_c, int nc,
    int *list_abc)
{

  if(!is_sorted(list_a, na) || !is_sorted(list_b, nb) || !is_sorted(list_c, nc)) {
    return false;
  }

  int ia = 0, ib = 0, ic = 0;
  int idx = 0;

  while(ia < na || ib < nb || ic < nc) {
    int va = (ia < na) ? list_a[ia] : INT_MAX;
    int vb = (ib < nb) ? list_b[ib] : INT_MAX;
    int vc = (ic < nc) ? list_c[ic] : INT_MAX;

    if(va <= vb && va <= vc) {
      list_abc[idx++] = va;
      ia++;
    }
    else if(vb <= va && vb <= vc) {
      list_abc[idx++] = vb;
      ib++;
    }
    else {
      list_abc[idx++] = vc;
      ic++;
    }
  }

  return true;
}
