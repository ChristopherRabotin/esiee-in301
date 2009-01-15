all:	TestAchatVente TestMessage TestRedirection TestLogger

TestAchatVente:	PrixAchatVente.o TestAchatVente.c # TestAchatVente
	gcc PrixAchatVente.o TestAchatVente.c -o ../Debug/TestAchatVente -D DEBUG

TestMessage: message.o alea.o logger.o TestMessage.c # TestMessage
	gcc TestMessage.c message.o alea.o logger.o -o ../Debug/TestMessage -D DEBUG

TestRedirection: TestRedirection.c
	gcc TestRedirection.c -o  ../Debug/TestRedirection -D DEBUG # TestRedirection

TestLogger: logger.o TestLogger.c # TestLogger 
	gcc TestLogger.c logger.o -o ../Debug/TestLogger -D DEBUG

TestServers: communication.o logger.o TestServers.c # TestServers
	gcc TestServers.c communication.o logger.o -o ../Debug/TestServers -D DEBUG

# ici vont tous les sous-builds (par ordre alphabetique!)
alea.o: ../libbourse/alea.h ../libbourse/alea.c
	gcc -Wall -c ../libbourse/alea.c -D DEBUG

communication.o: logger.o message.o ../libcomm/communication.h ../libcomm/communication.c
	gcc -c -Wall ../libcomm/communication.c -D DEBUG

logger.o: ../libcomm/logger.h ../libcomm/logger.c
	gcc -c -Wall ../libcomm/logger.c -D DEBUG
	
message.o: ../libcomm/message.h ../libcomm/message.c
	gcc -Wall -c ../libcomm/message.c -D DEBUG
	
PrixAchatVente.o:	../libbourse/PrixAchatVente.c ../libbourse/PrixAchatVente.h
	gcc -c ../libbourse/PrixAchatVente.c -D DEBUG

# le clean est ICI
clean:	
	rm -f ../bin/*.o
