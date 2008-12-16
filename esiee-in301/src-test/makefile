all:	TestAchatVente TestMessage TestRedirection

PrixAchatVente.o:	../libbourse/PrixAchatVente.c ../libbourse/PrixAchatVente.h
	gcc -c ../libbourse/PrixAchatVente.c 

TestAchatVente:	PrixAchatVente.o TestAchatVente.c
	gcc PrixAchatVente.o TestAchatVente.c -o ../Debug/TestAchatVente

message.o: ../libcomm/message.c ../libcomm/message.h
	gcc -Wall -c ../libcomm/message.c

alea.o: ../libbourse/alea.h ../libbourse/alea.c
	gcc -Wall -c ../libbourse/alea.c

TestMessage: message.o alea.o TestMessage.c
	gcc TestMessage.c message.o alea.o -o  ../Debug/TestMessage

TestRedirection: TestRedirection.c
	gcc TestRedirection.c -o  ../Debug/TestRedirection

clean:	
	rm -f ../bin/*.o
