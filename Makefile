CC = cc

TARGET = zi_fch
OBJ = memio.o parse.o load.o main.o convert.o
CFLAGS = -O2 -Wall -DCODETYPE=0x03	#ISO-8859-1

all:	$(TARGET)

$(TARGET):	$(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ) $(TARGET)
