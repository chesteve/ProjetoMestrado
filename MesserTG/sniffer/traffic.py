import pyshark
import sys
import os.path
import logging
import ProtocolConstants as header
import time

DEBUG_PacketInfo = False
verbose = True
# capture_method = "--live-test"
capture_method = "--live"
internetIf = 'enp3s0'


# internetIf='wlan0'


# file_name = '/home/anderson/ProjetoMestrado/Pcap/tese/lan_diurnalFirewallCapture.pcap'
# filebasename = os.path.basename(file_name)
# file_log_name = 'fileCapture_' + filebasename + '.log'
# logging.basicConfig(filename=file_log_name, format='[%(levelname)s] (%(threadName)-10s) %(message)s',level=logging.INFO)



class Print:
    def printf(format, *args):
        sys.stdout.write(format % args)


class PacketInfo:
    def __init__(self, pkt, reference_time=0):
        self.flowID = 0
        actual_time = float(pkt.sniff_timestamp) - float(reference_time)
        self.time = actual_time
        self.number = pkt.number
        self.length = pkt.captured_length
        self.prot_link = ''
        self.mac_src = pkt.eth.src
        self.mac_dst = pkt.eth.dst
        # init members
        self.prot_network = header.ETHERTYPE_NONE
        self.ip_dst = ''
        self.ip_src = ''
        self.transport = 0
        self.port_src = 0
        self.port_dst = 0
        self.ttl = 0
        try:
            self.prot_network = int(pkt.eth.type, 16)
            self.prot_link = 'ether'
            try:
                # IPv4 packet
                if self.prot_network == header.ETHERTYPE_IP:
                    self.ip_src = pkt.ip.src
                    self.ip_dst = pkt.ip.dst
                    self.ttl = pkt.ip.ttl
                    self.transport = int(pkt.ip.proto)
                    # tranport layer
                    if self.transport == header.PROTOCOL_TCP:
                        self.port_dst = pkt.tcp.dstport
                        self.port_src = pkt.tcp.srcport
                    elif self.transport == header.PROTOCOL_UDP:
                        self.port_dst = pkt.udp.dstport
                        self.port_src = pkt.udp.srcport
                    else:  # new modification
                        pass
                        # elif self.transport == PROTOCOL_ICMP:
                        #     pass
                        # elif self.transport == PROTOCOL_DCCP:
                        #     self.port_dst = pkt.dccp.dstport
                        #     self.port_src = pkt.dccp.srcport
                        # elif self.transport == PROTOCOL_SCTP:
                        #     self.port_dst = pkt.sctp.dstport
                        #     self.port_src = pkt.sctp.srcport
                        # elif self.transport == PROTOCOL_HOPOPT:
                        #     pass
                        # elif (self.transport <= PROTOCOL_ROHC) | (
                        #                 PROTOCOL_RESERVED_FOR_TESTING1 <=
                        #                self.transport <= PROTOCOL_RESERVED_FOR_EXTRA):
                        #     self.port_dst = 0
                        #     self.port_src = 0
                        # else:  # Error
                        #     print(dir(pkt), pkt)
                        #     print(dir(pkt.ip), pkt.ip)
                        #     self.print_error_message(
                        #         "[" + str(str(self.number)) + "] " + "An strange tranport protocol number was captured : ",
                        #         self.transport)
                # IPv6 packet
                elif self.prot_network == header.ETHERTYPE_IPV6:
                    # print(dir( pkt.ipv6))
                    self.ip_src = pkt.ipv6.addr
                    self.ip_dst = pkt.ipv6.dst
                    self.transport = int(pkt.ipv6.nxt)
                    self.ttl = int(pkt.ipv6.hlim)

                    # tranport layer
                    if self.transport == header.PROTOCOL_TCP:
                        self.port_dst = pkt.tcp.dstport
                        self.port_src = pkt.tcp.srcport
                    elif self.transport == header.PROTOCOL_UDP:
                        self.port_dst = pkt.udp.dstport
                        self.port_src = pkt.udp.srcport
                    else:
                        pass
                        # elif self.transport == PROTOCOL_Ipv6_ICMP:
                        #    self.port_dst = 0
                        #    self.port_src = 0
                        # elif self.transport == PROTOCOL_DCCP:
                        #    self.port_dst = pkt.dccp.dstport
                        #    self.port_src = pkt.dccp.srcport
                        # elif self.transport == PROTOCOL_SCTP:
                        #    self.port_dst = pkt.sctp.dstport
                        #    self.port_src = pkt.sctp.srcport
                        # elif self.transport == PROTOCOL_HOPOPT:
                        #    pass
                        # elif (self.transport <= PROTOCOL_ROHC) | (
                        #                PROTOCOL_RESERVED_FOR_TESTING1 <= self.transport <= PROTOCOL_RESERVED_FOR_EXTRA):
                        #    pass
                        # else:
                        #    print(dir(pkt), pkt)
                        #    print(dir(pkt.ip), pkt.ip)
                        #    self.print_error_message(
                        #        "[" + str(str(self.number)) + "] " + "An strange tranport protocol number was captured : ",
                        #        self.transport)
                # Other protocols, like ARP and REVARP
                else:
                    pass
            except (AttributeError, TypeError)  as detail:
                logging.error("[%s] Invalid packet attribute: %s \n %s\n\n", str(self.number), detail, str(pkt))

        except (AttributeError, TypeError)  as detail:
            # Spanning tree packet
            if ('stp' in dir(pkt)):
                self.prot_link = 'stp'
            else:
                logging.error("[%s] Invalid packet attribute: %s \n %s\n\n", str(self.number), detail, str(pkt))

    def __repr__(self):
        return ('(numb:' + str(self.number) + ' time:' + str(self.time) + ' length:' + str(
            self.length) + ' flowID:' + str(
            self.flowID) + ' prot_link:' + self.prot_link + ' mac_src:' + self.mac_src + ' mac_dst:' + self.mac_dst + ' prot_network:' + str(
            self.prot_network) + ' ip_src:' + self.ip_src + ' ip_dst:' + self.ip_dst + ' ttl:' + str(
            self.ttl) + ' transport:' + str(
            self.transport) + ' port_src:' + str(self.port_src) + ' port_dst:' + str(self.port_dst) + ')')

    def print_error_message(text_message, data_val):
        logging.error("%s %s", text_message, str(data_val))

    def flow_str(self):
        return (
            self.prot_link + str(self.prot_network) + self.ip_src + self.ip_dst + str(self.transport) + str(
                self.port_src) + str(
                self.port_dst))

    def setFlowId(self, fid=0):
        self.flowID = fid


