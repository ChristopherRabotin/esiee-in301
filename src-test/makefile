all:	TestAchatVente TestMessage TestRedirection TestLogger

# TestAchatVente
PrixAchatVente.o:	../libbourse/PrixAchatVente.c ../libbourse/PrixAchatVente.h
	gcc -c ../libbourse/PrixAchatVente.c -D DEBUG

TestAchatVente:	PrixAchatVente.o TestAchatVente.c
	gcc PrixAchatVente.o TestAchatVente.c -o ../Debug/TestAchatVente -D DEBUG
# TestMessage
message.o: ../libcomm/message.h ../libcomm/message.c
	gcc -Wall -c ../libcomm/message.c -D DEBUG

alea.o: ../libbourse/alea.h ../libbourse/alea.c
	gcc -Wall -c ../libbourse/alea.c -D DEBUG

TestMessage: message.o alea.o logger.o TestMessage.c
	gcc TestMessage.c message.o alea.o logger.o -o ../Debug/TestMessage -D DEBUG
# TestRedirection
TestRedirection: TestRedirection.c
	gcc TestRedirection.c -o  ../Debug/TestRedirection -D DEBUG
# TestLogger
logger.o: ../libcomm/logger.h ../libcomm/logger.c
	gcc -c -Wall ../libcomm/logger.c -D DEBUG
	
TestLogger: logger.o TestLogger.c 
	gcc TestLogger.c logger.o -o ../Debug/TestLogger -D DEBUG

# le clean est ICI
clean:	
	rm -f ../bin/*.o
