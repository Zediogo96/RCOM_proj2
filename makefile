SDIR    =./src
IDIR    =./include
ODIR    =./obj
DDIR    =./downloads

CC      =gcc
CFLAGS  =-Wall -Wextra -g -I$(IDIR)

all: download
 
download: $(ODIR)/main.o $(ODIR)/URLparser.o $(ODIR)/clientTCP.o
	$(CC) $(ODIR)/main.o $(ODIR)/URLparser.o $(ODIR)/clientTCP.o $(CFLAGS) -o download

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) -c $< $(CFLAGS) -o $@

$(ODIR):
	mkdir $(ODIR)

test: test_vpn

test_vpn:
	./download ftp://netlab1.fe.up.pt/pub.txt 				 
	./download ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt       
	./download ftp://rcom:rcom@netlab1.fe.up.pt/files/pic1.jpg
	./download ftp://rcom:rcom@netlab1.fe.up.pt/files/pic2.png
	./download ftp://rcom:rcom@netlab1.fe.up.pt/files/crab.mp4

clean: 
	rm -f download
	rm -rf obj
	rm -f 1MB.zip crab.mp4 pic1.jpg pic2.png pipe.txt pub.txt README README.html
	rm -f ${DDIR}/*

present: clean all test_vpn


