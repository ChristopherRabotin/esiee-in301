all:	TestAchatVente TestMessage TestRedirection TestLogger

# TestAchatVente
PrixAchatVente.o:	../libbourse/PrixAchatVente.c ../libbourse/PrixAchatVente.h
	gcc -c ../libbourse/PrixAchatVente.c 

TestAchatVente:	PrixAchatVente.o TestAchatVente.c
	gcc PrixAchatVente.o TestAchatVente.c -o ../Debug/TestAchatVente
# TestMessage
message.o: ../libcomm/message.c ../libcomm/message.h
	gcc -Wall -c ../libcomm/message.c

alea.o: ../libbourse/alea.h ../libbourse/alea.c
	gcc -Wall -c ../libbourse/alea.c

TestMessage: message.o alea.o TestMessage.c
	gcc TestMessage.c message.o alea.o -o  ../Debug/TestMessage
# TestRedirection
TestRedirection: TestRedirection.c
	gcc TestRedirection.c -o  ../Debug/TestRedirection
# TestLogger
logger.o: ../libcomm/logger.c ../libcomm/logger.h
	gcc -c -Wall ../libcomm/logger.c
	
TestLogger: logger.o TestLogger.c 
	gcc TestLogger.c -o ../Debug/TestLogger

# le clean est ICI
clean:	
	rm -f ../bin/*.o
