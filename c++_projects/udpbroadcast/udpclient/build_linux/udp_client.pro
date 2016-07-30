QT	+= core network

SOURCES += \
	udp_client.cpp \
	udp_client_main.cpp

HEADERS += \
	udp_client.h 

unix {
	MOC_DIR = .moc
	OBJECTS_DIR = .obj
}
	
