CXX      = g++
CXXFLAGS = -std=c++11
PREFIX   = /opt

src = $(wildcard *.cpp)
obj = $(src:.c=.o)

LDFLAGS = -lm

vaca: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: install
install: vaca
	mkdir -p $(DESTDIR)$(PREFIX)/app
	cp $< $(DESTDIR)$(PREFIX)/app/vaca
	cp vaca.service $(DESTDIR)/etc/systemd/system/vaca.service

.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/app/vaca
	rm -f $(DESTDIR)/etc/systemd/system/vaca.service

.PHONY: clean
clean:
	rm -f *.o vaca

