#include "../libcomm/message.h"
#include "../src/execution.h"

int main(int argc, char *argv[]) {
	msg * msg2 = create_msg("0033125218", "Achat", "0001000001", "007");
	printf("msg2: %s", msg_to_str(msg2));
	execution_msg(msg2);
	return 0;

}
