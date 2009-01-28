all:	TestAchatVente TestMessage TestRedirection TestLogger

TestAchatVente:	PrixAchatVente.o TestAchatVente.c # TestAchatVente
	gcc PrixAchatVente.o TestAchatVente.c -o ../Debug/TestAchatVente -D DEBUG

TestMessage: message.o alea.o logger.o TestMessage.c # TestMessage
	gcc TestMessage.c message.o alea.o logger.o -o ../Debug/TestMessage -D DEBUG

TestRedirection: TestRedirection.c
	gcc TestRedirection.c -o  ../Debug/TestRedirection -D DEBUG # TestRedirection

TestLogger: logger.o TestLogger.c # TestLogger 
	gcc TestLogger.c logger.o -o ../Debug/TestLogger -D DEBUG

TestServers: communication.o message.o logger.o alea.o TestServers.c # TestServers
	gcc TestServers.c communication.o message.o alea.o logger.o -o ../Debug/TestServers -D DEBUG

TestExecution: alea.o execution.o logger.o message.o PrixAchatVente.o
	gcc TestExecution.c execution.o alea.o logger.o message.o PrixAchatVente.o -o ../Debug/TestExecution -D DEBUG

TestTerminal: alea.o logger.o terminal.o message.o
	gcc TestTerminal.c alea.o logger.o terminal.o message.o -o ../Debug/TestTerminal -D DEBUG
	
TestInterboursier: logger.o message.o communication.o
	gcc TestInterboursier logger.o message.o communication.o -o ../Debug/TestInterboursier -D DEBUG
	
# ici vont tous les sous-builds (par ordre alphabetique!)
alea.o: ../libbourse/alea.h ../libbourse/alea.c
	gcc -c -Wall ../libbourse/alea.c -D DEBUG

communication.o: logger.o message.o execution.o ../libcomm/communication.h ../libcomm/communication.c
	gcc -c -Wall ../libcomm/communication.c -D DEBUG

execution.o: logger.o message.o alea.o PrixAchatVente.o ../src/execution.h ../src/execution.c
	gcc -c -Wall ../src/execution.c -D DEBUG

logger.o: ../libcomm/logger.h ../libcomm/logger.c
	gcc -c -Wall ../libcomm/logger.c -D DEBUG
	
message.o: ../libcomm/message.h ../libcomm/message.c
	gcc -c -Wall ../libcomm/message.c -D DEBUG
	
PrixAchatVente.o:	../libbourse/PrixAchatVente.c ../libbourse/PrixAchatVente.h
	gcc -c -Wall ../libbourse/PrixAchatVente.c -D DEBUG

terminal.o: logger.o message.o alea.o ../src/terminal.h ../src/terminal.c
	gcc -c -Wall ../src/terminal.c -D DEBUG

# le clean est ICI
clean:	
	rm -f ../bin/*.o
