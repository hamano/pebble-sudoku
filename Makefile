
.PHONY: build

PEBBLE_SDK=~/project/pebble/PebbleSDK-2.8
PEBBLE = $(PEBBLE_SDK)/bin/pebble
#PEBBLE_PHONE = 192.168.1.242
PEBBLE_PHONE = 10.0.1.104
APPNAME=pebble-sudoku

build:
	$(PEBBLE) build

install: build
	$(PEBBLE) install build/$(APPNAME).pbw --phone $(PEBBLE_PHONE)

clean:
	rm -rf build .lock-waf_linux2_build

logs:
	$(PEBBLE) logs --phone $(PEBBLE_PHONE)
