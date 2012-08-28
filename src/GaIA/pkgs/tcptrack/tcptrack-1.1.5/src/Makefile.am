bin_PROGRAMS = tcptrack

tcptrack_SOURCES = Collector.cc main.cc TCContainer.cc \
                 TextUI.cc  PacketBuffer.cc \
                 Sniffer.cc TCPConnection.cc util.cc \
                 SortedIterator.cc IPv4Packet.cc IPv4Address.cc \
                 TCPPacket.cc NetworkPacket.cc \
                 IPv4TCPPacket.cc IPv4TCPCapture.cc \
                 TCPTrack.cc SocketPair4.cc \
                 AppError.cc PcapError.cc GenericError.cc Guesser.cc

noinst_HEADERS = Collector.h PacketBuffer.h TextUI.h \
	defs.h Sniffer.h headers.h \
	SortedIterator.h util.h TCContainer.h \
	TCPConnection.h Guesser.h \
	IPv4Packet.h IPv4Address.h TCPPacket.h NetworkPacket.h \
	IPv4TCPPacket.h IPv4TCPCapture.h \
        TCPTrack.h SocketPair4.h \
        AppError.h PcapError.h GenericError.h

man_MANS = tcptrack.1

EXTRA_DIST = tcptrack.1
