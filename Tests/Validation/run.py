#!/usr/bin/python3.5
import argparse
import os
import sys
import time
from config import config
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/..')

import GnuplotScripts.GnuplotScripts as gps
import Cd.Cd as dir

# PCAP_FILE1 = "../../Pcap/wireshark-wiki_http.pcap"
# PCAP_FILE2 = "../../Pcap/wireshark-wiki_ospf.pcap"
# TEST_NAME = "lemur"


#def main(args):
def main(replot):
    pcap1 = config.pcap1
    pcap2 = config.pcap2
    pcap_name1 = config.pcap1_type
    pcap_name2 = config.pcap2_type
    analyzis_name = config.analysis_name
    # input arguments
    pcap_file1 = os.path.dirname(os.path.abspath(__file__)) + '/' + pcap1
    pcap_file2 = os.path.dirname(os.path.abspath(__file__)) + '/' + pcap2
    plots_dir = 'plots/' + analyzis_name
    # making sure the program is being executed in the source location, so it can be executed from anyware
    cd = dir.Cd(os.path.dirname(os.path.abspath(__file__)))
    if replot == False:
        run_analyzis(pcap_file1=pcap_file1, pcap_name1=pcap_name1, pcap_file2=pcap_file2, pcap_name2=pcap_name2,
            pktfilter_prefix=config.pktfilter_prefix, analyzis_name=analyzis_name, plots_dir=plots_dir, cd=cd, comments=config.comments)
    plot_data(config.pcap1_type, config.pcap2_type, analyzis_name, plots_dir)

def validation_help():
    print('To execute run:')
    print('    ./run.py          : run the calculations and plot the data')
    print('    ./run.py --replot : replot the data')
    print('To configure edite the file config.py')

def print_header(title):
    print('')
    print('###############################################################################')
    print('# ' + title)
    print('###############################################################################')


def run_analyzis(pcap_file1, pcap_name1, pcap_file2, pcap_name2, pktfilter_prefix, analyzis_name, plots_dir, cd, comments):
    # print info
    print_header("Analysis " + analyzis_name + " using pcaps: " + pcap_file1 + ' and ' + pcap_file2)
    print('> pcap_file1: ' + pcap_file1 )
    print('> pcap_name1: ' + pcap_name1)
    print('> pcap_file2: ' + pcap_file2)
    print('> pcap_name1: ' + pcap_name2)
    # go to script analysis dir
    cd.cd('./scripts/')
    # clean sim dir
    os.system('mkdir -p ./data')
    os.system('rm -rf data/*')
    # filter packet data
    print_header('Filtering data from pcap ' + pcap_file1)
    os.system('./analysis-pkt-filter.py ' + pcap_name1 + " " + pcap_file1)
    print_header('Filter inter-pacekt data from pcap ' + pcap_file2)
    os.system('./analysis-pkt-filter.py ' +  pcap_name2 + " "  + pcap_file2)
    datafile1 =  pktfilter_prefix + pcap_name1 + ".csv"
    datafile2 =  pktfilter_prefix + pcap_name2 + ".csv"
    print('> (datafile1, datafile2) = ', datafile1, datafile2)
    # run analyzis
    os.system('./analysis-waveletMra.m ' + datafile1 + ' ' + datafile2 + ' ' + analyzis_name)
    os.system('./analysis-hustExponent.m  ' + datafile1 + ' ' + datafile2)
    os.system('./analysis-bandwidth.m ' + datafile1 + ' ' + datafile2 + ' "1" "10^6"')
    os.system('./analysis-flow.m ' + datafile1 + ' ' + datafile2 + ' "1"')
    os.system('./analysis-pcapinfo.sh ' + pcap_file1 + ' ' + pcap_file2)
    # back to root dir
    cd.back()
    # creating plots dir
    os.system('rm -rf ' + plots_dir)
    os.system('mkdir -p ' + plots_dir)
    os.system('mv scripts/data/* ' + plots_dir)
    str_about = 'Analysis:' + analyzis_name + " using pcaps " + pcap_file1 + ' and ' + pcap_file2 + ' '
    str_date = '@ ' + str(time.localtime().tm_mday) + '/' + str(time.localtime().tm_mon) + '/' + str(
        time.localtime().tm_year) + '-' + str(time.localtime().tm_hour) + ':' + str(
        time.localtime().tm_min) + ':' + str(time.localtime().tm_sec)
    os.system('echo \"' + str_about + '\" >>' + plots_dir + '/about.log')
    os.system('echo \"' + str_date + '\" >>' + plots_dir + '/about.log')
    os.system('echo \"' + 'comments: ' + comments + '\" >>' + plots_dir + '/about.log')


def plot_data(trace_name1, trace_name2, analyzis_name, plots_dir):
    font_config = 'Helvetica,15'
    print_header("Plots for:" + analyzis_name + " using traces " + trace_name1 + ' and ' + trace_name2)
    gp = gps.GnuplotScripts(data_dir=plots_dir, plot_dir=plots_dir, font=font_config, linestyle_1='b+',
                            linestyle_2='rx',
                            linestyle_3='g-', linestyle_4='v-', type='linespoints', line_width=2)

    print('Ploting Wavelet Multiresolution Analisis')
    gp.plot_config(xlabel='Time scale j', ylabel='log2(Energy(j))', legend1=trace_name1, legend2=trace_name2,
                   type='linespoints', title=' Wavelet Multiresolution Analisis')
    gp.plot_2functionxyxy(datafile='WaveletMREA.dat', filename='WaveletMREA')

    print('Ploting Bandwidth')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Mbps', legend1=trace_name1, legend2=trace_name2, type='lines',
                   linestyle_1='b-', linestyle_2='r-', title='Bandwidth')
    gp.plot_2function(datafile='Bandwidth.dat', filename='Bandwidth')

    print('Ploting Flow data (FlowPs and FlowCDF)')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Number of Flows', legend1=trace_name1, legend2=trace_name2,
                   type='lines', linestyle_1='b-', linestyle_2='r-', title='Flows per second')
    gp.plot_2function(datafile='FlowsPs.dat', filename='FlowsPs')
    gp.plot_config(xlabel='Time(seconds)', ylabel='Flows CDF', legend1=trace_name1, legend2=trace_name2,
                   type='lines', linestyle_1='b-', linestyle_2='r-', title='Flows CDF distributions')
    gp.plot_2function(datafile='FlowCdf.dat', filename='FlowCdf')


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--replot', dest='replot', action='store_true')
    args = parser.parse_args()
    # if (len(sys.argv) == 1) or (len(sys.argv) == 2):
    #    validation_help()
    # else:
    #    main(sys.argv[1:])
    main(args.replot)


