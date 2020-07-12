# 排序算法

### 插入排序
从序列中第二个值开始，把当前值看作新插入的元素，在序列中找到合适的插入位置，升序排列，左侧值都小于当前值
<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_08/insertion_sort.png" width = "800" height = "600">

```cpp
void insertion_sort(vector<int>& arr) {
  for (int i = 1; i < arr.size(); i++) {
    int cur = arr[i];
    int j = i;
    while (j > 0 && arr[j-1] > cur) {
      arr[j] = arr[j-1];
      j--;
    }
    arr[j] = cur;
  }
}
```

### 选择排序
```cpp
void selection_sort(vector<int>& arr) {
  int n = arr.size();
  int min_i;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      min_i = arr[j] < min_i ? j : min_i;
    }
    int temp = arr[min_i];
    arr[min_i] = arr[i];
    arr[i] = temp;
  }
}
```

### 冒泡排序
```cpp
void bubble_sort(vector<int>& arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; i++) { 
    // 每轮交换完成后，最大值排在最后
    for (int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j+1]) {
        int temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
      }
    }
  }
}
```

### 快速排序
用pivot将序列拆分成左右两部分，左边的小于pivot，右边的大于pivot，然后递归分治左右

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_08/quick_sort.png" width = "300" height = "300">

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_08/quick_sort2.png" width = "600" height = "600">

```cpp
int partition(vector<int>& nums, int left, int right) {
  int pivot = right;
  int counter = left;
  for (int i = left; i < right; i++) {
    # counter左边总是比nums[pivot]小的数
    if (a[i] < a[pivot]) {
       int temp = a[i];
       a[i] = a[counter];
       a[counter] = temp;
       counter++;
    }
  }
  
  int temp = a[pivod];
  a[pivot] = a[counter];
  a[counter] = temp;
  return counter;
}

void quick_sort(vector<int>& nums, int left, int right) {
  if (right <= left) return;
  int pivot = partition(nums, left, right);
  quick_sort(nums, left, pivot - 1);
  quick_sort(nums, pivot + 1, right);
}
```

### 归并排序
先分后合，排序在合的过程中完成。

<img src="https://github.com/lwdhw1987/algorithm009-class01/blob/master/Week_08/merge_sort.png" width = "600" height = "600">

```cpp
void merge(vector<int>& nums, int left, int mid, int right) {
  vector<int> temp(right-left+1);
  for (int i = left; i <= right; i++) {
    temp[i] = nums[i];
  }
  
  int i = left;
  int p1 = left;
  int p2 = mid + 1; 
  // 前后部分分别有序，合并
  while (p1 <= mid || p2 <= right) {
      if (p1 > mid || (p2 <= right && temp[p1] > temp[p2])) {
          nums[i++] = temp[p2++];
      }
      else {
          nums[i++] = temp[p1++];
      }
  }
}

int mergeSort(vector<int>& nums, int left, int right) {
  if (right <= left) {
    return 0;
  }

  int mid = left + (right - left) / 2;
  int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);

  merge(nums, left, mid, right);

  return count;
}
```
