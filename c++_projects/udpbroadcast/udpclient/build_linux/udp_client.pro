QT	+= core network

SOURCES += \
	..\src\udp_client.cpp \
	..\src\udp_client_main.cpp

HEADERS += \
	..\src\udp_client.h 

unix {
	MOC_DIR = .moc
	OBJECTS_DIR = .obj
}
	
