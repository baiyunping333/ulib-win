#
TOPDIR = ../..
#
include $(TOPDIR)/make.inc

#
INCS = -I"$(TOPDIR)/inc"
LIBS = -L"$(TOPDIR)/lib" -mwindows -lole32 -loleaut32 -luuid -luwin
CFLAGS +=
CXXFLAGS += -DBUILD_EXE

#
OBJ = test_sysadm.o \


BIN = test_sysadm.exe
RC  = sysadm.rc
RES = ${RC:.rc=.res}
#
HEADER = $(INCDIR)/udialogx.h \
          ./usysadm.h

#
all: $(BIN)

#
$(BIN) : $(OBJ) $(RES)
	$(CXX) -o $(BIN) $^ $(LIBS)
	cp -v $@ $(BINDIR)/$@

.PHONY : test
test :
	$(WINE) $(BINDIR)/$(BIN)     
#
.PHONY : clean
clean :
	$(RM) ${OBJ} ${RES} ${BIN}

