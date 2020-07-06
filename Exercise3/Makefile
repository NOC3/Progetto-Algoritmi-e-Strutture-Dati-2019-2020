clean:
	$(RM) -rf bin/* 

run_test: src/hash_map_lib.c include/hash_map_lib.h test/hash_map_lib_test.c
	$(info	---Compiling test of exercise 3---)
	$(CC) test/hash_map_lib_test.c src/hash_map_lib.c ../Resources/C/Unity/unity.c -o bin/hash_map_lib_test
	$(info	---Running test of exercise 3---)
	bin/hash_map_lib_test

hash_map_app: app/hash_map_app.c  src/hash_map_lib.c include/hash_map_lib.h src/array_lib.c include/array_lib.h 
	$(info	---Compiling app of exercise 3---)
	$(CC) app/hash_map_app.c src/hash_map_lib.c src/array_lib.c ../Resources/C/Unity/unity.c -o bin/hash_map_app
	$(info	---Running app of exercise 3---)
	bin/hash_map_app ../../dataset/hashes.csv