class Trace:
    def __init__(self, traceName="trace-name", commentaries="no-comment"):
        self.captureDate = time.strftime("%H:%M:%S") + ", " + time.strftime("%d/%m/%Y")
        self.traceName = traceName
        self.commentaries = commentaries

class Flow:
    def __init__(self, flowId=0, protocolLink="", protocolNet=header.ETHERTYPE_NONE, protocolTransport=0, macSrc="", macDst="",
                 netSrc="" , netDst="", portSrc=0, portDst=0):
        self.flowId = flowId
        self.protocolLink = protocolLink
        self.protocolNet = protocolNet
        self.protocolTransport = protocolTransport
        self.macSrc = macSrc
        self.macDst = macDst
        self.netSrc = netSrc
        self.netDst = netDst
        self.portSrc = portSrc
        self.portDst = portDst

class Packet:
    def __init__(self,seq=0, arrivalTime=0, pktSize=0, ttl=0, winSize=0):
        self.seq = seq
        self.arrivalTime = arrivalTime
        self.pktSize = pktSize
        self.ttl = ttl
        self.winSize = winSize


if DEBUG_PacketInfo == True:
    internetIf = 'enp3s0'
    pcap_buffer = []
    capture = pyshark.LiveCapture(interface=internetIf)
    capture.sniff(timeout=0)

    # print(capture.sniff_timestamp)
    i = 0
    for pkt in capture.sniff_continuously():
        # Evaluate initial time
        if (i == 0):
            initial_time = pkt.sniff_timestamp

        pktInfo = PacketInfo(pkt, initial_time)
        print(pktInfo)
