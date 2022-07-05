add_library(mbed-remote-stick INTERFACE)

target_include_directories(mbed-remote-stick
    INTERFACE
        .
)

target_sources(mbed-remote-stick
    	INTERFACE
	PeripheralPins.c
)