PROJECT_ROOT := $(shell pwd)
BUILD_DIR := $(PROJECT_ROOT)/build
EXECUTABLE := $(BUILD_DIR)/SpotifyGUI

all: build

build:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

run:
	@set -a && \
	. $(PROJECT_ROOT)/config.env && \
	set +a && \
	$(EXECUTABLE)
	

clean:
	rm -rf $(BUILD_DIR)
