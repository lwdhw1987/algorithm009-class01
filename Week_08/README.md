# 排序算法

### 插入排序
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
