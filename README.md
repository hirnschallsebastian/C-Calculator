# C-Calculator 
![build status](https://travis-ci.com/hirnschallsebastian/C-Calculator.svg?branch=master)
![GitHub release](https://img.shields.io/badge/release-v0.1-blue.svg)


### Features:
- [x] ability to compute the result of a given calculation
  - input as string
  - support for + - * / and ()
  - use variables to store exact results and use later on
  - support for pow using ^
- [ ] support for sin,cos,abs,sqrt...
- [ ] solve equation systems using matrices (numsolve)
- [ ] solve polynomial functions (polysolve)
- [x] plot(f(x),xmin:xmax) support
- [x] display time it takes to compute result (see 

### Compile:
CMAKE:        
```mkdir build && cd build && cmake .. && make```          
GCC:        
```gcc main.c io.c plot.c solve.c resize.c -lreadline -o ccalc```        

|Flag                  | Info             |
|----------------------|------------------|
|```-DCOMPATIBILITY``` |In case you do not have [Nerd Fonts](https://github.com/ryanoasis/nerd-fonts) installed|
|```-DTIME```|Display time it takes to compute result|

