clean:
	$(RM) -rf bin/* 

run_test: test/sorting_lib_test.c include/sorting_lib.h src/sorting_lib.c
	$(info	---Compiling test of exercise 1---)
	$(CC) test/sorting_lib_test.c src/sorting_lib.c ../Resources/C/Unity/unity.c -o bin/test_sorting_lib
	$(info	---Running test of exercise 1---)
	./bin/test_sorting_lib

sorting_lib_app: app/sorting_lib_app.c include/sorting_lib.h src/sorting_lib.c 
	$(info	---Compiling app of exercise 1---)
	$(CC) app/sorting_lib_app.c src/sorting_lib.c -o bin/sorting_lib_app
	$(info	---Running app of exercise 1---)
	bin/sorting_lib_app "../../dataset/records.csv" 3 q