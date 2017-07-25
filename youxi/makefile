FINAL:=main
OBJECT:=menu.o gameMenu.o sign_in_up.o gamev0.2.o
OPTIONS:=-g -Wall
CC:=gcc
$(FINAL):$(OBJECT)
	$(CC) $^ -o $@ $(OPTIONS)
%.o:%.c
	$(CC) -c $< -o $@ $(OPTIONS)
clean:
	rm -rvf $(OBJECT) $(FINAL)
