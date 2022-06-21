# PageRank

**Fork**
[https://github.com/andreacarrara/pagerank/](https://github.com/andreacarrara/pagerank/)

A C++ single-file header-only pagerank library

## Example
<p align="center">
  <img src="assets/example-light.png#gh-light-mode-only" width="350px" />
  <img src="assets/example-dark.png#gh-dark-mode-only" width="350px" />
</p>

```cpp
//main.cpp
int main() {
    pagerank::matrix::matrix_t matrix = {
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
    };
    
    auto score = pagerank::compute(matrix);
    
    for (int i = 0; i < size; i++) {
        std::cout << i << "-" << score[i] << std::endl;
    }
}
```

```shell
0-0.479694
1-0.173435
2-0.173435
3-0.173435
```

## Resources
* [wikipedia.org](https://wikipedia.org/wiki/PageRank)
* [rose-hulman.edu](https://www.rose-hulman.edu/~bryan/googleFinalVersionFixed.pdf)
* [youtube.com](https://youtube.com/playlist?list=PLLssT5z_DsK9JDLcT8T62VtzwyW9LNepV)
* [courses.cs.washington.edu](https://courses.cs.washington.edu/courses/cse373/17au/project3/project3-3.html)