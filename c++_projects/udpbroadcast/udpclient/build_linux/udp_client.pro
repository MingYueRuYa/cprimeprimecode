QT	+= core network

SOURCES += \
	../src/udp_client.cpp \
	../src/udp_client_main.cpp

HEADERS += \
	../src/udp_client.h 

TARGET = ../bin_linux/udp_client
	
unix {
	MOC_DIR = .moc
	OBJECTS_DIR = .obj
}
	
