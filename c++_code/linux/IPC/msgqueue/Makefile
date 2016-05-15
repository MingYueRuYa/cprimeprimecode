msgqueuebasic:msgqueuebasic.c
	gcc -Wall -g $< -o $@

msgctl:msgctl.c
	gcc -Wall -g $< -o $@

msgsend:msgsend.c
	gcc -Wall -g $< -o $@

msgrecv:msgrecv.c
	gcc -Wall -g $< -o $@

msgall:msgall.c
	gcc -Wall -g $< -o $@

.PHONY: clean
clean:
	-rm -rf msgqueuebasic msgctl msgsend msgrecv msgall
