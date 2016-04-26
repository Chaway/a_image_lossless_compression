all:encode decode
encode:Video_Code.o predictions.o transfer.o Arith_Code.o
	gcc Video_Code.o predictions.o transfer.o Arith_Code.o -o encode -lm
decode:Video_Decode.o depredictions.o transfer.o Arith_Decode.o
	gcc Video_Decode.o depredictions.o transfer.o Arith_Decode.o -o decode -lm
Video_Code.o:Video_Code.c
	gcc -c Video_Code.c
Video_Decode.o:Video_Decode.c
	gcc -c Video_Decode.c
depredictions.o:depredictions.c 
	gcc -c depredictions.c
predictions.o:predictions.c 
	gcc -c predictions.c
Arith_Code.o:Arith_Code.c
	gcc -c Arith_Code.c
Arith_Decode.o:Arith_Decode.c
	gcc -c Arith_Decode.c
transfer.o:transfer.c	
	gcc -c transfer.c	
clean:
	rm *.o

