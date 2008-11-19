YUIC=yuicompressor

all: campus_emergency_receiver.js
debug:
	cp campus_emergency_receiver.jsrc campus_emergency_receiver.js

%.js: %.jsrc
	$(YUIC) -o $@ --type js $<
