# MiniRT-42Lisbon

### reference links 
https://start.me/p/5vzAjP/pagina-inicial		//updated
added Uni projects links, classic test models

## srcs/chap_11
gcc *.c -lm
./a.out pyramidw.plg

// how to compile leaving out unused functions.
// use list to refactor 
gcc -ffunction-sections -fdata-sections -Wl,--gc-sections,--print-gc-sections *.c -lm 2> unused_functions.log


// static analysis
gcc -fanalyzer *.c -lm 2> gcc_fanalyzer.log


// srcs/vector/
// gcc -o test_vector test_vector.c vector.c vector_advanced.c vector_aux.c -lm
// ./test_vector
